#include <iostream>

#include "huffman.h"

int main(int argc, char const *argv[])
{
    HuffmanCompressor hc("wap.txt", "wap.cmp");

    std::cout << hc.height(hc.root) << std::endl;

    return 0;
}
