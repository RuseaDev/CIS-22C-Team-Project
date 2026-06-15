#include "test_utils.h"

#include "../include/fileIO.h"

void testBST(TestRunner &t) {
  printGroup("BST");

  HashTable hashTable(determineHashSize(SAMPLE_FILE));
  BST bst;
  loadSample(hashTable, bst);

  // BST-01: Inorder traversal should print the flight numbers alphabetically.
  string inorderOutput = captureOutput([&]() { bst.inorder(); });
  bool aaBeforeBa = inorderOutput.find("AA101") < inorderOutput.find("BA505");
  bool baBeforeDl = inorderOutput.find("BA505") < inorderOutput.find("DL303");
  bool dlBeforeSw = inorderOutput.find("DL303") < inorderOutput.find("SW404");
  printResult(t, "BST-01 inorder traversal is sorted",
              aaBeforeBa && baBeforeDl && dlBeforeSw);

  // BST-02 and BST-03: Search for one existing key and one missing key.
  printResult(t, "BST-02 AA101 search succeeds", bst.search("AA101") != -1);
  printResult(t, "BST-03 XX999 search fails", bst.search("XX999") == -1);

  // BST-04: Delete SW404, a BST node with two children.
  int swIndex = bst.search("SW404");
  bool removed = swIndex != -1 && hashTable.removeAtIndex(swIndex);
  bst.remove("SW404");

  printResult(t, "BST-04 SW404 delete succeeds", removed);
  printResult(t, "BST-04 SW404 removed from BST",
              bst.search("SW404") == -1);

  // BST-06: A new BST starts empty.
  BST emptyBST;
  printResult(t, "BST-06 new BST is empty", emptyBST.isEmpty());
}
