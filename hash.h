// CMSC 341 - Fall 2020 - Project 4
// hash.h

// Templated, hash table implementation.  Each buckets is a heap.  A
// bucket contains objects with the same key values stored as a
// max-heap based on priority.  Collisions are resolved by linear
// probing.

// To work with Heap and HashTable, the template class T must provide
// the following:
//  (a) Default constructor
//  (b) priority function (unsigned priority())
//  (c) key function (string key())
//  (d) overloaded insertion operator

#ifndef _HASH_H
#define _HASH_H

#include <string>
#include "heap.h"

using std::string;

// Hash function typedef.  The hash function must return an 'unsigned
// int' value.  Reduction mod N is the responsiblity of the caller,
// not the hash function.
typedef unsigned (*hash_fn)(string);

class Grader;

template <class T>
class HashTable {

  friend Grader;
  
 public:
  // Constructor.  Requires table size and hash function.
  HashTable(unsigned size, hash_fn hash);

  // Destructor, copy, and assignment
  ~HashTable();
  HashTable(const HashTable<T>& ht);
  const HashTable<T>& operator=(const HashTable<T>& ht);

  // In-line functions
  
  // Table size; set by constructor
  unsigned tableSize() const { return _N; }
  // Number of entries in the table
  unsigned numEntries() const { return _n; }
  // Load factor
  float lambda() const { return ((float) _n) / _N; }

  // Main hash table functions
  
  // insert returns 'true' if successful; 'false' otherwise
  bool insert(const T& object);
  // getNext retrieves **and removes** the highest priority order of
  // type indicated by key.  It returns 'true' if successful; 'false'
  // otherwise.
  bool getNext(string key, T& obj);

  // Dump the entire hash table
  void dump() const;
  
 private:
  unsigned _N;       // hash table size
  unsigned _n;       // current number of entries
  hash_fn _hash;     // hash function
  Heap<T> *_table;   // array of heaps

  // ***********************************************
  // Private helper function declarations go here! *
  // ***********************************************
  
};

// *****************************************
// Templated function definitions go here! *
// *****************************************

// Constructor.  Requires table size and hash function.
template <class T>
HashTable<T>::HashTable(unsigned size, hash_fn hash){
    _hash = hash;
    _N = size;
    _n = 0;
    _table = new Heap<T>[_N]{Heap<T>()};
}

// Destructor
template <class T>
HashTable<T>::~HashTable(){
    delete[] _table;
}

// copy constructor
template <class T>
HashTable<T>::HashTable(const HashTable<T>& ht){
    // set variables equal
    _n = ht._n;
    _hash = ht._hash;
    _N = ht.tableSize();

    // dynamically create new table & set all the heaps equal
    _table = new Heap<T>[_N]{Heap<T>()};
    for (unsigned int i = 0; i < _N; i++) {
        _table[i] = ht._table[i];
    }
}

//assignment operator
template <class T>
const HashTable<T>& HashTable<T>::operator=(const HashTable<T>& ht){
    // same as copy but we delete our table first
    delete[] _table;
    _hash = ht._hash;
    _n = ht._n;
    _N = ht.tableSize();
    _table = new Heap<T>[_N]{Heap<T>()};
    for (unsigned int i = 0; i < _N; i++) {
        _table[i] = ht._table[i];
    }
}

// insert returns 'true' if successful; 'false' otherwise
template <class T>
bool HashTable<T>::insert(const T& object){
    // if its full return false
    if (_N == _n) {
        return false;
    }
    bool putted = false; // for exiting the loop, we need this since it modulates
    int checkIndex = _hash(object.key()) % _N;
    while (!putted) {
        if (_table[checkIndex].used()) {
            if (!_table[checkIndex].empty() && _table[checkIndex].readTop().key() == object.key()) {
                _table[checkIndex].insert(object);
                putted=true;
            }
            checkIndex++; // we dont even need an else here cause it wont get used if it doesn't loop
            checkIndex%=_N; // we keepin this shit [[compact]]
        } else {
            _table[checkIndex].insert(object);
            _n++;
            putted = true;
        }
    }
    return true;
}
// getNext retrieves **and removes** the highest priority order of
// type indicated by key.  It returns 'true' if successful; 'false'
// otherwise.
template <class T>
bool HashTable<T>::getNext(string key, T& obj){
    if (_N == _n) {
        return false;
    }
    bool putted = false; // for exiting the loop
    int checkIndex = _hash(key) % _N;
    while (!putted) {
        if (_table[checkIndex].used()) { // if its used
            if (!_table[checkIndex].empty() && _table[checkIndex].readTop().key() == key) { 
                obj = _table[checkIndex].readTop(); // and not empty and the key works then we can add one
                _table[checkIndex].removeTop();
                putted=true;
            }
            checkIndex++; // if used and empty then we skip
            checkIndex%=_N;
        } else {
            return false; // if not used then we can add a new one
        }
    }
    return true;
}

// Dump the entire hash table
template <class T>
void HashTable<T>::dump() const{
    for (unsigned int i = 0; i < _N; i++) {
        cout << "[" << i << "]:\n";
        if (!_table[i].empty()) {
            _table[i].dump();
        }
    }
}

#endif
