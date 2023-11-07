#include "hashTable.h"
using namespace std;

int main(void) {
  LinearProbingHashTable<int>* ht = new LinearProbingHashTable<int>{ 5 };
  ht->insert(89);
  ht->insert(18);
  ht->insert(49);
  ht->print();
  std::cout << std::endl;
  ht->insert(58);
  ht->insert(69);
  ht->remove(89);
  ht->insert(79);
  ht->print();
  std::cout << std::endl;

  delete ht;
  return 0;
}