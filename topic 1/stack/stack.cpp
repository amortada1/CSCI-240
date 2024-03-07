#include "stack.h"

void push(int val, Stack& stack)
{
    stack.stack[stack.top++] = val;  // post increment used bc it needs to be done at the end
}

void pop(Stack& stack) { --stack.top; } // pre increment and decrement has better performance than post    

int peek(const Stack& stack)
{
    return stack.stack[stack.top - 1]; // minus one bc position starts at 0? 
}

bool empty(Stack& stack) { return stack.top == 0; }
