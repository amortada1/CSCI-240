#include <functional>

#ifndef HEAP_H
#define HEAP_H

#define DEFAULT_SIZE 432
#define ROOT 1

template<typename T>
class Heap
{
public:
    Heap(std::function<bool(const T&, const T&)> compare) : Heap(compare, DEFAULT_SIZE) { }

    Heap(std::function<bool(const T&, const T&)> compare, size_t initialSize)
        : compare{compare},  heap{new T[initialSize]}, currentSize{initialSize}, count{} { }

    Heap(std::function<bool(const T&, const T&)> compare, const T array[], size_t arraySize) 
        : compare{compare}, currentSize{arraySize + 1}, count{arraySize}
    {
        heap = new T[currentSize];
        for (size_t i = 0; i < arraySize; ++i)
            heap[i + 1] = array[i];

        heapify();
    }

    void add(const T& item) 
    {
        if (count == currentSize) resize();
        heap[++count] = item;

        if (count > 1) upHeap(count >> 1);
    }

    T get() const {return heap[ROOT];}

    void remove() 
    {
        heap[ROOT] = heap[count--];
        downHeap(ROOT);
    }

    bool empty() const {return count == 0;}

    void clear() {count = 0;}
private:
    size_t currentSize;
    size_t count;
    std::function<bool(const T&, const T&)> compare;
    T* heap;

    size_t extrema(size_t a, size_t b) {return compare(heap[a], heap[b]) ? a : b;}

    bool isLeaf(size_t idx) {return (idx << 1) > count;}

    void heapify()
    {
        // TODO: implement
    }

    void upHeap(size_t parent)
    {
        // TODO: implement
    }
    
    void downHeap(size_t parent)
    {
        size_t extremaIdx;
        size_t child{parent << 1};

        if (isLeaf(parent)) return;

        // compare with left child
        extremaIdx = extrema(parent, child);

        // compare with right child (if it exists)
        ++child;
        if (child <= count) extrema(extremaIdx, child);

        if (extremaIdx != parent)
        {
            std::swap(heap[parent], heap[extremaIdx]);
            downHeap(extremaIdx);
        }
    }

    
};

#endif