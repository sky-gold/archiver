#pragma once

#include <vector>
#include <map>

#include "symbol.h"

class Trie {
public:
    Trie();
    size_t GetHead() const;
    void SetHead(size_t index);
    size_t MakeNode();
    size_t MakeNode(Symbol symbol);
    size_t MakeLeft(size_t index);
    size_t MakeRight(size_t index);
    size_t GetParent(size_t index) const;
    size_t GetLeft(size_t index) const;
    size_t GetRight(size_t index) const;
    Symbol GetSymbol(size_t index) const;
    void Add(Symbol symbol, std::vector<bool> path);
    size_t Unite(size_t left_index, size_t right_index);
    std::vector<bool> GetCode(Symbol symbol);
    void LengthCount(size_t node_index, std::vector<std::pair<size_t, Symbol>>& result, size_t length = 0) const;

private:
    class Node {
    public:
        Node(){};
        explicit Node(Symbol symbol) : symbol(symbol){};
        Node(Symbol symbol, size_t left, size_t right, size_t parent = 0, size_t edge = false)
            : symbol(symbol), left(left), right(right), parent(parent), edge(edge){};
        Symbol symbol = Symbol();
        size_t left = 0;
        size_t right = 0;
        size_t parent = 0;
        bool edge = false;
    };
    std::vector<Node> nodes_ = {Node(), Node()};
    size_t head_ = 1;
    std::map<Symbol, size_t> node_index_of_symbol_;
};
