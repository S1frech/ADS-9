// Copyright 2022 NNTU-CS
#include <chrono>
#include <iostream>
#include <random>
#include "tree.h"


int main() {
  std::vector<char> input = {'1', '3', '5', '7'};
  PMTree tree(input);

  auto all = getAllPerms(tree);
  std::cout << "All permutations:\n";
  for (auto& perm : all) {
    for (char ch : perm) std::cout << ch;
    std::cout << "\n";
  }

  std::cout << "\nPerm 1 (via getPerm1): ";
  auto p1 = getPerm1(tree, 1);
  for (char ch : p1) std::cout << ch;
  std::cout << "\n";

  std::cout << "Perm 2 (via getPerm2): ";
  auto p2 = getPerm2(tree, 2);
  for (char ch : p2) std::cout << ch;
  std::cout << "\n";

  // Эксперимент
  std::cout << "\nExperiment:\n";
  for (int n = 3; n <= 8; ++n) {
    std::vector<char> alphabet;
    for (int i = 0; i < n; ++i) alphabet.push_back('1' + i);

    PMTree t(alphabet);
    int total = 1;
    for (int i = 2; i <= n; ++i) total *= i;

    std::mt19937 gen(42);
    std::uniform_int_distribution<> dist(1, total);

    auto start1 = std::chrono::high_resolution_clock::now();
    getAllPerms(t);
    auto end1 = std::chrono::high_resolution_clock::now();

    auto start2 = std::chrono::high_resolution_clock::now();
    getPerm1(t, dist(gen));
    auto end2 = std::chrono::high_resolution_clock::now();

    auto start3 = std::chrono::high_resolution_clock::now();
    getPerm2(t, dist(gen));
    auto end3 = std::chrono::high_resolution_clock::now();

    std::cout << "n = " << n << ", getAllPerms = "
              << std::chrono::duration<double>(end1 - start1).count()
              << "s, getPerm1 = "
              << std::chrono::duration<double>(end2 - start2).count()
              << "s, getPerm2 = "
              << std::chrono::duration<double>(end3 - start3).count() << "s\n";
  }

  return 0;
}
