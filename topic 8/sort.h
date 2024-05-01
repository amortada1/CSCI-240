#include <cstddef>
#include <cstdint>
#include <functional>
#include <vector>

#ifndef SORTER_H
#define SORTER_H

using Bucket = std::vector<uint32_t>;

template<typename T>
class Sort
{
    using Comparator = std::function<bool(const T&, const T&)>;
public:
    
    static void radixSort(uint32_t array[], size_t size)
    {
        Bucket buckets[2];
        buckets[0].reserve(size);
        buckets[1].reserve(size);
        const uint32_t MASK{1};
        size_t i, j, k;
        size_t v0idx, v1idx;
        
        for (i = 0; i < (sizeof(array[0]) << 3); ++i)
        {
            k = 0;
            v0idx = 0;
            v1idx = 0;

            for (j = 0; j < size; ++j)
                (((array[j] & (MASK << i)) == 0) ? buckets[0][v0idx++] : buckets[1][v1idx++]) = array[j];

            for (j = 0; j < v0idx; ++j)
                array[k++] = buckets[0][j];

            for (j = 0; j < v1idx; ++j)
                array[k++] = buckets[1][j];
        }
    }
    
    static void bubbleSort(T array[], size_t size, Comparator compare)
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

    static void selectionSort(T array[], size_t size, Comparator compare)
    {
        size_t extremeIdx;
        for (size_t i = 0; i < size - 1; ++i)
        {
            extremeIdx = extrema(array, i, size - 1, compare);
            if (extremeIdx != i) swap(array[i], array[extremeIdx]);
            
        }
        
    }

    static void insertionSort(T array[], size_t size, Comparator compare)
    {
        T temp;
        int i, j;
        for (i = 1; i < size; ++i)
        {
            temp = array[i];
            for (j = i - 1; j >= 0; --j)
            {
                if (compare(temp, array[j]))
                {
                    swap(array[j], array[j + 1]);
                    array[j] = temp;
                }
            }
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