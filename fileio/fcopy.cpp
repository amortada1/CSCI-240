#include <fstream>

#define BUFFER_SIZE 1024

int main(int argc, char const *argv[])
{
    char buffer[BUFFER_SIZE];
    std::ifstream in("fart.txt", std::ios::binary);
    std::ofstream out;
    int qtyRead;

    if (in) // make sure input file was opened
    {
        out.open("fart_copy.txt", std::ios::binary);

        while (true)
        {
            in.read(buffer, BUFFER_SIZE);
            qtyRead = in.gcount();
            if (qtyRead == 0) break;
            out.write(buffer, qtyRead);
        }
        
    }

    return 0;
}
