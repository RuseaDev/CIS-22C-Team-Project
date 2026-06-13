# CIS 22C Team Project — UML Class Diagrams

---

## Complete UML Diagrams

### Flight

```
┌──────────────────────────────────────────────┐
│                    Flight                    │
├──────────────────────────────────────────────┤
│ - flight_number:   string                    │
│ - origin:          string                    │
│ - destination:     string                    │
│ - departure_time:  string                    │
│ - arrival_time:    string                    │
│ - status:          string                    │
│ - airplane:        Airplane                  │
├──────────────────────────────────────────────┤
│ + Flight()                                   │
│ + Flight(flight_number, origin, destination, │
│           departure_time, arrival_time,      │
│           status: string,                    │
│           airplane: Airplane)                │
│ + setFlightNumber(flight_number: string): void│
│ + setOrigin(origin: string): void            │
│ + setDestination(destination: string): void  │
│ + setDepartureTime(departure_time: string):  │
│                                          void│
│ + setArrivalTime(arrival_time: string): void │
│ + setStatus(status: string): void            │
│ + getFlightNumber(): string                  │
│ + getOrigin(): string                        │
│ + getDestination(): string                   │
│ + getDepartureTime(): string                 │
│ + getArrivalTime(): string                   │
│ + getStatus(): string                        │
│ + getAirplane(): Airplane                    │
└──────────────────────────────────────────────┘
```

---

### Airplane

```
┌──────────────────────────────────────────────┐
│                   Airplane                   │
├──────────────────────────────────────────────┤
│ - aircraft_id:     string                    │
│ - aircraft_type:   string                    │
│ - seat_capacity:   int                       │
│ - airline_name:    string                    │
│ - seats_occupied:  int                       │
├──────────────────────────────────────────────┤
│ + Airplane()                                 │
│ + Airplane(aircraft_id, aircraft_type,       │
│             airline_name: string,            │
│             seat_capacity, seats_occupied:   │
│                                          int)│
│ + setAirplaneId(airplane_id: string): void   │
│ + setAirlineName(airline_name: string): void │
│ + setAircraftType(aircraft_type: string):void│
│ + setSeatCapacity(seat_capacity: int): void  │
│ + setSeatsOccupied(seats_occupied: int): void│
│ + getAirplaneId(): string                    │
│ + getAirlineName(): string                   │
│ + getAircraftType(): string                  │
│ + getSeatCapacity(): int                     │
│ + getSeatsOccupied(): int                    │
│ + isSeatEmpty(): bool                        │
└──────────────────────────────────────────────┘
```

---

### BSTNode *(struct)*

```
┌──────────────────────────────────────────────┐
│               <<struct>> BSTNode             │
├──────────────────────────────────────────────┤
│ + key:        string                         │
│ + hashIndex:  int                            │
│ + left:       BSTNode*                       │
│ + right:      BSTNode*                       │
├──────────────────────────────────────────────┤
│ + BSTNode(k: string, idx: int)               │
└──────────────────────────────────────────────┘
```

---

### BST

```
┌──────────────────────────────────────────────┐
│                     BST                      │
├──────────────────────────────────────────────┤
│ - root: BSTNode*                             │
├──────────────────────────────────────────────┤
│ - _insert(node: BSTNode*, key: string,       │
│            hashIndex: int): BSTNode*         │
│ - _remove(node: BSTNode*,                    │
│            key: string): BSTNode*            │
│ - _findMin(node: BSTNode*): BSTNode*         │
│ - _inorder(node: BSTNode*): void             │
│ - _printIndented(node: BSTNode*,             │
│                   level: int): void          │
│ - _destroyTree(node: BSTNode*): void         │
├──────────────────────────────────────────────┤
│ + BST()                                      │
│ + ~BST()                                     │
│ + insert(key: string, hashIndex: int): void  │
│ + remove(key: string): void                  │
│ + clear(): void                              │
│ + inorder(): void                            │
│ + printIndented(): void                      │
│ + isEmpty(): bool                            │
└──────────────────────────────────────────────┘
```

---

### HashTable *(with inner Slot struct and SlotState enum)*

