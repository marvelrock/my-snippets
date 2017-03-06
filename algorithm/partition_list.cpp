// https://leetcode.com/problems/partition-list/
#include <iostream>

struct ListNode {
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(nullptr) {}
};

class Solution {
 public:
  ListNode* partition(ListNode* head, int x) {
    ListNode *left_head = nullptr, *left = nullptr;
    ListNode *right_head = nullptr, *right = nullptr;
    while (head) {
      ListNode **pphead = nullptr, **pp = nullptr;
      if (head->val < x) {
        pphead = &left_head;
        pp = &left;
      } else {
        pphead = &right_head;
        pp = &right;
      }
      if (*pphead == nullptr) {
        *pphead = head;
        *pp = head;
      } else {
        (*pp)->next = head;
        *pp = head;
      }
      // 这行必须在下一行前面
      head = head->next;
      (*pp)->next = nullptr;
    }
    if (left_head) {
      left->next = right_head;
      return left_head;
    }
    return right_head;
  }
};

int main(int argc, const char* argv[]) {
  ListNode* head = new ListNode(2);
  head->next = new ListNode(3);
  head->next->next = new ListNode(1);

  Solution s;
  ListNode* p = s.partition(head, 3);
  while (p) {
    std::cout << p->val << " ";
    p = p->next;
  }
  std::cout << std::endl;

  return 0;
}
