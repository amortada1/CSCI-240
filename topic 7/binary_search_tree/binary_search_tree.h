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
            root = new BinaryTreeNode{item, nullptr, nullptr, nullptr};
            return;
        }
        
        add(root, item);
    }

    void remove (const T& item) 
    {
        BinaryTreeNode* targetNode{find(root, item)};
        BinaryTreeNode* replacementNode{};

        if (targetNode == nullptr) return;

        if (isLeaf(targetNode) || targetNode->lchild == nullptr) 
        {
            deleteNode(targetNode);
        }
        else
        {
            replacementNode = findRightMost(targetNode->lchild);
            targetNode->item = replacementNode->item;
            deleteNode(replacementNode);
        } 
    }

    size_t getHeight() const
    {
        if (root == nullptr) return 0;

        return root->height();
    }

    bool empty() const {return root == nullptr;}

private:
    struct BinaryTreeNode
    {
        T item;

        BinaryTreeNode* parent;
        BinaryTreeNode* lchild;
        BinaryTreeNode* rchild;

        bool isLeaf()
        {
            return lchild == nullptr && rchild == nullptr;
        }

        size_t height() const
        {
            size_t leftHeight{};
            size_t rightHeight{};

            leftHeight = (lchild == nullptr) ? 0 : lchild->height();
            rightHeight = (rchild == nullptr) ? 0 : rchild->height();

            return 1 + std::max(leftHeight, rightHeight);
        }
    };
    
    BinaryTreeNode* root;

    BinaryTreeNode* find(BinaryTreeNode* root, const T& item) const
    {
        if (root == nullptr) return nullptr;
        if (item < root->item) return find(root->lchild, item);
        if (item > root->item) return find(root->rchild, item);

        return root;
    }

    const T* get(BinaryTreeNode* root, const T& item) const
    {
        const BinaryTreeNode* node{find(root, item)};

        return (node == nullptr) ? nullptr : &node->item;
    }

    BinaryTreeNode* findRightMost(BinaryTreeNode* root)
    {
        if (root == nullptr) return nullptr;

        if (root->rchild == nullptr) return root;

        return findRightMost(root->rchild);
    }
    
    void add(BinaryTreeNode* root, const T& item)
    {
        // storing address of lchild or rchild in child's pointer's pointer
        BinaryTreeNode** child {(item <= root->item) ? &root->lchild : &root->rchild};

        // *child is lchild or rchild's address
        if (*child == nullptr)
            *child = new BinaryTreeNode{item, root, nullptr, nullptr};
        else
            add(*child, item); // recursively call add to go down to the next node
    }

    bool isLeaf(const BinaryTreeNode* node) const {return node->lchild == nullptr && node->rchild == nullptr;}

    void deleteNode(BinaryTreeNode* node)
    {
        BinaryTreeNode* parent{node->parent};
        BinaryTreeNode* child{};

        if (node == root)
        {
            root = (node->isLeaf())
                ? nullptr
                : (node->lchild == nullptr) ? node->rchild : node->lchild;
        }
        else if (node->isLeaf())
        {
           ((parent->lchild == node) ? parent->lchild : parent->rchild) = nullptr;
        }
        else
        {
            child = (node->lchild == nullptr) ? node->rchild : node->lchild;
            ((parent->lchild == node) ? parent->lchild : parent->rchild) = child;
            child->parent = parent;
        }

        delete node;
    }
};

#endif