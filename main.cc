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

/*
AUTHORS:			Andrew Huang & Micha de Jong
STUDENTID:			S1913999 & S1821784
DATE OF COMPLETION: 09-12-2016
ASSIGNMENT:			4 "GOMOKU"
COMPILER:			g++
*/
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

//Reads an option and validates it for a particular mode.
void readOption(char & option, int mode, int playernum) {
	char opt;
	while (true) {
		if (mode == 1) {
			cout << "Player " << playernum << ": [C]omputer or [H]uman" << endl;
			cin >> opt;
			if (opt == 'C' || opt == 'H') { option = opt; break; }
			else { cout << "Only input C, H allowed" << endl; }
		}
		else if (mode == 2) {
			cin >> opt;
			if (opt == MOVEOPT || opt == UNDOOPT || opt == POSMOVE) { option = opt; break; }
			else { cout << "Only input M, U, C allowed" << endl; }
		}
		else if (mode == 3) {
			cout << "Enter color: ";
			cin >> opt;
			if (opt == BLACK || opt == WHITE) {	option = opt; break; }
			else { cout << "Enter valid color: " << BLACK << " or " << WHITE << endl; }
		}
		else if (mode == 4) {
			cout << "Enter [Y]es or [N]o: ";
			cin >> opt;
			if (opt == 'Y' || opt == 'N') { option = opt; break; }
			else { cout << "Only input Y or N allowed" << endl; }
		}
	}
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

//Sets up variables for the board and it's players.
void setupGame(int & height, int & width, int & gameType, char & color, int mode) {
	char setupPlayer1, setupPlayer2;
	cout << "GAME SETUP"<< endl;
	if (mode == 1) { readSize(height, width); }
	readOption(setupPlayer1, 1, 1);
	readOption(setupPlayer2, 1, 2);
	cout << "P1: " << setupPlayer1 << ", P2: " << setupPlayer2 << endl;
	if (setupPlayer1 == 'C' && setupPlayer2 == 'C') {
		gameType = CVC;
		}
	else if (setupPlayer1 == 'H' && setupPlayer2 == 'H') {
		gameType = PVP;
		readOption(color, 3, 0);
		}
	else {
		gameType = PVC;
		readOption(color, 3, 0);
	}
}

//Menu for the player(s)
void playerMenu(char &color, int height, int width, int & x, int & y, char & option ) {
	cout << "~MENU~" << endl;
	cout << "It's now " << color << "'s turn!" << endl;
	cout << "[M]ove, [U]ndo Move, [C]alculate U. Games" << endl;
	readOption(option, 2, 0);
	
	if (option == MOVEOPT) {
		cout << "Enter x-coordinate: ";
		x = readDigit(width);
		cout << "Enter y-coordinate: ";
		y = readDigit(height);
	}
}

//Menu for replaying a game.
void replayMenu(bool & replay, char & option, int & gametype, char & color, int & height, int & width) {
	cout << "Do you want to play a new game?" << endl;
	readOption(option, 4, 0);
	if (option == 'Y') { 
		replay = true; 
		setupGame(height, width, gametype, color, 0);
	}
	else {
		replay = false;
	}
}

//Function for the main menu.
void printMenu() {
	int height, width, y, x, gametype;
	char color = BLACK, option = ' ';
	bool succ = false, replay = true;
	setupGame(height, width, gametype, color, 1);
	srand(height*width - height);
	Goboard Gobord(height, width);
	Gobord.createBoard();

	while (replay) {
		Gobord.setGameType(gametype);
		Gobord.setPlayerCol(color);
		Gobord.print();
		color = BLACK;

		while (!Gobord.getGameStatus()) {
			y = rand() % height, x = rand() % width;
			if (PLAYERTURN) {
				playerMenu(color, height, width, x, y, option);
			}
			else if (Gobord.getGameType() == PVP) {
				playerMenu(color, height, width, x, y, option);
			}
			Gobord.turn(color, y, x, succ, option);

			if (!Gobord.getGameStatus()) {
				Gobord.print();
			}
		}
		Gobord.reset();
		replayMenu(replay, option, gametype, color, height, width);
	}
	cin.get();
}
/*
Function to display information intended for users.
*/
void displayInformation() {
	cout << "_____________________________________________________" << endl;
	cout << "This program is made by Andrew Huang & Micha de Jong" << endl;
	cout << "Students at Leiden University 2016 " << endl;
	cout << "\nThis program can play the game Gomoku." << endl;
	cout << "The user is able to choose the type of gamemode. " << endl;
	cout << "For example PVP, CVC or PVC and the user is able to ." << endl;
	cout << "choose the color. Black is the color which starts the game." << endl;
	cout << "The user has 3 options: Make a move, undo a move and" << endl;
	cout << "calculate the ammount of games there can be played." << endl;
	cout << "At the end of a game you can choose if you  want to stop" << endl;
	cout << "or continue." << endl;
	cout << "_____________________________________________________" << endl;
}

int main ( ) {
	displayInformation();
	printMenu();
	cin.get();
	return 0;
}//main
