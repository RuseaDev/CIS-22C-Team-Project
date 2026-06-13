#include "BST.h"
#include "fileIO.h"
#include "HashTable.h"
#include "manager.h"
#include <iostream>
#include <string>
using namespace std;

int main() {

  cout << "wassup!" << endl;
  cout << "File to read: ";

  string filename;
  getline(cin, filename);

  int hashSize = determineHashSize(filename);
  if (hashSize == -1) {
    cout << "bye bye" << endl;
    return 1;
  }

  HashTable hashTable(hashSize);
  BST bst;

  readFile(filename, hashTable, bst);

  displayManager(hashTable, bst);

  cout << "bye bye" << endl;

  return 0;
}
