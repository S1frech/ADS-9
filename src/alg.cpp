// Copyright 2022 NNTU-CS
#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>

#include "tree.h"

Node::Node(char val) : value(val) {}
Node::~Node() {
  for (auto child : children) delete child;
}

PMTree::PMTree(std::vector<char> symbols) {
  root = new Node('*');
  buildTree(root, symbols);
}

PMTree::~PMTree() { delete root; }

void PMTree::buildTree(Node* current, std::vector<char> remaining) {
  if (remaining.empty()) return;

  std::sort(remaining.begin(), remaining.end());

  for (size_t i = 0; i < remaining.size(); ++i) {
    char ch = remaining[i];
    Node* child = new Node(ch);
    current->children.push_back(child);

    std::vector<char> next_remaining = remaining;
    next_remaining.erase(next_remaining.begin() + i);

    buildTree(child, next_remaining);
  }
}

void PMTree::getAllPermsHelper(Node* node, std::vector<char>& path,
                               std::vector<std::vector<char>>& result) {
  if (node->value != '*') path.push_back(node->value);

  if (node->children.empty()) {
    result.push_back(path);
  } else {
    for (auto child : node->children) {
      getAllPermsHelper(child, path, result);
    }
  }

  if (!path.empty()) path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  tree.getAllPermsHelper(tree.root, path, result);
  return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = getAllPerms(tree);
  if (num <= 0 || num > all.size()) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;
  Node* node = tree.root;
  int idx = num - 1;
  std::vector<int> factorial;

  int n = node->children.size();
  factorial.push_back(1);
  for (int i = 1; i <= n; ++i) factorial.push_back(factorial.back() * i);

  std::vector<Node*> level_nodes = node->children;
  std::sort(level_nodes.begin(), level_nodes.end(),
            [](Node* a, Node* b) { return a->value < b->value; });

  for (int i = n; i > 0; --i) {
    int fact = factorial[i - 1];
    int chosen = idx / fact;
    idx %= fact;

    Node* chosen_node = level_nodes[chosen];
    result.push_back(chosen_node->value);

    std::vector<Node*> next_level;
    for (auto ch : chosen_node->children) next_level.push_back(ch);
    std::sort(next_level.begin(), next_level.end(),
              [](Node* a, Node* b) { return a->value < b->value; });

    level_nodes = next_level;
  }

  return result;
}
