#include <algorithm>
#include <iostream>
#include <vector>

bool MyPrevPermutation(std::vector<int>::iterator begin,
                       std::vector<int>::iterator end) {
  if (begin == end) return false;
  std::vector<int>::iterator i = end;
  if (begin == --i) return false;

  auto i1 = i;
  while (*--i <= *i1) {
    if (i == begin) {
      std::reverse(begin, end);
      return false;
    }
    i1 = i;
  }
  auto i2 = i1;
  auto i3 = i2;
  while (++i3 != end && *i > *i3) {
    i2 = i3;
  }
  std::iter_swap(i, i2);
  std::reverse(i1, end);
  return true;
}

int main(int argc, char *argv[]) {
  std::vector<int> arr{4, 2, 2, 1};
  do {
    std::copy(arr.begin(), arr.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
  } while (MyPrevPermutation(std::begin(arr), std::end(arr)));

  std::vector<int> arr1{6, 5, 4, 2, 2, 1};
  std::vector<int> arr2 = arr1;
  while (true) {
    auto r1 = MyPrevPermutation(std::begin(arr1), std::end(arr1));
    auto r2 = std::prev_permutation(std::begin(arr2), std::end(arr2));
    if (r1 == false && r2 == false) {
      std::cout << "my permutation is OK"
                << "\n";
      break;
    }
    if (arr1 != arr2) {
      std::copy(arr1.begin(), arr1.end(),
                std::ostream_iterator<int>(std::cout, " "));
      std::cout << "\n";
      std::copy(arr2.begin(), arr2.end(),
                std::ostream_iterator<int>(std::cout, " "));
      std::cout << "\n";
      std::cout << "my permutation is error"
                << "\n";
      break;
    }
  }

  return 0;
}
