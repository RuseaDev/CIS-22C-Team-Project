/**~*~*~*
 * HashTable.cpp
 *
 * Unit 3 — Hash List Algorithms
 * Implementation of HashTable declared in HashTable.h
 *~*/

#include "HashTable.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ═══════════════════════════════════════════════════════════════
// Constructor / Destructor
// ═══════════════════════════════════════════════════════════════

HashTable::HashTable(int initialCapacity)
    : tableSize(_nextPrime(initialCapacity))
    , count(0)
    , totalCollisions(0)
{
    table = new Slot[tableSize];
}

HashTable::~HashTable()
{
    delete[] table;
}

// ═══════════════════════════════════════════════════════════════
// Polynomial Rolling Hash — How It Works
//
// ── The formula ─────────────────────────────────────────────────
// We scan the key left to right, maintaining a running hash value:
//
//   h  = 0
//   for each character c in key:
//       h = (h * BASE + ascii(c)) % tableSize
//
// Expanding the loop makes the underlying polynomial explicit:
//
//   hash(key) = ( ascii(key[0]) * BASE^(n-1)
//              +  ascii(key[1]) * BASE^(n-2)
//              +  ...
//              +  ascii(key[n-1]) * BASE^0 ) % tableSize
//
// Each character gets a unique positional weight (BASE^position),
// so rearranging characters always yields a different hash.
// "DL303" and "LD303" will NOT collide the way they would with a
// simple character-sum hash.
//
// ── Why BASE = 31? ───────────────────────────────────────────────
//   1. It is prime — reduces the number of key pairs that map to
//      the same value compared with a composite base.
//   2. It is small — (h * 31 + c) fits easily in a 64-bit long
//      before the modulo step, so no overflow occurs.
//   3. It is the standard for alphanumeric strings (it is the base
//      used inside Java's String.hashCode()).
//
// ── Why NOT simple modulo-division? ─────────────────────────────
// The project spec forbids "converting the key to a number and
// using a simple modulo-division hash function."  That means:
//
//   BAD:  h = stoi("003") % tableSize  ->  h = 3 % 53 = 3
//
// stoi() reduces the entire string to one integer, throwing away
// all character-position information.  Keys "003" and "300" would
// hash identically.  Polynomial rolling hash weighs EVERY character
// at its position, satisfying the spec requirement.
//
// ── Worked example: key = "DL303", tableSize = 11 ───────────────
//
//   char | ASCII | h = (h * 31 + ASCII) % 11
//   -----|-------|----------------------------------
//   'D'  |  68   | ( 0 * 31 +  68) % 11 =  68 % 11 = 2
//   'L'  |  76   | ( 2 * 31 +  76) % 11 = 138 % 11 = 6
//   '3'  |  51   | ( 6 * 31 +  51) % 11 = 237 % 11 = 6
//   '0'  |  48   | ( 6 * 31 +  48) % 11 = 234 % 11 = 3
//   '3'  |  51   | ( 3 * 31 +  51) % 11 = 144 % 11 = 1
//                                                      ^
//                                            final index = 1
//
// ── Sequential key clustering (known limitation) ─────────────────
// Flight numbers such as "AA101" and "DL303" include both letters
// and digits, so the polynomial hash uses each character's position
// instead of reducing the key to a numeric ID.
// ═══════════════════════════════════════════════════════════════

int HashTable::_hash(const string& key) const
{
    const int BASE = 31;
    long long h = 0;
    for (char c : key)
        h = (h * BASE + static_cast<unsigned char>(c)) % tableSize;
    return static_cast<int>(h);
}

// ═══════════════════════════════════════════════════════════════
// Prime helpers
// ═══════════════════════════════════════════════════════════════

bool HashTable::_isPrime(int n) const
{
    if (n < 2)      return false;
    if (n == 2)     return true;
    if (n % 2 == 0) return false;
    for (int i = 3; static_cast<long long>(i) * i <= n; i += 2)
        if (n % i == 0) return false;
    return true;
}

int HashTable::_nextPrime(int n) const
{
    if (n < 2) return 2;
    int c = (n % 2 == 0) ? n + 1 : n;
    while (!_isPrime(c)) c += 2;
    return c;
}

