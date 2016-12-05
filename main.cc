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
		if (width < 15 || height < 15) {
			cout << "Please enter a height and width above 15" << endl;
		}
		else {
			break;
		}
	}
}

void printMenu() {
	int height, width;
	readSize(height,width);
	Goboard Gobord(height, width);
	Gobord.createBoard();
	Gobord.print();
	Gobord.move(BLACK, 2, 2);
	Gobord.move(WHITE, 2, 2);
	Gobord.move(WHITE, 2, 3);
	Gobord.move(BLACK, 2, 4);
	Gobord.print();
	cin.get();
	
}

int main ( ) {
  printMenu();
  cin.get();
  return 0;
}//main
