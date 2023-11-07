#ifndef __HASHTABLE__
#define __HASHTABLE__
#include <vector>
#include <string>
#include <iostream>
#include <cmath>

size_t nextPrime(size_t x) {
  x = (x % 2 == 0) ? x - 1 : x;
  bool isPrime = false;
  while (!isPrime && (x += 2)) {
    isPrime = true;
    for (int i = 3; isPrime && i <= static_cast<size_t>(std::sqrt(x)); i += 2) {
      isPrime = (x % i != 0);
      // std::cout << x << ", " << i << ", " << isPrime << std::endl;
    }
  }
  return x;
}

// Interface
template <typename HashedObj>
class HashTable {
public:
  virtual bool contains(const HashedObj& x) const = 0;

  virtual void makeEmpty() = 0;
  virtual bool insert(const HashedObj& x) = 0;
  virtual bool insert(HashedObj&& x) = 0;
  virtual bool remove(const HashedObj& x) = 0;

  virtual ~HashTable() = default;

private:
  virtual void rehash() = 0;
  virtual size_t myhash(const HashedObj& x) const = 0;
};

template <typename Key>
struct hash {
  size_t operator()(const Key& key) const { return 0; }
};

template <>
struct hash<int> {
  size_t operator()(int key) const { return key; }
};

/*
  An implementation of Separate chaining hash table.
*/
template <typename HashedObj>
class SeparateChainingHashTable : public HashTable<HashedObj> {
public:
  SeparateChainingHashTable(size_t tableSize = 101) {
    objVectors.reserve(tableSize);
  }

  bool contains(const HashedObj& x) const override;

  void makeEmpty() override;
  bool insert(const HashedObj& x) override;
  bool insert(HashedObj&& x) override;
  bool remove(const HashedObj& x) override;

private:
  std::vector<std::vector<HashedObj>> objVectors;
  int currentSize { 0 };

  void rehash() override;
  size_t myhash(const HashedObj& x) const override;
};

/*
  An implementation of probing hash table.
*/
template <typename HashedObj>
class LinearProbingHashTable : public HashTable<HashedObj> {
public:
  LinearProbingHashTable(size_t tableSize = 101) {
    objVector = std::vector<HashedObjAndStatus>(tableSize);
    makeEmpty();
  }

  bool contains(const HashedObj& x) const override;

  void makeEmpty() override;
  bool insert(const HashedObj& x) override;
  bool insert(HashedObj&& x) override;
  bool remove(const HashedObj& x) override;

  enum CellStatus { EMPTY, OCCUPIED, DELETED }; // DELETED is for lazy deletion for successful probe operaiton after remove.

  void print() {
    for (auto& x : objVector) {
      if (x.status == EMPTY) std::cout << "N/A" << "\t" << "EMPTY\n";
      else if (x.status == OCCUPIED) std::cout << x.obj << "\t" << "OCCUPIED\n";
      else std::cout << x.obj << "\t" << "DELETED\n";
    }
  }

private:
  struct HashedObjAndStatus {
    HashedObj obj;
    CellStatus status;

    HashedObjAndStatus(const HashedObj& _obj = HashedObj {}, CellStatus _status = EMPTY)
      : obj { _obj }, status { _status }
    {}
  };

  std::vector<HashedObjAndStatus> objVector;
  int currentSize { 0 };

  void rehash() override;
  size_t myhash(const HashedObj& x) const override;
  size_t collisionResolution(size_t i) const { return i; }
  size_t probe(const HashedObj& x) const;
};

template <typename HashedObj>
void SeparateChainingHashTable<HashedObj>::rehash() {
  std::vector<std::vector<HashedObj>> oldVec(objVectors.size());

  objVectors.resize(nextPrime(2 * objVectors.size()));
  makeEmpty();

  for (auto& vec : oldVec)
    insert(std::move(vec));
}

// // Separate Chaining Hash Table
template <typename HashedObj>
size_t SeparateChainingHashTable<HashedObj>::myhash(const HashedObj& x) const {
  static hash<HashedObj> hf;
  return hf(x) % objVectors.size();
}

template <typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::contains(const HashedObj& x) const {
  auto& whichVector = objVectors[myhash(x)];
  return std::find(whichVector.begin(), whichVector.end(), x) != objVectors.end();
}

template <typename HashedObj>
void SeparateChainingHashTable<HashedObj>::makeEmpty() {
  currentSize = 0;
  for (auto& objVector : objVectors)
    objVector.clear();
}

template <typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::insert(const HashedObj& x) {
  auto& whichVector = objVectors[myhash(x)];
  if (std::find(whichVector.begin(), whichVector.end(), x) != whichVector.end())
    return false;
  whichVector.push_back(x);
  if (++currentSize > objVectors.size())
    rehash();
  return true;
}

template <typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::remove(const HashedObj& x) {
  auto& whichVector = objVectors[myhash(x)];
  auto it = std::find(whichVector.begin(), whichVector.end(), x);
  if (it == whichVector.end())
    return false;
  whichVector.erase(it);
  currentSize--;
  return true;
}

// Linear Probing Hash Table
template <typename HashedObj>
size_t LinearProbingHashTable<HashedObj>::myhash(const HashedObj& x) const {
  static hash<HashedObj> hf;
  return hf(x) % objVector.size();
}

template <typename HashedObj>
void LinearProbingHashTable<HashedObj>::rehash() {
  std::vector<HashedObjAndStatus> oldVec { objVector };

  objVector.resize(nextPrime(2 * objVector.size()));
  makeEmpty();

  for (auto& hashedObj : oldVec) {
    if (hashedObj.status == OCCUPIED)
      insert(std::move(hashedObj.obj));
  }
}

template <typename HashedObj>
size_t LinearProbingHashTable<HashedObj>::probe(const HashedObj& x) const {
  size_t pos = myhash(x), oldPos = pos;
  size_t i = 0;
  while (objVector[pos].obj != x && objVector[pos].status != EMPTY) {
    pos = (oldPos + collisionResolution(i++)) % objVector.size();
  }
  return pos;
}

template <typename HashedObj>
bool LinearProbingHashTable<HashedObj>::contains(const HashedObj& x) const {
  size_t pos = probe(x);
  return objVector[pos].obj == x;
}

template <typename HashedObj>
void LinearProbingHashTable<HashedObj>::makeEmpty() {
  currentSize = 0;
  for (size_t i = 0; i < objVector.size(); i++)
    objVector[i].status = EMPTY;
}

template <typename HashedObj>
bool LinearProbingHashTable<HashedObj>::insert(const HashedObj& x) {
  size_t pos = probe(x);
  bool isInserted = false;

  if (objVector[pos].status != OCCUPIED) {
    objVector[pos].obj = x;
    objVector[pos].status = OCCUPIED;
    isInserted = true;
  }
  
  if (++currentSize > objVector.size() / 2)
    rehash();

  return isInserted;
}

template <typename HashedObj>
bool LinearProbingHashTable<HashedObj>::insert(HashedObj&& x) {
  size_t pos = probe(x);
  bool isInserted = false;

  if (objVector[pos].status != OCCUPIED) {
    objVector[pos].obj = std::move(x);
    objVector[pos].status = OCCUPIED;
    isInserted = true;
  }

  if (++currentSize > objVector.size() / 2)
    rehash();

  return isInserted;
}

template <typename HashedObj>
bool LinearProbingHashTable<HashedObj>::remove(const HashedObj& x) {
  size_t pos = probe(x);
  bool isRemoved = false;

  if (objVector[pos].status == OCCUPIED) {
    objVector[pos].status = DELETED;
    isRemoved = true;
  }

  return isRemoved;
}

#endif