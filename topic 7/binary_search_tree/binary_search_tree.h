#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

// type T should have relational operators overloaded 

template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree() : root{nullptr} {}

    ~BinarySearchTree() {}

    // returns a pointer so we can return nullptr if item is not found
    const T* get(const T& item) const 
    {
        return get(root, item);
    }

    void add(const T& item) 
    {
        if (empty())
        {
            root = new BinaryTreeNode{item, nullptr, nullptr};
            return;
        }
        
        add(root, item);
    }

    void remove (const T&) 
    {
        // TODO: implement
    }

    bool empty() const {return root == nullptr;}

private:
    struct BinaryTreeNode
    {
        T item;
        BinaryTreeNode* lchild;
        BinaryTreeNode* rchild;
    };
    
    BinaryTreeNode* root;

    const T* get(BinaryTreeNode* root, const T& item) const
    {
        if (root == nullptr) return nullptr;
        if (item < root->item) return get(root->lchild, item);
        if (item > root->item) return get(root->rchild, item);

        return &root->item;
    }
    
    void add(BinaryTreeNode* root, const T& item)
    {
        // storing address of lchild or rchild in child's pointer's pointer
        BinaryTreeNode** child {(item <= root->item) ? &root->lchild : &root->rchild};

        // *child is lchild or rchild's address
        if (*child == nullptr)
            *child = new BinaryTreeNode{item, nullptr, nullptr};
        else
            add(*child, item); // recursively call add to go down to the next node
    }
};

#endif