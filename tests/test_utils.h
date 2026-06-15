#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include "../include/BST.h"
#include "../include/HashTable.h"
#include "../include/flight.h"

#include <functional>
#include <string>

extern const std::string SAMPLE_FILE;
extern const std::string TMP_DIR;
extern const std::string CSV_HEADER;

struct TestRunner {
  int passed = 0;
  int failed = 0;
};

void printGroup(const std::string &name);
void printResult(TestRunner &t, const std::string &name, bool passed);
int printSummary(const TestRunner &t);

std::string captureOutput(const std::function<void()> &fn);
std::string withInput(const std::string &input,
                      const std::function<void()> &fn);
bool contains(const std::string &text, const std::string &needle);
bool almostEqual(double actual, double expected, double tolerance);

std::string readWholeFile(const std::string &filename);
std::string readFirstLine(const std::string &filename);
void writeFile(const std::string &filename, const std::string &contents);
void setupTempFiles();

Flight makeFlight(const std::string &flightNumber,
                  const std::string &status = "On Time");
void loadSample(HashTable &hashTable, BST &bst);
void removeByKey(HashTable &hashTable, BST &bst, const std::string &key);
void rebuildBSTFromHash(const HashTable &hashTable, BST &bst);

std::string validInsertInput(const std::string &flightNumber);
std::string invalidSeatThenValidInput(const std::string &flightNumber);
std::string deleteConfirmInput(const std::string &flightNumber);
std::string deleteCancelInput(const std::string &flightNumber);

void testFileIO(TestRunner &t);
void testHashTable(TestRunner &t);
void testBST(TestRunner &t);
void testDisplayAndManager(TestRunner &t);
void testCrudAndUndo(TestRunner &t);

#endif
