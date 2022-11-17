#include "List.h"
#include <iostream>
#include <vector>
int main() {
  List<int> list;
  for (int i = 1; i <= 3; ++i) { list.insertBack(i); }  // 1 2 3
  // std::cout << *(list.end()) << std::endl;
  for (auto curr = list.begin(); curr != list.end(); ++curr) {
    std::cout << *curr << std::endl;
  }
  // auto iter = list.begin();
  // for (int i = 0; i < 3; ++i) {
    // iter++;
  // }
  // std::cout << static_cast<bool>((iter == list.end())) << std::endl;

  // --end;
  // --end;
  // --end;
  // for (auto i = list.begin(); i != list.end(); ++i) {
    // std::cout << *i << " " << std::endl;
  // }
  // std::vector<int> vec(list.begin(), end);
  // for (auto& num : vec) { std::cout << num << " ";} std::cout << std::endl;
  // vec.end();

  return 0;
}
