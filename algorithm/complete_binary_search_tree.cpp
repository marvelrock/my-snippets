#include <cmath>

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using std::vector;
using std::queue;

struct RangeIndex {
  int index;
  int size;
  RangeIndex(int i, int s) : index(i), size(s) {}
};

int FindRoot(int index, int size) {
  if (size <= 0) return -1;
  int complete_bst_depth = static_cast<int>(std::log2(size + 1));
  int complete_last_level_leaves = 1 << complete_bst_depth;
  int last_level_leaves = size - ((1 << complete_bst_depth) - 1);
  int left_last_level_leaves =
      std::min(last_level_leaves, complete_last_level_leaves / 2);
  int root_index = (size - last_level_leaves) / 2 + left_last_level_leaves;
  return index + root_index;
}

vector<int> ConstructCompleteBST(const vector<int>& arr) {
  if (arr.size() <= 1) return arr;
  queue<RangeIndex> range_queue;
  range_queue.push(RangeIndex(0, static_cast<int>(arr.size())));

  vector<int> result;
  while (range_queue.size()) {
    RangeIndex range_index = range_queue.front();
    range_queue.pop();
    int root_index = FindRoot(range_index.index, range_index.size);
    if (root_index == -1) {
      std::cout << "fatal error, index = " << range_index.index
                << " size = " << range_index.size << "\n";
      break;
    }

    result.push_back(arr[static_cast<size_t>(root_index)]);

    if (range_index.index < root_index)
      range_queue.push(
          RangeIndex(range_index.index, root_index - range_index.index));
    if (root_index + 1 < range_index.index + range_index.size)
      range_queue.push(
          RangeIndex(root_index + 1,
                     range_index.size + range_index.index - root_index - 1));
  }
  return result;
}

int main(int argc, char* argv[]) {
  vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  vector<int> result = ConstructCompleteBST(arr);
  std::copy(result.begin(), result.end(),
            std::ostream_iterator<int>(std::cout, " "));

  return 0;
}
