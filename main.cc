// file main.cc
#include <iostream>
#include "goboard.h"
#include "stack.h"

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '


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

void readSize(int & height, int & width) {
	while (true) {
		cout << "Enter a height: ";
		height = readDigit(50);
		cout << "Enter a width: ";
		width = readDigit(50);
		if (width <= 5 || height <= 5) {
			cout << "Please enter a height and width above 4" << endl;
		}
		else {
			break;
		}
	}
}

void printMenu() {
	int height, width, y, x;
	readSize(height,width);
	Goboard Gobord(height, width);
	Gobord.createBoard();
	Gobord.print();
	Gobord.randomMove(BLACK, y, x);
	Gobord.randomMove(WHITE, y, x);
	Gobord.randomMove(BLACK, y, x);
	Gobord.randomMove(WHITE, y, x);
	Gobord.print();
	cin.get();
	
}

int main ( ) {
  printMenu();
  cin.get();
  return 0;
}//main
