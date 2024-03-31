// who:  Ali Mortada
// what: Test Linked/Array List
// why:  List ADT
// when: 3/31/24

#include <iostream>

#include "test.h"
#include "list.h"
#include "linked_list.h"
#include "array_list.h"

// #define SETUP List<int>* l{new LinkedList<int>}
// #define TEARDOWN delete l

#define SETUP List<int>* a{new ArrayList<int>}
#define TEARDOWN delete a

#define TEST_VALUE_1 5
#define TEST_VALUE_2 8
#define TEST_VALUE_3 10


void testInitialState();
void testAddFunction();
void testAtFunction();
void testRemoveFunction();
void testRemoveSpecificValue();
void testInsertFunction();
void testReplaceFunction();
void testContainsFunction();
void testClearFunction();

int main(int argc, char const *argv[])
{
    testInitialState();
    testAddFunction();
    testAtFunction();
    testRemoveFunction();
    testRemoveSpecificValue();
    testInsertFunction();
    testReplaceFunction();
    testContainsFunction();
    testClearFunction();

    return 0;
}

void testInitialState()
{
    SETUP;

    std::cout << "Testing initial state..." << std::endl;

    testTrue(a->empty(), "test list is initially empty");

    testTrue(a->size() == 0, "test if list's size is initially zero");

    TEARDOWN;
}

void testAddFunction() 
{
    SETUP;

    std::cout << "Testing add() function..." << std::endl;

    a->add(TEST_VALUE_1);

    testFalse(a->empty(), "list should not be empty after add");

    testTrue(a->size() == 1, "list size should be one after add");

    testTrue(a->at(1) == TEST_VALUE_1, "value added should be equal to the test value");

    TEARDOWN;
}

void testAtFunction()
{
    SETUP;

    std::cout << "Testing at() function..." << std::endl;

    a->add(TEST_VALUE_1);

    try
    {
        a->at(2);
        testFail("test that at function throws an exception at out of bounds error");
    }
    catch(const std::out_of_range&)
    {
        testPass("test that at function throws an exception at out of bounds error");
    }

    TEARDOWN;
}

void testRemoveFunction()
{
    SETUP;

    std::cout << "Testing remove() function..." << std::endl;

    a->add(TEST_VALUE_1);

    testTrue(TEST_VALUE_1 == a->remove(), "test that remove returns the item at beginning of list");
    testTrue(a->empty(), "list should be empty after removing its only item");

    TEARDOWN;
}

void testRemoveSpecificValue()
{
    SETUP;

    std::cout << "Testing removing a specific item..." << std::endl;

    a->add(TEST_VALUE_1);
    a->add(TEST_VALUE_2);
    a->add(TEST_VALUE_3);

    testTrue(TEST_VALUE_2 == a->remove(2), "test that removing item at specific index returns that item");

    TEARDOWN;
}

void testInsertFunction()
{
    SETUP;

    std::cout << "Testing insert() function..." << std::endl;

    a->add(TEST_VALUE_1);
    a->add(TEST_VALUE_2);
    a->add(TEST_VALUE_3);

    a->insert(TEST_VALUE_1, 3);
    testTrue(a->at(3) == TEST_VALUE_1, "test that item is inserted at specific position");

    try
    {
        a->insert(TEST_VALUE_2, 6);
        testFail("test that insert function throws an exception at out of bounds error");
    }
    catch(const std::out_of_range&)
    {
        testPass("test that insert function throws an exception at out of bounds error");
    }

    TEARDOWN;
}

void testReplaceFunction()
{
    SETUP;

    std::cout << "Testing replace() function..." << std::endl;

    a->add(TEST_VALUE_1);
    a->add(TEST_VALUE_2);
    a->add(TEST_VALUE_3);

    a->replace(TEST_VALUE_1, 2);
    testTrue(a->at(2) == TEST_VALUE_1, "test that item at a specific position is replaced with another item");

    try
    {
        a->replace(TEST_VALUE_2, 4);
        testFail("test that replace function throws an exception at out of bounds error");
    }
    catch(const std::out_of_range&)
    {
        testPass("test that replace function throws an exception at out of bounds error");
    }

    TEARDOWN;
}

void testContainsFunction()
{
    SETUP;

    std::cout << "Testing contains() function..." << std::endl;

    a->add(TEST_VALUE_1);
    a->add(TEST_VALUE_2);
    a->add(TEST_VALUE_3);

    testTrue(a->contains(TEST_VALUE_3), "test that the list contains a specific value");

    TEARDOWN;
}

void testClearFunction()
{
    SETUP;

    std::cout << "Testing clear() function..." << std::endl;

    a->add(TEST_VALUE_1);
    a->add(TEST_VALUE_2);
    a->add(TEST_VALUE_3);

    a->clear();
    testTrue(a->empty(), "list is empty after clearing it");

    TEARDOWN;
}
