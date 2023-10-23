#include "hashTable.h"

template <typename HashedObj>
size_t SeparateChainingHashTable<HashedObj>::myhash(const HashedObj& x) const {
  static hash<HashedObj> hf;
  return hf(x) % objVectors.size();
}

template <typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::contains(const HashedObj& x) const {
  auto& whichVector = objVectors[myhash<HashedObj>(x)];
  return std::find(whichVector.begin(), whichVector.end(), x) != objVectors.end();
}

template <typename HashedObj>
void SeparateChainingHashTable<HashedObj>::makeEmpty() {
  for (auto& objVector : objVectors)
    objVector.clear();
}

template <typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::insert(const HashedObj& x) {
  auto& whichVector = objVectors[myhash<HashedObj>(x)];
  if (std::find(whichVector.begin(), whichVector.end(), x) != whichVector.end())
    return false;
  whichVector.push_back(x);
  if (++currentSize > objVectors.size())
    rehash();
  return true;
}

template <typename HashedObj>
bool SeparateChainingHashTable<HashedObj>::remove(const HashedObj& x) {
  auto& whichVector = objVectors[myhash<HashedObj>(x)];
  auto it = std::find(whichVector.begin(), whichVector.end(), x);
  if (it == whichVector.end())
    return false;
  whichVector.erase(it);
  currentSize--;
  return true;
}

template <typename HashedObj>
size_t LinearProbingHashTable<HashedObj>::myhash(const HashedObj& x) const {
  static hash<HashedObj> hf;
  return hf(x) % objVector.size();
}

template <typename HashedObj>
bool LinearProbingHashTable<HashedObj>::contains(const HashedObj& x) const {
  size_t pos = myhash(x), oldPos = pos;
  size_t i = 0;
  while (objVector[pos] != x || objVector[pos].status == EMPTY) {
    pos = (oldPos + probe(i++)) % objVector.size();
    continue;
  }
}

template <typename HashedObj>
bool LinearProbingHashTable<HashedObj>::insert(const HashedObj& x) {
  size_t key = myhash<HashedObj>(x);
  
}

template <typename HashedObj>
bool LinearProbingHashTable<HashedObj>::remove(const HashedObj& x) {
  auto& whichVector = objVectors[myhash<HashedObj>(x)];
  auto it = std::find(whichVector.begin(), whichVector.end(), x);
  if (it == whichVector.end())
    return false;
  whichVector.erase(it);
  return true;
}