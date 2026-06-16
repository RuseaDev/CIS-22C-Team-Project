/**
 * @file manager.h
 * @brief Declares menu manager functions for flight database actions.
 */

#ifndef MANAGER_H
#define MANAGER_H

#include "BST.h"
#include "HashTable.h"

void searchManager(const HashTable &hashTable, const BST &bst);
void secondarySearchManager(const HashTable &hashTable);
void displayManager(HashTable &hashTable, BST &bst);
void deleteManager(HashTable &hashTable, BST &bst);
void insertManager(HashTable &hashTable, BST &bst);
void saveManager(HashTable &hashTable);
void updateManager(HashTable &hashTable, BST &bst);
void undoDeleteManager(HashTable &hashTable, BST &bst);

#endif
