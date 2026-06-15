#include "test_utils.h"

#include "../include/fileIO.h"
#include "../include/manager.h"

using namespace std;

void testCrudAndUndo(TestRunner &t) {
  printGroup("CRUD / Undo");

  // CRUD-01: Insert a new valid flight.
  HashTable insertTable(determineHashSize(SAMPLE_FILE));
  BST insertBST;
  loadSample(insertTable, insertBST);
  string insertOutput = withInput(
      validInsertInput("ZZ999"),
      [&]() { insertManager(insertTable, insertBST); });

  printResult(t, "CRUD-01 valid insert prints inserted index",
              contains(insertOutput, "Flight inserted at index"));
  printResult(t, "CRUD-01 ZZ999 becomes searchable",
              insertBST.search("ZZ999") != -1);

  // CRUD-02: Try to insert with an empty flight number.
  HashTable emptyFlightTable(determineHashSize(SAMPLE_FILE));
  BST emptyFlightBST;
  loadSample(emptyFlightTable, emptyFlightBST);
  string emptyFlightOutput = withInput(
      "\n", [&]() { insertManager(emptyFlightTable, emptyFlightBST); });

  printResult(t, "CRUD-02 empty flight number is rejected",
              contains(emptyFlightOutput,
                       "Insert cancelled. Flight number cannot be empty."));

  // CRUD-03: Try to insert a duplicate flight number from the menu.
  HashTable duplicateTable(determineHashSize(SAMPLE_FILE));
  BST duplicateBST;
  loadSample(duplicateTable, duplicateBST);
  string duplicateOutput = withInput(
      "\nAA101\n", [&]() { insertManager(duplicateTable, duplicateBST); });

  printResult(t, "CRUD-03 duplicate menu insert is rejected",
              contains(duplicateOutput,
                       "Insert cancelled. Flight already exists."));

  // CRUD-04: Enter an invalid seat capacity, then enter a valid one.
  HashTable seatTable(determineHashSize(SAMPLE_FILE));
  BST seatBST;
  loadSample(seatTable, seatBST);
  string seatOutput = withInput(
      invalidSeatThenValidInput("ZZ998"),
      [&]() { insertManager(seatTable, seatBST); });

  printResult(t, "CRUD-04 invalid seat capacity prompts again",
              contains(seatOutput, "Invalid seat capacity, please try again"));
  printResult(t, "CRUD-04 insert succeeds after valid capacity",
              seatBST.search("ZZ998") != -1);

  // CRUD-05: Update DL303's status.
  HashTable updateTable(determineHashSize(SAMPLE_FILE));
  BST updateBST;
  loadSample(updateTable, updateBST);
  string updateOutput = withInput(
      "DL303\n5\nOn Time\n",
      [&]() { updateManager(updateTable, updateBST); });

  Flight updated;
  updateTable.getAtIndex(updateBST.search("DL303"), updated);

  printResult(t, "CRUD-05 update prints success",
              contains(updateOutput, "Flight updated."));
  printResult(t, "CRUD-05 update changes status",
              updated.getStatus() == "On Time");
  printResult(t, "CRUD-05 update preserves flight number",
              updated.getFlightNumber() == "DL303");

  // CRUD-06: Cancel a delete request.
  HashTable cancelTable(determineHashSize(SAMPLE_FILE));
  BST cancelBST;
  loadSample(cancelTable, cancelBST);
  string cancelOutput = withInput(
      deleteCancelInput("BA505"),
      [&]() { deleteManager(cancelTable, cancelBST); });

  printResult(t, "CRUD-06 cancel delete prints cancellation",
              contains(cancelOutput, "Delete cancelled."));
  printResult(t, "CRUD-06 BA505 remains searchable",
              cancelBST.search("BA505") != -1);

  // CRUD-07: Confirm a delete request.
  HashTable deleteTable(determineHashSize(SAMPLE_FILE));
  BST deleteBST;
  loadSample(deleteTable, deleteBST);
  string deleteOutput = withInput(
      deleteConfirmInput("AA101"),
      [&]() { deleteManager(deleteTable, deleteBST); });

  printResult(t, "CRUD-07 confirm delete prints success",
              contains(deleteOutput, "Flight deleted."));
  printResult(t, "CRUD-07 AA101 removed from BST",
              deleteBST.search("AA101") == -1);
  printResult(t, "CRUD-07 AA101 removed from hash table",
              deleteTable.search("AA101") == -1);

  // Clear the shared undo stack so CRUD-08 can test an empty undo history.
  captureOutput([&]() { undoDeleteManager(deleteTable, deleteBST); });

  // CRUD-08: Undo before anything has been deleted.
  HashTable undoEmptyTable(determineHashSize(SAMPLE_FILE));
  BST undoEmptyBST;
  loadSample(undoEmptyTable, undoEmptyBST);
  string undoEmptyOutput =
      captureOutput([&]() { undoDeleteManager(undoEmptyTable, undoEmptyBST); });

  printResult(t, "CRUD-08 undo empty stack reports no deleted flights",
              contains(undoEmptyOutput, "No deleted flights to restore."));

  // CRUD-09: Delete two flights, then undo only the most recent delete.
  HashTable undoRecentTable(determineHashSize(SAMPLE_FILE));
  BST undoRecentBST;
  loadSample(undoRecentTable, undoRecentBST);
  withInput(deleteConfirmInput("AA101"),
            [&]() { deleteManager(undoRecentTable, undoRecentBST); });
  withInput(deleteConfirmInput("DL303"),
            [&]() { deleteManager(undoRecentTable, undoRecentBST); });
  string undoRecentOutput = captureOutput(
      [&]() { undoDeleteManager(undoRecentTable, undoRecentBST); });

  printResult(t, "CRUD-09 undo prints restored message",
              contains(undoRecentOutput, "Flight restored."));
  printResult(t, "CRUD-09 most recent DL303 restored",
              undoRecentBST.search("DL303") != -1);
  printResult(t, "CRUD-09 older AA101 remains deleted",
              undoRecentBST.search("AA101") == -1);

  // CRUD-10: Save after delete, then try undo.
  // This test is expected to fail until Save clears or blocks undo.
  HashTable saveUndoTable(determineHashSize(SAMPLE_FILE));
  BST saveUndoBST;
  loadSample(saveUndoTable, saveUndoBST);
  withInput(deleteConfirmInput("AA101"),
            [&]() { deleteManager(saveUndoTable, saveUndoBST); });

  string savedFile = TMP_DIR + "/delete_save_undo.txt";
  captureOutput([&]() { saveToFile(savedFile, saveUndoTable); });
  string undoAfterSaveOutput =
      captureOutput([&]() { undoDeleteManager(saveUndoTable, saveUndoBST); });
  string savedContents = readWholeFile(savedFile);

  printResult(t, "CRUD-10 saved file keeps AA101 deleted",
              !contains(savedContents, "AA101,"));
  printResult(t, "CRUD-10 undo after save should be blocked or ineffective",
              saveUndoBST.search("AA101") == -1 &&
                  !contains(undoAfterSaveOutput, "Flight restored."));
}
