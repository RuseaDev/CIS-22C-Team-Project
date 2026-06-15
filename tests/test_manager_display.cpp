#include "test_utils.h"

#include "../include/fileIO.h"
#include "../include/manager.h"

#include <iostream>

using namespace std;

void displayFlight(const Flight &flight);
int choiceInput();

void testDisplayAndManager(TestRunner &t) {
  printGroup("Display / Manager");

  HashTable hashTable(determineHashSize(SAMPLE_FILE));
  BST bst;
  loadSample(hashTable, bst);

  // UI-01: Display one flight and check that labels are printed.
  Flight aa101;
  hashTable.getAtIndex(bst.search("AA101"), aa101);
  string flightOutput = captureOutput([&]() { displayFlight(aa101); });

  printResult(t, "UI-01 search display labels flight number",
              contains(flightOutput, "Flight Number: AA101"));
  printResult(t, "UI-01 search display labels origin",
              contains(flightOutput, "Origin: JFK - New York"));
  printResult(t, "UI-01 search display labels status",
              contains(flightOutput, "Status: On Time"));

  // UI-02: The new letter menu is printed.
  string menuOutput =
      withInput("Q\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-02 letter menu prints add option",
              contains(menuOutput, "[A] - Add data"));
  printResult(t, "UI-02 letter menu prints undo option",
              contains(menuOutput, "[U] - Undo delete"));
  printResult(t, "UI-02 letter menu prints quit option",
              contains(menuOutput, "[Q] - Quit"));

  // UI-03: Use the list menu option.
  string displayAllOutput =
      withInput("L\nQ\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-03 list records prints table index 0",
              contains(displayAllOutput, "[ 0] IB2323"));
  printResult(t, "UI-03 list records prints table index 37",
              contains(displayAllOutput, "[37] AA101"));

  // UI-04: Lowercase commands are accepted.
  HashTable lowercaseTable(determineHashSize(SAMPLE_FILE));
  BST lowercaseBST;
  loadSample(lowercaseTable, lowercaseBST);
  string lowercaseOutput =
      withInput("a" + validInsertInput("ZZ997") + "q\n",
                [&]() { displayManager(lowercaseTable, lowercaseBST); });

  printResult(t, "UI-04 lowercase add inserts record",
              contains(lowercaseOutput, "Flight inserted at index"));
  printResult(t, "UI-04 lowercase quit exits cleanly",
              contains(lowercaseOutput, "Exiting..."));

  // UI-05: Enter an invalid menu choice.
  string invalidMenuOutput =
      withInput("X\nQ\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-05 invalid menu choice prints validation message",
              contains(invalidMenuOutput, "Invalid choice, please try again"));

  // UI-06: Statistics command prints hash table stats.
  string statsOutput =
      withInput("T\nQ\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-06 statistics command prints stats",
              contains(statsOutput, "=== Hash Table Statistics ==="));

  // UI-07: Write command saves records to the requested file.
  const string menuSaveFile = TMP_DIR + "/menu_save.txt";
  string writeOutput = withInput(
      "W\n" + menuSaveFile + "\nQ\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-07 write command prints save count",
              contains(writeOutput, "records saved to " + menuSaveFile));
  printResult(t, "UI-07 write command writes CSV header",
              readFirstLine(menuSaveFile) == FILE_HEADER);

  // UI-08: Primary key search command finds a flight.
  string searchOutput =
      withInput("P\nAA101\nQ\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-08 primary key search finds AA101",
              contains(searchOutput, "Found flight:"));
  printResult(t, "UI-08 primary key search prints flight number",
              contains(searchOutput, "Flight Number: AA101"));

  // UI-09: Secondary key search finds all flights for an airline name.
  string secondaryOutput =
      withInput("S\nAmerican Airlines\nQ\n",
                [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-09 secondary key search finds AA101",
              contains(secondaryOutput, "Flight Number: AA101"));
  printResult(t, "UI-09 secondary key search finds AA909",
              contains(secondaryOutput, "Flight Number: AA909"));

  // UI-10: Secondary key search reports when no airline matches.
  string secondaryMissingOutput =
      withInput("S\nMissing Airline\nQ\n",
                [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-10 secondary key missing airline prints not found",
              contains(secondaryMissingOutput,
                       "No flights found for that airline."));

  // UI-11: Undo delete command restores the most recently deleted flight.
  HashTable undoTable(determineHashSize(SAMPLE_FILE));
  BST undoBST;
  loadSample(undoTable, undoBST);
  string undoOutput = withInput(
      "D\nBA505\ny\nU\nQ\n", [&]() { displayManager(undoTable, undoBST); });

  printResult(t, "UI-11 undo command restores deleted flight",
              contains(undoOutput, "Flight restored."));
  printResult(t, "UI-11 undo command makes BA505 searchable again",
              undoBST.search("BA505") != -1);

  // UI-12: Enter text where a number is expected.
  string nonNumericOutput = withInput("abc\n2\n", []() {
    int choice = choiceInput();
    cout << "choice=" << choice;
  });

  printResult(t, "UI-12 non-numeric choice prints validation message",
              contains(nonNumericOutput, "Invalid choice, please try again"));
  printResult(t, "UI-12 non-numeric choice eventually returns valid number",
              contains(nonNumericOutput, "choice=2"));
}
