/*#############################################################################
## Author: Shaun Reed                                                        ##
## Legal: All Content (c) 2020 Shaun Reed, all rights reserved               ##
## About: An example of a vector implementation                              ##
##                                                                           ##
## Contact: shaunrd0@gmail.com  | URL: www.shaunreed.com | GitHub: shaunrd0  ##
##############################################################################
## vector.h
*/

#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>

class Vector {
  public:
    Vector() : maxSize(0), curIndex(-1), data(NULL) {};
    Vector(const Vector& rhs);
    Vector operator=(Vector rhs);
    ~Vector();
    bool push(int val);
    int pop();
    void makeEmpty();
    int peek() const;
    bool isEmpty() const;
    bool isFull() const;
    void print() const;
    int getMax() const;
    int getSize() const;
    int getIndex() const;
    int getValue(int index) const;

  private:
    int maxSize;
    int curIndex;
    int *data;
    bool push(int val, int *&data);
    int pop(int *&data);
    void makeEmpty(int *&data);
    int peek(int *data) const;
    void print(int *data) const;
    
};

#endif
