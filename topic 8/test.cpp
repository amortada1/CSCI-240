#include "sort.h"
#include "test.h"

#define ARRAY_SIZE 8
#define TEST_ARRAY uint32_t array[]{3, 1, 2, 5, 6, 4, 9, 8}
#define SOLUTION_ARRAY uint32_t solutionArray[]{1, 2, 3, 4, 5, 6, 8, 9}

void testBubbleSort();
void testSelectionSort();
void testInsertionSort();
void testRadixSort();
bool compare(uint32_t a, uint32_t b) {return a < b;}

int main(int argc, char const *argv[])
{
    // testBubbleSort();
    // testSelectionSort();
    // testInsertionSort();
    testRadixSort();
    
    return 0;
}

void testBubbleSort()
{
    TEST_ARRAY;
    uint32_t lastVal;

    size_t size{sizeof(array) / sizeof(array[0])};

    Sort<uint32_t>::bubbleSort(array, size, compare);
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
    TEST_ARRAY;
    uint32_t lastVal;

    size_t size{sizeof(array) / sizeof(array[0])};

    Sort<uint32_t>::selectionSort(array, size, compare);
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

void testInsertionSort()
{
    TEST_ARRAY;
    SOLUTION_ARRAY;

    Sort<uint32_t>::insertionSort(array, ARRAY_SIZE, compare);

    for (size_t i = 1; i < ARRAY_SIZE; ++i)
    {   
        if(array[i] != solutionArray[i])
        {
            testFail("insertion sort properly ordered");
            return;
        }
    }
    
    testPass("insertion sort properly ordered");

    return;   
}

void testRadixSort()
{
    TEST_ARRAY;
    SOLUTION_ARRAY;

    Sort<uint32_t>::radixSort(array, ARRAY_SIZE);

    for (size_t i = 1; i < ARRAY_SIZE; ++i)
    {   
        if(array[i] != solutionArray[i])
        {
            testFail("radix sort properly ordered");
            return;
        }
    }
    
    testPass("radix sort properly ordered");
}