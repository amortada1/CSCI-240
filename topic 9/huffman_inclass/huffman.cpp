#include <fstream>

#include "huffman.h"

#define BYTE_MASK 0xFFull

HuffmanCompressor::HuffmanCompressor(const std::string& src, const std::string& dst)
    : srcPath{src}, dstPath{dst}, pqueue{[](Node* a, Node* b){return a->freq > b->freq;}}
{
    // get frequencies of symbols
    buildMap();

    // build the tree
    loadPqueue();
    buildTree(); 

    // build the table
        // record [1B char] [1B size of code] [4B code]
    buildTable();

    // store the table in output file
    
    // compress and store the data
}

void HuffmanCompressor::buildMap()
{
    #define BUFFER_SIZE 4096
    std::ifstream in(srcPath);
    char buffer[BUFFER_SIZE];

    while (true)
    {
        in.read(buffer, BUFFER_SIZE);

        if (in.gcount() == 0) break;

        for (size_t i = 0; i < in.gcount(); ++i)
        {
            if (map.find(buffer[i]) == map.end())
                map[buffer[i]] = 1;
            else
                ++map[buffer[i]];
        }   
    }
}

void HuffmanCompressor::buildTree()
{
    Node* node;
    while (pqueue.size() > 1)
    {
        node = new Node;
        node->freq = pqueue.top()->freq;
        node->lchild = pqueue.top();
        pqueue.pop();
        node->freq += pqueue.top()->freq;
        node->rchild = pqueue.top();
        pqueue.pop();
        pqueue.emplace(node);
    }

    root = pqueue.top();
    pqueue.pop();
}

void HuffmanCompressor::loadPqueue()
{
    for (auto p: map)
        pqueue.emplace(new Node{p.first, p.second, nullptr, nullptr});
}

void HuffmanCompressor::buildTable()
{
    traverse(root);
}

size_t HuffmanCompressor::height(const Node* root)
{
    if (root == nullptr) return 0;

    return 1 + std::max(height(root->lchild), height(root->rchild));
}

void HuffmanCompressor::traverse(const Node* node)
{
    static uint64_t code;
    static uint8_t depth;
    if (node->symbol != 0)
    {
        table.push_back({node->symbol, depth, code})
        return;
    }

    code <<= 1;
    ++depth;
    traverse(node->lchild);
    code |= 1;
    traverse(node->rchild);

    --depth;
    code >>= 1;
}