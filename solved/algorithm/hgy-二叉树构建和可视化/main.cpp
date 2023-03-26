#include <bits/stdc++.h>
#include "BtPrettyPrint.hpp"

using namespace BtPrettyPrint;

class IntTreeNode : public TreeNode<int>
{
public:
    using TreeNode<int>::TreeNode;

    virtual std::string dataToString() override
    {
        return std::to_string(this->data);
    }

    virtual bool isNull() override
    {
        return (this->data < 0);
    }
};

class StringTreeNode : public TreeNode<std::string>
{
public:
    using TreeNode<std::string>::TreeNode;

    virtual std::string dataToString() override {return this->data;}
    virtual bool isNull() override {return this->data == "null";}

    static std::vector<std::string> stringToVector(const std::string& s)
    {
        std::stringstream input(s);
        std::string item;
        std::vector<std::string> res;
        
        auto stripSpace = [](std::string& s){
            int l, r = s.size();
            while(l < s.size() && s[l] == ' ')  l++;
            while(r > l && s[r] == ' ') r--;
            s = s.substr(l, r - l + 1);
        };

        while(std::getline(input, item, ',')){
            stripSpace(item);
            res.emplace_back(item);
        }

        return res;
    }

};


int main(int, char**) {

    // test int
    {
        std::vector<int> nums{1, 234, 2, -1, 3213, 323, -1, 4564, 32, -2};
        TreeNode<int>* root = LevelBuild<int, IntTreeNode>(nums);
        prettyPrintTree<int>(root);
    }

    // test string
    {
        std::string str = "121, 234, 2, null, 313, null, null, 45, 322, null";
        auto nums = StringTreeNode::stringToVector(str);
        TreeNode<std::string>* root = LevelBuild<std::string, StringTreeNode>(nums);
        prettyPrintTree<std::string>(root);
    }


    return 0;
}
