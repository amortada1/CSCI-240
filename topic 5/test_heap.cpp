#include "test.h"
#include "heap.h"
#include "array_heap.h"
#include "priority_queue.h"

#define TEST_VALS int array[]{0, 5, 2, 7, 3, 4, 9, 1, 8}

// comparator for max heap
bool comparator(int a, int b) {return a < b;}
// comparator for min heap
// bool comparator(int a, int b) {return a > b;}

void testMaxHeap();
void testMinHeap();

int main(int argc, char const *argv[])
{
    testMaxHeap();

    return 0;
}

void testMaxHeap()
{
    TEST_VALS;

    std::cout << "Creating a max heap..." << std::endl;

    size_t size{sizeof(array) / sizeof(array[0])};
    
    PriorityQueue<int>* p{new PriorityQueue<int>(comparator, array, size)};

    // for (size_t i = 1; i < size; ++i)
    //     p->enqueue(array[i]);

    testFalse(p->empty(), "test that the priority queue is not empty after filling it with values");
    
    int maxValue = 0;
    for (size_t i = 0; i < size; ++i)
        if (array[i] > maxValue) maxValue = array[i];
        
    testTrue(p->front() == maxValue, "test that the max value is at the front of the priority queue");

}
