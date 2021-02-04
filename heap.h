// CMSC 341 - Fall 2020 - Project 4
// heap.h
// Templated, vector-based heap implementation

// To work with Heap, the template class T must provide the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) overloaded insertion operator
// To work with Heap *and* HashTable, it also needs:
//  (d) key function (string key())

#ifndef _HEAP_H
#define _HEAP_H

#include <iostream>
#include <vector>
#include <exception>
#include <utility>   // swap

using std::vector;
using std::endl;
using std::cout;
using std::swap;
using std::range_error;

// To work with Heap and HashTable, class T must provide the
// following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

class Grader;

template <class T>
class Heap {

  friend Grader;
  
 public:
  // Constructor
  Heap();

  // Inline functions: size, empty, used 
  unsigned size() const { return _heap.size() - 1 ; }
  bool empty() const { return _heap.size() <= 1 ; }
  bool used() const { return _used ; }

  // Main heap operations: insert, read, remove
  void insert(const T& object);
  T readTop() const;
  void removeTop();

  // Dump the entire heap
  void dump() const;

  // Root node always has index 1
  static const unsigned ROOT = 1;
  
 private:
  vector<T> _heap;   // Vector-based heap
  bool _used;        // Has the heap ever been used?  Needed for
		     // linear probing.

  // *********************************************
  // Private helper function declarations go here!
  // *********************************************
    void balance();
};

// ***************************************
// Templated function definitions go here!
// ***************************************
// Main heap operations: insert, read, remove

template <class T>
Heap<T>::Heap() {
    _heap.push_back(T()); 
    _used = false;    
}

template <class T>
void Heap<T>::balance(){
    int i = size();

    // balance this
    while ((i/2) > 0) {
        if (_heap[i].priority() > _heap[i/2].priority()){ // just check which one is larger
            T temp = _heap[i/2]; // and swap
            _heap[i/2] = _heap[i];
            _heap[i] = temp;
        }
        i /= 2;
    }
}


template <class T>
void Heap<T>::insert(const T& object){
    _used = true;
    _heap.push_back(object);
    balance();
}

template <class T>
T Heap<T>::readTop() const {
    if (empty()) {
        throw range_error("Trying to readTop on empty heap.");
    }
    return _heap[1];
}

template <class T>
void Heap<T>::removeTop(){
    if (empty()) {
        throw range_error("Trying to removeTop on empty heap.");
    }
    _heap[1] = _heap[size()];
    _heap.pop_back();
    balance();
}

template <class T>
void Heap<T>::dump() const {
    for (unsigned int i = 1; i < size()+1; i++) {
        cout << _heap[i] << "\n";
    }
}


#endif
