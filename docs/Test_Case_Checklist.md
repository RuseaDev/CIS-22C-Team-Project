# Flight Database Test Case 

Project task: Flight database with File I/O, Hash Table, BST, Display Manager, and Undo Delete  
Test data: `sample_input.txt` with 25 flight records

## File I/O Test Cases

- `FI-01` Valid file load
  - Menu action: Start the program and enter `sample_input.txt`.
  - Test data: Original 25-record input file.
  - Expected result: Program reports `25 records loaded successfully`; hash table size is `53`; load factor is `47.17%`.
  - Purpose: Confirms the program can open, read, and load the required input file.

- `FI-02` Wrong file name
  - Menu action: Start the program and enter `wrongfile.txt`.
  - Test data: File name that does not exist.
  - Expected result: Program prints `Error: File not found` and exits or returns safely.
  - Purpose: Confirms missing-file error handling.

- `FI-03` Empty input file
  - Menu action: Start the program with a text file that only has the header row.
  - Test data: Header-only `.txt` file using the same field layout as the input file.
  - Expected result: Program reports zero records loaded or gives a clear empty-file message; no crash occurs.
  - Purpose: Confirms the program handles an input file with no flight records.

- `FI-04` Duplicate record inside file
  - Menu action: Start the program with a file that contains a second `AA101` row.
  - Test data: Modified input file with one duplicate flight number.
  - Expected result: Duplicate `AA101` is skipped; active record count remains `25`; original `AA101` remains unchanged.
  - Purpose: Confirms duplicate flight numbers do not create duplicate records or overwrite existing data.

- `FI-05` Save to file format
  - Menu action: Load `sample_input.txt`, then save the records to an output file.
  - Test data: Original 25-record input file.
  - Expected result: Saved `.txt` file uses the same header and field order as the input file: `flight_number, airline_name, origin, destination, departure_time, arrival_time, status, aircraft_type, seat_capacity`.
  - Purpose: Save to File must preserve the input `.txt` file format.

- `FI-06` Save after delete
  - Menu action: Delete `AA101`, confirm delete, then save to file.
  - Test data: Original file after deleting one record.
  - Expected result: Saved `.txt` file does not contain `AA101`; all remaining records still use the same field order as the input file.
  - Purpose: Confirms deleted records are not written to the saved output file.

## Hash Table Test Cases

- `HT-01` Initial hash table layout
  - Menu action: Load `sample_input.txt`, then display the hash table.
  - Test data: Original 25-record input file.
  - Expected result: Table size is `53`; occupied slots include `0:IB2323`, `37:AA101`, `46:SW404`, `47:QF707`, and `51:JL1818`.
  - Purpose: Confirms records are placed in the expected hash-table positions.

- `HT-02` Wrap-around collision
  - Menu action: Load records through `IB2323`, then inspect the hash-table placement.
  - Test data: Records from `sample_input.txt` through `IB2323`.
  - Expected result: `IB2323` starts at home index `47`, probes through occupied slots `47` through `52`, wraps around, and is stored at index `0`.
  - Purpose: Confirms linear probing wraps from the end of the table back to the beginning.

- `HT-03` Duplicate insert
  - Menu action: Choose Insert and enter an existing flight number, `BA505`.
  - Test data: Existing record `BA505`.
  - Expected result: Insert is rejected or cancelled; record count does not increase; existing `BA505` is unchanged.
  - Purpose: Confirms duplicate primary keys are not allowed.

- `HT-04` Long collision chain
  - Menu action: Load records through `JL1818`, then inspect the hash-table placement.
  - Test data: Records from `sample_input.txt` through `JL1818`.
  - Expected result: `JL1818` starts at home index `46` and is stored at index `51` after probing past occupied slots.
  - Purpose: Demonstrates a longer collision chain in the hash table.

- `HT-05` Lazy deletion with `SW404`
  - Menu action: Delete `SW404`, confirm delete, then search for `QF707`.
  - Test data: Original file after deleting `SW404`.
  - Expected result: `SW404` is removed; its hash-table slot is treated as deleted, not empty; `QF707` is still found at index `47`.
  - Purpose: Combining hash-table lazy deletion with the BST two-child delete case.

