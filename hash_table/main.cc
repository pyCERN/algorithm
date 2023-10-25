#include "hashTable.h"
using namespace std;

int main(void) {
  LinearProbingHashTable<int>* ht = new LinearProbingHashTable<int>{ 10 };
  ht->insert(89);
  ht->insert(18);
  ht->insert(49);
  ht->insert(58);
  ht->insert(69);
  // ht->remove(89);
  // ht->insert(79);
  ht->print();

  delete ht;
  return 0;
}