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
├──────────────────────────────────────────────┤
│ + Flight()                                   │
│ + Flight(flight_number, origin, destination, │
│           departure_time, arrival_time,      │
│           status: string)                   │
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

### Stack *(not yet implemented — placeholder)*

```
┌──────────────────────────────────────────────┐
│                    Stack                     │
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

*(Fill in once the Stack class is implemented.)*

---

---

## Simplified Relationship Diagram

> Only member **names** are shown — no types, no parameters.

```
┌───────────┐                    ┌────────────┐
│  Airplane │                    │   Flight   │
└─────┬─────┘                    └──────▲─────┘
      │ (planned has-a)                 │ (contained in Slot)
      └────────────────────────────     │
                                  ┌─────┴──────────┐
                                  │   HashTable    │◆──────────────────┐
                                  │                │  (owns Slot array) │
                                  └───────┬────────┘               ┌───▼───┐
                                          │                         │ Slot  │
                                          │ (hashIndex links)       └───────┘
                                          │
                                  ┌───────▼────────┐
                                  │      BST       │◆──────────────────────────┐
                                  └────────────────┘  (owns BSTNodes)          │
                                                                          ┌─────▼────┐
                                                                          │ BSTNode  │◄──┐
                                                                          │  left    │   │ (self-ref)
                                                                          │  right   │───┘
                                                                          └──────────┘

                                  ┌────────────────┐
                                  │     Stack      │◆── Flight  (undo/delete buffer)
                                  └────────────────┘
```

---

### Simplified Class List (names only)

```
┌───────────┐       ┌──────────────┐ ◆──▶ ┌──────────┐
│  Airplane │       │  HashTable   │      │   Slot   │
└─────┬─────┘       └──────┬───────┘      └────┬─────┘
      │ (planned)           │ uses              │ contains
      │ has-a               │ hashIndex         ▼
      ▼                     │            ┌──────────┐
  ┌────────┐                └───────────▶│  Flight  │
  │ Flight │                             └──────────┘
  └────────┘

┌──────────┐ ◆        ┌──────────┐  ◄──┐
│   BST    │──────────│ BSTNode  │     │ (left / right)
└──────────┘  owns    └──────────┘─────┘

┌───────────┐ ◆
│   Stack   │──────── Flight  (planned undo stack)
└───────────┘
```

---

### Relationship Legend

| Symbol   | Meaning                                                       |
|----------|---------------------------------------------------------------|
| `◆────`  | **Composition** — owner manages lifetime (filled diamond)     |
| `o────`  | **Aggregation** — uses but does not own (open diamond)        |
| `──▶`   | **Association / dependency**                                  |
| `──▷`   | **Inheritance** (none yet in this project)                    |

---

### Summary of Relationships

| Relationship                    | Type        | Notes                                                      |
|---------------------------------|-------------|------------------------------------------------------------|
| `BST` → `BSTNode`               | Composition | BST creates and destroys all nodes via `root`              |
| `BSTNode` → `BSTNode`           | Self-ref    | `left` and `right` pointers                                |
| `HashTable` → `Slot[]`          | Composition | `table` array owned and deleted by HashTable               |
| `Slot` → `Flight`               | Composition | Each slot holds one Flight object by value                 |
| `BST` ↔ `HashTable`             | Collaboration | `BSTNode::hashIndex` maps back into HashTable's array    |
| `Stack` → `Flight`              | Aggregation | Holds deleted flights for undo (planned)                   |
| `Airplane` → `Flight`           | Association | Planned has-a relationship — not yet in code               |

> **Note:** `Airplane` is currently a standalone class with no connection to `Flight` in the code.
> Once integrated, `Flight` will likely embed an `Airplane` member (has-a / composition).
