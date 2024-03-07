#include <string>

#ifndef COLLECTION_H
#define COLLECTION_H

template<typename T>
struct Collection
{
    // adds an item to the container
    virtual void add(const T&) = 0;

    // removes an item from the container
    // does not return it
    virtual void remove() = 0;

    // gets an item from the container
    // does not remove it
    virtual T get() const = 0;

    // return true if empty or false otherwise
    virtual bool empty() const = 0;

    // returns string representation of the collection
    virtual std::string print() const = 0;
};


#endif