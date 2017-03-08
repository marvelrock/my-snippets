// https://leetcode.com/problems/super-pow/

#include <cmath>
#include <iostream>
#include <vector>

class Solution {
 public:
  int superPow(int a, std::vector<int>& b) {
    int mod = 1337;
    int base = a % mod;
    int result = -1;
    while (b.size()) {
      int k = b[b.size() - 1];
      b.pop_back();
      int n = k == 0 ? 10 : k;
      int r = base;
      int base0 = base;
      for (int i = 2; i <= 10; ++i) {
        base = (base * base0) % mod;
        if (i == n) {
          r = base;
          if (b.size() == 0) break;
        }
      }
      if (k != 0) {
        if (result == -1)
          result = r;
        else
          result = (result * r) % mod;
      }
      if (result == 0) return 0;
    }
    if (result == -1) return 0;
    return result;
  }
};

int main(int argc, const char* argv[]) {
  Solution s;
  std::vector<int> b{1, 7, 7};
  std::vector<int> b0{7};
  std::vector<int> b1{7, 7};
  std::cout << s.superPow(78267, b0) << "\n";
  std::cout << s.superPow(78267, b1) << "\n";
  std::cout << s.superPow(78267, b) << "\n";
  std::vector<int> c{1, 0};
  std::cout << "2 ** 10 = " << s.superPow(2, c) << "\n";
  return 0;
}
