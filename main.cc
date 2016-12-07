// file main.cc
#include <iostream>
#include "goboard.h"
#include "stack.h"

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

#define PVC 1
#define CVC 2


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

//Reads a user given size for the board.
void readSize(int & height, int & width) {
	while (true) {
		cout << "Enter a height: ";
		height = readDigit(50);
		cout << "Enter a width: ";
		width = readDigit(50);
		if (width <  5 || height < 5) {
			cout << "Please enter a height and width above 4" << endl;
		}
		else {
			break;
		}
	}
}

//Reads a user given color for player 1.
void readPlayerCol(Goboard & goboard, char & color) {
	char col;
	while (true) {
		cout << "Enter color: ";
		cin >> col;
		if (col != BLACK && col != WHITE) {
			cout << "Enter valid color" << endl;
		}
		else {
			goboard.setPlayerCol(col);
			break;
		}
	}
}

//Function for the main menu.
void printMenu() {
	int height, width, y, x;
	char color = BLACK;
	bool succ = false;
	readSize(height,width);
	Goboard Gobord(height, width);
	Gobord.createBoard();
	getOption(color);
	readPlayerCol(Gobord,color);
	Gobord.setGameType(1);
	Gobord.print();

	while (!Gobord.getGameStatus()) {
		Gobord.turn(color, y, x, succ);
		Gobord.print();
	}

	cin.get();
	
}

int main ( ) {
	printMenu();
	cin.get();
	return 0;
}//main
