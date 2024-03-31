#include <stdexcept>

#include "list.h"

#ifndef LINKED_LIST
#define LINKED_LIST

template<typename T>
class LinkedList : public List<T>
{
public:
    
    /* Constructor */
    LinkedList() : count{}, head{nullptr}, tail{nullptr} {}
    
    /* Destructor */
    ~LinkedList() {clear();}

    /** Add an item to the back of the list 
     * item: the item to add */
    void add(const T& item) override
    {
        // If list is empty, head and tail are equal
        if (empty())
        {
            head = tail = new Node{item, nullptr};
        }
        
        // Otherwise, add item to the end of the list
        tail->next = new Node{item, nullptr};
        tail = tail->next;
        
        ++count;
    }

    /** Add an item to the list at a certain position
     * item: the item to add
     * pos: the position (1 <= p <= n + 1) in which to insert the item 
     * Throws: std::out_of_range error if pos is out of range */ 
    void insert(const T& item, size_t pos) override
    {
        if (pos > count + 1) throw std::out_of_range("position is out of range!");

        Node* current{head};

        // Iterate to the position before the one we want to add to
        for (int i = 1; i < pos; ++i) current = current->next;

        // Create the node and rewire the previous node to point to it
        current->next = new Node{item, current->next};

        ++count;
    }   

    /** Remove and return an item at a certain position 
     * pos: the position of the item to remove and return (1 <= p <= n) */
    T remove(size_t pos) override
    {
        T rtnItem;
        Node* current{head};

        // Iterate to the position before the one we want to remove from
        for (int i = 1; i < pos; ++i) current = current->next;

        // Rewire previous node to go to the next node and delete the desired node
        Node* tmp{current->next};
        rtnItem = tmp->item;
        current->next = current->next->next;
        delete tmp;

        --count;

        return rtnItem;
    }

    /** Remove and return the item at the front of the list 
     * Param1: None */
    T remove() override 
    {
        T rtnItem{head->item};

        Node* tmp{head};
        head = head->next;
        delete tmp;

        --count;

        return rtnItem;
    }

    /** Replace an item in the list at a certain position
     * item: The item to add to the list
     * pos: The position of the item that gets replaced (1 <= p <= n)
     * Throws: std::out_of_range error if pos is out of range */ 
    void replace(const T& item, size_t pos) override 
    {
        Node* current{head};
        
        if (pos > count) throw std::out_of_range("position is out of range!");

        // Iterate to the position we want to replace
        for (int i = 1; i <= pos; ++i) current = current->next;

        // Replace that node's item with the one we want
        current->item = item;
    }

    /** Returns the item at a certain position but does not remove it
     * pos: the position of the item to be returned (1 <= p <= n) 
     * Return: the item at the position
     * Throws: std::out_of_range error if pos is out of range */ 
    T at(size_t pos) const override
    {
        Node* current{head};
        
        if (pos > count) throw std::out_of_range("position is out of range!");

        // Iterate to the position we want to return the item of
        for (int i = 1; i <= pos; ++i) current = current->next;

        return current->item;
    }

    /** Check for containment of an item
     * item: the search term
     * Return: true if the list contains the item or false otherwise */
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

    /** Returns the quantity of items stored in the list */
    size_t size() const override {return count;}

    /** Test if the list is empty  
     * Return true if the list is empty or false otherwise */
    bool empty() const override {return count == 0;}

    /** Clear the list */
    void clear() override
    {
        while (head != nullptr)
        {
            Node* tmp{head};
            head = head->next;
            delete tmp;
        }

        count = 0;
    }

private:
    struct Node 
    {
        T item;
        Node* next;
    };

    Node* head;
    Node* tail;
    size_t count;
};

#endif /* LINKED_LIST */
