#include <functional>
#include <cmath>

#include "heap.h"

#ifndef ARRAY_HEAP_H
#define ARRAY_HEAP_H

#define DEFAULT_SIZE 128
#define SCALING_FACTOR 2

template<typename T>
class ArrayHeap : public Heap<T>
{ 
public:
    ArrayHeap(std::function<bool(const T&, const T&)> comparator) 
        : ArrayHeap(comparator, DEFAULT_SIZE) {}

    ArrayHeap(std::function<bool(const T&, const T&)> comparator, size_t initialSize) 
        : store{new T[initialSize]}, count{0}, currentSize{initialSize}, comparator{comparator} {}

    ArrayHeap(std::function<bool(const T&, const T&)> comparator, const T srcArray[], size_t size) 
    { 
        store = new T[size];
        count = 0;
        currentSize = size;
        
        // copy the elements of the passed array into the heap's data store
        for (size_t i = 1; i < size; ++i)
        {
            store[i] = srcArray[i];
            ++count;
        }

        // run heapify on internal store to put it into minheap/maxheap order
        heapify(store, size);
    }
    
    ~ArrayHeap() {delete[] store;}

    void add(const T& item)
    {
        // add item to the end of the array
        if (count == currentSize) resize();
        store[++count] = item;

        // run upheap on store
        if (count == 1) upHeap(1);
        upHeap(count / 2);
    }

    void remove()
    {
        // copy last element of store over root element and decrement store
        store[1] = store[count];
        --count;

        // run downheap on store
        downHeap(1);
    }

    T get() const {return store[1];}

    bool empty() const {return count == 0;}

    void clear() {count = 0;}

private:
    T* store;
    size_t currentSize;
    size_t count;
    std::function<bool(const T&, const T&)> comparator;
    
    void downHeap(const size_t parent)
    {
        // compare parent with both left and right child and swap if needed
        size_t lChild = 2 * parent;
        size_t rChild = lChild + 1;

        if (comparator(store[parent], store[lChild]))
        {
            T temp = store[lChild];
            store[lChild] = store[parent];
            store[parent] = temp;
            return downHeap(lChild);
        }

        if (comparator(store[parent], store[rChild]))
        {
            T temp = store[rChild];
            store[rChild] = store[parent];
            store[parent] = temp;
            return downHeap(rChild);
        }
    }

    void upHeap(const size_t parent)
    {           
        if (count == 1 || parent == 1) return;
        
        // compare parent with both left and right child and swap if needed
        size_t lChild = 2 * parent;
        size_t rChild = lChild + 1;

        if (comparator(store[parent], store[lChild]))
        {
            T temp = store[parent];
            store[parent] = store[lChild];
            store[lChild] = temp;
        }

        if (comparator(store[parent], store[rChild]))
        {
            T temp = store[parent];
            store[parent] = store[rChild];
            store[rChild] = temp;
        }

        // recursively call upheap function
        return upHeap(parent / 2);
    }

    void heapify(T array[], size_t size)
    {
        for (size_t finalParentNode = ceil((size - 1) / 2); finalParentNode > 0; --finalParentNode)
            upHeap(finalParentNode);
        
    }
    
    void resize()
    {
        size_t newSize{currentSize * SCALING_FACTOR};
        T* newArray{new T[newSize]};

        for (size_t i = 1; i <= currentSize; ++i)
            newArray[i] = store[i];

        delete[] store;
        currentSize = newSize;
        store = newArray;
    }
};

#endif /* ARRAY_HEAP_H */
