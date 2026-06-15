# Hash Table Algorithms

This document explains the main algorithms used by `HashTable`. The source code
keeps short comments near the implementation; this file holds the longer
algorithm notes.

## Insert With Linear Probing

`HashTable::insert()` stores each flight by its flight number.

The algorithm is:

1. Rehash automatically if the load factor is at least `0.75`.
2. Compute the home index with the polynomial rolling hash.
3. Probe linearly through `(home + i) % tableSize`.
4. Insert at the first available `EMPTY` slot, or reuse the first `DELETED` slot
   seen earlier in the probe sequence.
5. Return the final slot index, or `-1` if the table is completely full.

## Duplicate Handling

During probing, if an `OCCUPIED` slot has the same flight number, insertion stops
and returns that existing slot index. The hash table does not insert a duplicate
and does not increase the active record count.

If an `OCCUPIED` slot has a different flight number, that is a collision. The
algorithm keeps probing until it finds the key, an insertion point, or completes
a full table scan.

## Deleted Slot Reuse

Deletion is lazy: a removed record leaves its slot marked `DELETED` instead of
`EMPTY`. A `DELETED` slot cannot stop a search, because matching records may have
been inserted farther down the same probe chain.

When insertion sees a `DELETED` slot, it remembers the first one but keeps
probing to detect duplicates. If no duplicate is found before an `EMPTY` slot,
the remembered `DELETED` slot is reused. This reclaims space while preserving
correct duplicate detection.

## Collision Counting

The hash table tracks cumulative collision cost in `totalCollisions`.

For a normal insert, the collision count is the number of probe steps needed to
reach the insertion point. If insertion reuses a `DELETED` slot, the count uses
the probe distance to that first deleted slot.

`totalCollisions` intentionally accumulates across rehashes, so it represents
work performed over the table's lifetime rather than only the current layout.

## Search With Empty And Deleted Slots

`HashTable::search()` computes the home index, then probes linearly.

- `EMPTY` means the key cannot exist later in that probe chain, so search returns
  `-1`.
- `DELETED` is skipped because it preserves the chain for records inserted past
  the deleted slot.
- `OCCUPIED` with a matching flight number returns that slot index.
- `OCCUPIED` with a different flight number continues probing.

## Lazy Deletion

`remove()` and `removeAtIndex()` mark a slot as `DELETED` and decrement the
active count. They do not clear the slot to `EMPTY`, because doing so would break
linear-probing searches for records stored after that slot.

The caller is responsible for removing the same key from the BST, because the
BST stores hash table indexes for primary-key lookup.

## Rehashing

`_rehash()` grows the table to the next prime number after `tableSize * 2`.

It reinserts every `OCCUPIED` record into the new table and drops `DELETED`
slots. In that sense, rehashing also works as a cleanup pass for lazily deleted
slots.

After a rehash, slot indexes can change. Any structure storing hash indexes must
be synchronized.

## BST Index Sync After Rehash

The BST maps flight numbers to hash table slot indexes. Since rehashing moves
records to new slots, BST indexes become stale after the table grows.

Callers detect rehashing by comparing the table size before and after insertion.
If the size changed, they rebuild the BST using:

```cpp
auto entries = hashTable.getAllEntries();
```

`getAllEntries()` returns every active `(flight_number, current_index)` pair so
the BST can be rebuilt with correct slot indexes.

## Statistics

`loadFactor()` reports active records divided by table size.

`getLongestPath()` scans occupied slots and measures how far each record sits
from its home index. This reflects the current table layout and can change after
insertions, deletions, and rehashing.

`printStats()` displays table size, occupied slots, load factor, total
collisions, and longest path.
