/**
 * @file HashTable.h
 * @brief Declares a hash table for storing and finding flight records.
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "flight.h"
#include <string>
#include <utility> // std::pair
#include <vector>

class HashTable {
private:
  enum SlotState { EMPTY, OCCUPIED, DELETED };

  struct Slot {
    Flight data;
    SlotState state;
    Slot() : state(EMPTY) {}
  };

  Slot *table;
  int tableSize;
  int count;           // number of OCCUPIED slots
  int totalCollisions; // cumulative across all insertions + rehashes

  int _hash(const std::string &key) const;
  void _rehash();
  bool _isPrime(int n) const;
  int _nextPrime(int n) const;

public:
  explicit HashTable(int initialCapacity);
  ~HashTable();

  // Disallow copy/move (raw pointer ownership)
  HashTable(const HashTable &) = delete;
  HashTable &operator=(const HashTable &) = delete;

  // Triggers rehash automatically if load factor >= 0.75.
  int insert(const Flight &flight);

  int search(const std::string &key) const;

  // Retrieve the Flight stored at a known index.
  // Used by Display Manager: idx = bst.search(key) => getAtIndex(idx, f)
  // Returns false if the index is out of range or not OCCUPIED.
  bool getAtIndex(int idx, Flight &out) const;

  // Lazy deletion: marks the slot DELETED and decrements count.
  // Also remove the corresponding key from the BST after calling this.
  bool remove(const std::string &key);
  bool removeAtIndex(int idx);
  bool restoreAtIndex(int idx, const Flight &flight);

  // Update an existing flight without changing its primary key.
  bool update(const std::string &key, const Flight &updatedFlight);
  bool updateAtIndex(int idx, const Flight &updatedFlight);

  // BST sync helper
  // Returns every (flight_number, current_index) pair in the table.
  std::vector<std::pair<std::string, int>> getAllEntries() const;

  // Statistics
  double loadFactor() const;
  int getTotalCollisions() const { return totalCollisions; }
  int getLongestPath() const; // longest probe chain currently in table
  int getCount() const { return count; }
  int getTableSize() const { return tableSize; }

  void printStats() const;
  void printTable() const;
};

#endif