- `HT-06` Search not found
  - Menu action: Search for `ZZ000`.
  - Test data: Flight number not present in the file.
  - Expected result: Program prints `Flight not found.`
  - Purpose: Confirms unsuccessful search is handled clearly.

- `HT-07` Hash table statistics
  - Menu action: Load all records and display hash-table statistics.
  - Test data: Original 25-record input file.
  - Expected result: Table size `53`; occupied slots `25`; load factor `47.17%`; total collisions `15`; longest path `6`.
  - Purpose: Confirms collision tracking, load factor, and longest probe path.

- `HT-08` Rehash trigger
  - Menu action: Load the original file, then insert enough new unique records to pass the rehash threshold.
  - Test data: Original file plus additional unique test flights.
  - Expected result: Hash table resizes from `53` to `107`, and all active records remain searchable after resizing.
  - Purpose: Confirms automatic resizing keeps the hash table and BST index consistent.

## BST Test Cases

- `BST-01` Sorted traversal
  - Menu action: Load `sample_input.txt`, then display records sorted by flight number.
  - Test data: Original 25-record input file.
  - Expected result: Flight numbers appear in alphabetical order.
  - Purpose: Confirms the BST stores flight numbers in sorted order.

- `BST-02` Search existing key
  - Menu action: Search for `AA101`.
  - Test data: Existing flight number.
  - Expected result: Program finds `AA101` and displays its flight details.
  - Purpose: Confirms successful BST-backed search.

- `BST-03` Search missing key
  - Menu action: Search for `XX999`.
  - Test data: Flight number not present in the file.
  - Expected result: Program prints `Flight not found.`
  - Purpose: Confirms unsuccessful BST-backed search.

- `BST-04` Delete node with two children
  - Menu action: Delete `SW404`, confirm delete, then display records sorted by flight number.
  - Test data: Original file after deleting `SW404`.
  - Expected result: `SW404` no longer appears; sorted display remains in alphabetical order.
  - Purpose: Covers teacher feedback to include a delete case for a BST node with two children.

- `BST-05` Indented tree display
  - Menu action: Load `sample_input.txt`, then display the indented BST.
  - Test data: Original 25-record input file.
  - Expected result: Tree is displayed as a rotated tree with indentation by level.
  - Purpose: Confirms the tree structure display is understandable and does not change stored data.

- `BST-06` Empty tree guard
  - Menu action: Check BST behavior before any records are inserted.
  - Test data: Empty BST.
  - Expected result: Empty-tree check returns true; traversal produces no records and does not crash.
  - Purpose: Confirms empty-tree operations are safe.

## Screen Output and Display Manager Test Cases

-  `UI-01` Search output format
  - Menu action: Search for `AA101`.
  - Test data: Existing flight number.
  - Expected result: Output shows labeled fields, one field per line: flight number, origin, destination, departure, arrival, and status.
  - Purpose: Confirms search results are readable on screen.

- `UI-02` Display all records
  - Menu action: Choose Display All Records after loading `sample_input.txt`.
  - Test data: Original 25-record input file.
  - Expected result: All 25 active records are displayed with their hash-table index positions.
  - Purpose: Confirms the display option shows the loaded records.

- `UI-03` Diagnostic display
  - Menu action: Choose the hidden or diagnostic display option.
  - Test data: Original 25-record input file.
  - Expected result: Internal hash table or BST structure is displayed without changing any records.
  - Purpose: Confirms diagnostic display can be used for demonstration.

- `UI-04` Invalid numeric display choice
  - Menu action: Enter `9`, then enter a valid choice.
  - Test data: Out-of-range menu choice.
  - Expected result: Program rejects or exits the invalid choice cleanly and still accepts the next valid choice.
  - Purpose: Confirms invalid menu choices do not crash the program.

