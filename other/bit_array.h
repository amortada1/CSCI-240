#include <cstddef>
#include <cstdint>

#ifndef BIT_ARRAY_H
#define BIT_ARRAY_H

class BitArray
{
public:
    BitArray(size_t);
    void setBit(size_t, bool);
    bool getBit(size_t) const;
    void setAll(bool);

private:
    void setBit(size_t);
    void unsetBit(size_t);

    size_t byteQty;
    size_t bitQty;
    uint8_t* array;

};

#endif