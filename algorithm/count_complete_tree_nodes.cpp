// https://leetcode.com/problems/count-complete-tree-nodes/
#include <deque>
#include <iostream>

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
 public:
  // deep first search
  int countNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    return 1 + countNodes(root->left) + countNodes(root->right);
  }
};

class Solution2 {
 public:
  // 从当前节点到最左端叶子节点的深度
  int GetLeftDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int max_depth = 0;
    while (root) {
      ++max_depth;
      root = root->left;
    }
    return max_depth;
  }
  // 从当前节点到最右端叶子节点的深度
  int GetRightDepth(TreeNode* root) {
    if (root == nullptr) return 0;
    int max_depth = 0;
    while (root) {
      ++max_depth;
      root = root->right;
    }
    return max_depth;
  }
  // binary search
  // clang-format off
  // 1) 如果完全二叉树是一个完美二叉树, 直接计算节点数, 否则, 再判断左右两个子树
  // 2) 如果左子树是完美二叉树, 说明右子树可能还存在完全二叉树最下面一层的叶子节点, 以右子树根节点作为下次循环的根
  // 3) 如果左子树不是完美二叉树, 说明右子树上不可能存在完全二叉树最下面一层的叶子节点, 以左子树作为下次循环的根
  // 4) 通过深度判断完美二叉树的叶子节点是否是完全二叉树的叶子节点, 如果是, 把这些叶子节点数进行累加
  // 5) 如果子树根节点不为 nullptr, 跳转到 1)
  // clang-format on
  int countNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    int max_depth = GetLeftDepth(root);
    // 以 root 为第一个左子树节点, 父节点数量为 0
    int parent_nodes = (1 << (max_depth - 1)) - 1;
    int left_leaves = 0;
    int current_depth = 1;  // root
    TreeNode* p = root;
    TreeNode* right = nullptr;
    while (p) {
      int left_depth = GetLeftDepth(p);
      int right_depth = GetRightDepth(p);
      if (left_depth == right_depth) {
        p = right;
        right = nullptr;
        if (left_depth - 1 + current_depth == max_depth) {
          left_leaves += 1 << (left_depth - 1);
        }
      } else {
        right = p->right;
        p = p->left;
        ++current_depth;  // 处理子树
      }
    }
    return parent_nodes + left_leaves;
  }
};

void ConstructCompleteTree(TreeNode** root, int size) {
  if (size <= 0) {
    *root = nullptr;
    return;
  }
  *root = new TreeNode(0);
  --size;
  std::deque<TreeNode*> node_deque;
  node_deque.push_back(*root);

  while (size > 0) {
    TreeNode* parent = node_deque[0];
    if (size-- > 0) {
      TreeNode* left = new TreeNode(0);
      parent->left = left;
      node_deque.push_back(left);
    }
    if (size-- > 0) {
      TreeNode* right = new TreeNode(0);
      parent->right = right;
      node_deque.push_back(right);
    }
    node_deque.pop_front();
  }
}

int main(int argc, const char* argv[]) {
  Solution s;
  Solution2 s2;
  for (int i = 0; i < 100; ++i) {
    TreeNode* root = nullptr;
    ConstructCompleteTree(&root, i);
    std::cout << "Solution Tree contains " << s.countNodes(root)
              << " nodes; Solution2 Tree contains " << s2.countNodes(root)
              << " nodes\n";
  }
  return 0;
}
