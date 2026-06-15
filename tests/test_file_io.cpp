#include "test_utils.h"

#include "../include/fileIO.h"

using namespace std;

void testFileIO(TestRunner &t) {
  printGroup("File I/O");

  // FI-01: Load the normal 25-record sample file.
  int sampleSize = determineHashSize(SAMPLE_FILE);
  HashTable sampleTable(sampleSize);
  BST sampleBST;
  string loadOutput =
      captureOutput([&]() { readFile(SAMPLE_FILE, sampleTable, sampleBST); });

  printResult(t, "FI-01 hash size for sample_input.txt", sampleSize == 53);
  printResult(t, "FI-01 load output reports 25 records",
              contains(loadOutput, "25 records loaded successfully"));
  printResult(t, "FI-01 active record count", sampleTable.getCount() == 25);
  printResult(t, "FI-01 load factor",
              almostEqual(sampleTable.loadFactor() * 100, 47.17, 0.01));

  // FI-02: Try to load a file that does not exist.
  int missingSize = 0;
  string missingOutput = captureOutput(
      [&]() { missingSize = determineHashSize(TMP_DIR + "/missing.csv"); });

  printResult(t, "FI-02 missing file size result", missingSize == -1);
  printResult(t, "FI-02 missing file prints error",
              contains(missingOutput, "Error: File not found"));

  // FI-03: Load a file with only the CSV header.
  HashTable emptyTable(determineHashSize(TMP_DIR + "/empty.csv"));
  BST emptyBST;
  string emptyOutput = captureOutput(
      [&]() { readFile(TMP_DIR + "/empty.csv", emptyTable, emptyBST); });

  printResult(t, "FI-03 empty file active count",
              emptyTable.getCount() == 0);
  printResult(t, "FI-03 empty file reports zero records",
              contains(emptyOutput, "0 records loaded successfully"));

  // FI-04: Load a file that repeats AA101 once.
  HashTable duplicateTable(determineHashSize(TMP_DIR + "/duplicate_aa101.csv"));
  BST duplicateBST;
  string duplicateOutput = captureOutput([&]() {
    readFile(TMP_DIR + "/duplicate_aa101.csv", duplicateTable, duplicateBST);
  });

  printResult(t, "FI-04 duplicate file keeps 25 active records",
              duplicateTable.getCount() == 25);
  printResult(t, "FI-04 original AA101 remains searchable",
              duplicateBST.search("AA101") != -1);
  printResult(t, "FI-04 duplicate load should not claim 26 records",
              !contains(duplicateOutput, "26 records loaded successfully"));

  // FI-05: Save the loaded table and check the CSV header.
  string savedFile = TMP_DIR + "/saved.csv";
  captureOutput([&]() { saveToFile(savedFile, sampleTable); });

  printResult(t, "FI-05 saved CSV header matches input format",
              readFirstLine(savedFile) == CSV_HEADER);

  // FI-06: Delete AA101, save, and make sure AA101 is not in the file.
  HashTable deleteTable(determineHashSize(SAMPLE_FILE));
  BST deleteBST;
  loadSample(deleteTable, deleteBST);
  removeByKey(deleteTable, deleteBST, "AA101");

  string deletedSaveFile = TMP_DIR + "/saved_after_delete.csv";
  captureOutput([&]() { saveToFile(deletedSaveFile, deleteTable); });
  string deletedSaveContents = readWholeFile(deletedSaveFile);

  printResult(t, "FI-06 save after delete excludes AA101",
              !contains(deletedSaveContents, "AA101,"));
  printResult(t, "FI-06 save after delete keeps CSV header",
              readFirstLine(deletedSaveFile) == CSV_HEADER);
}
