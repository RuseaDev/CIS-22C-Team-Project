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

  // UI-02: Use the display-all menu option.
  string displayAllOutput =
      withInput("2\n9\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-02 display all records prints table index 0",
              contains(displayAllOutput, "[ 0] IB2323"));
  printResult(t, "UI-02 display all records prints table index 37",
              contains(displayAllOutput, "[37] AA101"));

  // UI-03: Use the hidden hash table display option.
  string hiddenOutput =
      withInput("1\n6\n9\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-03 hidden diagnostic option prints hash table",
              contains(hiddenOutput, "[46] SW404"));

  // UI-04: Enter an invalid submenu choice.
  string invalidSubmenuOutput =
      withInput("1\n9\n9\n", [&]() { displayManager(hashTable, bst); });

  printResult(t, "UI-04 invalid submenu choice returns cleanly",
              contains(invalidSubmenuOutput, "Returning to main menu"));

  // UI-05: Enter text where a number is expected.
  string nonNumericOutput = withInput("abc\n2\n", []() {
    int choice = choiceInput();
    cout << "choice=" << choice;
  });

  printResult(t, "UI-05 non-numeric choice prints validation message",
              contains(nonNumericOutput, "Invalid choice, please try again"));
  printResult(t, "UI-05 non-numeric choice eventually returns valid number",
              contains(nonNumericOutput, "choice=2"));
}
