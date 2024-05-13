#include <fstream>

struct Widget
{
    double loc;
    int size;
};

int main(int argc, char const *argv[])
{
    Widget array[113];
    int elementSize{sizeof(Widget)};
    int arraySize{elementSize * 113};
    std::ofstream out("outstruct.bin");

    char* deepFake = reinterpret_cast<char*>(array);
    out.write(deepFake, arraySize);

    return 0;
}

