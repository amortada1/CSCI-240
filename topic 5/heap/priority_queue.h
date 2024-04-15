#include <functional>
#include "heap.h"

#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

template<typename T>
class PriorityQueue
{
public:
    PriorityQueue(std::function<bool(const T&, const T&)> compare) 
    : heap(compare){ }
    void enqueue(const T& item) { heap.add(item) };
    void dequeue() { heap.remove() } ;
    T front() const { return heap.get(); }
    bool empty() const { return heap.empty(); }
    void clear { heap.clear(); }

private:
    Heap<T> heap;

};

#endif /* PRIORITY_QUEUE_H */