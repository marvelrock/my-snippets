// https://leetcode.com/problems/house-robber/
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>

using std::vector;

// recursive
class Solution {
 public:
  int rob(vector<int>& nums) {
    cache_.resize(nums.size());
    std::fill(std::begin(cache_), std::end(cache_), -1);
    int rob_from_first = robFrom(0, nums);
    int rob_from_second = robFrom(1, nums);
    return rob_from_first > rob_from_second ? rob_from_first : rob_from_second;
  }

 private:
  int robFrom(size_t index, vector<int>& nums) {
    if (index >= nums.size()) return 0;
    if (cache_[index] != -1) return cache_[index];
    int rob_from_2th = 0, rob_from_3th = 0;
    if (index < nums.size()) {
      rob_from_2th += nums[index] + robFrom(index + 2, nums);
      rob_from_3th += nums[index] + robFrom(index + 3, nums);
    }

    int max_value = rob_from_2th > rob_from_3th ? rob_from_2th : rob_from_3th;
    cache_[index] = max_value;
    return max_value;
  }

 private:
  vector<int> cache_;
};

class Solution2 {
 public:
  int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    auto i = nums.size() - 1;
    while (true) {
      auto after_2th = i + 2;
      auto after_3th = i + 3;
      if (after_2th < nums.size()) {
        auto max_value = nums[after_2th];
        if (after_3th < nums.size() && nums[after_3th] > max_value)
          max_value = nums[after_3th];
        nums[i] += max_value;
      }
      if (i == 0) break;
      --i;
    }
    return nums[0] > nums[1] ? nums[0] : nums[1];
  }
};

int main(int argc, const char* argv[]) {
  Solution s;
  Solution2 s2;

  vector<int> house(10, 0);
  for (int i = 0; i < 10; ++i) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(0, 20);
    for (auto& v : house) v = dis(gen);

    std::copy(std::begin(house), std::end(house),
              std::ostream_iterator<int>(std::cout, " "));

    std::cout << "max rob solution is " << s.rob(house) << " solution2 is "
              << s2.rob(house) << "\n";
  }
  return 0;
}
