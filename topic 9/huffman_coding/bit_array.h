#include <cstddef>
#include <cstdint>
#include <stdexcept>

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

#define ALL_ZERO 0   // all bits set to 0
#define ALL_ONE 0xFF // all bits set to 1
#define MASK 0b00000001
#define BIT_MASK 0b111

class BitArray
{
public:
    BitArray(size_t bitQty) : BitArray(bitQty, false) {}

    BitArray(size_t, bool initState)
    : bitQty{bitQty}, byteQty{(bitQty >> 3) + 1}, array{new uint8_t[byteQty]} 
    {
        clear(initState);
    }

    void setBit(size_t pos, bool state)
    {
        if (pos >= bitQty) throw std::length_error("position out of bounds!");

        state ? setBit(pos) : unsetBit(pos);
    }

    bool getBit(size_t pos) const
    {
        if (pos >= bitQty) throw std::length_error("position out of bounds!");
        
        size_t bytePos{pos >> 3};
        size_t bitPos{pos & BIT_MASK};
        
        return array[bytePos] & (MASK << bitPos);
    }

    void clear(bool state)
    {
        for (size_t i = 0; i < byteQty; ++i)
            array[i] = state ? ALL_ONE : ALL_ZERO;
    }

    void clear() {clear(false);}

private:
    void setBit(size_t pos)
    {
        if (pos >= bitQty) throw std::length_error("position out of bounds!");
        
        size_t bytePos{pos >> 3};
        size_t bitPos{pos & BIT_MASK};

        array[bytePos] |= MASK << bitPos;
    }

    void unsetBit(size_t pos)
    {
        if (pos >= bitQty) throw std::length_error("position out of bounds!");
        
        size_t bytePos{pos >> 3};
        size_t bitPos{pos & BIT_MASK};

        array[bytePos] &= ~(MASK << bitPos);
    }

    size_t byteQty;
    size_t bitQty;
    uint8_t* array;

};

#endif