#include "test.h"
#include "binary_search_tree.h"

int main(int argc, char const *argv[])
{
    const int* valuePtr;
    // no need for pointer here since we aren't implementing an interface
    BinarySearchTree<int> b;

    b.add(5);
    b.add(10);
    b.add(0);
    b.add(19);

    valuePtr = b.get(5);
    testTrue(valuePtr != nullptr && *valuePtr == 5, "test getting an existing value");

    valuePtr = b.get(20);
    testTrue(valuePtr == nullptr, "test getting a non-existing value");

    return 0;
}

