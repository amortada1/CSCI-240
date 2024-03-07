#include <iostream>

#include "func.h"

int main(int argc, char const *argv[])
{
    int a[]{1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size{sizeof a / sizeof a[0]}; // we divide by sizeof the first element to adjust size to the type of the array

    std::cout << &size << std::endl; // ampersand in expression gets the address of whatever follows it
    std::cout << a << std::endl; // since it is an array, it will just print out the address
    std::cout << *a << std::endl; // so we use the dereference operator, which gives the actual value of the first element in array

    printIntArray(a, size); 

    std::cout << std::endl;

    return 0;
}


void printIntArray(int array[], size_t size)
{
    char comma{' '};

    std::cout << '[';
    for (size_t i = 0; i < size; ++i)
    {
        std::cout << comma << array[i];
        comma = ',';
    }
    std::cout << " ]";
}
