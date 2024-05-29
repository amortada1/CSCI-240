#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <functional>
#include <cstdint>

#ifndef HUFFMAN_H
#define HUFFMAN_H

struct Node
{
    char symbol;
    size_t freq{};
    Node* lchild{};
    Node* rchild{};
};

struct triple
{
    char symbol;
    uint8_t bitQty;
    uint64_t code;
};

using Map = std::unordered_map<uint8_t, size_t>;
using PQueue = std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>>;

struct HuffmanCompressor
{
    HuffmanCompressor(const std::string&, const std::string&);
    void buildMap();
    void buildTree();
    void loadPqueue();
    void buildTable();
    size_t height(const Node*);
    void traverse(const Node*);

    std::string srcPath;
    std::string dstPath;
    Map map;
    PQueue pqueue;
    Node* root;
    std::vector<triple> table;
};

#endif