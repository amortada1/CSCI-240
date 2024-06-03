#include <fstream>

#include "huffman.h"
#include "bit_array.h"

#define BYTE_MASK 0xFFull

HuffmanCompressor::HuffmanCompressor(const std::string& src, const std::string& dst)
    : srcPath{src}, dstPath{dst}, symbolQty{}, tableSize{}, bitQty{}, pqueue{[](Node* a, Node* b){return a->freq > b->freq;}}
{
    std::ofstream out;
    
    // get frequencies of symbols
    buildMap();

    // build the tree
    loadPqueue();

    // isValidPqueue();

    buildTree(); 

    // build the table
        // record [1B char] [1B size of code] [4B code]
    buildTable();

    out.open(dstPath, std::ios::binary);

    // store symbol count
    storeSymbolQty(out);

    // store size of the table
    storeTableSize(out);

    // store the table in output file
    storeTable(out);
    
    // compress and store the data
    BitArray ba{bitQty};

    compress(ba);

    storeCompressedData(ba, out);
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
            
            ++symbolQty;
        }   
    }

    tableSize = map.size() << 1;
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
        pqueue.emplace(new Node{p.first, p.second, nullptr, nullptr, true});
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
    
    if (!node) return;

    if (node->terminal)
    {
        table.push_back({node->symbol, depth, code, node->freq});
        tableSize += (depth >> 3) + (((depth & 0b111) == 0) ? 0u : 1u);
        bitQty += depth * node->freq;
    }

    code <<= 1;
    ++depth;
    traverse(node->lchild);
    code |= 1;
    traverse(node->rchild);

    --depth;
    code >>= 1;
}

void HuffmanCompressor::storeSymbolQty(std::ofstream& out)
{
    char* bytes{reinterpret_cast<char*>(&symbolQty)};
    out.write(bytes, sizeof symbolQty);
}

void HuffmanCompressor::storeTableSize(std::ofstream& out)
{
    char* bytes{reinterpret_cast<char*>(&tableSize)};
    out.write(bytes, sizeof tableSize);
}

void HuffmanCompressor::storeTable(std::ofstream& out)
{
    const char* ptr;

    for (const Triple& t : table)
    {
        ptr = reinterpret_cast<const char*>(&t);

        size_t size{2u + (t.bitQty >> 3) + static_cast<uint8_t>(((t.bitQty & 0b111) == 0) ? 0u : 1u)};

        out.write(ptr, size);
    }
}

void HuffmanCompressor::compress(BitArray&)
{}

void HuffmanCompressor::storeCompressedData(BitArray& ba, std::ofstream& out)
{
    const char* ptr{reinterpret_cast<const char*>(ba.getArray())};
    out.write(ptr, ba.getByteQty());
}

// bool HuffmanCompressor::isValidPqueue()
// {
//     size_t prevFreq{pqueue.top()->freq};
//     size_t freq;
//     pqueue.pop();

//     while (!pqueue.empty())
//     {
//         freq = pqueue.top()->freq;
//         if (freq < prevFreq) return false;

//         pqueue.pop();
//         prevFreq = freq;
//     }

//     return true;
// }

/*
Compressed File Layout

4B - symbol count
4B - size of table
table
compressed bit stream
*/