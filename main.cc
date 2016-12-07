// file main.cc
#include <iostream>
#include "goboard.h"
#include "stack.h"

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

#define PVC 1
#define CVC 2
#define PVP 3

#define PLAYERTURN (Gobord.getGameType() == PVC && Gobord.getPlayerCol() == color)

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
			cout << "Enter valid color: " << BLACK << " or " << WHITE << endl;
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
	char color = BLACK, option = ' ';
	bool succ = false;
	readSize(height,width);
	Goboard Gobord(height, width);
	Gobord.createBoard();
	getOption(color);
	readPlayerCol(Gobord,color);
	Gobord.setGameType(PVP);
	Gobord.print();
	option = 'M';

	while (!Gobord.getGameStatus()) {
		if (PLAYERTURN && Gobord.getGameType() == PVC) {
			cout << "It's now " << color << "'s turn!" << endl;
			cout << "Enter x-coordinate: ";
			x = readDigit(height);
			cout << "Enter y-coordinate: ";
			y = readDigit(width);
		}
		else if (Gobord.getGameType() == PVP) {
			cout << "It's now " << color << "'s turn!" << endl;
			cout << "Enter x-coordinate: ";
			x = readDigit(height);
			cout << "Enter y-coordinate: ";
			y = readDigit(width);
		}
		Gobord.turn(color, y, x, succ, option);
		Gobord.print();
	}

	cin.get();
	
}

int main ( ) {
	printMenu();
	cin.get();
	return 0;
}//main
