#include "sort.h"
#include "test.h"

#define ARRAY_SIZE 8
#define TEST_ARRAY int array[]{3, 1, 2, 5, 6, 4, 9, 8}
#define SOLUTION_ARRAY int solutionArray[]{1, 2, 3, 4, 5, 6, 8, 9}

void testBubbleSort();
void testSelectionSort();
void testInsertionSort();
bool compare(int a, int b) {return a < b;}

int main(int argc, char const *argv[])
{
    // testBubbleSort();
    // testSelectionSort();
    testInsertionSort();
    
    return 0;
}

void testBubbleSort()
{
    TEST_ARRAY;
    int lastVal;

    size_t size{sizeof(array) / sizeof(array[0])};

    Sort<int>::bubbleSort(array, size, compare);
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
    int lastVal;

    size_t size{sizeof(array) / sizeof(array[0])};

    Sort<int>::selectionSort(array, size, compare);
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

    Sort<int>::insertionSort(array, ARRAY_SIZE, compare);

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
