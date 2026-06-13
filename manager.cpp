#include "manager.h"
#include "BST.h"
#include "HashTable.h"
#include "Stack.h"
#include "airplane.h"
#include "flight.h"
#include <iostream>
#include <limits>
#include <utility>
#include <vector>

using namespace std;

// util function

static Stack deletedFlights;

static void rebuildBST(const HashTable &hashTable, BST &bst) {
  bst.clear();
  vector<pair<string, int>> entries = hashTable.getAllEntries();
  for (const auto &entry : entries) {
    bst.insert(entry.first, entry.second);
  }
}

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

bool findFlight(const HashTable &hashTable, const BST &bst, const string &key,
                Flight &flight, int &index) {
  index = bst.search(key);
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

void displayManager(HashTable &hashTable, BST &bst) {
  bool running = true;
  while (running) {
    cout << "1. Display menu " << endl;
    cout << "2. Display all records " << endl;
    cout << "Any other number to quit." << endl;
    cout << "Enter your choice: ";

    switch (choiceInput()) {
    case 1:
      cout << "Display menu" << endl;
      cout << "watchu wanna do?" << endl;
      cout
          << "1. Insert\n 2. Update\n 3. Delete\n 4. Undo Delete\n 5. Search\n "
             " Any other number to return"
          << endl;

      switch (choiceInput()) {
      case 1:
        insertManager(hashTable, bst);
        break;
      case 2:
        updateManager(hashTable, bst);
        break;
      case 3:
        deleteManager(hashTable, bst);
        break;
      case 4:
        undoDeleteManager(hashTable, bst);
        break;
      case 5:
        searchManager(hashTable, bst);
        break;
      case 6:
        hashTable.printTable();
        break;
      default:
        cout << "Returning to main menu..." << endl;
        break;
      }
      break;
    case 2:
      cout << "Display all records" << endl;
      cout << "================================================================"
           << endl;
      hashTable.printTable();
      cout << "================================================================"
           << endl;

      break;
    default:
      cout << "Exiting..." << endl;
      running = false;
      break;
    }
  }
}

void searchManager(const HashTable &hashTable, const BST &bst) {
  string key;
  cout << "Enter the flight number to search: ";

  cin >> key;

  Flight flight;
  int index;
  if (!findFlight(hashTable, bst, key, flight, index))
    return;

  cout << "Found flight:" << endl;
  displayFlight(flight);
}

void deleteManager(HashTable &hashTable, BST &bst) {
  string key;
  cout << "Delete Manager" << endl;
  cout << "Enter the flight number to delete: ";
  cin >> key;

  Flight flight;
  int index;
  if (!findFlight(hashTable, bst, key, flight, index))
    return;

  cout << "Flight to delete:" << endl;
  displayFlight(flight);
  cout << "Confirm delete? (y/n): ";

  char confirm;
  cin >> confirm;
  if (confirm == 'y' || confirm == 'Y') {
    if (hashTable.removeAtIndex(index)) {
      bst.remove(key);
      deletedFlights.push(
          DeletedFlight(flight, index, hashTable.getTableSize()));
      cout << "Flight deleted." << endl;
    } else {
      cout << "Delete failed." << endl;
    }
  } else {
    cout << "Delete cancelled." << endl;
  }
}

void updateManager(HashTable &hashTable, BST &bst) {
  string key;
  cout << "Update Manager" << endl;
  cout << "Enter the flight number to update: ";
  cin >> key;

  Flight flight;
  int index;
  if (!findFlight(hashTable, bst, key, flight, index))
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

  if (hashTable.updateAtIndex(index, flight)) {
    cout << "Flight updated." << endl;
  } else {
    cout << "Update failed." << endl;
  }
}

void undoDeleteManager(HashTable &hashTable, BST &bst) {
  if (deletedFlights.isEmpty()) {
    cout << "No deleted flights to restore." << endl;
    return;
  }

  DeletedFlight deletedFlight = deletedFlights.peek();
  Flight flight = deletedFlight.flight;
  string key = flight.getFlightNumber();

  if (bst.search(key) != -1) {
    cout << "Restore failed. Flight already exists." << endl;
    return;
  }

  if (hashTable.getTableSize() != deletedFlight.tableSize) {
    cout << "Restore failed. Hash table size changed." << endl;
    return;
  }

  int index = deletedFlight.hashIndex;
  if (hashTable.restoreAtIndex(index, flight)) {
    bst.insert(key, index);
    deletedFlights.pop();
    cout << "Flight restored." << endl;
  } else {
    cout << "Restore failed." << endl;
  }
}

void insertManager(HashTable &hashTable, BST &bst) {
  cout << "Insert Manager" << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  string flightNumber;
  string origin;
  string destination;
  string departureTime;
  string arrivalTime;
  string status;
  string airlineName;
  string aircraftType;
  int seatCapacity;

  cout << "Enter flight number: ";
  getline(cin, flightNumber);

  if (flightNumber.empty()) {
    cout << "Insert cancelled. Flight number cannot be empty." << endl;
    return;
  }

  if (bst.search(flightNumber) != -1) {
    cout << "Insert cancelled. Flight already exists." << endl;
    return;
  }

  cout << "Enter origin: ";
  getline(cin, origin);
  cout << "Enter destination: ";
  getline(cin, destination);
  cout << "Enter departure time: ";
  getline(cin, departureTime);
  cout << "Enter arrival time: ";
  getline(cin, arrivalTime);
  cout << "Enter status: ";
  getline(cin, status);
  cout << "Enter airline name: ";
  getline(cin, airlineName);
  cout << "Enter aircraft type: ";
  getline(cin, aircraftType);
  cout << "Enter seat capacity: ";
  cin >> seatCapacity;
  while (cin.fail() || seatCapacity < 0) {
    cout << "Invalid seat capacity, please try again" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter seat capacity: ";
    cin >> seatCapacity;
  }

  Airplane airplane;
  airplane.setAirlineName(airlineName);
  airplane.setAircraftType(aircraftType);
  airplane.setSeatCapacity(seatCapacity);

  Flight flight(flightNumber, origin, destination, departureTime, arrivalTime,
                status, airplane);
  int prevSize = hashTable.getTableSize();
  int index = hashTable.insert(flight);

  if (index != -1) {
    if (hashTable.getTableSize() != prevSize) {
      rebuildBST(hashTable, bst);
    } else {
      bst.insert(flightNumber, index);
    }
    cout << "Flight inserted at index " << index << "." << endl;
  } else {
    cout << "Insert failed." << endl;
  }
}
