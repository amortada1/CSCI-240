#include <string>
#include <unordered_map>
#include <queue>
#include <vector>
#include <functional>
#include <cstdint>

#include "bit_array.h"

#ifndef HUFFMAN_H
#define HUFFMAN_H

struct Node
{
    char symbol;
    uint64_t freq{};
    Node* lchild{};
    Node* rchild{};
    bool terminal{}; // false by default
};

struct Triple
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
    void storeSymbolQty(std::ofstream&);
    void storeTableSize(std::ofstream&);
    void storeTable(std::ofstream&);
    void compress(BitArray&);
    void storeCompressedData(BitArray&, std::ofstream&);
    const Triple* lookupSymbol(char);

    // bool isValidPqueue();

    std::string srcPath;
    std::string dstPath;
    uint32_t symbolQty;
    uint32_t tableSize;
    uint64_t bitQty;
    Map map;
    PQueue pqueue;
    Node* root;
    std::vector<Triple> table;
};

#endif