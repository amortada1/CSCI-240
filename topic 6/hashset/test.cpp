#include "bucket_set.h"
#include "test.h"

void testAdd();
void testContains();
void testRemove();
void testGet();
void testGetThrowsException();

#define TEST_STUDENT Student s{"a12345", "Fred", 2.6}
#define TEST_BUCKET BucketSet<Student> b

struct Student
{
    std::string id;
    std::string name;
    double gpa;

    bool operator==(const Student& other) const {return id == other.id;}
    bool operator!=(const Student& other) const {return !(*this == other);}
};

int main(int argc, char const *argv[])
{
    BucketSet<Student> buckets[103];
    // Student s1{"a12345", "cunt", {}};
    // Student s2{"a123456", "hjkaldshf", 3.75};
    // std::cout << std::boolalpha << (s1 == s2) << std::endl;

    testAdd();
    testContains();
    testRemove();
    testGet();
    testGetThrowsException();

    return 0;
}

void testAdd()
{
    TEST_BUCKET;
    TEST_STUDENT;

    std::cout << "Testing add() function..." << std::endl;

    testTrue(b.size() == 0, "test size is zero before add");
    testTrue(b.empty(), "test empty before add");

    b.add(s);
    testTrue(b.size() > 0, "test size is greater than zero after add");
    testFalse(b.empty(), "test not empty after add");
}

void testContains()
{
    TEST_BUCKET;
    TEST_STUDENT;

    std::cout << "Testing contains() function..." << std::endl;

    testFalse(b.contains(s), "check empty bucket does not contain the test student");
    b.add(s);
    testTrue(b.contains(s), "check that bucket does contain the test student after adding");
}

void testRemove()
{
    TEST_BUCKET;
    TEST_STUDENT;

    std::cout << "Testing remove() function..." << std::endl;

    b.add(s);
    b.remove(s);

    testFalse(b.contains(s), "test that student is not in bucket after removing");
    testTrue(b.empty(), "test that bucket is empty after remove operation");
}

void testGet()
{
    TEST_BUCKET;
    TEST_STUDENT;

    std::cout << "Testing get() function..." << std::endl;

    b.add(s);

    testTrue(s == b.get(s), "test that we can get an added student");
}

void testGetThrowsException()
{
    TEST_BUCKET;
    TEST_STUDENT;

    try
    {
        b.get(s);
        testFail("test that get throws exception if student does not exist");
    }
    catch (const std::logic_error&)
    {
        testPass("test that get throws exception if student does not exist");
    }
    
}