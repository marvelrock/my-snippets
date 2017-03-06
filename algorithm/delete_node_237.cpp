// https://leetcode.com/problems/delete-node-in-a-linked-list/
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
 public:
  void deleteNode(ListNode* node) {
    ListNode* next = node->next;
    node->val = next->val;
    node->next = next->next;
  }
};

int main(int argc, const char* argv[]) {
  ListNode* head = new ListNode(2);
  ListNode* next = new ListNode(3);
  head->next = next;
  head->next->next = new ListNode(1);

  Solution s;
  s.deleteNode(next);
  ListNode* p = head;
  while (p) {
    std::cout << p->val << " ";
    p = p->next;
  }
  std::cout << std::endl;

  return 0;
}
