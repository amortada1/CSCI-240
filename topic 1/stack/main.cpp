#include <iostream>

#include "stack.h"

int main(int argc, char const *argv[])
{
    Stack s;

    for (size_t i = 10; i; --i)
        push(i, s);
    
    while (!empty(s))
    {
        std::cout << peek(s) << " ";
        pop(s);
    }
    
    std::cout << std::endl;

    return 0;
}
