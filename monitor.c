#include <stdio.h>
#include <libgen.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

#define     PROGRAM     argv[0]

void print_arr(char** arr, const char* separator)
{
    if (!arr) return;
    char** ptr = arr;
    for (char* c = *ptr; c; c=*++ptr)
    {
        printf("%s%s\n", separator ? separator : "", c);
    }
}

static char* commands[] =
{
    "infrastructure",
    "networking",
    "foo",
    "someotherthing",
    NULL
};

static char* subcommands_infra[] =
{
    "subinfra01",
    "subinfra02",
    "subinfra03",
    NULL
};

static char* subcommands_netw[] =
{
    "subnet01",
    "subnet02",
    "subnet03",
    NULL
};

void usage_general(char* program)
{
    printf(
            "Usage: %s [OPTIONS] COMMAND {SUBCOMMAND | help}\n"
            ", where OPTIONS:\n"
            "           -h      Show general information\n"
            "           -v      Be verbose\n"
            ", where COMMAND:\n"
            , basename(program)
          );
    print_arr(commands, "           ");
}

void usage_infra(char* program)
{
    printf(
            "USAGE: %s infrastructure SUBCOMAND ARGS...\n"
            ", where SUBCOMMAND:\n"
            , basename(program)
          );
    print_arr(subcommands_infra, "          ");
}
void usage_netw(char* program)
{
    printf(
            "USAGE: %s networking SUBCOMAND ARGS...\n"
            ", where SUBCOMMAND:\n"
            , basename(program)
          );
    print_arr(subcommands_netw, "          ");
}

int check_cmd(char* cmd, char** cmds)
{
    char** ptr = cmds;
    for (char* c = *ptr; c; c=*++ptr)
    {
        if (!strcmp(c, cmd))
            return 0;
    }
    return 1;
}

int process_cmd(char* cmd, char** argv, int optindx)
{
    // Depending on which command that was passed, a specific
    // subcommand list needs to be fetched
    char** subcmds;
    char* subcmd;
    if (!strcmp(cmd, "infrastructure"))
        subcmds = subcommands_infra;
    else if (!strcmp(cmd, "networking"))
        subcmds = subcommands_netw;
    else
        subcmds = subcommands_netw;

    subcmd = argv[optindx];
    if (check_cmd(subcmd, subcmds) != 0)
    {
        fprintf(stderr, "Wrong subcommand \"%s\" for cmd `%s'\n", subcmd, cmd);
        if (!strcmp(cmd, "infrastructure"))
            usage_infra(PROGRAM);
        else if (!strcmp(cmd, "networking"))
            usage_netw(PROGRAM);
        else
            usage_general(PROGRAM);
        exit(2);
    }
    printf("Subcommand '%s' accepted\n", argv[optindx]);

    return 0;
}

int main(int argc, char* argv[])
{
    int c;
    char* cmd;

    // Parse OPTIONS
    while ((c = getopt(argc, argv, "h")) != EOF)
    {
        switch (c)
        {
            case 'h':
                usage_general(PROGRAM);
                exit(0);
            default:
                usage_general(PROGRAM);
                exit(1);
        }
    }
    if (argc - optind < 2)
    {
        fprintf(stderr, "Not enough input arguments\n");
        usage_general(PROGRAM);
        exit(1);
    }
    // At this point, argv[optind] should contain the COMMAND to use
    cmd = argv[optind];
    if (check_cmd(cmd, commands) != 0)
    {
        fprintf(stderr, "Wrong command \"%s\"\n", cmd);
        usage_general(PROGRAM);
        exit(1);
    }

    return process_cmd(cmd, argv, optind + 1);
}

