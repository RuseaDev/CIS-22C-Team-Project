#include "manager.h"
#include "HashTable.h"
#include "Stack.h"
#include "flight.h"
#include <iostream>
#include <limits>

using namespace std;

// util function

static Stack deletedFlights;

void displayFlight(const Flight &flight) {
  cout << "Flight Number: " << flight.getFlightNumber() << endl;
  cout << "Origin: " << flight.getOrigin() << endl;
  cout << "Destination: " << flight.getDestination() << endl;
  cout << "Departure: " << flight.getDepartureTime() << endl;
  cout << "Arrival: " << flight.getArrivalTime() << endl;
  cout << "Status: " << flight.getStatus() << endl;
}

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

bool findFlight(const HashTable &hashTable, const string &key, Flight &flight) {
  int index = hashTable.search(key);
  if (index == -1) {
    cout << "Flight not found." << endl;
    return false;
  }

  if (!hashTable.getAtIndex(index, flight)) {
    cout << "Unable to retrieve flight record." << endl;
    return false;
  }

  return true;
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
      updateManager(hashTable);
      break;
    case 3:
      deleteManager(hashTable);
      break;
    case 4:
      undoDeleteManager(hashTable);
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

  Flight flight;
  if (!findFlight(hashTable, key, flight))
    return;

  cout << "Found flight:" << endl;
  displayFlight(flight);
}

void deleteManager(HashTable &hashTable) {
  string key;
  cout << "Delete Manager" << endl;
  cout << "Enter the flight number to delete: ";
  cin >> key;

  Flight flight;
  if (!findFlight(hashTable, key, flight))
    return;

  cout << "Flight to delete:" << endl;
  displayFlight(flight);
  cout << "Confirm delete? (y/n): ";

  char confirm;
  cin >> confirm;
  if (confirm == 'y' || confirm == 'Y') {
    if (hashTable.remove(key)) {
      deletedFlights.push(flight);
      cout << "Flight deleted." << endl;
    } else {
      cout << "Delete failed." << endl;
    }
  } else {
    cout << "Delete cancelled." << endl;
  }
}

void updateManager(HashTable &hashTable) {
  string key;
  cout << "Update Manager" << endl;
  cout << "Enter the flight number to update: ";
  cin >> key;

  Flight flight;
  if (!findFlight(hashTable, key, flight))
    return;

  cout << "Current flight:" << endl;
  displayFlight(flight);
  cout << "Choose field to update:" << endl;
  cout << "1. Origin" << endl;
  cout << "2. Destination" << endl;
  cout << "3. Departure time" << endl;
  cout << "4. Arrival time" << endl;
  cout << "5. Status" << endl;
  cout << "Any other number to cancel." << endl;
  cout << "Enter your choice: ";

  int choice = choiceInput();
  if (choice < 1 || choice > 5) {
    cout << "Update cancelled." << endl;
    return;
  }

  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  string value;
  cout << "Enter new value: ";
  getline(cin, value);

  switch (choice) {
  case 1:
    flight.setOrigin(value);
    break;
  case 2:
    flight.setDestination(value);
    break;
  case 3:
    flight.setDepartureTime(value);
    break;
  case 4:
    flight.setArrivalTime(value);
    break;
  case 5:
    flight.setStatus(value);
    break;
  }

  if (hashTable.update(key, flight)) {
    cout << "Flight updated." << endl;
  } else {
    cout << "Update failed." << endl;
  }
}

void undoDeleteManager(HashTable &hashTable) {
  if (deletedFlights.isEmpty()) {
    cout << "No deleted flights to restore." << endl;
    return;
  }

  Flight flight = deletedFlights.peek();
  string key = flight.getFlightNumber();

  if (hashTable.search(key) != -1) {
    cout << "Restore failed. Flight already exists." << endl;
    return;
  }

  if (hashTable.insert(flight) != -1) {
    deletedFlights.pop();
    cout << "Flight restored." << endl;
  } else {
    cout << "Restore failed." << endl;
  }
}

void insertManager() {
  cout << "insert";
  cout << endl;
}