```
┌──────────────────────────────────────────────┐
│                  HashTable                   │
├──────────────────────────────────────────────┤
│         <<enum>> SlotState                   │
│         EMPTY, OCCUPIED, DELETED             │
├──────────────────────────────────────────────┤
│         <<inner struct>> Slot                │
│         + data:  Flight                      │
│         + state: SlotState                   │
│         + Slot()                             │
├──────────────────────────────────────────────┤
│ - table:           Slot*                     │
│ - tableSize:       int                       │
│ - count:           int                       │
│ - totalCollisions: int                       │
├──────────────────────────────────────────────┤
│ - _hash(key: string): int                    │
│ - _rehash(): void                            │
│ - _isPrime(n: int): bool                     │
│ - _nextPrime(n: int): int                    │
├──────────────────────────────────────────────┤
│ + HashTable(initialCapacity: int)            │
│ + ~HashTable()                               │
│ + insert(flight: Flight): int                │
│ + search(key: string): int                   │
│ + getAtIndex(idx: int, out: Flight&): bool   │
│ + remove(key: string): bool                  │
│ + update(key: string,                        │
│           updatedFlight: Flight): bool       │
│ + getAllEntries():                            │
│     vector<pair<string,int>>                 │
│ + loadFactor(): double                       │
│ + getTotalCollisions(): int                  │
│ + getLongestPath(): int                      │
│ + getCount(): int                            │
│ + getTableSize(): int                        │
│ + printStats(): void                         │
│ + printTable(): void                         │
└──────────────────────────────────────────────┘
```

---

### Stack *(with inner StackNode struct)*

```
┌──────────────────────────────────────────────┐
│                    Stack                     │
├──────────────────────────────────────────────┤
│         <<inner struct>> StackNode           │
│         + data: Flight                       │
│         + next: StackNode*                   │
│         + StackNode(flight: Flight)          │
├──────────────────────────────────────────────┤
│ - top:   StackNode*                          │
│ - count: int                                 │
├──────────────────────────────────────────────┤
│ + Stack()                                    │
│ + ~Stack()                                   │
│ + push(flight: Flight): void                 │
│ + pop(): Flight                              │
│ + peek(): Flight                             │
│ + isEmpty(): bool                            │
│ + getCount(): int                            │
└──────────────────────────────────────────────┘
```

---

### Manager *(free-function module)*

> Not a class — these are free functions declared in `manager.h` / `manager.cpp`.
> A file-scope `Stack deletedFlights` serves as the undo buffer.

```
┌──────────────────────────────────────────────┐
│              <<module>> Manager              │
├──────────────────────────────────────────────┤
│ ~ deletedFlights: Stack          (static)    │
├──────────────────────────────────────────────┤
│ ~ displayFlight(flight: Flight): void        │
│ ~ choiceInput(): int                         │
│ ~ findFlight(hashTable: HashTable,           │
│               key: string,                   │
│               flight: Flight&): bool         │
├──────────────────────────────────────────────┤
│ + searchManager(hashTable: HashTable): void  │
│ + displayManager(hashTable: HashTable): void │
│ + deleteManager(hashTable: HashTable): void  │
│ + insertManager(): void                      │
│ + updateManager(hashTable: HashTable): void  │
│ + undoDeleteManager(                         │
│       hashTable: HashTable): void            │
└──────────────────────────────────────────────┘
```

*(~ = file-scope / internal linkage; not accessible outside manager.cpp)*

---

### FileIO *(free-function module)*

> Not a class — these are free functions declared in `fileIO.h` / `fileIO.cpp`.

```
┌──────────────────────────────────────────────┐
│              <<module>> FileIO               │
├──────────────────────────────────────────────┤
│ + isPrime(n: int): bool                      │
│ + determineHashSize(filename: string): int   │
│ + parseLine(line: string): Flight            │
│ + readFile(filename: string,                 │
│             hashTable: HashTable&,           │
│             bst: BST&): void                 │
│ + saveToFile(filename: string,               │
│               hashTable: HashTable&): void   │
└──────────────────────────────────────────────┘
```

---

---

## Simplified Relationship Diagram

> Only member **names** are shown — no types, no parameters.

