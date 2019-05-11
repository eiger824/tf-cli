#include <iostream>
#include <string>

#include <libgen.h>
#include <getopt.h>

#include <curl/curl.h>

#include "common.hh"
#include "cmd.hh"

#define     PROGRAM     "tf-monitor" 

using namespace std;

// Add main commands (roots)
static tf_node root_infra{"infrastructure"};
static tf_node root_sec{"security"};
static tf_node root_netw{"networking"};
static tf_node root_dbg{"debug"};

static void populate_cmd_tree()
{
    /************************************************************************/
    /*************** Infrastructure: populate commands **********************/
    /************************************************************************/
    root_infra.addChild("dashboard");
    root_infra.getChild("dashboard").addChild("system-info");
    root_infra.getChild("dashboard").addChild("logs");

    root_infra.addChild("control-nodes");
    root_infra.getChild("control-nodes").addChild("foo");
    root_infra.getChild("control-nodes").addChild("bar");

    root_infra.addChild("virtual-routers");
    root_infra.getChild("virtual-routers").addChild("routes");
    root_infra.getChild("virtual-routers").addChild("flows");
    root_infra.getChild("virtual-routers").addChild("vrfs");
    root_infra.getChild("virtual-routers").addChild("interfaces");
    root_infra.addChild("analytics-nodes");
    root_infra.addChild("config-nodes");
    root_infra.addChild("database-nodes");
    root_infra.addChild("help");
    /************************************************************************/
    /*************** Security: populate commands ****************************/
    /************************************************************************/
    root_sec.addChild("help");
    /************************************************************************/
    /*************** Networking : populate commands *************************/
    /************************************************************************/
    root_netw.addChild("networks");
    root_netw.addChild("instances");
    root_netw.addChild("ports");
    root_netw.addChild("asdfas");
    root_netw.addChild("asdfas");
    root_netw.addChild("asdfas");
    root_netw.addChild("asdfas");
    root_netw.addChild("help");
    /************************************************************************/
    /*************** Debug: populate commands *******************************/
    /************************************************************************/
    root_dbg.addChild("help");
}

void usage_general(char* program)
{
    cout <<
        "Usage: " << basename(program) << " [OPTIONS] COMMAND {SUBCOMMAND | help}\n"
        ", where OPTIONS:\n"
        "           -h      Show general information\n"
        "           -v      Be verbose\n"
        ", where COMMAND:\n"
        "           infrastructure\n"
        "           security\n"
        "           networking\n"
        "           debug\n\n"
        "Whole COMMAND/SUBCOMMAND hierarchy:\n"
        ;
    root_infra.printTree();
    root_sec.printTree();
    root_netw.printTree();
    root_dbg.printTree();
}

void usage_infra(char* program)
{
    cout <<
        "USAGE: " << basename(program) << " infrastructure SUBCOMAND ARGS...\n"
        ", where SUBCOMMAND:\n"
        "           dashboard\n"
        "           control-nodes\n"
        "           virtual-routers\n"
        "           analytics-nodes\n"
        "           config-nodes\n"
        "           database-nodes\n"
        "           help\n"
        ;
}
void usage_netw(char* program)
{
    cout <<
        "USAGE: " << basename(program) << " networking SUBCOMAND ARGS...\n"
        ", where SUBCOMMAND:\n"
        "           virtual-networks\n"
        "           instances\n"
        "           etc\n"
        ;
}

int process_cmdline(int argc, char** argv, int optindx)
{
    // Depending on which command that was passed, a specific
    // subcommand list needs to be fetched
    // First command should be on argv[optindx]
    string cmd{argv[optindx]};
    int TODO;
    if (cmd == "infrastructure")
    {
        //TODO: implement
        TODO=1;

        // Curl-related (please move to another file asap...)
        CURL* curl;
        CURLcode res;

        curl_global_init(CURL_GLOBAL_DEFAULT);
        curl = curl_easy_init();
        if (curl)
        {
            curl_easy_setopt(curl, CURLOPT_URL, "santi.lmera.ericsson.se:5050/some/path/of/the/rest/api/specification");
            // Don't verify CAcert or host
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
            curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
            res = curl_easy_perform(curl);
            if (res != CURLE_OK)
                err("curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            // Cleanup
            curl_easy_cleanup(curl);
        }
        curl_global_cleanup();
    }
    else if (cmd == "security")
    {
        //TODO: implement
        TODO=1;
    }
    else if (cmd == "networking")
    {
        //TODO: implement
        TODO=1;
    }
    else if (cmd == "debug")
    {
        //TODO: implement
        TODO=1;
    }
    else
    {
        err("Wrong command `%s'\n", cmd.c_str());
        usage_general((char*)PROGRAM);
        return 1;
    }

    return 0;
}

int main(int argc, char* argv[])
{
    int c;

    populate_cmd_tree();

    // Parse OPTIONS
    while ((c = getopt(argc, argv, "hv")) != EOF)
    {
        switch (c)
        {
            case 'h':
                usage_general((char*)PROGRAM);
                exit(0);
            case 'v':
                root_infra.setVerbose(true);
                root_sec  .setVerbose(true);
                root_netw .setVerbose(true);
                root_dbg  .setVerbose(true);
                break;
            default:
                usage_general((char*)PROGRAM);
                exit(1);
        }
    }
    if (argc - optind < 2)
    {
        cerr << "Not enough input arguments\n";
        usage_general((char*)PROGRAM);
        exit(1);
    }

    return process_cmdline(argc, argv, optind);
}

