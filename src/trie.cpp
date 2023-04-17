#include "trie.h"

#include <iostream>

#include "text_exception.h"

Trie::Trie(){};

size_t Trie::GetHead() const {
    return head_;
}

void Trie::SetHead(size_t index) {
    if (!(0 < index && index < nodes_.size())) {
        throw TextException("Trie::SetHead wrong index");
    }
    head_ = index;
}

size_t Trie::MakeNode() {
    nodes_.push_back(Node());
    return nodes_.size() - 1;
}

size_t Trie::MakeNode(Symbol symbol) {
    nodes_.push_back(Node(symbol));
    node_index_of_symbol_[symbol] = nodes_.size() - 1;
    return nodes_.size() - 1;
}

size_t Trie::MakeLeft(size_t index) {
    if (!(0 < index && index < nodes_.size())) {
        throw TextException("Trie::MakeLeft wrong index");
    }
    if (nodes_[index].left == 0) {
        nodes_[index].left = MakeNode();
        nodes_[nodes_[index].left].parent = index;
        nodes_[nodes_[index].left].edge = false;
    }
    return nodes_[index].left;
}

size_t Trie::MakeRight(size_t index) {
    if (!(0 < index && index < nodes_.size())) {
        throw TextException("Trie::MakeRight wrong index");
    }
    if (nodes_[index].right == 0) {
        nodes_[index].right = MakeNode();
        nodes_[nodes_[index].right].parent = index;
        nodes_[nodes_[index].right].edge = true;
    }
    return nodes_[index].right;
}

size_t Trie::GetLeft(size_t index) const {
    if (!(0 < index && index < nodes_.size())) {
        throw TextException("Trie::GetLeft wrong index");
    }
    return nodes_[index].left;
}

size_t Trie::GetRight(size_t index) const {
    if (!(0 < index && index < nodes_.size())) {
        throw TextException("Trie::GetRight wrong index");
    }
    return nodes_[index].right;
}

size_t Trie::GetParent(size_t index) const {
    if (!(0 < index && index < nodes_.size())) {
        throw TextException("Trie::GetParent wrong index");
    }
    return nodes_[index].parent;
}

Symbol Trie::GetSymbol(size_t index) const {
    if (!(0 < index && index < nodes_.size())) {
        throw TextException("Trie::SetSymbol wrong index");
    }
    return nodes_[index].symbol;
}

void Trie::Add(Symbol symbol, std::vector<bool> path) {
    if (path.empty()) {
        throw TextException("Trie::Add empty path");
    }
    size_t node_index = head_;
    for (bool edge : path) {
        if (edge) {
            node_index = MakeRight(node_index);
        } else {
            node_index = MakeLeft(node_index);
        }
    }
    nodes_[node_index].symbol = symbol;
    if (node_index_of_symbol_.find(symbol) != node_index_of_symbol_.end()) {
        throw TextException("Trie::Add double symbol");
    }
    node_index_of_symbol_[symbol] = node_index;
}

size_t Trie::Unite(size_t left_index, size_t right_index) {
    size_t result = MakeNode();
    nodes_[result].left = left_index;
    nodes_[left_index].parent = result;
    nodes_[left_index].edge = false;
    nodes_[result].right = right_index;
    nodes_[right_index].parent = result;
    nodes_[right_index].edge = true;
    return result;
}

std::vector<bool> Trie::GetCode(Symbol symbol) {
    if (node_index_of_symbol_.find(symbol) == node_index_of_symbol_.end()) {
        throw TextException("Trie::Add symbol not in trie");
    }
    size_t node_index = node_index_of_symbol_[symbol];
    std::vector<bool> result;
    while (node_index != head_) {
        result.push_back(nodes_[node_index].edge);
        node_index = GetParent(node_index);
    }
    std::reverse(result.begin(), result.end());
    return result;
}

void Trie::LengthCount(size_t node_index, std::vector<std::pair<size_t, Symbol>> &result, size_t length) const {
    if (GetLeft(node_index) == 0 && GetRight(node_index) == 0) {
        result.push_back(std::make_pair(length, nodes_[node_index].symbol));
    } else {
        if (GetLeft(node_index) != 0) {
            LengthCount(GetLeft(node_index), result, length + 1);
        }
        if (GetRight(node_index) != 0) {
            LengthCount(GetRight(node_index), result, length + 1);
        }
    }
}
