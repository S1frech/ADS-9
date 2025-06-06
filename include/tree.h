// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_

#include <vector>

class Node {
 public:
  char value;
  std::vector<Node*> children;

  explicit Node(char val);
  ~Node();  // освобождение памяти
};

class PMTree {
 private:
  Node* root;
  void build(Node* current, std::vector<char> remaining);
  void collectPerms(Node* node, std::vector<char>& path,
                    std::vector<std::vector<char>>& result);

 public:
  explicit PMTree(const std::vector<char>& input);
  ~PMTree();

  std::vector<std::vector<char>> getAllPerms();

  friend std::vector<char> getPerm1(PMTree& tree, int num);
  friend std::vector<char> getPerm2(PMTree& tree, int num);
};

std::vector<std::vector<char>> getAllPerms(PMTree& tree);
std::vector<char> getPerm1(PMTree& tree, int num);
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_



