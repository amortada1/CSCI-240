#include <cstddef>
#include <cstdint>

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

class BitArray
{
public:
    BitArray(size_t);
    BitArray(size_t, bool);
    void setBit(size_t, bool);
    bool getBit(size_t) const;
    void clear(bool);
    void clear(); // unsets all bits
    const uint8_t* getArray();
    size_t getByteQty();

private:
    void setBit(size_t);
    void unsetBit(size_t);

    size_t byteQty;
    size_t bitQty;
    uint8_t* array;

};

#endif