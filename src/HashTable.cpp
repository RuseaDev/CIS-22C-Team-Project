/**
 * @file HashTable.cpp
 * @brief Implements the hash table used to store and find flight records.
 */

#include "../include/HashTable.h"
#include <iomanip>
#include <iostream>

using namespace std;

HashTable::HashTable(int initialCapacity)
    : tableSize(_nextPrime(initialCapacity)), count(0), totalCollisions(0) {
  table = new Slot[tableSize];
}

HashTable::~HashTable() { delete[] table; }

// Polynomial rolling hash.
int HashTable::_hash(const string &key) const {
  const int BASE = 31;
  long long h = 0;
  for (char c : key)
    h = (h * BASE + static_cast<unsigned char>(c)) % tableSize;
  return static_cast<int>(h);
}

// helpers

bool HashTable::_isPrime(int n) const {
  if (n < 2)
    return false;
  if (n == 2)
    return true;
  if (n % 2 == 0)
    return false;
  for (int i = 3; static_cast<long long>(i) * i <= n; i += 2)
    if (n % i == 0)
      return false;
  return true;
}

int HashTable::_nextPrime(int n) const {
  if (n < 2)
    return 2;
  int c = (n % 2 == 0) ? n + 1 : n;
  while (!_isPrime(c))
    c += 2;
  return c;
}

// Inserts with linear probing. See docs/HashTable_Algorithms.md for duplicate
// handling, DELETED-slot reuse, collision counting, and rehash behavior.
int HashTable::insert(const Flight &flight) {
  if (loadFactor() >= 0.75)
    _rehash();

  const string &key = flight.getFlightNumber();
  int home = _hash(key);
  int firstDeleted = -1;
  int firstDeletedStep = -1;

  for (int i = 0; i < tableSize; ++i) {
    int probe = (home + i) % tableSize;

    if (table[probe].state == OCCUPIED) {
      if (table[probe].data.getFlightNumber() == key)
        return probe; // duplicate — no insert
      continue;       // collision — keep probing
    }

    if (table[probe].state == DELETED) {
      if (firstDeleted == -1) {
        firstDeleted = probe;
        firstDeletedStep = i;
      }
      continue; // keep probing for duplicates
    }

    // EMPTY slot reached; insert at the first reusable slot.
    int insertAt = (firstDeleted != -1) ? firstDeleted : probe;
    int collisions = (firstDeleted != -1) ? firstDeletedStep : i;

    table[insertAt].data = flight;
    table[insertAt].state = OCCUPIED;
    ++count;
    totalCollisions += collisions;
    return insertAt;
  }

  // Full circle with no EMPTY slot; fall back to first DELETED
  if (firstDeleted != -1) {
    table[firstDeleted].data = flight;
    table[firstDeleted].state = OCCUPIED;
    ++count;
    totalCollisions += firstDeletedStep;
    return firstDeleted;
  }

  return -1; // table completely full
}

// Searches by flight number. EMPTY stops the probe; DELETED keeps it going.
int HashTable::search(const string &key) const {
  int home = _hash(key);
  for (int i = 0; i < tableSize; ++i) {
    int probe = (home + i) % tableSize;

    if (table[probe].state == EMPTY)
      return -1;

    if (table[probe].state == OCCUPIED &&
        table[probe].data.getFlightNumber() == key)
      return probe;

    // DELETED → continue (do not break the chain)
  }
  return -1;
}

// Retrieves the Flight at a known slot index.
bool HashTable::getAtIndex(int idx, Flight &out) const {
  if (idx < 0 || idx >= tableSize)
    return false;
  if (table[idx].state != OCCUPIED)
    return false;
  out = table[idx].data;
  return true;
}

// Lazy deletion preserves probe chains. Callers also remove the key from BST.
bool HashTable::remove(const string &key) {
  int idx = search(key);
  return removeAtIndex(idx);
}

bool HashTable::removeAtIndex(int idx) {
  if (idx < 0 || idx >= tableSize)
    return false;
  if (table[idx].state != OCCUPIED)
    return false;
  table[idx].state = DELETED;
  --count;
  return true;
}

bool HashTable::restoreAtIndex(int idx, const Flight &flight) {
  if (idx < 0 || idx >= tableSize)
    return false;
  if (table[idx].state != DELETED)
    return false;
  if (search(flight.getFlightNumber()) != -1)
    return false;

  table[idx].data = flight;
  table[idx].state = OCCUPIED;
  ++count;
  return true;
}

bool HashTable::update(const string &key, const Flight &updatedFlight) {
  int idx = search(key);
  return updateAtIndex(idx, updatedFlight);
}

bool HashTable::updateAtIndex(int idx, const Flight &updatedFlight) {
  if (idx < 0 || idx >= tableSize)
    return false;
  if (table[idx].state != OCCUPIED)
    return false;
  Flight storedFlight = updatedFlight;
  storedFlight.setFlightNumber(table[idx].data.getFlightNumber());
  table[idx].data = storedFlight;
  return true;
}

// Rebuilds into a larger table and drops DELETED slots. Callers sync BST indexes.
void HashTable::_rehash() {
  Slot *oldTable = table;
  int oldSize = tableSize;

  tableSize = _nextPrime(tableSize * 2);
  table = new Slot[tableSize];
  count = 0;
  // totalCollisions intentionally accumulates across rehashes

  for (int i = 0; i < oldSize; ++i)
    if (oldTable[i].state == OCCUPIED)
      insert(oldTable[i].data); // re-hash into the new table

  delete[] oldTable;
}

// Returns active (flight_number, current_index) pairs for BST rebuilds.
vector<pair<string, int>> HashTable::getAllEntries() const {
  vector<pair<string, int>> entries;
  entries.reserve(count);
  for (int i = 0; i < tableSize; ++i)
    if (table[i].state == OCCUPIED)
      entries.emplace_back(table[i].data.getFlightNumber(), i);
  return entries;
}

// Statistics

double HashTable::loadFactor() const {
  return static_cast<double>(count) / tableSize;
}

// getLongestPath — scans every OCCUPIED slot and measures how far
// it sits from its home index.  Reflects the current state of the
// table (may change after deletions/rehashing).
int HashTable::getLongestPath() const {
  int longest = 0;
  for (int i = 0; i < tableSize; ++i) {
    if (table[i].state == OCCUPIED) {
      int home = _hash(table[i].data.getFlightNumber());
      int path = ((i - home) + tableSize) % tableSize;
      if (path > longest)
        longest = path;
    }
  }
  return longest;
}

void HashTable::printStats() const {
  cout << "=== Hash Table Statistics ===" << endl;
  cout << "  Table size       : " << tableSize << endl;
  cout << "  Occupied slots   : " << count << endl;
  cout << fixed << setprecision(2);
  cout << "  Load factor      : " << loadFactor() * 100 << "%" << endl;
  cout << "  Total collisions : " << totalCollisions << endl;
  cout << "  Longest path     : " << getLongestPath() << endl;
}

void HashTable::printTable() const {
  for (int i = 0; i < tableSize; ++i) {
    cout << "[" << setw(2) << i << "] ";
    switch (table[i].state) {
    case EMPTY:
      cout << "-- empty --\n";
      break;
    case DELETED:
      cout << "-- deleted --\n";
      break;
    case OCCUPIED:
      cout << table[i].data.getFlightNumber() << "  "
           << table[i].data.getOrigin() << " -> "
           << table[i].data.getDestination() << "\n";
      break;
    }
  }
}