// ═══════════════════════════════════════════════════════════════
// insert
//
// Algorithm:
//   1. Auto-rehash if load factor >= 75 %.
//   2. Compute home = _hash(key).
//   3. Linear probe: step through (home+i) % size for i=0,1,...
//      – OCCUPIED + same key  → duplicate, return existing index.
//      – OCCUPIED + diff key  → collision; record count, continue.
//      – DELETED              → remember first deleted slot;
//                               keep probing to detect duplicates.
//      – EMPTY                → insertion point found; use first
//                               DELETED slot if one was seen earlier
//                               (reclaims space and preserves chains).
//   4. Collision count = probe steps taken to reach insertion point.
//
// Returns the final slot index, or -1 if the table is full
// (should never occur with auto-rehash at 75 %).
// ═══════════════════════════════════════════════════════════════

int HashTable::insert(const Flight& flight)
{
    if (loadFactor() >= 0.75)
        _rehash();

    const string& key    = flight.getFlightNumber();
    int           home   = _hash(key);
    int firstDeleted     = -1;
    int firstDeletedStep = -1;

    for (int i = 0; i < tableSize; ++i)
    {
        int probe = (home + i) % tableSize;

        if (table[probe].state == OCCUPIED)
        {
            if (table[probe].data.getFlightNumber() == key)
                return probe;              // duplicate — no insert
            continue;                      // collision — keep probing
        }

        if (table[probe].state == DELETED)
        {
            if (firstDeleted == -1)
            {
                firstDeleted     = probe;
                firstDeletedStep = i;
            }
            continue;                      // keep probing for duplicates
        }

        // ── EMPTY slot reached ──────────────────────────────────────
        int insertAt   = (firstDeleted != -1) ? firstDeleted  : probe;
        int collisions = (firstDeleted != -1) ? firstDeletedStep : i;

        table[insertAt].data  = flight;
        table[insertAt].state = OCCUPIED;
        ++count;
        totalCollisions += collisions;
        return insertAt;
    }

    // Full circle with no EMPTY slot; fall back to first DELETED
    if (firstDeleted != -1)
    {
        table[firstDeleted].data  = flight;
        table[firstDeleted].state = OCCUPIED;
        ++count;
        totalCollisions += firstDeletedStep;
        return firstDeleted;
    }

    return -1;   // table completely full
}

// ═══════════════════════════════════════════════════════════════
// search
//
// Returns the slot index where key is found, or -1.
// Stops early at an EMPTY slot (a key cannot exist past a slot
// that was always empty under linear-probe / lazy-delete).
// DELETED slots are skipped — they preserve the probe chain for
// items inserted beyond them.
// ═══════════════════════════════════════════════════════════════

