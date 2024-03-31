// who:  Ali Mortada
// what: Test Linked/Array List
// why:  List ADT
// when: 3/31/24

#include <iostream>

#include "test.h"
#include "list.h"
#include "linked_list.h"

#define SETUP List<int>* l{new LinkedList<int>}
#define TEARDOWN delete l
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

    testTrue(l->empty(), "test list is initially empty");

    testTrue(l->size() == 0, "test if list's size is initially zero");

    TEARDOWN;
}

void testAddFunction() 
{
    SETUP;

    l->add(TEST_VALUE_1);

    testFalse(l->empty(), "list should not be empty after add");

    testTrue(l->size() == 1, "list size should be one after add");

    testTrue(l->at(1) == TEST_VALUE_1, "value added should be equal to the test value");

    TEARDOWN;
}

void testAtFunction()
{
    SETUP;

    l->add(TEST_VALUE_1);

    try
    {
        l->at(2);
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

    l->add(TEST_VALUE_1);

    testTrue(TEST_VALUE_1 == l->remove(), "test that remove returns the item at beginning of list");
    testTrue(l->empty(), "list should be empty after removing its only item");

    TEARDOWN;
}


void testRemoveSpecificValue()
{
    SETUP;

    l->add(TEST_VALUE_1);
    l->add(TEST_VALUE_2);
    l->add(TEST_VALUE_3);

    testTrue(TEST_VALUE_2 == l->remove(2), "test that removing item at specific index returns that item");

    TEARDOWN;
}

void testInsertFunction()
{
    SETUP;

    l->add(TEST_VALUE_1);
    l->add(TEST_VALUE_2);
    l->add(TEST_VALUE_3);

    l->insert(TEST_VALUE_1, 3);
    testTrue(l->at(3) == TEST_VALUE_1, "test that item is inserted at specific position");

    try
    {
        l->insert(TEST_VALUE_2, 6);
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

    l->add(TEST_VALUE_1);
    l->add(TEST_VALUE_2);
    l->add(TEST_VALUE_3);

    l->replace(TEST_VALUE_1, 2);
    testTrue(l->at(2) == TEST_VALUE_1, "test that item at a specific position is replaced with another item");

    try
    {
        l->replace(TEST_VALUE_2, 4);
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

    l->add(TEST_VALUE_1);
    l->add(TEST_VALUE_2);
    l->add(TEST_VALUE_3);

    testTrue(l->contains(TEST_VALUE_3), "test that the list contains a specific value");

    TEARDOWN;
}

void testClearFunction()
{
    SETUP;

    l->add(TEST_VALUE_1);
    l->add(TEST_VALUE_2);
    l->add(TEST_VALUE_3);

    l->clear();
    testTrue(l->empty(), "list is empty after clearing it");

    TEARDOWN;
}