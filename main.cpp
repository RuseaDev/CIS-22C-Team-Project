#include "HashTable.h"
#include "manager.h"
#include <iostream>
using namespace std;

int main() {

  cout << "wassup!" << endl;
  cout << "File to read: " << endl;
  // TODO: implement readfile and init function

  HashTable hashTable(53);

  displayManager(hashTable);

  cout << "bye bye" << endl;

  return 0;
}