#include <cstddef>
#include <algorithm>

#include "linked_queue.h"

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

template<typename T>
class SplayTree
{
public:
    SplayTree() : root{nullptr} {}
    ~SplayTree() {}

    void add(const T& item)
    {
        // if (empty())
        // {
        //     root = new Node{item, nullptr, nullptr, nullptr};
        //     return;
        // }
        
        // add(root, item);
        // ++count;

        // splay(find(root, item)); // need to splay newly added node

        Node* newNode{new Node{item}};

        if (root == nullptr)
            root = newNode;
        insertNode(root, newNode);

        splay(newNode);
    }

    void remove(const T& item)
    {
        Node* targetNode{find(root, item)};

        if (targetNode != nullptr)
        {
            splay(targetNode); // splay node of item we need to find
            deleteNode(root); 
        }
        
    }

    const T* get(const T& item)
    {
        Node* node{find(root, item)};

        if (node != nullptr)
        {
            splay(node);
            return &node->item;
        }
        return nullptr;
    }

    bool contains(const T& item) const {return get(item) != nullptr;}

    size_t size() const {return getSize(root);}

    bool empty() const {return root == nullptr;}

    T* preOrder() 
    {
        T* array{new T[getSize(root)]};
        preOrder(root, array, 0);
        return array;
    }

    T* inOrder() 
    {
        T* array{new T[getSize(root)]};

        // for (size_t i = 0; i < count; ++i)
        //     array[i] = inOrder(root);

        return array;
    }

    T* postOrder() 
    {
        T* array{new T[getSize(root)]};

        // for (size_t i = 0; i < count; ++i)
        //     array[i] = postOrder(root);

        return array;
    }

    T* levelOrder() 
    {
        T* array{new T[getSize(root)]};

        // for (size_t i = 0; i < count; ++i)
        //     array[i] = levelOrder(root);

        return array;
    }

private:
    struct Node
    {
        T item;

        Node* parent;
        Node* lchild;
        Node* rchild;

        bool isLeaf() {return lchild == nullptr && rchild == nullptr;}

        size_t height() const
        {
            size_t leftHeight{};
            size_t rightHeight{};

            leftHeight = (lchild == nullptr) ? 0 : lchild->height();
            rightHeight = (rchild == nullptr) ? 0 : rchild->height();

            return 1 + std::max(leftHeight, rightHeight);
        }
    };
    
    Node* root;

    // right rotation
    void zig(Node* pivot) 
    {
        Node* newRoot = pivot->lchild;

        if (newRoot)
        {
            pivot->lchild = newRoot->rchild;
            if (newRoot->rchild) newRoot->rchild->parent = pivot;
            newRoot->parent = pivot->parent;
        }

        if (!pivot->parent)
            root = newRoot;
        else if (pivot == pivot->parent->rchild)
            pivot->parent->rchild = newRoot;
        else
            pivot->parent->lchild = newRoot;
        
        if (newRoot) newRoot->rchild = pivot;

        pivot->parent = newRoot;
    }

    // left rotation
    void zag(Node* pivot) 
    {
        Node* newRoot = pivot->rchild;

        if (newRoot)
        {
            pivot->rchild = newRoot->lchild;

            if (newRoot->lchild)
                newRoot->lchild->parent = pivot;

            newRoot->parent = pivot->parent;
        }

        if (!pivot->parent)
            root = newRoot;
        else if (pivot == pivot->parent->lchild)
            pivot->parent->lchild = newRoot;
        else
            pivot->parent->rchild = newRoot;

        if (newRoot) newRoot->lchild = pivot;

        pivot->parent = newRoot;
    }

    void splay(Node* node)
    {
        while (node != root)
        {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;

            // zig: no grandparent
            if (grandparent == nullptr)
            {
                if (node == parent->lchild) zig(parent);
                else zag(parent);
            }

            else // zig-zig or zig-zag: has grandparent
            {
                bool nodeIsLeftChild = (node == parent->lchild);
                bool parentIsLeftChild = (parent == grandparent->lchild);

                if (nodeIsLeftChild == parentIsLeftChild) // right-right
                {
                    if (nodeIsLeftChild) zig(grandparent);
                    else zag(grandparent);
                }
                else // right-left
                {
                    if (nodeIsLeftChild) zig(parent);
                    else zag(parent);
                }
            }
        }
    }

    const T* get(Node* root, const T& item) const
    {
        Node* node(find(root, item));

        if(node != nullptr)
        {
            splay(node);
            return &node->item;
        }

        return nullptr;
    }

    size_t getSize(Node* node) const
    {
        if (node == nullptr)
            return 0;
        else
            return 1 + getSize(node->lchild) + getSize(node->rchild);
    }

    void insertNode(Node* root, Node* newNode)
    {
        if (newNode->item < root->item)
        {
            if (root->lchild == nullptr)
            {
                root->lchild = newNode;
                newNode->parent = root;
            } 
            else 
            {
                insertNode(root->lchild, newNode);
            }
        }
        else
        {
            if (root->rchild == nullptr)
            {
                root->rchild = newNode;
                newNode->parent = root;
            }
            else
            {
                insertNode(root->rchild, newNode);
            }
        }
    }

    // private versions of tree traversal functions
    T preOrder(Node* node, T* array, size_t index) 
    {
        if (node != nullptr)
        {
            // process root -> lchild -> rchild
            array[index++] = node->item;
            preOrder(node->lchild, array, index);
            preOrder(node->rchild, array, index);
        }
        return index;
    }

    T inOrder(Node* node) 
    {
        // if (node == nullptr) return;
        
        // process lchild -> root -> rchild
        inOrder(node->lchild);
        return node->item;
        inOrder(node->rchild);
    }

    T postOrder(Node* node) 
    {
        // if (node == nullptr) return;

        // process lchild -> rchild -> root
        inOrder(node->lchild);
        inOrder(node->rchild);
        return node->item;
    }

    T levelOrder(Node* node) 
    {
        size_t h = height(node);

        for (size_t i = 1; i <= h; ++i)
            return currentLevel(node, i);
    }

    T currentLevel(Node* node, size_t level)
    {
        if (node == nullptr) return;
        if (level == 1) return node->item;

        return currentLevel(node->lchild, level - 1);
        return currentLevel(node->rchild, level - 1);
    }

    void deleteNode(Node* node)
    {
        Node* parent{node->parent};
        Node* child{};

        if (node == root)
        {
            root = (node->isLeaf())
                ? nullptr
                : (node->lchild == nullptr) ? node->rchild : node->lchild;
        }
        else
        {
            child = (node->lchild == nullptr) ? node->rchild : node->lchild;
            ((parent->lchild == node) ? parent->lchild : parent->rchild) = child;
            if (!node->isLeaf())
                child->parent = parent;
        }

        delete node;
    }

    Node* find(Node* root, const T& item) const
    {
        if (root == nullptr) return nullptr;
        if (item < root->item) return find(root->lchild, item);
        if (item > root->item) return find(root->rchild, item);

        return root;
    }
};

#endif