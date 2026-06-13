#ifndef FILEIO_H
#define FILEIO_H

#include <string>
#include "HashTable.h"
#include "BST.h"
#include "flight.h"

bool   isPrime(int n);
int    determineHashSize(std::string filename);
Flight parseLine(const std::string& line);
void   readFile(std::string filename, HashTable& hashTable, BST& bst);
void   saveToFile(std::string filename, HashTable& hashTable);

#endif
