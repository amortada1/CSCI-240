#include "deque.h"

#ifndef LINKED_DEQUE_H
#define LINKED_DEQUE_H

template<typename T>
class LinkedDeque : public Deque<T>
{
public:
    LinkedDeque() : head{nullptr}, tail{nullptr} {}

    ~LinkedDeque() override {while (!empty()) dequeueBack();}

    void enqueueBack(const T& item) override
    {
        Node* ptr = new Node{item, nullptr};

        (empty() ? head : tail->next) = ptr;
        
        tail = ptr;
    }

    void enqueueFront(const T& item) override
    {
        Node* ptr = new Node{item, nullptr};

        (empty() ? tail : head->next) = ptr;

        head = ptr;
    }

    void dequeueBack() override
    {
        Node* current{head};

        while (current->next->next != nullptr)
            current = current->next;

        Node* tmp{tail};
        current->next = nullptr;
        delete tmp;
    }

    void dequeueFront() override
    {
        Node* ptr{head};
        head = head->next;
        delete ptr;

        if(empty()) tail = nullptr;
    }

    T front() const override {return head->item;}

    T back() const override {return tail->item;}

    bool empty() const override {return head == nullptr;}

private:
    struct Node
    {
        T item;
        Node* next;
    };

    Node* head;
    Node* tail;
};

#endif /* LINKED_DEQUE_H */