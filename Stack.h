#ifndef STACK_H
#define STACK_H

#include "flight.h"

class Stack {
private:
  struct StackNode {
    Flight data;
    StackNode *next;

    explicit StackNode(const Flight &flight);
  };

  StackNode *top;
  int count;

public:
  Stack();
  ~Stack();

  Stack(const Stack &) = delete;
  Stack &operator=(const Stack &) = delete;

  void push(const Flight &flight);
  Flight pop();
  Flight peek() const;
  bool isEmpty() const;
  int getCount() const;
};

#endif
