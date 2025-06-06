// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#pragma once
#include <vector>

class Node {
 public:
  char value;
  std::vector<Node*> children;

  Node(char val);
  ~Node();
};

class PMTree {
 private:
  Node* root;

  void buildTree(Node* current, std::vector<char> remaining);
  void getAllPermsHelper(Node* node, std::vector<char>& path,
                         std::vector<std::vector<char>>& result);

 public:
  PMTree(std::vector<char> symbols);
  ~PMTree();

  friend std::vector<std::vector<char>> getAllPerms(PMTree& tree);
  friend std::vector<char> getPerm1(PMTree& tree, int num);
  friend std::vector<char> getPerm2(PMTree& tree, int num);
};


#endif  // INCLUDE_TREE_H_
