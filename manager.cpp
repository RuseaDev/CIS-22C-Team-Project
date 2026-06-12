#include "manager.h"
#include "HashTable.h"
#include "flight.h"
#include <iostream>

using namespace std;

// util function
int choiceInput() {
  int choice;
  cin >> choice;
  while (cin.fail()) {
    cout << "Invalid choice, please try again" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter your choice: ";
    cin >> choice;
  }
  return choice;
}

// Managers

void displayManager(const HashTable &hashTable) {
  int choice;
  cout << "1. Display menu " << endl;
  cout << "2. Display all records " << endl;
  cout << "Any other number to quit." << endl;
  cout << "Enter your choice: ";

  choice = choiceInput();

  switch (choice) {
  case 1:
    cout << "Display menu" << endl;
    cout << "watchu wanna do?" << endl;
    cout << "1. Insert\n 2. Update\n 3. Delete\n 4. Undo Delete\n 5. Search\n "
            "6.Display\n Any other number to quit"
         << endl;

    switch (choiceInput()) {
    case 1:
      insertManager();
      break;
    case 2:
      updateManager();
      break;
    case 3:
      deleteManager();
      break;
    case 4:
      undoDeleteManager();
      break;
    case 5:
      searchManager(hashTable);
      break;
    default:
      cout << "Existing..." << endl;
      break;
    }
    break;
  case 2:
    cout << "Display all records" << endl;
    hashTable.printTable();

    break;
  default:
    cout << "Existing..." << endl;
    break;
  }
}

void searchManager(const HashTable &hashTable) {
  string key;
  cout << "Enter the flight ID to search: ";

  cin >> key;
  int index = hashTable.search(key);

  if (index == -1) {
    cout << "Flight not found." << endl;
    return;
  }

  Flight flight;
  if (hashTable.getAtIndex(index, flight)) {
    cout << "Found flight:" << endl;
    cout << "ID: " << flight.getFlightID() << endl;
    cout << "Flight Number: " << flight.getFlightNumber() << endl;
    cout << "Origin: " << flight.getOrigin() << endl;
    cout << "Destination: " << flight.getDestination() << endl;
    cout << "Departure: " << flight.getDepartureTime() << endl;
    cout << "Arrival: " << flight.getArrivalTime() << endl;
    cout << "Status: " << flight.getStatus() << endl;
  }
}

void deleteManager() {
  cout << "Delete Manager\n";
  cout << endl;
}

void updateManager() {
  cout << "update";
  cout << endl;
}

void undoDeleteManager() {
  cout << "undo";
  cout << endl;
}

void insertManager() {
  cout << "insert";
  cout << endl;
}
