#include "set.h"
#include "hash_set.h"
#include "test.h"

#define TEST_HASHSET HashSet<int>* h{new HashSet<int>([](int a){return abs(a) % 223;})}
#define TEST_VAL 5

void testAdd();
void testRemove();

int main(int argc, char const *argv[])
{
    testAdd();
    testRemove();

    return 0;
}

void testAdd()
{
    TEST_HASHSET;

    std::cout << "Testing add() function..." << std::endl;

    testTrue(h.size() == 0, "test size is zero before add");
    testTrue(h.empty(), "test empty before add");

    h.add(TEST_VAL);
    testTrue(h.size() > 0, "test size is greater than zero after add");
    testFalse(h.empty(), "test not empty after add");
}

void testRemove()
{
    TEST_HASHSET;

    std::cout << "Testing remove() function..." << std::endl;

    h.add(TEST_VAL);
    h.remove(TEST_VAL);

    testFalse(h.contains(TEST_VAL), "test that student is not in bucket after removing");
    testTrue(h.empty(), "test that bucket is empty after remove operation");
}