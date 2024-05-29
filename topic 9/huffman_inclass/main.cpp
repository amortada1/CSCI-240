#include <iostream>

#include "huffman.h"

int main(int argc, char const *argv[])
{
    HuffmanCompressor hc("wap.txt", "");

    std::cout << hc.height(hc.root) << std::endl;

    return 0;
}
