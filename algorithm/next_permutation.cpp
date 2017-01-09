#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
bool MyNextPermutation(vector<int>::iterator begin, vector<int>::iterator end) {
  if (begin == end) return false;
  vector<int>::iterator i = end;
  if (begin == --i) return false;

  vector<int>::iterator i1 = i;
  while (*--i >= *i1) {
    if (i == begin) {
      std::reverse(begin, end);
      return false;
    }
    i1 = i;
  }
  vector<int>::iterator i2 = end;
  while (*i >= *--i2)
    ;
  std::iter_swap(i, i2);
  std::reverse(i1, end);
  return true;
}

int main(int argc, char *argv[]) {
  vector<int> arr{1, 2, 2, 4};
  do {
    std::copy(arr.begin(), arr.end(),
              std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\n";
  } while (MyNextPermutation(std::begin(arr), std::end(arr)));
  //} while (next_permutation(std::begin(arr), std::end(arr)));

  vector<int> arr1{1, 2, 2, 4, 5, 6};
  vector<int> arr2 = arr1;
  while (true) {
    auto r1 = MyNextPermutation(std::begin(arr1), std::end(arr1));
    auto r2 = std::next_permutation(std::begin(arr2), std::end(arr2));
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
