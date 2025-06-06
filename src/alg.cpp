// Copyright 2022 NNTU-CS
#include <algorithm>
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

  std::sort(remaining.begin(), remaining.end());  // по возрастанию

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
    for (Node* child : node->children) collectPerms(child, path, result);
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

  std::vector<int> factorials;
  int n = current->children.size();
  int fact = 1;
  for (int i = 1; i <= n; ++i) {
    fact *= i;
    factorials.push_back(fact);
  }

  --num;
  std::vector<Node*> level = current->children;
  while (!level.empty()) {
    int f = factorials[--n];
    int index = num / f;
    num %= f;

    if (index >= (int)level.size()) return {};  // перестановка не существует

    Node* chosen = level[index];
    result.push_back(chosen->value);
    level.erase(level.begin() + index);
    level = chosen->children;
  }

  return result;
}
