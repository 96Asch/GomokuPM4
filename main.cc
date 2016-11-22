// file main.cc
#include <iostream>

#include "goboard.h"
#include "stack.h"

using namespace std;

int main ( ) {
  Goboard Gobord;

  Stack stack;
  stack.push(1,2);
  stack.push(3,4);

  int from, to;
  stack.pop(from, to);
  cout << from << ", " << to << endl;
  cout << stack.isEmpty() << endl;
  stack.pop(from, to);
  cout << from << ", " << to << endl;
  cout << stack.isEmpty() << endl;
  return 0;
}//main
