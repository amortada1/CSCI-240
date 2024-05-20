#include <string>
#include <vector>
#include <queue>
#include <fstream>

#include "bit_array.h"
#include "heap.h"

#ifndef HUFFMAN_H
#define HUFFMAN_H

#define INIT_SIZE 1

// huffman tree node
struct Node
{
    char data;
    size_t freq;
    BitArray code;
    Node* lchild;
    Node* rchild;

    Node(char c, size_t f) : data{c}, freq{f}, code(INIT_SIZE), lchild{nullptr}, rchild{nullptr} {}
};

// function to compare two nodes (used in constructing min heap)
struct compare 
{
    bool operator()(Node* l, Node* r) {return l->freq > r->freq;}
};

// function to scan a text file and find the frequency of each character
// takes in a file and modifies a character vector and frequency vector
void findFrequency(std::ifstream inputFile, std::vector<size_t>& asciiArray)
{
    char ascii;

    while (inputFile >> ascii)
        asciiArray[ascii]++;
    
}

void createCodes(Node* node, std::string str)
{
    if ((node == nullptr) || (node->data == ' ')) return;

    if (node->data != '*')
    {
        // modify the node's bitarray
        BitArray newCode(str.length());
        for (size_t i = 0; i < str.length(); ++i)
            if (str[i] == 1) newCode.setBit(i, true); 
        node->code = newCode;
    }

    createCodes(node->lchild, str + "0");
    createCodes(node->rchild, str + "1");
}

// function to build a huffman tree
void buildHuffmanTree(std::vector<char>& data, std::vector<size_t>& freq, size_t size)
{
    Node* lChild;
    Node* rChild;
    Node* root;

    // create and load up minheap
    std::priority_queue<Node*, std::vector<Node*>, compare> minHeap;
    for (size_t i = 0; i < size; ++i) minHeap.push(new Node(data[i], freq[i]));

    while (minHeap.size() != 1)
    {
        // get two items with smallest frequency
        lChild = minHeap.top();
        minHeap.pop();
        rChild = minHeap.top();
        minHeap.pop();

        // create parent node with sum of frequencies of the two nodes
        root = new Node('*', lChild->freq + rChild->freq);
        root->lchild = lChild;
        root->rchild = rChild;

        minHeap.push(root);
    }

    // create codes for each node
    createCodes(minHeap.top(), "");
}


#endif