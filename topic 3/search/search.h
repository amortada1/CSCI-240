#include <cstddef>

#ifndef SEARCH_H
#define SEARCH_H

template<typename T>
class Searcher
{
public:
    // assumes that array is sorted
    static int binSearch(const T array[], int count, const T& term)
    {
        if (count < 1) return -1;

        // call the private recursive function
        return binSearch(array, 0, count - 1, term);
    }

private:
    static int binSearch(const T array[], int start, int end, const T& term) 
    {
        int mid;
        if (start > end) return -1;
        mid = (start + end) >> 1;   // shifting bit to the right by 1 divides by 2

        if (array[mid] == term) return mid;

        if (array[mid] < term) 
            return binSearch(array, mid + 1, end, term);

        return binSearch(array, start, mid - 1, term);
    }
};

#endif