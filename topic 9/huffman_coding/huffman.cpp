#include "huffman.h"

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    char buffer[BUFFER_SIZE];
    std::vector<size_t> asciiVector[128];
    std::ifstream in("War_and_Peace.txt", std::ios::binary);
    std::ofstream out;
    size_t qtyRead;

    if (!in) return -1;

    out.open("War_and_Peace_compressed.txt", std::ios::binary);

    while (true)
        {
            in.read(buffer, BUFFER_SIZE);
            qtyRead = in.gcount();
            if (qtyRead == 0) break;
            out.write(buffer, qtyRead);
        }

    return 0;
}
