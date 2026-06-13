#ifndef MANAGER_H
#define MANAGER_H

#include "HashTable.h"

void searchManager(const HashTable &hashTable);
void displayManager(HashTable &hashTable);
void deleteManager(HashTable &hashTable);
void insertManager(HashTable &hashTable);
void updateManager(HashTable &hashTable);
void undoDeleteManager(HashTable &hashTable);

#endif
