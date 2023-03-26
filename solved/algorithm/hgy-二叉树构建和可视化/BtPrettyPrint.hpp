#ifndef __BtPrettyPrint__
#define __BtPrettyPrint__

#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

namespace BtPrettyPrint {

template <typename DataType>
class TreeNode {

public:
    DataType data;
    TreeNode* left;
    TreeNode* right;

    /*
    *  d : DataType item representing the node's data
    *  l : pointer to node's left child
    *  r : pointer to node's right child
    */
    TreeNode(DataType d, TreeNode* l = nullptr, TreeNode* r = nullptr)
            : data(d), left(l), right(r) {}

    virtual std::string dataToString() = 0;
    virtual bool isNull() = 0;
};

template <typename DataType, typename TN = TreeNode<DataType>>
std::vector<TN*> inorderTraversal(TN* root) {
    std::vector<TN*> res;
    std::stack<TN*> stk;
    while (root != nullptr || !stk.empty()) {
        while (root != nullptr) {
            stk.push(root);
            root = root->left;
        }
        root = stk.top();
        stk.pop();
        res.push_back(root);
        root = root->right;
    }
    return res;
}

template <typename DataType, typename TN = TreeNode<DataType>>
void prettyPrintTree(TN* root) {
    if (root == nullptr)  return;

    auto tmp = root;
    std::vector<TN*> intv = inorderTraversal<DataType>(tmp);

    // 1. 储存中序遍历的节点的最终的打印位置，很巧妙，无论节点数据多长，都是 “好看” 的二叉树
    std::string template_str;
    std::unordered_map<TN*, int> first_locations;
    for (auto&& e : intv) {
        first_locations[e] = template_str.size();
        template_str += (e->dataToString() + "  ");
    }

    // 2. 把模板全部置为空格方便后续使用
    for (auto& e : template_str)    e = ' ';  

    // 3. 层序遍历
    std::queue<TN*> q;
    q.push(root);
    while (!q.empty()) {
        int cur_level_size = q.size();
        // 清空将要写的两行
        std::string line1 = template_str, line2 = template_str;

        for (int i = 1; i <= cur_level_size; ++i) {
            auto node = q.front();
            q.pop();
            auto cur_loc = first_locations[node];
            std::string cur_str = node->dataToString();
            
            // 1. 左边，如果存在左孩子，那么在第二行对应位置打印 '/'，在第一行补上'_'
            if (node->left) {
                q.push(node->left);
                auto str = node->left->dataToString();
                auto mid_loc = first_locations[node->left] + str.size() / 2;
                line2[mid_loc++] = '/';
                while (mid_loc < cur_loc)   line1[mid_loc++] = '_';
            }

            // 2. 中间，对应位置打印节点值（有可能为多位数）
            for (int j = 0; j < cur_str.size(); ++j, ++cur_loc) {
                line1[cur_loc] = cur_str[j];
            }

            // 3. 右边，如果存在右孩子，那么在第二行对应位置打印'\'，在第一行补上'_'
            if (node->right) {
                q.push(node->right);
                auto str = node->right->dataToString();
                int mid_loc = first_locations[node->right] + str.size() / 2;
                line2[mid_loc] = '\\';
                while (cur_loc < mid_loc)   line1[cur_loc++] = '_';
            }
        }

        //打印两行
        std::cout << line1 << std::endl;
        std::cout << line2 << std::endl;
    }
}

// 层级构建二叉树：从数据构建二叉树
template <typename DataType, typename DerivedTN, typename TN = TreeNode<DataType>>
TN* LevelBuild(std::vector<DataType>& nums)
{
    static_assert(std::is_base_of<TN, DerivedTN>::value, "virtual class TreeNode should be implemented!");

    if(nums.empty())    return nullptr;

    int n = nums.size();
    TN* root = new DerivedTN(nums.front());
    std::queue<TN*> q;
    q.push(root);
    int next = 0;

    while(!q.empty()){
        for(int i=0; i<q.size(); i++)
        {
            // 1. deal with left
            auto& top = q.front();
            if(++next < n){
                auto tmp = new DerivedTN(nums[next]);
                if(!tmp->isNull()){
                    top->left = tmp;
                    q.push(top->left);
                }
            }
            
            // 2. deal with right
            if(++next < n){
                auto tmp = new DerivedTN(nums[next]);
                if(!tmp->isNull()){
                    top->right = tmp;
                    q.push(top->right);
                }    
            }

            q.pop();
        }
    }
    return root;
}

}   // namespace BtPrettyPrint


#endif /* defined(__BtPrettyPrint__) */