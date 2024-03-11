#include "test.h"
#include "bucket_interface.h"
#include "array_bucket.h"

#define SETUP Bucket<int>* b{new ArrayBucket<int>}
#define TEARDOWN delete b
#define TEST_VALUE 5

void testInitialState();
void testAddFunction();
void testRemoveFunction();
void testRemoveQty();
void testContains();
void testRemoveSpecificItem();
void testRemoveSpecificItems();

int main(int argc, char const *argv[])
{
    
    testInitialState();
    testAddFunction();
    testRemoveFunction();
    testRemoveQty();
    testContains();
    testRemoveSpecificItem();
    testRemoveSpecificItems();

    return 0;
}

void testInitialState()
{
    SETUP;

    testTrue(b->empty(), "test bucket is initially empty");

    testTrue(b->size() == 0, "test if bucket's size is initially zero");

    try
    {
        b->remove();
        testFail("test that empty bucket throws an exception on remove");
    }
    catch(const std::logic_error&)
    {
        testPass("test that empty bucket throws an exception on remove");
    }

    TEARDOWN;
}

void testAddFunction()
{
    SETUP;

    b->add(TEST_VALUE);

    testFalse(b->empty(), "bucket should not be empty after add");

    testTrue(b->size() == 1, "bucket size should be one after add");

    TEARDOWN;
}

void testRemoveFunction()
{
    SETUP;

    b->add(TEST_VALUE);

    testTrue(TEST_VALUE == b->remove(), "test that remove returns the test value");

    TEARDOWN;
}

void testRemoveQty()
{
    SETUP;

    bool foundValues[10]{};

    for (int i = 0; i < 10; ++i)
        b->add(i);
    
    while (!b->empty())
        foundValues[b->remove()] = true;   
    
    for (size_t i = 0; i < 10; ++i)
    {
        if (!foundValues[i])
        {
            testFail("test remove added values");
            return;
        }
    }

    TEARDOWN;
}

void testContains()
{
    SETUP;

    b->add(TEST_VALUE);
    testTrue(b->contains(TEST_VALUE), "test contains a specific item");

    TEARDOWN;
}

void testRemoveSpecificItem()
{
    SETUP;

    b->add(TEST_VALUE);
    testTrue(b->remove(TEST_VALUE), "test removes a specific item");

    TEARDOWN;
}

void testRemoveSpecificItems()
{
    int size{5};
    int testValues[]{1, 2, 4, 4, 1};
    
    SETUP;

    for (auto &i : testValues)
        b->add(i);
    
    b->remove(4);
    testTrue(b->size() == 3, "test remove of multiple equal items");

    TEARDOWN;
}
