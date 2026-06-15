#include "test_utils.h"

int main() {
  setupTempFiles();

  TestRunner runner;
  testFileIO(runner);
  testHashTable(runner);
  testBST(runner);
  testDisplayAndManager(runner);
  testCrudAndUndo(runner);

  return printSummary(runner);
}
