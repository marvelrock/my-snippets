#include <iostream>
#include <string>

void Reverse(std::string& str, std::size_t lower_bound,
             std::size_t upper_bound) {
  if (lower_bound >= upper_bound) return;
  auto i = lower_bound;
  auto j = upper_bound - 1;
  while (i < j) std::swap(str[i++], str[j--]);
}

std::size_t FindDotIndex(const std::string& str, std::size_t begin) {
  std::size_t length = str.length();
  if (begin >= length) return std::string::npos;
  while (str[begin] != '.' && begin < length) ++begin;
  return begin;
}

int main(int argc, const char* argv[]) {
  std::string domain_name = "sport.sina.com.cn";
  if (argc > 1) domain_name = argv[1];
  std::size_t dot_index = 0;
  do {
    std::size_t next_dot_index = FindDotIndex(domain_name, dot_index);
    if (next_dot_index == std::string::npos) break;
    Reverse(domain_name, dot_index, next_dot_index);
    dot_index = next_dot_index + 1;
  } while (true);
  Reverse(domain_name, 0, domain_name.length());
  std::cout << "reverse_domain_name: " << domain_name << "\n";
  return 0;
}
