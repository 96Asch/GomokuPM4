// file main.cc
#include <iostream>
#include "goboard.h"
#include <cstdlib>
#include "stack.h"

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

#define PVC 1
#define CVC 2
#define PVP 3

#define MOVEOPT 'M'
#define UNDOOPT	'U'
#define POSMOVE 'C'

#define PLAYERTURN (Gobord.getGameType() == PVC && Gobord.getPlayerCol() == color)

using namespace std;

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
void readPlayerCol(char & color) {
	char col;
	while (true) {
		cout << "Enter color: ";
		cin >> col;
		if (col != BLACK && col != WHITE) {
			cout << "Enter valid color: " << BLACK << " or " << WHITE << endl;
		}
		else {
			color = col;
			break;
		}
	}
}

void setupGame(int & height, int & width, int & gameType, char & color) {
	
	char setupPlayer1, setupPlayer2;
	cout << "GAME SETUP"<< endl;
	readSize(height, width);
	cout << "Player 1: [C]omputer or [H]uman" << endl;
	if ((cin >> setupPlayer1) && (setupPlayer1 == 'C' || setupPlayer1 == 'H' )) {
		cout << "Player 2: [C]omputer or [H]uman" << endl;
		if ((cin >> setupPlayer2) && (setupPlayer2 == 'C' || setupPlayer2 == 'H')) {
			if ((setupPlayer1 == 'C' && setupPlayer2 == 'H') || (setupPlayer1 == 'H' && setupPlayer2 == 'C')) {
				cout << "P1: " << setupPlayer1 << ", P2: " << setupPlayer2 << endl;
				gameType = PVC;
			}
			else if (setupPlayer1 == 'C' && setupPlayer2 == 'C') {
				gameType = CVC;
			}
			else  {
				gameType = PVP;
			}
		}
		else { cout << "Only Input: C, H" << endl; }
	}
	else { cout << "Only Input: C, H" << endl; }
	readPlayerCol(color);
	
}

void playerMenu(char &color, int height, int width, int & x, int & y, char & option ) {
	cout << "~MENU~" << endl;
	cout << "It's now " << color << "'s turn!" << endl;
	cout << "[M]ove, [U]ndo Move, [C]alculate U. Games" << endl;
	if ((cin >> option) && (option == MOVEOPT || option == UNDOOPT || option == POSMOVE)) {
		if (option == MOVEOPT) {
			cout << "Enter x-coordinate: ";
			x = readDigit(width);
			cout << "Enter y-coordinate: ";
			y = readDigit(height);
		}
	}
	else {
		cout << "Only: " << MOVEOPT << ", " << UNDOOPT << ", ";
		cout << POSMOVE << " allowed " << endl;
	}
}

//Function for the main menu.
void printMenu() {
	int height, width, y, x, gametype;
	char color = BLACK, option = ' ';
	bool succ = false;

	setupGame(height, width, gametype, color);
	srand(height*width - height);
	Goboard Gobord(height, width);
	Gobord.setGameType(gametype);
	Gobord.setPlayerCol(color);
	Gobord.createBoard();
	Gobord.print();
	color = BLACK;
	while (!Gobord.getGameStatus()) {
		y = rand() % height, x = rand() % width;
		if (Gobord.getGameType() == PVC && Gobord.getPlayerCol() == color) {
			playerMenu(color, height, width, x, y, option);
		}
		else if (Gobord.getGameType() == PVP) {
			playerMenu(color, height, width, x, y, option);
		}
		Gobord.print();
		Gobord.turn(color, y, x, succ, option);
	}
	cin.get();
}

int main ( ) {

	printMenu();
	
	cin.get();
	return 0;
}//main
