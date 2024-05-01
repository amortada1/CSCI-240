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
    // testPreOrder();
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
}

void testLevelOrder()
{
    SETUP;

    std::cout << "Testing levelOrder() function..." << std::endl;
}
