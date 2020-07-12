/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a max heap implementation                            ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## maxheap.h
*/

#ifndef MAXHEAP_H
#define MAXHEAP_H

#include <iostream>

#define ROOT 1

class MaxHeap {

  public:
    MaxHeap();
    MaxHeap(const MaxHeap& rhs);
    MaxHeap(int _size);
    ~MaxHeap();
    MaxHeap operator=(MaxHeap rhs);
    void insert(int val);
    void del();
    void print() const;
    void makeEmpty();
    int findMax() const;
    int findMin() const;
    bool isEmpty() const;
    bool isFull() const;

private:
    void insert(int*& heap, int _size, int val);
    void del(int* heap);
    void print(int* heap, int _index) const;
    void grow(int*& heap, int _size);
    void siftUp(int* heap, int _index);
    void siftDown(int* heap, int currentMax);
    int size, index;
    int *heap;
};

#endif //MAXHEAP_H
