#include "fileIO.h"
#include "airplane.h"
#include <fstream>
#include <sstream>
#include <iostream>

const string FILE_ERROR_MESSAGE = "Error: File not found";

using namespace std;

/*
Function: determineHashSize
*/
int determineHashSize(string filename) {
    ifstream file(filename);
    if (!file) {
        cout << FILE_ERROR_MESSAGE << endl;
        return -1;
    }

    string line;
    getline(file, line); // skip header

    int count = 0;
    while (getline(file, line))
        count++;

    file.close();

    // multiply by 2, find next prime
    // NOTE: Oak's _nextPrime() isn't accessible (private)
    // so I write our own small prime finder here
    int size = count * 2;
    while (!isPrime(size))
        size++;
    return size; // returns 53 for your 25-record file
}

/*
Helper Function: isPrime
since Oak's _isPrime() is private
*/
bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return false;
    return true;
}

/*
Helper: trim leading/trailing whitespace from a token
*/
static string trimToken(const string& s) {
    size_t start = s.find_first_not_of(" \t\r");
    if (start == string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r");
    return s.substr(start, end - start + 1);
}

/*
Helper Function: parseLine
Parses one CSV line into a Flight object.
Expected columns (no flight_id):
  flight_number, airline_name, origin, destination,
  departure_time, arrival_time, status, aircraft_type, seat_capacity
*/
Flight parseLine(const string& line) {
    stringstream ss(line);
    string token;
    string f[9];
    int i = 0;
    while (getline(ss, token, ',') && i < 9)
        f[i++] = trimToken(token);

    int seatCap = 0;
    try { seatCap = stoi(f[8]); } catch (...) {}

    // Airplane constructor takes non-const refs
    string emptyId = "";
    Airplane ap(emptyId, f[7], seatCap, f[1], 0);
    return Flight(f[0], f[2], f[3], f[4], f[5], f[6], ap);
}

/*
Function: readFile
*/
void readFile(string filename, HashTable& hashTable, BST& bst){
    ifstream file(filename);
    if (!file) {
        cout << FILE_ERROR_MESSAGE << endl;
        return;
    }

    string line;
    getline(file, line); //skip the first line

    int count = 0;
    int prevSize = hashTable.getTableSize(); 

    while (getline(file, line)){
        Flight f = parseLine(line);

        //insert() returns slot index, or -1 on failure
        int idx = hashTable.insert(f);

        if (idx == -1){
            cout << "Duplicate skipped: "
                << f.getFlightNumber() << endl;
            continue;
        }
        // check if rehash happened
        // if table size changed, BST indices are stale
        // rebuild BST from getAllEntries()
        if (hashTable.getTableSize() != prevSize) {
            bst.clear(); 
            auto entries = hashTable.getAllEntries();
            for (auto& pair : entries)
                bst.insert(pair.first, pair.second);
            prevSize = hashTable.getTableSize();
            cout << "Rehash occurred — BST rebuilt" << endl;
        } else {
            // normal insert into BST
            bst.insert(f.getFlightNumber(), idx);
        }

        count++;
    }

    file.close();
    cout << count << " records loaded successfully" << endl;
}

/*
Function: saveToFile
*/
void saveToFile(string filename, HashTable& hashTable) {
    ofstream file(filename);
    if (!file) {
        cout << FILE_ERROR_MESSAGE << endl;
        return;
    }

    // write header
    file << "flight_number, airline_name, origin, "
         << "destination, departure_time, arrival_time, "
         << "status, aircraft_type, seat_capacity" << endl;

    // walk hash table index by index
    int saved = 0;
    for (int i = 0; i < hashTable.getTableSize(); i++) {
        Flight f;
        if (hashTable.getAtIndex(i, f)) {  // returns false if empty/deleted
            Airplane ap = f.getAirplane();
            file << f.getFlightNumber()  << ", "
                 << ap.getAirlineName()  << ", "
                 << f.getOrigin()        << ", "
                 << f.getDestination()   << ", "
                 << f.getDepartureTime() << ", "
                 << f.getArrivalTime()   << ", "
                 << f.getStatus()        << ", "
                 << ap.getAircraftType() << ", "
                 << ap.getSeatCapacity() << endl;
            saved++;
        }
    }

    file.close();
    cout << saved << " records saved to " << filename << endl;
}