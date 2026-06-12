#include "Stack.h"

Stack::StackNode::StackNode(const Flight &flight) {
  data = flight;
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

void Stack::push(const Flight &flight) {
  StackNode *newNode = new StackNode(flight);
  newNode->next = top;
  top = newNode;
  ++count;
}

Flight Stack::pop() {
  if (isEmpty()) {
    return Flight();
  }

  StackNode *nodeToDelete = top;
  Flight flight = nodeToDelete->data;
  top = top->next;

  delete nodeToDelete;
  --count;

  return flight;
}

Flight Stack::peek() const {
  if (isEmpty()) {
    return Flight();
  }

  return top->data;
}

bool Stack::isEmpty() const { return top == nullptr; }

int Stack::getCount() const { return count; }
