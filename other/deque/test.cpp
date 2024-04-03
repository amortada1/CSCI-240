#include "test.h"
#include "deque.h"
#include "linked_deque.h"

#define SETUP Deque<int>* d{new LinkedDeque<int>}
#define TEARDOWN delete d
#define TEST_VAL_1 5
#define TEST_VAL_2 6

void testInitialCondition();
void testEnqueueBack();
void testEnqueueFront();

int main()
{
    testInitialCondition();
    testEnqueueBack();
    //testEnqueueFront();
    
    return 0;
}

void testInitialCondition()
{
    SETUP;

    std::cout << "Testing initial condition:" << std::endl;

    testTrue(d->empty(), "test that the deque is initially empty");

    TEARDOWN;
}

void testEnqueueBack()
{
    SETUP;

    std::cout << "Testing enqueueBack():" << std::endl;

    d->enqueueBack(TEST_VAL_1);
    testTrue(d->back() == TEST_VAL_1, "test that the back value is the test value");
    testTrue(d->front() == TEST_VAL_1, "test that the front value is the test value");
    testFalse(d->empty(), "deque should not be empty after adding a value");

    d->enqueueBack(TEST_VAL_2);
    testTrue(d->back() == TEST_VAL_2, "test that the back value is the new test value added");
    testFalse(d->back() == TEST_VAL_1, "test that the old test value is no longer at the back of the deque");
    testTrue(d->front() == TEST_VAL_1, "test that the old value is now at the front of the deque");
    testFalse(d->front() == TEST_VAL_2, "test that the new test value is not at the front of the deque");

    TEARDOWN;
}
/*
void testEnqueueFront()
{
    SETUP;

    std::cout << "Testing enqueueFront():" << std::endl;

    d->enqueueFront(TEST_VAL_1);
    testTrue(d->front() == TEST_VAL_1, "test that the front value is the test value");
    testTrue(d->back() == TEST_VAL_1, "test that the back value is the test value");
    testFalse(d->empty(), "deque should not be empty after adding a value");

    d->enqueueFront(TEST_VAL_2);
    testTrue(d->front() == TEST_VAL_2, "test that the front value is the new test value added");
    testFalse(d->front() == TEST_VAL_1, "test that the old test value is no longer at the front of the deque");
    testTrue(d->back() == TEST_VAL_1, "test that the old value is now at the back of the deque");
    testFalse(d->back() == TEST_VAL_2, "test that the new test value is not at the back of the deque");

    TEARDOWN;
}
*/
