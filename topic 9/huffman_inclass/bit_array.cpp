#include <stdexcept>

#include "bit_array.h"

#define ALL_ZERO 0   // all bits set to 0
#define ALL_ONE 0xFF // all bits set to 1
#define MASK 0b00000001
#define BIT_MASK 0b111

BitArray::BitArray(size_t bitQty) : BitArray(bitQty, false) {}

BitArray::BitArray(size_t, bool initState)
    : bitQty{bitQty}, byteQty{(bitQty >> 3) + 1}, array{new uint8_t[byteQty]} 
{
    clear(initState);
}

void BitArray::setBit(size_t pos, bool state)
{
    if (pos >= bitQty) throw std::length_error("position out of bounds!");

    state ? setBit(pos) : unsetBit(pos);
}

void BitArray::setBit(size_t pos)
{
    if (pos >= bitQty) throw std::length_error("position out of bounds!");
    
    size_t bytePos{pos >> 3};
    size_t bitPos{pos & BIT_MASK};

    array[bytePos] |= MASK << bitPos;
}

void BitArray::unsetBit(size_t pos)
{
    if (pos >= bitQty) throw std::length_error("position out of bounds!");
    
    size_t bytePos{pos >> 3};
    size_t bitPos{pos & BIT_MASK};

    array[bytePos] &= ~(MASK << bitPos);
}

bool BitArray::getBit(size_t pos) const
{
    if (pos >= bitQty) throw std::length_error("position out of bounds!");
    
    size_t bytePos{pos >> 3};
    size_t bitPos{pos & BIT_MASK};
    
    return array[bytePos] & (MASK << bitPos);
}

void BitArray::clear(bool state)
{
    for (size_t i = 0; i < byteQty; ++i)
        array[i] = state ? ALL_ONE : ALL_ZERO;
}

void BitArray::clear() {clear(false);}

const uint8_t* BitArray::getArray() {return array;}

size_t BitArray::getByteQty() {return byteQty;}