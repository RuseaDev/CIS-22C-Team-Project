/**~*~*~*
 * HashTable.h
 *
 * Unit 3 — Hash List Algorithms
 *
 * Data structure : hashed array of Flight objects.
 * Hash function  : Polynomial Rolling Hash (base 31).
 * Collision res. : Linear Probe with lazy deletion.
 * Rehash trigger : load factor >= 75 %; new size = nextPrime(size * 2).
 *
 * BST integration (Option 2 — key + hash index):
 *   insert() returns the final slot index so the caller can do:
 *       int idx = hashTable.insert(flight);
 *       bst.insert(flight.getFlightNumber(), idx);
 *
 *   WARNING: _rehash() reallocates the array and gives every record a
 *   new index.  After a rehash, ALL BST-stored hash indices are stale.
 *   Call getAllEntries() to get the new (key → index) mapping and
 *   rebuild the BST before the next search.
 *~*/

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "flight.h"
#include <string>
#include <vector>
#include <utility>   // std::pair

class HashTable
{
private:
    // ── Slot state ──────────────────────────────────────────────────
    enum SlotState { EMPTY, OCCUPIED, DELETED };

    struct Slot
    {
        Flight    data;
        SlotState state;
        Slot() : state(EMPTY) {}
    };

    // ── Internal data ────────────────────────────────────────────────
    Slot* table;
    int   tableSize;
    int   count;           // number of OCCUPIED slots
    int   totalCollisions; // cumulative across all insertions + rehashes

    // ── Private helpers ──────────────────────────────────────────────
    int  _hash(const std::string& key) const;
    void _rehash();
    bool _isPrime(int n) const;
    int  _nextPrime(int n) const;

public:
    // ── Constructor / Destructor ─────────────────────────────────────
    explicit HashTable(int initialCapacity);
    ~HashTable();

    // Disallow copy/move (raw pointer ownership)
    HashTable(const HashTable&)            = delete;
    HashTable& operator=(const HashTable&) = delete;

    // ── Core operations ──────────────────────────────────────────────

    // Insert flight into hash table.
    // Returns the final slot index, or -1 on failure.
    // Triggers rehash automatically if load factor >= 0.75.
    int  insert(const Flight& flight);

    // Search by flight number.
    // Returns the slot index if found, or -1.
    int  search(const std::string& key) const;

    // Retrieve the Flight stored at a known index.
    // Used by Display Manager: idx = bst.search(key) → getAtIndex(idx, f)
    // Returns false if the index is out of range or not OCCUPIED.
    bool getAtIndex(int idx, Flight& out) const;

    // Lazy deletion: marks the slot DELETED and decrements count.
    // Also remove the corresponding key from the BST after calling this.
    bool remove(const std::string& key);

    // Update an existing flight without changing its primary key.
    // Returns false if the key is not found.
    bool update(const std::string& key, const Flight& updatedFlight);

    // ── BST sync helper ──────────────────────────────────────────────
    // Returns every (flight_number, current_index) pair in the table.
    // Call this after a rehash to update all BST node hashIndex fields.
    std::vector<std::pair<std::string, int>> getAllEntries() const;

    // ── Statistics ───────────────────────────────────────────────────
    double loadFactor()         const;
    int    getTotalCollisions() const { return totalCollisions; }
    int    getLongestPath()     const;  // longest probe chain currently in table
    int    getCount()           const { return count;     }
    int    getTableSize()       const { return tableSize; }

    void printStats() const;
    void printTable() const;
};

#endif
