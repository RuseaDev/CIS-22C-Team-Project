#include "test_utils.h"

#include "../include/airplane.h"
#include "../include/fileIO.h"

#include <cerrno>
#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <sys/stat.h>
#include <utility>
#include <vector>

using namespace std;

const string SAMPLE_FILE = "sample_input.txt";
const string TMP_DIR = "tests/tmp";
const string FILE_HEADER =
    "flight_number, airline_name, origin, destination, departure_time, "
    "arrival_time, status, aircraft_type, seat_capacity";

const string GREEN = "\033[32m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

void printGroup(const string &name) { cout << "\n=== " << name << " ===\n"; }

void printResult(TestRunner &t, const string &name, bool passed) {
  if (passed) {
    t.passed++;
    cout << GREEN << "PASS" << RESET << ": " << name << "\n";
  } else {
    t.failed++;
    cout << RED << "FAIL" << RESET << ": " << name << "\n";
  }
}

int printSummary(const TestRunner &t) {
  cout << "\n=== Summary ===\n";
  cout << "Passed: " << t.passed << "\n";
  cout << "Failed: " << t.failed << "\n";
  return t.failed == 0 ? 0 : 1;
}

string captureOutput(const function<void()> &fn) {
  ostringstream out;
  streambuf *oldOut = cout.rdbuf(out.rdbuf());
  fn();
  cout.rdbuf(oldOut);
  return out.str();
}

string withInput(const string &input, const function<void()> &fn) {
  istringstream in(input);
  streambuf *oldIn = cin.rdbuf(in.rdbuf());
  cin.clear();
  string output = captureOutput(fn);
  cin.rdbuf(oldIn);
  cin.clear();
  return output;
}

bool contains(const string &text, const string &needle) {
  return text.find(needle) != string::npos;
}

bool almostEqual(double actual, double expected, double tolerance) {
  return fabs(actual - expected) <= tolerance;
}

string readWholeFile(const string &filename) {
  ifstream file(filename);
  ostringstream contents;
  contents << file.rdbuf();
  return contents.str();
}

string readFirstLine(const string &filename) {
  ifstream file(filename);
  string line;
  getline(file, line);
  return line;
}

void writeFile(const string &filename, const string &contents) {
  ofstream file(filename);
  file << contents;
}

void createTempDirectory() {
  if (mkdir(TMP_DIR.c_str(), 0755) != 0 && errno != EEXIST) {
    cerr << "Unable to create " << TMP_DIR << "\n";
  }
}

void setupTempFiles() {
  createTempDirectory();

  writeFile(TMP_DIR + "/empty.txt", FILE_HEADER + "\n");

  ifstream sample(SAMPLE_FILE);
  string header;
  string firstRecord;
  getline(sample, header);
  getline(sample, firstRecord);

  string sampleContents = readWholeFile(SAMPLE_FILE);
  writeFile(TMP_DIR + "/duplicate_aa101.txt",
            sampleContents + firstRecord + "\n");
}

Flight makeFlight(const string &flightNumber, const string &status) {
  Airplane airplane;
  airplane.setAirlineName("Test Airline");
  airplane.setAircraftType("Test Jet");
  airplane.setSeatCapacity(100);
  return Flight(flightNumber, "AAA - Origin", "BBB - Destination",
                "2025-07-01 08:00", "2025-07-01 10:00", status, airplane);
}

void loadSample(HashTable &hashTable, BST &bst) {
  captureOutput([&]() { readFile(SAMPLE_FILE, hashTable, bst); });
}

void removeByKey(HashTable &hashTable, BST &bst, const string &key) {
  int index = bst.search(key);
  if (index != -1 && hashTable.removeAtIndex(index)) {
    bst.remove(key);
  }
}

void rebuildBSTFromHash(const HashTable &hashTable, BST &bst) {
  bst.clear();
  vector<pair<string, int>> entries = hashTable.getAllEntries();
  for (size_t i = 0; i < entries.size(); i++) {
    bst.insert(entries[i].first, entries[i].second);
  }
}

string validInsertInput(const string &flightNumber) {
  return "\n" + flightNumber +
         "\nAAA - Origin\nBBB - Destination\n"
         "2025-07-01 08:00\n2025-07-01 10:00\nOn Time\n"
         "Test Airline\nTest Jet\n100\n";
}

string invalidSeatThenValidInput(const string &flightNumber) {
  return "\n" + flightNumber +
         "\nAAA - Origin\nBBB - Destination\n"
         "2025-07-01 08:00\n2025-07-01 10:00\nOn Time\n"
         "Test Airline\nTest Jet\n-5\n100\n";
}

string deleteConfirmInput(const string &flightNumber) {
  return flightNumber + "\ny\n";
}

string deleteCancelInput(const string &flightNumber) {
  return flightNumber + "\nn\n";
}
