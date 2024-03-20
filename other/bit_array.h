#include <cstddef>
#include <cstdint>

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

class BitArray
{
public:
    BitArray(size_t);
    void setBit(size_t, bool);
    void unsetBit(size_t);
    bool getBit(size_t) const;
    void setAll(bool);

private:
    size_t byteQty;
    size_t bitQty;
    uint8_t* array;

};

#endif