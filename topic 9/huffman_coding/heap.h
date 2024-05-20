#include <functional>

#ifndef HEAP_H
#define HEAP_H

#define DEFAULT_SIZE 256
#define ROOT 1

/*
    a > b yields a max heap
*/

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
        if (count >= currentSize - 1) resize();
        heap[++count] = item;

        if (count > 1) upHeap(count);
    }

    void remove() 
    {
        heap[ROOT] = heap[count--];
        downHeap(ROOT);
    }

    T get() const {return heap[ROOT];}

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
        for (size_t parent = count >> 1; parent >= ROOT; --parent)
            downHeap(parent);
    }

    void upHeap(size_t child)
    {
        size_t parent{child << 1};
        size_t extremaIdx;

        if(child <= ROOT) return;
        extremaIdx = extrema(parent, child);

        if(extremaIdx != parent)
        {
            std::swap(heap[parent], heap[extremaIdx]);
            upHeap(extremaIdx);
        }
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
        if (child <= count) extremaIdx = extrema(extremaIdx, child);

        if (extremaIdx != parent)
        {
            std::swap(heap[parent], heap[extremaIdx]);
            downHeap(extremaIdx);
        }
    }

    void resize()
    {
        T* newHeap;
        currentSize += DEFAULT_SIZE;
        newHeap = new T[currentSize];

        for (size_t i = 1; i <= count; i++)
            newHeap[i] = heap[i];
        
        delete[] heap;
        heap = newHeap;
        // don't delete new heap because newHeap is just a pointer, it'll delete the actual heap 
    }
};

#endif