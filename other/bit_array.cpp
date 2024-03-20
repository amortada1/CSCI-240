#include "bit_array.h"

#define ALL_ZERO 0   // all bits set to 0
#define ALL_ONE 0xFF // all bits set to 1
#define MASK 0b00000001

BitArray::BitArray(size_t bitQty) 
    : bitQty{bitQty}, byteQty{(bitQty >> 3) + 1}, array{new uint8_t[byteQty]} {}

void BitArray::setBit(size_t pos, bool state)
{
    state ? setBit(pos) : unsetBit(pos);
}

void BitArray::setBit(size_t pos)
{
    size_t bytePos{pos >> 3};
    size_t bitPos{pos % 8};

    array[bytePos] |= MASK << bitPos;
}

void BitArray::unsetBit(size_t pos)
{
    size_t bytePos{pos >> 3};
    size_t bitPos{pos % 8};

    array[bytePos] &= ~(MASK << bitPos);
}

bool BitArray::getBit(size_t pos) const
{
    size_t bytePos{pos >> 3};
    size_t bitPos{pos % 8};
    
    return array[bytePos] & (MASK << bitPos);
}

void BitArray::setAll(bool state)
{
    for (size_t i = 0; i < byteQty; ++i)
        array[i] = state ? ALL_ONE : ALL_ZERO;
}
