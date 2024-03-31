#include <stdexcept>
#include <iostream>

#include "list.h"

#ifndef ARRAY_LIST
#define ARRAY_LIST

#define INIT_SIZE 16
#define RESIZE_BY 16

template<typename T>
class ArrayList : public List<T>
{
public:
    /* Constructor */
    ArrayList() : count{}, currentSize{INIT_SIZE}, array{new T[INIT_SIZE]} {}

    /* Destructor */
    ~ArrayList() {delete[] array;}

    /** Add an item to the back of the list 
     * item: the item to add */
    void add(const T& item) override
    {
        if (count == currentSize) resize();

        array[count++] = item;
    }

    /** Add an item to the list at a certain position
     * item: the item to add
     * pos: the position (1 <= p <= n + 1) in which to insert the item 
     * Throws: std::out_of_range error if pos is out of range */ 
    void insert(const T& item, size_t pos) override
    {
        if (pos > count + 1 || pos < 1) throw std::out_of_range("position is out of range");

        if (count == currentSize) resize();

        size_t i;
        T* newArray{new T[currentSize]};

        // Copy old contents into new array up until insertion index
        for (i = 0; i < pos - 1; ++i) newArray[i] = array[i];
        // Insert item at insertion index
        newArray[i++] = item;
        // Copy the rest of the old array into the new array
        for (; i <= count + 1; ++i) newArray[i] = array[i - 1];

        delete[] array;
        array = newArray;

        ++count;
    }
    
    /** Remove and return an item at a certain position 
     * pos: the position of the item to remove and return (1 <= p <= n) */
    T remove(size_t pos) override
    {
        T rtnItem{array[pos - 1]};
        size_t i;
        T* newArray{new T[currentSize]};

        // Copy old contents into new array up until remove index
        for (i = 0; i < pos - 1; ++i) newArray[i] = array[i];
        // Copy everything after the remove index into the new array
        for (i = pos - 1; i <= count; ++i) newArray[i] = array[i + 1];

        delete[] array;
        array = newArray;
        
        return rtnItem;
    }

    /** Remove and return the item at the front of the list 
     * Param1: None */
    T remove() override
    {
        --count;
        return remove(1);
    }

    /** Replace an item in the list at a certain position
     * item: The item to add to the list
     * pos: The position of the item that gets replaced (1 <= p <= n)
     * Throws: std::out_of_range error if pos is out of range */ 
    void replace(const T& item, size_t pos) override
    {
        if (pos > count || pos < 1) throw std::out_of_range("position is out of range");

        array[pos - 1] = item; 
    }

    /** Returns the item at a certain position but does not remove it
     * pos: the position of the item to be returned (1 <= p <= n) 
     * Return: the item at the position
     * Throws: std::out_of_range error if pos is out of range */ 
    T at(size_t pos) const override
    {
        if (pos > count || pos < 1) throw std::out_of_range("position is out of range");

        return array[pos - 1];
    }

    /** Check for containment of an item
     * item: the search term
     * Return: true if the list contains the item or false otherwise */
    bool contains(const T& item) const override
    {
        for (size_t i = 1; i <= count; ++i)
            if (array[i] == item) return true;
        
        return false;
    }

    /** Returns the quantity of items stored in the list */
    size_t size() const override {return count;}

    /** Test if the list is empty  
     * Return true if the list is empty or false otherwise */
    bool empty() const override {return count == 0;}

    /** Clear the list */
    void clear() override {count = 0;}

private:
    T* array;
    size_t count;
    size_t currentSize;

    void resize() 
    {
        size_t newSize{currentSize + RESIZE_BY};
        T* newArray{new T[newSize]};

        for (size_t i = 1; i <= currentSize; ++i)
            newArray[i] = array[i];

        delete[] array;
        currentSize = newSize;
        array = newArray;
    }
};

#endif /* ARRAY_LIST */

