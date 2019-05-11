#include <iostream>
#include <cassert>
#include "cmd.hh"

using std::cout;
using std::endl;

int main(int argc, char* argv[])
{
    // add roots
    tf_node infra{"infrastructure"};

    //populate networking and children
    infra.addChild("dashboard");
    infra.addChild("control-nodes");
    infra.addChild("virtual-routers");
    infra.addChild("analytics-nodes");
    infra.addChild("config-nodes");
    infra.addChild("database-nodes");
    infra.addChild("help");

    // Populate level 2
    infra.getChild("dashboard").addChild("foo");
    infra.getChild("dashboard").addChild("bar");
    infra.getChild("dashboard").addChild("help");

    //Populate level 3, etc ,etc
    infra.getChild("dashboard").getChild("foo").addChild("wild");
    infra.getChild("dashboard").getChild("foo").addChild("card");

    // Let's print networking!
    infra.printTree();

    return 0;
}
