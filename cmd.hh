#ifndef COMMON_H_
#define COMMON_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class tf_node {
    public:
        tf_node(string const& name, bool _verbose = false);
        tf_node(const tf_node& rhs) = default;
        ~tf_node(){};

        void addChild(string const& child);
        inline const string& getName() const { return name;};
        size_t getChildNr();
        void printTree();
        friend std::ostream& operator<< (std::ostream& os, const tf_node& n);
        tf_node& getChild(string const& name);
        void setVerbose(bool _verbose);

    private:
        string name;
        vector<tf_node> children;
        bool verbose;
};

#endif /* COMMON_H_ */
