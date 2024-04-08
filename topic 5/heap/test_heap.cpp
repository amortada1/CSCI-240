#include "heap.h"

int main(int argc, char const *argv[])
{
    Heap<int> h([](int a, int b){return a > b;});

    return 0;
}
