#include <stdexcept>

#include "bucket_interface.h"

#ifndef LINKED_BUCKET_H
#define LINKED_BUCKET_H

template<typename T>
class LinkedBucket : public Bucket<T>
{
public:
    // constructor
    LinkedBucket() : count{}, head{nullptr} {}

    // destructor
    ~LinkedBucket() {clear();}

    // adds an item to the bucket
    void add(const T& item) override
    {
        head = new Node{item, head};
        ++count;
    }

    // removes and returns an arbitrary item from the bucket
    T remove() override  
    {
        T rtnItem;

        // Check if bucket is empty first, then continue with deletion
        if(empty()) throw std::logic_error("remove on an empty bucket! >:(");
        
        rtnItem = head->item;  // create temporary variable to return item's value after deleting
        
        removeHead();

        --count;

        return rtnItem;  
    }

    // removes all of the items that match the argument
    bool remove(const T& item) override 
    {
        bool removed{};
        Node* current{head};

        while (current != nullptr)
        {
            if (current->item == item) 
            {
                removed = true;
                --count;

                if (current == head)
                {
                    current = current->next;
                    removeHead();
                    continue;
                }

                current->item = head->item;
                removeHead();
            }

            current = current->next;
        }

        return removed;
    }

    // checks bucket for membership
    bool contains(const T& item) const override 
    {
        Node* current{head};
        while (current != nullptr)
        {
            if (current->item == item) return true;
            current = current->next;
        }

        return false;
    }

    // returns an array of items
    T* toArray() const override 
    {
        Node* current{head};
        T* rtnArray{new T[count]};

        for (size_t i = 0; i < count; ++i)
        {
            rtnArray[i] == current->item;
            current = current->next;
        }

        return rtnArray;
    }

    // empties the collection
    void clear() override 
    {
        while (head != nullptr) {removeHead();}
        count = 0;
    }

    // returns the number of items in the collection
    size_t size() const override {return count;}

    // returns true if empty and false otherwise
    bool empty() const override {return count == 0;}

private:
    struct Node
    {
        T item;
        Node* next;
    };

    Node* head;
    size_t count;

    // Helper function to remove head
    void removeHead()
    {
        Node* tmp{head};
        head = head->next;
        delete tmp;
    }

};

#endif