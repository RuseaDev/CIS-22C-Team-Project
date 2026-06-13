#include "Stack.h"

DeletedFlight::DeletedFlight() {
  hashIndex = -1;
  tableSize = 0;
}

DeletedFlight::DeletedFlight(const Flight &flight, int hashIndex,
                             int tableSize) {
  this->flight = flight;
  this->hashIndex = hashIndex;
  this->tableSize = tableSize;
}

Stack::StackNode::StackNode(const DeletedFlight &deletedFlight) {
  data = deletedFlight;
  next = nullptr;
}

Stack::Stack() {
  top = nullptr;
  count = 0;
}

Stack::~Stack() {
  while (!isEmpty()) {
    pop();
  }
}

void Stack::push(const DeletedFlight &deletedFlight) {
  StackNode *newNode = new StackNode(deletedFlight);
  newNode->next = top;
  top = newNode;
  ++count;
}

DeletedFlight Stack::pop() {
  if (isEmpty()) {
    return DeletedFlight();
  }

  StackNode *nodeToDelete = top;
  DeletedFlight deletedFlight = nodeToDelete->data;
  top = top->next;

  delete nodeToDelete;
  --count;

  return deletedFlight;
}

DeletedFlight Stack::peek() const {
  if (isEmpty()) {
    return DeletedFlight();
  }

  return top->data;
}

bool Stack::isEmpty() const { return top == nullptr; }

int Stack::getCount() const { return count; }
