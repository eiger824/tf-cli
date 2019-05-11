#include <iostream>
#include <stdexcept>
#include <iomanip>

#include "cmd.hh"

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

static int depthLevel{0};

tf_node::tf_node(string const& name, bool _verbose) : name(name), verbose(_verbose) {}

void tf_node::addChild(string const& child)
{
    tf_node c{child};
    children.push_back(c);
}

tf_node& tf_node::getChild(string const& child_name)
{
    // Loop through children to check whether "child_name" exists
    for (auto& c: children)
    {
        if (c.name == child_name) return c;
    }
    // raise an exception (child not found by that child_name)
    throw std::invalid_argument
        ("Non-existing child name `" + child_name + "' given for parent '" + name + "'");
}

size_t tf_node::getChildNr()
{
    return children.size();
}

void tf_node::printTree()
{
    // start off by the root node, a.k.a, this node
    cout << *this << endl;
    // loop through all my children and their children and etc etc etc
    if (children.size() > 0)
    {
        depthLevel++;
        for (auto & c: children)
        {
            cout << right << setw(8*depthLevel) << " ";
            c.printTree();
        }
        depthLevel--;
    }
}
void tf_node::setVerbose(bool _verbose)
{
    // Update this node
    verbose = _verbose;
    // And propagate verbosity across all child nodes
    for (auto& c: children)
    {
        c.setVerbose(_verbose);
    }
}

std::ostream& operator<< (std::ostream& os, const tf_node& n)
{
    os << left << setw(20) << n.name;
    if (n.verbose)
        os << " [" << n.children.size() << " children]";
    return os;
}

