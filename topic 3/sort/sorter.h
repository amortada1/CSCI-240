#include <cstddef>
#include <functional>

#ifndef SORTER_H
#define SORTER_H

template<typename T>
class Sorter
{
public:
    static void bubbleSort(T array[], size_t size, std::function<bool(const T&, const T&)> compare)
    {
        bool swapped;
        for (size_t i = size - 1; i > 0; --i)
        {
            swapped = false;
            for (size_t j = 0; i < i; ++j)
            {
                if (!compare(array[j], array[j+1]))
                {
                    swap(array[j], array[j+1]);
                    swapped = true;
                }
            }
            if (!swapped) return;
        }
    }

    static void selectionSort(T array[], size_t size, std::function<bool(const T&, const T&)> compare)
    {
        size_t extremeIdx;
        for (size_t i = 0; i < size - 1; ++i)
        {
            extremeIdx = extrema(array, i, size - 1, compare);
            if (extremeIdx != i) swap(array[i], array[extremeIdx]);
            
        }
        
    }

private:
    static void swap(T& a, T& b)
    {
        T temp{a};
        a = b;
        b = temp;
    }

    static size_t extrema(T array[], size_t start, size_t end, std::function<bool(const T&, const T&)> compare)
    {
        size_t extremeIdx{start};
        
        for (size_t i = start + 1; i <= end; ++i)
            if (compare(array[i], array[extremeIdx])) 
                extremeIdx = i;
        
        return extremeIdx;
    }

};

#endif