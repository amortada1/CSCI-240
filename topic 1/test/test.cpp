#include <iostream>
#include <cstdint>
#include "test.h"

#define ULL unsigned long long;

using std::cout;
using std::endl;

using ull = unsigned long long;

typedef unsigned long long Ull;

Ull i{10};

int main()
{
    printExit();
    
    return 0;
}

void printExit()
{
    uint32_t i;

    cout << sizeof i << endl;

    for (size_t i = 0; i < 10; ++i)
        cout << ::i << endl;
        cout << "Goodbye Cruel World" << " " << i << endl;
    
    
}