int HashTable::search(const string& key) const
{
    int home = _hash(key);
    for (int i = 0; i < tableSize; ++i)
    {
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

// ═══════════════════════════════════════════════════════════════
// getAtIndex
//
// Retrieves the Flight at a known slot index.
// Called by the Display Manager after the BST returns a hashIndex:
//   int idx = bst.search(key)  →  hashTable.getAtIndex(idx, flight)
// ═══════════════════════════════════════════════════════════════

bool HashTable::getAtIndex(int idx, Flight& out) const
{
    if (idx < 0 || idx >= tableSize)      return false;
    if (table[idx].state != OCCUPIED)     return false;
    out = table[idx].data;
    return true;
}

// ═══════════════════════════════════════════════════════════════
// remove
//
// Lazy deletion: marks the slot DELETED so probe chains remain
// intact for subsequent searches.
// IMPORTANT: the caller must also call bst.remove(key) to keep
// the BST consistent.
// ═══════════════════════════════════════════════════════════════

bool HashTable::remove(const string& key)
{
    int idx = search(key);
    return removeAtIndex(idx);
}

bool HashTable::removeAtIndex(int idx)
{
    if (idx < 0 || idx >= tableSize) return false;
    if (table[idx].state != OCCUPIED) return false;
    table[idx].state = DELETED;
    --count;
    return true;
}

bool HashTable::restoreAtIndex(int idx, const Flight& flight)
{
    if (idx < 0 || idx >= tableSize) return false;
    if (table[idx].state != DELETED) return false;
    if (search(flight.getFlightNumber()) != -1) return false;

    table[idx].data = flight;
    table[idx].state = OCCUPIED;
    ++count;
    return true;
}

bool HashTable::update(const string& key, const Flight& updatedFlight)
{
    int idx = search(key);
    return updateAtIndex(idx, updatedFlight);
}

bool HashTable::updateAtIndex(int idx, const Flight& updatedFlight)
{
    if (idx < 0 || idx >= tableSize) return false;
    if (table[idx].state != OCCUPIED) return false;
    Flight storedFlight = updatedFlight;
    storedFlight.setFlightNumber(table[idx].data.getFlightNumber());
    table[idx].data = storedFlight;
    return true;
}

// ═══════════════════════════════════════════════════════════════
// _rehash
//
// New size = nextPrime(tableSize × 2).
// All OCCUPIED slots are re-inserted; DELETED slots are dropped
// (rehash acts as a garbage-collection pass).
//
// After this call, every slot index has changed.
// The caller must sync the BST via getAllEntries():
//
//   auto entries = hashTable.getAllEntries();
//   // rebuild BST or update each node's hashIndex
// ═══════════════════════════════════════════════════════════════

void HashTable::_rehash()
{
    Slot* oldTable = table;
    int   oldSize  = tableSize;

    tableSize = _nextPrime(tableSize * 2);
    table     = new Slot[tableSize];
    count     = 0;
    // totalCollisions intentionally accumulates across rehashes

    for (int i = 0; i < oldSize; ++i)
        if (oldTable[i].state == OCCUPIED)
            insert(oldTable[i].data);   // re-hash into the new table

    delete[] oldTable;
}

// ═══════════════════════════════════════════════════════════════
// getAllEntries
//
// Returns (flight_number, current_index) for every OCCUPIED slot.
// Use this after a rehash to update BST node hashIndex fields.
// ═══════════════════════════════════════════════════════════════

vector<pair<string, int>> HashTable::getAllEntries() const
{
    vector<pair<string, int>> entries;
    entries.reserve(count);
    for (int i = 0; i < tableSize; ++i)
        if (table[i].state == OCCUPIED)
            entries.emplace_back(table[i].data.getFlightNumber(), i);
    return entries;
}

// ═══════════════════════════════════════════════════════════════
// Statistics
// ═══════════════════════════════════════════════════════════════

double HashTable::loadFactor() const
{
    return static_cast<double>(count) / tableSize;
}

// getLongestPath — scans every OCCUPIED slot and measures how far
// it sits from its home index.  Reflects the current state of the
// table (may change after deletions/rehashing).
int HashTable::getLongestPath() const
{
    int longest = 0;
    for (int i = 0; i < tableSize; ++i)
    {
        if (table[i].state == OCCUPIED)
        {
            int home = _hash(table[i].data.getFlightNumber());
            int path = ((i - home) + tableSize) % tableSize;
            if (path > longest) longest = path;
        }
    }
    return longest;
}

void HashTable::printStats() const
{
    cout << "=== Hash Table Statistics ===" << endl;
    cout << "  Table size       : " << tableSize                   << endl;
    cout << "  Occupied slots   : " << count                       << endl;
    cout << fixed << setprecision(2);
    cout << "  Load factor      : " << loadFactor() * 100 << "%"   << endl;
    cout << "  Total collisions : " << totalCollisions             << endl;
    cout << "  Longest path     : " << getLongestPath()            << endl;
}

void HashTable::printTable() const
{
    for (int i = 0; i < tableSize; ++i)
    {
        cout << "[" << setw(2) << i << "] ";
        switch (table[i].state)
        {
            case EMPTY:
                cout << "-- empty --\n";
                break;
            case DELETED:
                cout << "-- deleted --\n";
                break;
            case OCCUPIED:
                cout << table[i].data.getFlightNumber()
                     << "  " << table[i].data.getOrigin()
                     << " -> " << table[i].data.getDestination()
                     << "\n";
                break;
        }
    }
}
