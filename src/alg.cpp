// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include  "tree.h"
#include <algorithm>

Node::Node(char val) : value(val) {}
Node::~Node() {
    for (auto child : children) delete child;
}

PMTree::PMTree(std::vector<char> symbols) {
    root = new Node('*');
    buildTree(root, symbols);
}

PMTree::~PMTree() {
    delete root;
}

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

void PMTree::getAllPermsHelper(Node* node, std::vector<char>& path, std::vector<std::vector<char>>& result) {
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
