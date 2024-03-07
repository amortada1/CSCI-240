#include <stdexcept>

#include "stack.h"

Stack::Stack() : top{0}, array{new int[INIT_STACK_SIZE]}, currentSize{INIT_STACK_SIZE} {} // this way builds the variables uninitialized to save memory

Stack::~Stack() {delete[] array;}

void Stack::push(int val)
{
    if (top == currentSize)
        resize();
    array[top++] = val;
}

void Stack::pop()
{
    if (empty())
        throw std::logic_error("pop on an empty stack");
    --top;
}

int Stack::peek()
{
    if (empty())
        throw std::logic_error("peel on an empty stack");
    return array[top - 1];
}

bool Stack::empty() {return top == 0;}

void Stack::resize()
{
    size_t newSize{currentSize * SCALING_FACTOR};
    int* newArray{new int[newSize]};

    for (size_t i = 0; i < currentSize; ++i)
        newArray[i] = array[i];

    currentSize = newSize;
    delete[] array;
    array = newArray;
}