// https://leetcode.com/problems/longest-absolute-file-path/

#include <cstdlib>

#include <iostream>
#include <stack>
#include <string>

using std::string;
using std::stack;

size_t GetLevel(const string& input, size_t& index) {
  size_t level = 0;
  while (index < input.length() && input[index] == '\t') {
    ++index;
    ++level;
  }
  return level;
}

std::pair<int, bool> GetEntryLengthAndType(const string& input, size_t& index) {
  std::pair<int, bool> result{0, false};
  int entry_length = 0;
  // index != '\n' causes dead loop
  while (index < input.length() && input[index] != '\n') {
    ++entry_length;
    if (input[index] == '.') result.second = true;
    ++index;
  }
  result.first = entry_length + (result.second ? 0 : 1);
  return result;
}

// no file exists in the filesystem, return 0
int lengthLongestPath(string input) {
  int longest_path = 0;
  int length_path = 0;
  size_t index = 0;
  std::stack<int> length_stack;
  while (index < input.length()) {
    size_t level = 0;
    if (input[index] == '\n') {
      level = GetLevel(input, ++index);
    }
    while (level < length_stack.size()) {
      length_path -= length_stack.top();
      length_stack.pop();
    }
    auto entry_pair = GetEntryLengthAndType(input, index);
    length_path += entry_pair.first;

    length_stack.push(entry_pair.first);
    if (entry_pair.second && longest_path < length_path)
      longest_path = length_path;
  }
  return longest_path;
}

int main(int argc, const char* argv[]) {
  string fs[] = {"dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext",  // 1
                 "dir\n\tsubdir1\n\t\tfile1."                // 2
                 "ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2."
                 "ext",
                 "dir\n\tsubdir1\n\tsubdir2",                    // 3
                 "a\n\taa\n\t\taaa\n\t\t\taaaa\n\t\t\t\tfile1."  // 4
                 "txt\naaaaaaaaaaaaaaaaaaaa\n\tsth.png"};
  for (auto filesystem : fs) {
    std::cout << "filesystem:\n" << filesystem << "\n";
    std::cout << "the length of longest path : "
              << lengthLongestPath(filesystem) << "\n";
  }
  return 0;
}
