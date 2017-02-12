// https://leetcode.com/problems/house-robber-ii/
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using std::vector;

class Solution1 {
 public:
  int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    int max_value = nums[0];
    if (nums.size() > 1) {
      int temp = rob(nums, 0, nums.size() - 1);
      max_value = std::max(temp, max_value);
      temp = rob(nums, 1, nums.size());
      max_value = std::max(temp, max_value);
    }
    if (nums.size() > 2) {
      int temp = rob(nums, 0, nums.size() - 2);
      max_value = std::max(temp, max_value);
      temp = rob(nums, 1, nums.size() - 1);
      max_value = std::max(temp, max_value);
      temp = rob(nums, 2, nums.size());
      max_value = std::max(temp, max_value);
    }
    return max_value;
  }

 private:
  int rob(const vector<int>& nums, size_t lower_bound, size_t upper_bound) {
    int a = 0, b = 0;
    size_t index = lower_bound;
    while (index < upper_bound) {
      if ((index - lower_bound) % 2 == 0) {
        a = std::max(nums[index] + a, b);
      } else {
        b = std::max(nums[index] + b, a);
      }
      ++index;
    }
    return std::max(a, b);
  }
};

// todo(HuangTao)
class Solution2 {
 public:
  int rob(vector<int>& nums) { return 0; }
};

int main(int argc, const char* argv[]) {
  Solution1 s1;

  vector<int> house{5, 4, 8, 4, 20, 3, 12, 14, 20, 17};
  std::cout << "[fixed]max rob solution is " << s1.rob(house) << "\n";
  for (int i = 0; i < 10; ++i) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 20);
    for (auto& v : house) v = dis(gen);

    std::copy(std::begin(house), std::end(house),
              std::ostream_iterator<int>(std::cout, " "));

    std::cout << "max rob solution is " << s1.rob(house) << "\n";
  }
  return 0;
}
