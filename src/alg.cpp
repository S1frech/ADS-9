// Copyright 2022 NNTU-CS
#include <algorithm>  // sort, remove
#include <iostream>   // для отладки, можно убрать
#include <vector>
#include "tree.h"

Node::Node(char val) : value(val) {}
Node::~Node() {
  for (Node* child : children) delete child;
}

PMTree::PMTree(const std::vector<char>& input) {
  root = new Node('\0');  // фиктивный корень
  build(root, input);
}

PMTree::~PMTree() { delete root; }

void PMTree::build(Node* current, std::vector<char> remaining) {
  if (remaining.empty()) return;

  std::sort(remaining.begin(),
            remaining.end());  // сортируем для лексикографического порядка

  for (char c : remaining) {
    Node* child = new Node(c);
    current->children.push_back(child);

    std::vector<char> next = remaining;
    next.erase(std::remove(next.begin(), next.end(), c), next.end());

    build(child, next);
  }
}

void PMTree::collectPerms(Node* node, std::vector<char>& path,
                          std::vector<std::vector<char>>& result) {
  if (node->value != '\0') path.push_back(node->value);

  if (node->children.empty()) {
    result.push_back(path);
  } else {
    for (Node* child : node->children) {
      collectPerms(child, path, result);
    }
  }

  if (!path.empty()) path.pop_back();
}

std::vector<std::vector<char>> PMTree::getAllPerms() {
  std::vector<std::vector<char>> result;
  std::vector<char> path;
  collectPerms(root, path, result);
  return result;
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
  return tree.getAllPerms();
}

std::vector<char> getPerm1(PMTree& tree, int num) {
  auto all = tree.getAllPerms();
  if (num <= 0 || num > static_cast<int>(all.size())) return {};
  return all[num - 1];
}

std::vector<char> getPerm2(PMTree& tree, int num) {
  std::vector<char> result;
  Node* current = tree.root;

  int n = current->children.size();
  if (n == 0) return {};

  std::vector<int> factorials(n + 1, 1);
  for (int i = 1; i <= n; ++i) {
    factorials[i] = factorials[i - 1] * i;
  }

  if (num <= 0 || num > factorials[n]) return {};

  --num;

  std::vector<Node*> level = current->children;
  int level_size = n;

  while (level_size > 0) {
    int f = factorials[level_size - 1];
    int index = num / f;
    num %= f;

    if (index >= static_cast<int>(level.size())) return {};

    Node* chosen = level[index];
    result.push_back(chosen->value);

    level.erase(level.begin() + index);

    level = chosen->children;
    --level_size;
  }

  return result;
}
