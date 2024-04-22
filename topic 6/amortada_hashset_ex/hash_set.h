#include <cstddef>
#include <functional>

#include "set.h"

#ifndef HASH_SET_H
#define HASH_SET_H

#define DEFAULT_SIZE 223
#define NUM_ATTEMPTS 15
#define LOAD_CAPACITY 0.75

enum Prober
{
    LINEAR,
    QUADRATIC
};


template<typename T>
class HashSet : public Set<T>
{

public:

    // constructors
    HashSet(std::function<size_t(const T&)> hashcode) 
        : count{}, currentSize{DEFAULT_SIZE}, store{new T[DEFAULT_SIZE], hashcodes{new size_t[DEFAULT_SIZE]}} 
    {
        
    }

    /** adds an item to the set. 
     *  Replaces the item if it already exists
    */
    void add(const T& item)
    {
        if (count >= currentSize * LOAD_CAPACITY) resize();

        if (contains(item)) return;

        // create a hashcode for the item and store it
        store[++count] = item;
        hashcodes[count] = hashcode(item);
    }

    /** removes the item from the set
     *  throws a runtime error if the item is not a member
    */
    T remove(const T& item)
    {
        if (!contains(item)) throw std::runtime_error("item is not a member of the set");
        
        
    }

    /** returns true if the set is empty or false otherwise */
    bool empty() const {return count == 0;}

    /** returns true if the item is a member or false otherwise */
    bool contains(const T& item) const
    {
        bool found{};
        size_t itemhc = hashcode(item);

        for (size_t i = 0; i < count; ++i)
            if (store[i] == itemhc)
                found = true;
        
        return false;
    }

    /** returns the number of members in the set */
    size_t size() const {return count;}

private:
    T* store;
    size_t* hashcodes;
    size_t currentSize;
    size_t count;
    std::function<size_t(const T&)> hashcode;
        
    enum Status
    {
        OCCUPIED,
        EMPTY,
        FREE
    };

    int linearProbe(size_t hcode)
    {
        for (size_t i = 0; i < NUM_ATTEMPTS; ++i)
            if ((store[hcode + i].Status) % currentSize) // if status is not zero (occupied)
                return (hcode + i) / currentSize;
    
        return -1;
    }

    int quadraticProbe(size_t hcode)
    {
        size_t i = 0;
        size_t j = i;
        while (i < NUM_ATTEMPTS) 
        {
            if ((store[hcode + j].Status) % currentSize) // if status is not zero (occupied)
                return (hcode + j) / currentSize;

            ++i;
            j = i * i;
        }

        return -1;
    }

    // function to see if a number is prime
    bool isPrime(size_t& num)
    {
        if (n % 2 == 0 || n % 3 == 0) return false;

        for (size_t i = 5; i * i <= num ; i = i + 6)
            if (num % i == 0 || n % (i + 2) == 0)
                return false;

        return true;
    }
    
    // function to calculate the next prime when resizing
    size_t calculateNextPrime(size_t& num) 
    {
        size_t prime{num};
        bool found{};

        while (!found)
        {
            ++prime;
            if (isPrime(prime))
                found = true;
        }

        return prime;
    }

    // function to resize set when certain capacity has filled up
    void resize() 
    {
        currentSize = calculateNextPrime(currentSize);

        T* newStore{new T[currentSize]};
        size_t* newHashcodes{new size_t[currentSize]};

        for (size_t i = 0; i < count; ++i)
        {
            newStore[i] = store[i];
            // re hash the items
            newHashcodes[i] = hashcode(hashcodes[i]);
        }

        delete[] store;
        delete[] hashcodes;
        store = newStore;
        hashcodes = newHashcodes;
    }

};

#endif /* HASH_SET_H */
