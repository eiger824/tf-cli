/*
 * API specification at: http://www.opencontrail.org/documentation/api/r3.2/contrail_openapi.html
 * In this file only two example have been given:
 *
 * 1.) Listing a specific virtual network
 * 2.) Listing all virtual networks
 *
 * */
#include <iostream>
#include <string>

#include <libgen.h>
#include <getopt.h>

#include "common.hh"
#include "cmd.hh"
#include "url.hh"

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
    root_infra.getChild("dashboard").addChild("alarms");

    root_infra.addChild("control-nodes");
    root_infra.getChild("control-nodes").addChild("show");

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
    root_sec.addChild("dashboard");
    root_sec.addChild("traffic-groups");
    root_sec.addChild("help");
    /************************************************************************/
    /*************** Networking : populate commands *************************/
    /************************************************************************/
    root_netw.addChild("dashboard");
    root_netw.getChild("dashboard").addChild("networks");
    root_netw.getChild("dashboard").addChild("instances");
    root_netw.getChild("dashboard").addChild("interfaces");
    root_netw.getChild("dashboard").addChild("port-distribution");

    root_netw.addChild("projects");

    root_netw.addChild("networks");
    root_netw.getChild("networks").addChild("show");

    root_netw.addChild("instances");
    root_netw.getChild("instances").addChild("show");

    root_netw.addChild("interfaces");
    root_netw.getChild("interfaces").addChild("show");

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
    vector<string> cmdline;
    for (int i = optindx; i < argc; ++i)
        cmdline.push_back(string{argv[i]});

    string cmd = cmdline[0];
    int TODO;
    if (cmd == "infrastructure")
    {
        //TODO: implement
        TODO=1;

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
        string subcmd{};
        string netw_uuid{};

        if (cmdline.size() == 3)
        {
            subcmd = cmdline[1];
            if (subcmd == "show")
            {
                netw_uuid = cmdline[2];
                if (netw_uuid == "all")
                    curl_GET( "http://192.168.101.50:8082/virtual-networks" );
                else
                // Example on how to get virtual network details of VN with UUID c5228c98-8707-4f23-a6fa-a7787c17c374
                    curl_GET("http://192.168.101.50:8082/virtual-network/" + netw_uuid );
            }
            else
            {
                cout << "For demo-purposes, just enter the following command:\n\n\n"
                    << "tf-monitor networking show c5228c98-8707-4f23-a6fa-a7787c17c374 | jq" << endl
                    << endl << "or" << endl
                    << "tf-monitor networking show all | jq" << endl;
                return 0;
            }
        }
        else
        {
            cout << "For demo-purposes, just enter the following command:\n\n\n"
                << "tf-monitor networking show c5228c98-8707-4f23-a6fa-a7787c17c374 | jq" << endl
                << endl << "or" << endl
                << "tf-monitor networking show all | jq" << endl;
            return 0;
        }
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

