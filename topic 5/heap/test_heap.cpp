#include <cstdlib>

#include "heap.h"
#include "test.h"

int main(int argc, char const *argv[])
{
    int array[10];
    int previousValue;

    for (size_t i = 0; i < 10; ++i)
        array[i] = rand() % 100;

    Heap<int> h( [](int a, int b) { return a > b; }, array, 10 );

    previousValue = h.get();
    h.remove();

    while(!h.empty())
    {
        if(h.get() > previousValue)
        {
            testFail("test removal order");
            return 0;
        }

        previousValue = h.get();
        h.remove();
    }

    testPass("test removal order");

    return 0;
}

