#include "test.h"
#include "heap.h"
#include "array_heap.h"
#include "priority_queue.h"

#define TEST_VALS int array[]{0, 5, 2, 7, 3, 4, 9, 1, 8}

void testMaxHeap();
void testMinHeap();

int main(int argc, char const *argv[])
{
    testMaxHeap();
    testMinHeap();

    return 0;
}

void testMaxHeap()
{
    TEST_VALS;

    std::cout << "Creating a max heap..." << std::endl;

    size_t size{sizeof(array) / sizeof(array[0])};
    
    PriorityQueue<int>* p{new PriorityQueue<int>([](int a, int b){return a < b;}, array, size)};

    testFalse(p->empty(), "test that the priority queue is not empty after filling it with values");
    
    int maxValue = 0;
    for (size_t i = 0; i < size; ++i)
        if (array[i] > maxValue) maxValue = array[i];
        
    testTrue(p->front() == maxValue, "test that the max value is at the front of the priority queue");

    p->enqueue(100);

    testTrue(p->front() == 100, "test that a larger added value ends up at the front of the priority queue");

    p->dequeue();

    for (size_t i = 0; i < size; ++i)
        if (array[i] > maxValue) maxValue = array[i];

    testTrue(p->front() == maxValue, "test that the largest value is still at front of priority queue after removing a value");

    p->clear();

    testTrue(p->empty(), "test that the priority queue is empty after clearing it");
}

void testMinHeap()
{
    TEST_VALS;

    std::cout << "Creating a min heap..." << std::endl;

    size_t size{sizeof(array) / sizeof(array[0])};

    PriorityQueue<int>* p{new PriorityQueue<int>([](int a, int b){return a > b;}, array, size)};

    testFalse(p->empty(), "test that the priority queue is not empty after filling it with values");
    
    int minValue = 0;
    for (size_t i = 0; i < size; ++i)
        if (array[i] < minValue) minValue = array[i];
        
    testTrue(p->front() == minValue, "test that the min value is at the front of the priority queue");

    p->enqueue(1);

    testTrue(p->front() == 1, "test that a smaller added value ends up at the front of the priority queue");

    p->dequeue();

    for (size_t i = 0; i < size; ++i)
        if (array[i] > minValue) minValue = array[i];

    testTrue(p->front() == minValue, "test that the smallest value is still at front of priority queue after removing a value");

    p->clear();

    testTrue(p->empty(), "test that the priority queue is empty after clearing it");
}
