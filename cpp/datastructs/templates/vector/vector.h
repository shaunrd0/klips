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
#include <string>

template <typename T>
class Vector {
  public:
    Vector() : maxSize(0), curIndex(-1), data(NULL) {};
    Vector(const Vector& rhs);
    Vector<T> operator=(Vector<T> rhs);
    ~Vector();
    bool push(T val);
    T pop();
    void makeEmpty();
    T peek() const;
    bool isEmpty() const;
    bool isFull() const;
    void print() const;
    T getMax() const;
    T getSize() const;
    T getIndex() const;
    T getValue(T index) const;

  private:
    T maxSize;
    T curIndex;
    T *data;
    bool push(T val, T *&data);
    T pop(T *&data);
    void makeEmpty(T *&data);
    T peek(T *data) const;
    void print(T *data) const;
    
};

#endif
