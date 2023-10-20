#include "AVLTree.h"

int main(void) {
    BinarySearchTree* t { new BinarySearchTree { new AVLTreeImpl {} } };
    t->insert(10);
    t->insert(3);
    t->insert(5);
    t->printTree();

    t->remove(3);
    t->remove(100);
    t->printTree();
    delete t;

    return 0;
}