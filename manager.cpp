#include "manager.h"
#include "HashTable.h"
#include "flight.h"
#include <iostream>
#include <limits>

using namespace std;

void displayFlight(const Flight &flight) {
  cout << "Flight Number: " << flight.getFlightNumber() << endl;
  cout << "Origin: " << flight.getOrigin() << endl;
  cout << "Destination: " << flight.getDestination() << endl;
  cout << "Departure: " << flight.getDepartureTime() << endl;
  cout << "Arrival: " << flight.getArrivalTime() << endl;
  cout << "Status: " << flight.getStatus() << endl;
}

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

void displayManager(HashTable &hashTable) {
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
      deleteManager(hashTable);
      break;
    case 4:
      undoDeleteManager();
      break;
    case 5:
      searchManager(hashTable);
      break;
    default:
      cout << "Exiting..." << endl;
      break;
    }
    break;
  case 2:
    cout << "Display all records" << endl;
    hashTable.printTable();

    break;
  default:
    cout << "Exiting..." << endl;
    break;
  }
}

void searchManager(const HashTable &hashTable) {
  string key;
  cout << "Enter the flight number to search: ";

  cin >> key;
  int index = hashTable.search(key);

  if (index == -1) {
    cout << "Flight not found." << endl;
    return;
  }

  Flight flight;
  if (hashTable.getAtIndex(index, flight)) {
    cout << "Found flight:" << endl;
    displayFlight(flight);
  }
}

void deleteManager(HashTable &hashTable) {
  string key;
  cout << "Delete Manager" << endl;
  cout << "Enter the flight number to delete: ";
  cin >> key;

  int index = hashTable.search(key);
  if (index == -1) {
    cout << "Flight not found." << endl;
    return;
  }

  Flight flight;
  if (!hashTable.getAtIndex(index, flight)) {
    cout << "Unable to retrieve flight record." << endl;
    return;
  }

  cout << "Flight to delete:" << endl;
  displayFlight(flight);
  cout << "Confirm delete? (y/n): ";

  char confirm;
  cin >> confirm;
  if (confirm == 'y' || confirm == 'Y') {
    if (hashTable.remove(key)) {
      cout << "Flight deleted." << endl;
    } else {
      cout << "Delete failed." << endl;
    }
  } else {
    cout << "Delete cancelled." << endl;
  }
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
