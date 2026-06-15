#include "test_utils.h"

#include "../include/fileIO.h"

void testBST(TestRunner &t) {
  printGroup("BST");

  HashTable hashTable(determineHashSize(SAMPLE_FILE));
  BST bst;
  loadSample(hashTable, bst);

  // BST-02 and BST-03: Search for one existing key and one missing key.
  printResult(t, "BST-02 AA101 search succeeds", bst.search("AA101") != -1);
  printResult(t, "BST-03 XX999 search fails", bst.search("XX999") == -1);

  // BST-04 and HT-05: Delete SW404 and make sure QF707 is still findable.
  int swIndex = bst.search("SW404");
  bool removed = swIndex != -1 && hashTable.removeAtIndex(swIndex);
  bst.remove("SW404");

  printResult(t, "BST-04 SW404 delete succeeds", removed);
  printResult(t, "BST-04 SW404 removed from BST",
              bst.search("SW404") == -1);
  printResult(t, "HT-05 QF707 remains searchable through deleted SW404 slot",
              hashTable.search("QF707") == 47);

  // BST-06: A new BST starts empty.
  BST emptyBST;
  printResult(t, "BST-06 new BST is empty", emptyBST.isEmpty());
}
