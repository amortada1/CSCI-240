#ifndef DEQUE_H
#define DEQUE_H

template<typename T>
struct Deque
{
    virtual ~Deque() {};
    virtual void enqueueBack(const T&) = 0;
    virtual void enqueueFront(const T&) = 0;
    virtual void dequeueBack() = 0;
    virtual void dequeueFront() = 0;
    virtual T front() const = 0;
    virtual T back() const = 0;
    virtual bool empty() const = 0;
};


#endif /* DEQUE_H */