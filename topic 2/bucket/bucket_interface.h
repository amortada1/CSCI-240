#include <cstddef>

#ifndef BUCKET_INTERFACE_H
#define BUCKET_INTERFACE_H

/*
 * Interface for a bucket container
 * Type T must have the equality operator implemented/overloaded
*/
template<typename T>
struct Bucket
{
    virtual ~Bucket() {}

    // adds an item to the collection
    virtual void add(const T&) = 0;  // const bc we dont want param to be changed, reference bc it may be a large data structure
    
    // removes and returns an arbitrary item from the collection
    virtual T remove() = 0;

    // removes all of the items that match the argument 
    virtual bool remove(const T&) = 0;

    // checks collection for membership
    virtual bool contains(const T&) const = 0;

    // returns an array of items
    virtual T* toArray() const = 0;

    // empties the collection
    virtual void clear() = 0;

    // returns the number of items in the collection
    virtual size_t size() const = 0;

    // returns true if empty and false otherwise
    virtual bool empty() const = 0;
};


#endif