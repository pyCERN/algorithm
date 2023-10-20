// An implementation of AVL tree.
#ifndef __AVLTREE_H__
#define __AVLTREE_H__

#include <algorithm>
#include "tree.h"

struct AVLTreeNode : BinaryTreeNode {
    AVLTreeNode* left;
    AVLTreeNode* right;
    int height;

    AVLTreeNode(const int& elem, AVLTreeNode* lnode, AVLTreeNode* rnode, int h = 0)
      : left { lnode }, right { rnode }, height { h }, BinaryTreeNode(elem, lnode, rnode)
    {}
};

class AVLTreeImpl : public BinarySearchTreeImpl {
public:
    AVLTreeImpl()  = default;
    ~AVLTreeImpl() = default;

    bool contains(const int& x, const AVLTreeNode* node) const;
    void printTree(const AVLTreeNode* node) const;

    void insert(const int& x, AVLTreeNode*& node);
    void remove(const int& x, AVLTreeNode*& node);

private:
    void balance(AVLTreeNode*& node);
    void rotateWithLeftChild(AVLTreeNode*& k2);
    void rotateWithRightChild(AVLTreeNode*& k1);
    void doubleRotateWithLeftChild(AVLTreeNode*& k3);
    void doubleRotateWithRightChild(AVLTreeNode*& k3);

    inline int height(AVLTreeNode* node) const {
        return node == nullptr ? -1 : node->height;
    }
};

#endif