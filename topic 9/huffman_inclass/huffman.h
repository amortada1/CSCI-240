#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <functional>

#ifndef HUFFMAN_H
#define HUFFMAN_H

struct Node
{
    char symbol;
    size_t freq{};
    Node* lchild{};
    Node* rchild{};
};

using Map = std::unordered_map<uint8_t, size_t>;
using PQueue = std::priority_queue<Node*, std::vector<Node*>, std::function<bool(Node*, Node*)>>;

struct HuffmanCompressor
{
    HuffmanCompressor(const std::string&, const std::string&);
    void buildMap();
    void buildTree();
    void loadPqueue();

    std::string srcPath;
    std::string dstPath;

    Map map;

    PQueue pqueue;

    Node* root;
};

#endif