#include <stdexcept>

#include "bucket_interface.h"

#ifndef LINKED_BUCKET_H
#define LINKED_BUCKET_H

template<typename T>
class LinkedBucket : public Bucket<T>
{
public:
    // constructor
    LinkedBucket() : head{nullptr} {}

    // destructor
    ~LinkedBucket() {while (!empty()) remove();}

    // adds an item to the bucket
    void add(const T& item) override
    {
        head = new Node{item, head};
    }

    // removes and returns an arbitrary item from the bucket
    T remove() override  
    {
        if(empty()) throw std::logic_error("remove on an empty bucket! >:(");

        Node* tmp{head};
        T rtnItem = head->item;  // create temporary variable to return item's value after deleting
        head = head->next;
        delete tmp;
        return rtnItem;  
    }

    // removes all of the items that match the argument
    bool remove(const T& item) override 
    {
        bool removed{};
        Node* current{head};

        // iterate thru linked list and compare items
        while (current != nullptr)
        {
            if (current->item == item)  // if current node's item matches argument, remove it
            {
                Node* tmp{current};
                current = current->next;
                delete tmp;
                removed = true;
            }
            else
            {
                current = current->next;  // otherwise, traverse to the next node
            }
        }

        delete current;
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

        delete current;
        return false;
    }

    // returns an array of items
    T* toArray() const override 
    {
        size_t num{count()};
        Node* current{head};
        T* rtnArray{new T[num]};
        
        for (size_t i = 0; i < num; ++i, current = current->next)
        {
            rtnArray[i] == current->item;
        }

        delete current;
        return rtnArray;
    }

    // empties the collection
    void clear() override 
    {
        Node* current{head};
        while (current->next != nullptr)
        {
            Node* tmp{current};
            current = current->next;
            delete tmp;
        }

        delete current;
    }

    // returns the number of items in the collection
    size_t size() const override {return count();}

    // returns true if empty and false otherwise
    bool empty() const override {return head == nullptr;}

private:
    struct Node
    {
        T item;
        Node* next;
    };

    Node* head;

    // Helper function to find the size of linked list
    size_t count() const
    {
        size_t i{};
        Node* current{head};
        while (current != nullptr)
        {
            ++i;
            current = current->next;
        }

        delete current;
        return i;
    }
};

#endif