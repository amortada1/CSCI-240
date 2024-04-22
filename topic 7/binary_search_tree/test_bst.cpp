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
    b.add(3);
    b.add(2);

    testTrue(b.getHeight() == 4, "test get height == 4");

    valuePtr = b.get(5);
    testTrue(valuePtr != nullptr && *valuePtr == 5, "test getting an existing value");

    valuePtr = b.get(20);
    testTrue(valuePtr == nullptr, "test getting a non-existing value");

    b.remove(5);

    return 0;
}

