// file main.cc
#include <iostream>

#include "goboard.h"
#include "stack.h"

using namespace std;

// Returns a user given option.
char getOption(char invoer) {
	while (invoer == '\n') {
		cin.get(invoer);
	}
	return invoer;
}

// Converts a stream chars into a single int.
void convertCharstoInt(char letter, int & numberToCheck) {
	int temp = letter - '0';
	numberToCheck *= 10;
	numberToCheck += temp;
}

// Returns the digits of a stream of chars up to maxNumber.
int readDigit(int maxNumber) {
	int res = 0;
	char ch = '\n';
	while (!isdigit(ch)) {
	cin.get(ch);
	}
	convertCharstoInt(ch, res);
	while (ch != '\n') {
		cin.get(ch);
		if (isdigit(ch) && res < maxNumber) {
			convertCharstoInt(ch, res);
		}
	}
	if (res > maxNumber) {
		res /= 10;
	}
	cout << "You entered: " << res << endl;
	return res;
}
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
