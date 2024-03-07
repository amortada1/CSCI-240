#include <iostream>

#include "stack.h"

int main(int argc, char const *argv[])
{
    Stack stack;

    for (size_t i = 0; i <= 100; ++i)
        stack.push(i);

    while (!stack.empty())
    {
        std::cout << stack.peek() << ' ';
        stack.pop();
    }
    
    return 0;
}