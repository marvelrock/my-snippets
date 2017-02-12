// https://leetcode.com/problems/house-robber-iii/
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

// Definition for a binary tree node.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
class Solution {
 public:
  int rob(TreeNode *root) {
    auto pair_value = robInternal(root);
    return std::max(pair_value.first, pair_value.second);
  }

 private:
  std::pair<int, int> robInternal(TreeNode *root) {
    int a = 0, b = 0;
    if (root == nullptr) return std::make_pair(a, b);
    auto left_pair = std::make_pair(0, 0);
    if (root->left) left_pair = robInternal(root->left);
    auto right_pair = std::make_pair(0, 0);
    if (root->right) right_pair = robInternal(root->right);
    b = right_pair.first + left_pair.first;
    b = std::max(b, right_pair.first + left_pair.second);
    b = std::max(b, right_pair.second + left_pair.first);
    a = root->val + right_pair.second + left_pair.second;
    a = std::max(a, b);
    return std::make_pair(a, b);
  }

 public:
  // 使用先根遍历的方式构建树, 如果子节点为 null, nodes 值用 -1 表示
  void ConstructBinaryTree(const std::vector<int> &nodes, TreeNode **root) {
    if (nodes.size() == 0) return;
    std::stack<TreeNode *> tree;
    TreeNode *placenode = new TreeNode(0);
    TreeNode *node = nullptr;
    for (auto v : nodes) {
      TreeNode *child = nullptr;
      if (v == -1) {  // node 的子节点为 nullptr
        if (node->left == placenode)
          node->left = nullptr;
        else
          node->right = nullptr;
      } else {  // 创建新节点加到书中
        child = new TreeNode(v);
        child->left = placenode;
        child->right = placenode;
        if (*root == nullptr) {  // 根节点
          *root = child;
          node = child;  // 避免空指针
        } else {         // 非根节点, 以先根遍历的方式构建子树
          if (node->left == placenode)
            node->left = child;
          else
            node->right = child;
        }
      }
      // 当前节点的左右子树都被处理过了, 处理先根遍历中的下一个节点
      if (node->left != placenode && node->right != placenode) {
        tree.pop();
        // bugfix, 必须判定栈是否为空
        if (tree.size() > 0) node = tree.top();
      }

      if (child != nullptr) {  // 处理新创建的节点
        node = child;
        tree.push(child);
      }
    }
    delete placenode;
  }
};

int main(int argc, const char *argv[]) {
  Solution s1;
  {
    TreeNode *house = nullptr;
    std::vector<int> tree1 = {3, 2, -1, 3, -1, -1, 3, -1, 1, -1, -1};
    s1.ConstructBinaryTree(tree1, &house);
    std::cout << "max rob solution is " << s1.rob(house) << "\n";
  }
  {
    TreeNode *house = nullptr;
    std::vector<int> tree1 = {3, 4, 1, -1, -1, 3, -1, -1, 5, -1, 1, -1, -1};
    s1.ConstructBinaryTree(tree1, &house);
    std::cout << "max rob solution is " << s1.rob(house) << "\n";
  }
  {
    TreeNode *house = nullptr;
    std::vector<int> tree1 = {2, 3, 2, 3, -1, -1, -1, 5, -1, -1, 3, -1, -1};
    s1.ConstructBinaryTree(tree1, &house);
    std::cout << "max rob solution is " << s1.rob(house) << "\n";
  }
  return 0;
}
