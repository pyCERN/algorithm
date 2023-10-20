#include <iostream>
#include "tree.h"

BinarySearchTree::~BinarySearchTree() {
    clearTree();
    delete _impl;
}

bool BinarySearchTree::contains(const int& x) const {
    return _impl->contains(x, _root);
}

void BinarySearchTree::printTree() const {
    _impl->printTree(_root);
}

void BinarySearchTree::clearTree() {
    _impl->clearTree(_root);
}

void BinarySearchTree::insert(const int& x) {
    _impl->insert(x, _root);
}

void BinarySearchTree::remove(const int& x) {
    _impl->remove(x, _root);
}

bool BinarySearchTreeImpl::contains(const int& x, const BinaryTreeNode* node) const {
    if (node == nullptr) return false;
    else if (x < node->element)
        return contains(x, node->left);
    else if (x > node->element)
        return contains(x, node->right);
    else return true;
}

BinaryTreeNode*
BinarySearchTreeImpl::findMin(BinaryTreeNode* node) const {
    if (node == nullptr)
        return nullptr;
    else if (node->left == nullptr)
        return node;
    else
        return findMin(node->left);
}

BinaryTreeNode*
BinarySearchTreeImpl::findMax(BinaryTreeNode* node) const {
    if (node == nullptr)
        return nullptr;
    else if (node->right == nullptr)
        return node;
    else
        return findMax(node->right);
}

void BinarySearchTreeImpl::printTree(const BinaryTreeNode* node) const {
    if (node == nullptr) return;
    else {
        printTree(node->left);
        std::cout << node->element << std::endl;
        printTree(node->right);
    }
}

void BinarySearchTreeImpl::insert(const int& x, BinaryTreeNode*& node) {
    if (node == nullptr)
        node = new BinaryTreeNode { x, nullptr, nullptr };
    else if (x < node->element)
        insert(x, node->left);
    else if (x > node->element)
        insert(x, node->right);
    else return;
}

void BinarySearchTreeImpl::remove(const int& x, BinaryTreeNode*& node) {
    if (node == nullptr)
        return;
    else if (x < node->element)
        remove(x, node->left);
    else if (x > node->element)
        remove(x, node->right);
    else {
        if (node->left != nullptr && node->right != nullptr) {
            BinaryTreeNode* minNode = findMin(node->right);
            node->element = minNode->element;
            remove(minNode->element, node->right);
        }
    }
}

void BinarySearchTreeImpl::clearTree(BinaryTreeNode*& node) {
    if (node != nullptr) {
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }
    node == nullptr;
}