```
┌───────────┐
│  Airplane │◄──────────────────────────────────────┐
└─────┬─────┘                                        │ (has-a, by value)
      │                                              │
      │                                   ┌──────────┴─────┐
      │                                   │    Flight      │
      │                                   └───────▲────────┘
      │                                           │ (contained in Slot)
      │                               ┌───────────┴────────────┐
      │                               │       HashTable        │◆──────────────┐
      │                               │                        │ (owns Slot[]) │
      │                               └───────────┬────────────┘           ┌───▼───┐
      │                                           │                        │ Slot  │
      │                                           │ (hashIndex links)      └───────┘
      │                                           │
      │                               ┌───────────▼────────────┐
      │                               │          BST           │◆──────────────────────┐
      │                               └────────────────────────┘ (owns BSTNodes)       │
      │                                                                          ┌──────▼───┐
      │                                                                          │ BSTNode  │◄──┐
      │                                                                          │  left    │   │ (self-ref)
      │                                                                          │  right   │───┘
      │                                                                          └──────────┘

┌─────┴──────────────────────────────────────────────────────────────────┐
│                         Manager (module)                               │
│  uses: HashTable, Stack, Flight                                        │
└────────────────────────────────────────────────────────────────────────┘
        │
        │ owns (file-scope)
        ▼
┌───────────────┐
│     Stack     │◆──── StackNode ──── Flight   (undo/delete buffer)
└───────────────┘

┌────────────────────────────────────────────────────────────────────────┐
│                         FileIO (module)                                │
│  uses: HashTable, BST, Flight                                          │
└────────────────────────────────────────────────────────────────────────┘
```

---

### Simplified Class List (names only)

```
┌───────────┐ ◆
│  Airplane │──────── (embedded in Flight)
└─────┬─────┘
      │ has-a (by value)
      ▼
┌──────────┐       ┌──────────────┐ ◆──▶ ┌──────────┐
│  Flight  │◄──────│  HashTable   │      │   Slot   │
└──────────┘       └──────┬───────┘      └──────────┘
                          │ uses hashIndex
                          ▼
                   ┌──────────┐ ◆        ┌──────────┐  ◄──┐
                   │   BST    │──────────│ BSTNode  │     │ (left / right)
                   └──────────┘  owns    └──────────┘─────┘

┌───────────┐ ◆         ┌───────────┐ ◆
│   Stack   │───────────│ StackNode │──── Flight
└───────────┘  owns     └───────────┘

┌───────────────┐         ┌───────────────┐
│    Manager    │─uses──▶ │   HashTable   │
│   (module)    │─uses──▶ │     Stack     │
└───────────────┘         └───────────────┘

┌───────────────┐         ┌───────────────┐
│    FileIO     │─uses──▶ │   HashTable   │
│   (module)    │─uses──▶ │      BST      │
└───────────────┘         └───────────────┘
```

---

### Relationship Legend

| Symbol   | Meaning                                                       |
|----------|---------------------------------------------------------------|
| `◆────`  | **Composition** — owner manages lifetime (filled diamond)     |
| `o────`  | **Aggregation** — uses but does not own (open diamond)        |
| `──▶`    | **Association / dependency**                                  |
| `──▷`    | **Inheritance** (none in this project)                        |

---

### Summary of Relationships

| Relationship                    | Type          | Notes                                                                  |
|---------------------------------|---------------|------------------------------------------------------------------------|
| `Flight` → `Airplane`           | Composition   | `Flight` embeds `Airplane` by value; `getAirplane()` exposed           |
| `BST` → `BSTNode`               | Composition   | BST creates and destroys all nodes via `root`                          |
| `BSTNode` → `BSTNode`           | Self-ref      | `left` and `right` pointers                                            |
| `HashTable` → `Slot[]`          | Composition   | `table` array owned and deleted by HashTable                           |
| `Slot` → `Flight`               | Composition   | Each slot holds one Flight object by value                             |
| `BST` ↔ `HashTable`             | Collaboration | `BSTNode::hashIndex` maps back into HashTable's array                  |
| `Stack` → `StackNode`           | Composition   | Stack owns its linked list of StackNodes                               |
| `Stack` → `Flight`              | Composition   | Each StackNode holds a Flight by value (undo buffer in Manager)        |
| `Manager` → `HashTable`         | Dependency    | All manager functions take `HashTable&` as parameter                   |
| `Manager` → `Stack`             | Composition   | File-scope `deletedFlights` Stack owned by manager.cpp                 |
| `FileIO` → `HashTable`, `BST`   | Dependency    | `readFile` / `saveToFile` operate on both structures                   |
