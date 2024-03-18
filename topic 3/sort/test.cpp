#include "sorter.h"
#include "test.h"

#define TEST_VALS int array[]{5, 2, 7, 3, 2, 9, 1, 2}

void testBubbleSort();
void testSelectionSort();
bool compare(int a, int b) {return a < b;}

int main(int argc, char const *argv[])
{
    testBubbleSort();
    testSelectionSort();
    
    return 0;
}

void testBubbleSort()
{
    TEST_VALS;
    int lastVal;

    size_t size{sizeof(array) / sizeof(array[0])};

    Sorter<int>::bubbleSort(array, size, compare);
    lastVal = array[0];

    for (size_t i = 1; i < size; ++i)
    {
        if(lastVal > array[i])
        {
            testFail("bubble sort properly ordered");
            return;
        }

        lastVal = array[i];
    }
    
    testPass("bubble sort properly ordered");
    return;
}

void testSelectionSort()
{
    TEST_VALS;
    int lastVal;

    size_t size{sizeof(array) / sizeof(array[0])};

    Sorter<int>::selectionSort(array, size, compare);
    lastVal = array[0];

    for (size_t i = 1; i < size; ++i)
    {
        if(lastVal > array[i])
        {
            testFail("selection sort properly ordered");
            return;
        }

        lastVal = array[i];
    }
    
    testPass("selection sort properly ordered");

    return;
}
