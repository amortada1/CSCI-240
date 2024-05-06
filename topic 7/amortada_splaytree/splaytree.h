#include <cstddef>
#include <algorithm>

#ifndef SPLAY_TREE_H
#define SPLAY_TREE_H

template<typename T>
class SplayTree
{
public:
    // constructor
    SplayTree() : root{nullptr}, count{} {}

    // destructor
    ~SplayTree() {}

    // add
    void add(const T& item)
    {
        if (empty())
        {
            root = new Node{item, nullptr, nullptr, nullptr};
            return;
        }
        
        add(root, item);
        ++count;

        splay(find(root, item)); // need to splay newly added node
    }

    // remove
    void remove(const T& item)
    {
        Node* targetNode{find(root, item)};
        splay(targetNode); // splay node of item we need to find

        deleteNode(root);
        --count;
    }

    // contains
    bool contains(const T& item) const 
    {
        Node* targetNode{find(root, item)};
        if (targetNode == nullptr) return false;
        return true;
    }

    // size
    size_t size() const {return count;}

    // empty
    bool empty() const {return count == 0;}

    /* functions to perform tree traversal and return pointer to a heap-bound array
       storing the items in the correct order
    */
    // preorder
    T* preOrder() 
    {
        T* array{new T[count]};

        for (size_t i = 0; i < count; ++i)
            array[i] = preOrder(root);
    
        return array;
    }

    // inorder
    T* inOrder() 
    {
        T* array{new T[count]};

        for (size_t i = 0; i < count; ++i)
            array[i] = inOrder(root);

        return array;
    }

    // postOrder
    T* postOrder() 
    {
        T* array{new T[count]};

        for (size_t i = 0; i < count; ++i)
            array[i] = postOrder(root);

        return array;
    }

    // levelOrder
    T* levelOrder() 
    {
        T* array{new T[count]};

        for (size_t i = 0; i < count; ++i)
            array[i] = levelOrder(root);

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
    size_t count;

    // right rotation
    Node* zig(Node* nodeN) 
    {
        Node* nodeC{nodeN->lchild};
        nodeN->lchild = nodeC->rchild;
        nodeC->rchild = nodeN;
        return nodeC;
    }

    // left rotation
    Node* zag(Node* nodeN) 
    {
        Node* nodeC{nodeN->rchild};
        nodeN->rchild = nodeC->lchild;
        nodeC->lchild = nodeN;
        return nodeC;
    }

    // splay operation (bringing node to root)
    Node* splay(Node* node)
    {
        // check if node is root
        if (node == root) return root;

        // check if node is a child of root
        if (node == root->lchild || node == root->rchild)
        {
            (node == root->lchild) ? node = zig(root) : node = zag(root); 
        }

        // four conditions
        (node == root->lchild->lchild) ? node = zig(zig(node->parent)) : 
        (node == root->rchild->rchild) ? node = zag(zag(node->parent)) :
        (node == root->rchild->lchild) ? node = zig(zag(node->parent)) :
        (node == root->lchild->rchild) ? node = zag(zig(node->parent)) : splay(node);

        return splay(node);
    }

    void add(Node* root, const T& item)
    {
        // storing address of lchild or rchild in child's pointer's pointer
        Node** child {(item <= root->item) ? &root->lchild : &root->rchild};

        // *child is lchild or rchild's address
        if (*child == nullptr)
            *child = new Node{item, root, nullptr, nullptr};
        else
            add(*child, item); // recursively call add to go down to the next node
    }

    // private versions of tree traversal functions
    T preOrder(Node* node) 
    {
        // if (node == nullptr) return;

        // process root -> lchild -> rchild
        return node->item;

        inOrder(node->lchild);

        inOrder(node->rchild);
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