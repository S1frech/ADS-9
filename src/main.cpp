// Copyright 2022 NNTU-CS
#include <iostream>
#include <vector>
#include "tree.h"

int main() {
  std::vector<char> in = {'1', '2', '3'};
  PMTree tree(in);

  auto all = getAllPerms(tree);
  std::cout << "All permutations:\n";
  for (const auto& perm : all) {
    for (char c : perm) std::cout << c;
    std::cout << "\n";
  }

  std::cout << "\nPerm1 #2: ";
  auto p1 = getPerm1(tree, 2);
  for (char c : p1) std::cout << c;

  std::cout << "\nPerm2 #2: ";
  auto p2 = getPerm2(tree, 2);
  for (char c : p2) std::cout << c;
  std::cout << "\n";

  return 0;
}