- `UI-05` Non-numeric menu input
  - Menu action: Enter `abc` at a numeric menu prompt, then enter a valid number.
  - Test data: Non-numeric input.
  - Expected result: Program prints `Invalid choice, please try again`, clears the input error, and accepts the next valid number.
  - Purpose: Confirms menu input validation.

## Insert, Update, Delete, and Undo Test Cases

- `CRUD-01` Insert valid flight
  - Menu action: Choose Insert and enter a new flight number `ZZ999` with valid flight data.
  - Test data: New unique flight record.
  - Expected result: Program prints the inserted hash index; searching for `ZZ999` finds the new record.
  - Purpose: Confirms insert updates both storage and search results.

- `CRUD-02` Insert empty flight number
  - Menu action: Choose Insert and press Enter without typing a flight number.
  - Test data: Empty flight-number field.
  - Expected result: Program prints `Insert cancelled. Flight number cannot be empty.`
  - Purpose: Confirms invalid primary keys are rejected.

- `CRUD-03` Insert duplicate through menu
  - Menu action: Choose Insert and enter existing flight number `AA101`.
  - Test data: Existing flight number.
  - Expected result: Program prints `Insert cancelled. Flight already exists.`
  - Purpose: Confirms duplicate insert is blocked at the menu level.

- `CRUD-04` Invalid seat capacity
  - Menu action: Choose Insert, enter a negative or non-number seat capacity, then enter a valid value.
  - Test data: Invalid seat capacity followed by valid seat capacity.
  - Expected result: Program prints `Invalid seat capacity, please try again`; insert continues only after a valid non-negative value.
  - Purpose: Confirms numeric validation for seat capacity.

- `CRUD-05` Update flight status
  - Menu action: Choose Update for `DL303` and change status from `Delayed` to `On Time`.
  - Test data: Existing flight `DL303`.
  - Expected result: Program prints `Flight updated.`; searching `DL303` shows status `On Time`; flight number remains `DL303`.
  - Purpose: Confirms update changes non-key data without changing the primary key.

- `CRUD-06` Cancel delete
  - Menu action: Choose Delete for `BA505`, then answer `n` at confirmation.
  - Test data: Existing flight `BA505`.
  - Expected result: Program prints `Delete cancelled.`; searching `BA505` still finds the record.
  - Purpose: Confirms delete confirmation is respected.

- `CRUD-07` Confirm delete
  - Menu action: Choose Delete for `AA101`, answer `y`, then search for `AA101`.
  - Test data: Existing flight `AA101`.
  - Expected result: Program prints `Flight deleted.`; searching `AA101` returns `Flight not found.`
  - Purpose: Confirms confirmed delete removes the record from both display/search behavior.

- `CRUD-08` Undo empty stack
  - Menu action: Choose Undo Delete before deleting any flight.
  - Test data: No deleted records.
  - Expected result: Program prints `No deleted flights to restore.`
  - Purpose: Confirms undo handles an empty delete history.

- `CRUD-09` Undo restores only the most recent delete
  - Menu action: Delete `AA101`, delete `DL303`, choose Undo Delete once, then search both records.
  - Test data: Two deleted records.
  - Expected result: `DL303` is restored and found; `AA101` is still not found.
  - Purpose: One undo request restores only the most recently deleted item.

- `CRUD-10` Delete, Save to File, then Undo Delete
  - Menu action: Delete `AA101`, save to file, then choose Undo Delete.
  - Test data: One deleted record followed by Save to File.
  - Expected result: Saved file does not contain `AA101`; undo delete is not possible after saving, or it does not change the saved file.
  - Purpose: Save to File commits the deletion before undo is attempted.

## Final Acceptance Criteria

- Test cases use `sample_input.txt` unless the case explicitly says to use a modified input file.
- Expected hash values use polynomial rolling hash with base `31` and table size `53`.
- `SW404` is used to avoid redundant delete cases because it covers both a two-child BST delete and hash-table lazy deletion.
- Save-to-file tests explicitly verify that the output `.txt` file keeps the same field order as the input `.txt` file.
