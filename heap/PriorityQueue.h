// An implementation of Binary Heap.
#ifndef __PRIORITY_QUEUE_H__
#define __PRIORITY_QUEUE_H__

class PriorityQueue {
public:
    PriorityQueue(int capacity = 100);

    bool isEmpty() const;
    int findMin() const;

    void insert(int x);
    void deleteMin();
    void makeEmpty();

private:
    int currentSize;

};

#endif