#include <cstddef>

#ifndef STACK_H
#define STACK_H

#define INIT_STACK_SIZE 16
#define SCALING_FACTOR 2

class Stack 
{
public:
    Stack();
    ~Stack();
    void push(int);
    void pop();
    int peek();
    bool empty();

private:
    size_t top;
    size_t currentSize;
    int* array;

    void resize();
};

#endif