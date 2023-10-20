// An implementation of general Binary Search Tree.
#ifndef __TREE_H__
#define __TREE_H__

struct BinaryTreeNode {
    int element;
    BinaryTreeNode* left;
    BinaryTreeNode* right;

    BinaryTreeNode(const int& elem, BinaryTreeNode* lnode, BinaryTreeNode* rnode)
      : element { elem }, left { lnode }, right { rnode }
    {}
};

class BinarySearchTreeImpl {
public:
    BinarySearchTreeImpl() = default;
    ~BinarySearchTreeImpl() = default;

    bool contains(const int& x, const BinaryTreeNode* node) const;
    void printTree(const BinaryTreeNode* node) const;

    void clearTree(BinaryTreeNode*& node);
    void insert(const int& x, BinaryTreeNode*& node);
    void remove(const int& x, BinaryTreeNode*& node);

protected:
    BinaryTreeNode* findMin(BinaryTreeNode* node) const;
    BinaryTreeNode* findMax(BinaryTreeNode* node) const;
};

class BinarySearchTree {
public:
    BinarySearchTree()
      : _root { nullptr }, _impl { new BinarySearchTreeImpl {} } {}
    BinarySearchTree(BinarySearchTreeImpl* impl)
      : _root { nullptr }, _impl { impl } {}
    ~BinarySearchTree();

    bool contains(const int& x) const;
    bool isEmpty() const { return _root == nullptr; }
    void printTree() const;

    void clearTree();
    void insert(const int& x);
    void remove(const int& x);

private:
    BinaryTreeNode* _root;
    BinarySearchTreeImpl* _impl;
};

#endif