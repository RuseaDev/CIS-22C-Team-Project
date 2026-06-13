#ifndef STACK_H
#define STACK_H

#include "flight.h"

struct DeletedFlight {
  Flight flight;
  int hashIndex;
  int tableSize;

  DeletedFlight();
  DeletedFlight(const Flight &flight, int hashIndex, int tableSize);
};

class Stack {
private:
  struct StackNode {
    DeletedFlight data;
    StackNode *next;

    explicit StackNode(const DeletedFlight &deletedFlight);
  };

  StackNode *top;
  int count;

public:
  Stack();
  ~Stack();

  Stack(const Stack &) = delete;
  Stack &operator=(const Stack &) = delete;

  void push(const DeletedFlight &deletedFlight);
  DeletedFlight pop();
  DeletedFlight peek() const;
  bool isEmpty() const;
  int getCount() const;
};

#endif
