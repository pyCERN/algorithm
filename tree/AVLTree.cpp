#include "AVLTree.h"

bool AVLTreeImpl::contains(const int& x, const AVLTreeNode* node) const {
    return BinarySearchTreeImpl::contains(x, node);
}

void AVLTreeImpl::printTree(const AVLTreeNode* node) const {
    BinarySearchTreeImpl::printTree(node);
}

void AVLTreeImpl::insert(const int& x, AVLTreeNode*& node) {
    if (node == nullptr)
        node = new AVLTreeNode { x, nullptr, nullptr };
    else if (x < node->element)
        insert(x, node->left);
    else if (x > node->element)
        insert(x, node->right);
    balance(node);
}

void AVLTreeImpl::remove(const int& x, AVLTreeNode*& node) {
    if (node == nullptr)
        return;
    else if (x < node->element)
        remove(x, node->left);
    else if (x > node->element)
        remove(x, node->right);
    else {
        if (node->left != nullptr && node->right != nullptr) {
            node->element = findMin(node->right)->element;
            remove(node->element, node->right);
        }
        else {
            AVLTreeNode* oldNode = node;
            node = node->left != nullptr ? node->left : node->right;
            delete node;
        }
    }
    balance(node);
}

void AVLTreeImpl::balance(AVLTreeNode*& node) {
    if (node == nullptr)
        return;
    int leftHeight { height(node->left) };
    int rightHeight { height(node->right) };

    if (leftHeight - rightHeight > 1) {
        if (height(node->left->left) >= height(node->right->left))
            rotateWithLeftChild(node);
        else
            doubleRotateWithLeftChild(node);
    }
    else if (rightHeight - leftHeight > 1) {
        if (height(node->right->right) >= height(node->right->left))
            rotateWithRightChild(node);
        else
            doubleRotateWithLeftChild(node);
    }
}

void AVLTreeImpl::rotateWithLeftChild(AVLTreeNode*& k2) {
    AVLTreeNode* k1 { k2->left };
    k2->left = k1->right;
    k2->height = std::max(height(k2->left), height(k2->right)) + 1;
    k1->right = k2;
    k1->height = std::max(height(k1->left), height(k1->right))  + 1;
    k2 = k1;
}

void AVLTreeImpl::rotateWithRightChild(AVLTreeNode*& k1) {
    AVLTreeNode* k2 { k1->right };
    k1->right = k2->left;
    k1->height = std::max(height(k1->left), height(k1->right)) + 1;
    k2->left = k1;
    k2->height = std::max(height(k2->left), height(k2->right))  + 1;
    k1 = k2;
}

void AVLTreeImpl::doubleRotateWithLeftChild(AVLTreeNode*& k3) {
    rotateWithRightChild(k3->left);
    rotateWithLeftChild(k3);
}

void AVLTreeImpl::doubleRotateWithRightChild(AVLTreeNode*& k3) {
    rotateWithLeftChild(k3->right);
    rotateWithRightChild(k3);
}
