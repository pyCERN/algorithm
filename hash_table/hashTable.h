#ifndef __HASHTABLE__
#define __HASHTABLE__
#include <vector>
#include <string>

template <typename HashedObj>
class HashTable {
public:
  virtual bool contains(const HashedObj& x) const = 0;

  virtual void makeEmpty() = 0;
  virtual bool insert(const HashedObj& x) = 0;
  virtual bool remove(const HashedObj& x) = 0;

  virtual ~HashTable() = default;

private:
  virtual void rehash() = 0;
  virtual size_t myhash(const HashedObj& x) const = 0;
};

template <typename Key>
struct hash {
  size_t operator()(const Key& key) const;
};

template <>
struct hash<std::string> {
  size_t operator()(const std::string& s) const {
    size_t hashVal = 0;
    for (char ch : s)
      hashVal = 37 * hashVal + ch;
    return hashVal;
  }
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
  ProbingHashTable(size_t tableSize = 101) {
    objVector.reserve(tableSize);
  }

  bool contains(const HashedObj& x) const override;

  void makeEmpty() override;
  bool insert(const HashedObj& x) override;
  bool remove(const HashedObj& x) override;

private:
  enum CellStatus { EMPTY, OCCUPIED };

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
  size_t probe(size_t i) {
    return i;
  }
};

#endif