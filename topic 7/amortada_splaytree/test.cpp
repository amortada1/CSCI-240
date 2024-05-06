#include "splaytree.h"
#include "test.h"

#define SETUP SplayTree<int> s

void testInitialState();
void testAdd();
void testRemove();
void testPreOrder();
void testInOrder();
void testPostOrder();
void testLevelOrder();

int main(int argc, char const *argv[])
{
    testInitialState();
    testAdd();
    testRemove();
    testPreOrder();
    // testInOrder();
    // testPostOrder();
    // testLevelOrder();
    
    return 0;
}

void testInitialState()
{
    SETUP;
    
    std::cout << "Testing initial state..." << std::endl;

    testTrue(s.empty(), "test that splay tree is initially empty");

    testTrue(s.size() == 0, "test that splay tree's size is initially zero");
}

void testAdd()
{
    SETUP;

    std::cout << "Testing add() function..." << std::endl;

    s.add(5);
    
    testTrue(s.contains(5), "test that splay tree contains added value");

    s.add(10);

    testTrue(s.contains(10), "test that splay tree contains a second added value");
}

void testRemove()
{
    SETUP;

    std::cout << "Testing remove() function..." << std::endl;

    s.add(5);
    s.add(10);
    s.remove(10);

    testFalse(s.contains(10), "test that splay tree does not contain a value after removing it");
}

void testPreOrder()
{
    SETUP;

    std::cout << "Testing preOrder() function..." << std::endl;

    s.add(5);
    s.add(10);
    s.add(0);
    s.add(19);
    s.add(3);
    s.add(2);

    int* array = s.preOrder();

    for (size_t i = 0; i < 6; ++i)
    {
        std::cout << array[i] << " ";
    }
    
    std::cout << std::endl;
}

void testInOrder()
{
    SETUP;

    std::cout << "Testing inOrder() function..." << std::endl;
}

void testPostOrder()
{
    SETUP;

    std::cout << "Testing postOrder() function..." << std::endl;

    s.add(5);
    s.add(10);
    s.add(0);
    s.add(19);
    s.add(3);
    s.add(2);

    int* array = s.postOrder();

    for (size_t i = 0; i < 6; ++i)
    {
        std::cout << array[i] << " ";
    }
    
    std::cout << std::endl;
}

void testLevelOrder()
{
    SETUP;

    std::cout << "Testing levelOrder() function..." << std::endl;
}
