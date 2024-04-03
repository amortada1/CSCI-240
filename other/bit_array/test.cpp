#include "test.h"
#include "bit_array.h"

#define ARRAY_SIZE 100
#define TEST_BIT_POS 55

void createArray();
void createArrayInitialTrue();
void setSingleBit();
void unsetSingleBit();
void testThrowExceptionOnOutOfBounds();

int main(int argc, char const *argv[])
{
    createArray();
    createArrayInitialTrue();
    setSingleBit();
    unsetSingleBit();
    testThrowExceptionOnOutOfBounds();

    return 0;
}

void createArray()
{
    BitArray b(ARRAY_SIZE);

    for (size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        if (b.getBit(i))
        {
            testFail("initial bitarray elements are false");
            return;
        }
    }
    
    testPass("initial bitarray elements are false");
}

void createArrayInitialTrue()
{
    BitArray b(ARRAY_SIZE, true);

    for (size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        if (!b.getBit(i))
        {
            testFail("initial bitarray elements are true");
            return;
        }
    }
    
    testPass("initial bitarray elements are true");
}

void setSingleBit()
{
    BitArray b(ARRAY_SIZE);
    b.setBit(TEST_BIT_POS, true);

    testTrue(b.getBit(TEST_BIT_POS), "test that the bit was set");

    for (size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i != TEST_BIT_POS && b.getBit(i))
        {
            testFail("test the other bits were not set");
            return;
        }
    }

    testPass("test the other bits were not set");
}

void unsetSingleBit()
{
    BitArray b(ARRAY_SIZE, true);
    b.setBit(TEST_BIT_POS, false);

    testFalse(b.getBit(TEST_BIT_POS), "test that the bit was unset");

    for (size_t i = 0; i < ARRAY_SIZE; ++i)
    {
        if (i != TEST_BIT_POS && !b.getBit(i))
        {
            testFail("test the other bits were set");
            return;
        }
    }

    testPass("test the other bits were set");
}

void testThrowExceptionOnOutOfBounds()
{
    BitArray b(ARRAY_SIZE);

    try
    {
        b.setBit(ARRAY_SIZE, false);
        testFail("set throws exception when position is out of bounds");
    }
    catch(const std::length_error&)
    {
        testPass("set throws exception when position is out of bounds");
    }
    
}
