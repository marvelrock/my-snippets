#include <algorithm>
#include <iostream>
#include <vector>

void QuickSort(std::vector<int>& arr, size_t begin, size_t size) {
  if (size <= 1) return;

  size_t i = begin;
  size_t k = begin + size - 1;
  while (arr[i] < arr[k]) ++i;
  size_t j = i + 1;
  while (j < k) {
    if (arr[j] < arr[k]) {
      // print
      std::copy(std::begin(arr), std::end(arr),
                std::ostream_iterator<int>(std::cout, " "));
      std::cout << "\n";

      std::swap(arr[i], arr[j]);
      ++i;
    }
    ++j;
  }
  // print
  std::copy(std::begin(arr), std::end(arr),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";

  std::swap(arr[i], arr[k]);
  if (i > begin) QuickSort(arr, begin, i - begin);
  if (i + 1 < size + begin) QuickSort(arr, i + 1, begin + size - i - 1);
}

int main(int argc, const char* argv[]) {
  std::vector<int> arr{3, 4, 8, 7, 2, 9, 6, 1, 5};
  QuickSort(arr, 0, arr.size());
  std::copy(std::begin(arr), std::end(arr),
            std::ostream_iterator<int>(std::cout, " "));
  std::cout << "\n";
  return 0;
}
