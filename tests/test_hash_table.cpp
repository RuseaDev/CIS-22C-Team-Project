#include "test_utils.h"

#include "../include/fileIO.h"

using namespace std;

void testHashTable(TestRunner &t) {
  printGroup("Hash Table");

  HashTable hashTable(determineHashSize(SAMPLE_FILE));
  BST bst;
  loadSample(hashTable, bst);

  // HT-01: Check a few known hash table positions after loading.
  printResult(t, "HT-01 IB2323 placed at index 0",
              hashTable.search("IB2323") == 0);
  printResult(t, "HT-01 AA101 placed at index 37",
              hashTable.search("AA101") == 37);
  printResult(t, "HT-01 SW404 placed at index 46",
              hashTable.search("SW404") == 46);
  printResult(t, "HT-01 QF707 placed at index 47",
              hashTable.search("QF707") == 47);
  printResult(t, "HT-01 JL1818 placed at index 51",
              hashTable.search("JL1818") == 51);

  // HT-03: Try to insert a duplicate flight number.
  int beforeDuplicate = hashTable.getCount();
  int duplicateIndex = hashTable.insert(makeFlight("BA505"));

  printResult(t, "HT-03 duplicate BA505 returns existing index",
              duplicateIndex == 12);
  printResult(t, "HT-03 duplicate BA505 does not increase count",
              hashTable.getCount() == beforeDuplicate);

  // HT-06: Search for a flight number that does not exist.
  printResult(t, "HT-06 missing ZZ000 search result",
              hashTable.search("ZZ000") == -1);

  // HT-07: Check hash table statistics after the normal file load.
  printResult(t, "HT-07 table size", hashTable.getTableSize() == 53);
  printResult(t, "HT-07 occupied slots", hashTable.getCount() == 25);
  printResult(t, "HT-07 load factor",
              almostEqual(hashTable.loadFactor() * 100, 47.17, 0.01));
  printResult(t, "HT-07 total collisions",
              hashTable.getTotalCollisions() == 15);
  printResult(t, "HT-07 longest path", hashTable.getLongestPath() == 6);

  // HT-08: Insert enough records to trigger a rehash.
  HashTable rehashTable(determineHashSize(SAMPLE_FILE));
  BST rehashBST;
  loadSample(rehashTable, rehashBST);

  for (int i = 0; i < 16; i++) {
    string key = "ZZ" + to_string(900 + i);
    int oldSize = rehashTable.getTableSize();
    int index = rehashTable.insert(makeFlight(key));

    if (rehashTable.getTableSize() != oldSize) {
      rebuildBSTFromHash(rehashTable, rehashBST);
    } else if (index != -1) {
      rehashBST.insert(key, index);
    }
  }

  printResult(t, "HT-08 rehash after threshold grows table to 107",
              rehashTable.getTableSize() == 107);
  printResult(t, "HT-08 rehash keeps all active records",
              rehashTable.getCount() == 41);
}
