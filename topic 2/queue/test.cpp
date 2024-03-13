#include "test.h"
#include "simple_container.h"
#include "linked_queue.h"

#define SETUP SimpleContainer<int>* q{new LinkedQueue<int>}
#define TEARDOWN delete q
#define TEST_VAL 5

void testEmptyQueue();
void testAddItem();
void testPeekItem();
void testRemove();
void testRemoveOrder();
void testExceptionOnEmptyPeek();
void testExceptionOnEmptyRemove();

int main(int argc, char const *argv[])
{
    testEmptyQueue();
    testAddItem();
    testPeekItem();
    testRemove();
    testRemoveOrder();
    testExceptionOnEmptyPeek();
    testExceptionOnEmptyRemove();

    return 0;
}

void testEmptyQueue()
{
    SETUP;

    testTrue(q->empty(), "test queue is initially empty");

    TEARDOWN;
}

void testAddItem()
{
    SETUP;

    q->add(TEST_VAL);
    testTrue(!q->empty(), "test not empty after adding item");

    TEARDOWN;
}

void testPeekItem()
{
    SETUP;

    q->add(TEST_VAL);
    testTrue(q->peek() == TEST_VAL, "test peek returns an added item");
    
    TEARDOWN;
}

void testRemove()
{
    SETUP;

    q->add(TEST_VAL);
    q->remove();
    testTrue(q->empty(), "test empty after adding and removing item");

    TEARDOWN;
}

void testRemoveOrder()
{
    SETUP;
    size_t i;

    for (i = 0; i < TEST_VAL; ++i)
        q->add(i);
    
    for (i = 0; i < TEST_VAL; ++i)
    {
        if (q->peek() != i)
        {
            testFail("test ordering");
            break;
        }
        q->remove();
    }

    if (i == TEST_VAL) testPass("test ordering");

    TEARDOWN;
}

void testExceptionOnEmptyPeek()
{
    SETUP;

    try
    {
        q->peek();
        testFail("test throw logic_error on empty peek");
    }
    catch(const std::logic_error&)
    {
        testPass("test throw logic_error on empty peek");
    }
    
    TEARDOWN;
}

void testExceptionOnEmptyRemove()
{
    SETUP;

    try
    {
        q->remove();
        testFail("test throw logic_error on empty remove");
    }
    catch(const std::logic_error&)
    {
        testPass("test throw logic_error on empty remove");
    }

    TEARDOWN;
}
