// file gobord.cc
#include "goboard.h"
#include "stack.h"
#include <iostream>

using namespace std;

//Definitions for colors and empty spaces.
#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

#define PVC 1
#define CVC 2
#define PVP 3

//Definitions for player options.
#define MOVEOPT 'M'
#define UNDOOPT	'U'
#define POSMOVE 'C'

//Constructor for a board with a set height and width.
Goboard::Goboard ( ) {
	height = 5, width = 5;
	entrance = NULL, exit = NULL, leftUpper = NULL;
	gameType = 0;
	gameIsOver = false;
	playerCol = EMPTY;
}//gobord::gobord

 //Constructor for a board with a given height and width.
Goboard::Goboard(int h, int w) {
	height = h, width = w;
	gameType = 0;
	entrance = NULL, exit = NULL, leftUpper = NULL;
	gameIsOver = false;
	playerCol = EMPTY;
}//gobord::gobord

Goboard::~Goboard ( ) {
  // TODO
}//gobord::~gobord

//Gets the status of the game.
bool Goboard::getGameStatus() {
	return gameIsOver;
}

//Gets the type of game played.
int Goboard::getGameType() {
	return gameType;
}

//Sets the type of game to play.
void Goboard::setGameType(int gametype){
	gameType = gametype;
}

//Gets the player 1 color.
char Goboard::getPlayerCol() {
	return playerCol;
}

//Sets the player 1 color.
void Goboard::setPlayerCol(char color) {
	playerCol = color;
}

//Gets the height of a board.
int Goboard::getHeight() {
	return height;
}

//Gets the width of a board.
int Goboard::getWidth() {
	return width;
}

//Function to print the status of the board.
void Goboard::print ( ) {
	BoardSquare* ySquare = leftUpper, *xSquare = leftUpper;
	int counter = 0;
	cout << endl;
	for (int i = 0; i < (width * 2 + 1); i++) {
		cout << "-";
	}
	cout << endl;
	while (ySquare != NULL) {
		xSquare = ySquare;
		while (xSquare != NULL) {
			counter++;
			if (counter == 1) {
				cout << "|";
			}
			cout  << xSquare->color <<  "|";
			xSquare = xSquare->neighbours[2];
		}
		counter = 0;
		cout << endl;
		for (int i = 0; i < (width*2+1); i++) {
			cout << "-" ;
		}
		cout << endl;
		ySquare = ySquare->neighbours[4];		
		}
	
}//gobord::print

//Creates a board with a certain height and width.
void Goboard::createBoard(){
	createCols(height, width);
}

//Function to place a piece on the board
void Goboard::move(char color, int i, int j, bool & success) {
	if (i<height&&j<width) {
		BoardSquare* square;
		success = false;
		square = getSquareAt(i, j);
		if (!isOccupied(square)) {
			square->color = color;
			stack.push(i, j);
			success = true;
			gameOver(square, color);
		}
		else {
			if (gameType == PVC && playerCol == color) {
				cout << "Space is already occupied" << endl;
			}
		}
	}
	else{
		cout << "Move out of bounds" << endl;
	}
}

//Undo the last player move.
void Goboard::undoMove() {
	BoardSquare* squareC, *squareH;
	int y = 0, x = 0;
	if (stack.getLength() > 1) {
		for (int i = 0; i < 2; i++) {
			stack.pop(y, x);
			squareC = getSquareAt(y, x);
			squareC->color = EMPTY;	
		}
	}
	else { cout << "No moves to undo" << endl; }
}

//Function to let a human player place a piece.
void Goboard::moveHuman(char color, int & i, int & j, bool & succ, char option) {
	switch (option) {
	case MOVEOPT:
		move(color, i, j, succ);
		break;
	case UNDOOPT:
		undoMove();
		succ = false;
		break;
	case POSMOVE:
		// some function here
		break;
	default:
		break;
	}		
}

//A turn where a player or a computer can do a move.
void Goboard::turn(char & color, int & y, int & x, bool & succ, char & opt) {
	if (getGameType() == PVC && !getGameStatus()) {
		switch (playerCol) {
		case BLACK:
			if (stack.getLength() % 2 == 0) {	moveHuman(color, y, x, succ, opt);	}
			else { move(color, y, x, succ); }
			break;
		case WHITE:
			if (stack.getLength() % 2 == 1) { moveHuman(color, y, x, succ, opt); }
			else { move(color, y, x, succ); }
			break;
		default:
			break;
		}
		if (succ) {	switchColor(color);	}
	}
	else if (getGameType() == CVC && !getGameStatus()) {
		move(color, y, x, succ);
		if (succ) {	switchColor(color); }
	}
	else if (getGameType() == PVP && !getGameStatus()) {
		moveHuman(color, y, x, succ, opt);
		if (succ) {	switchColor(color); }
	}
}

//Function to determine when a game has ended in a stalemate.
bool Goboard::stalemate() {
	int totalMoves = 0;
	totalMoves = width * height;
	if (totalMoves == stack.getLength()) { return true; }
	else { return false; }
}

//Function to count the number of consecutive squares in each direction.
int Goboard::countConsecSquare(BoardSquare* square, int direction, int opdirection, char color) {
	int squareCounter = 1;
	BoardSquare* temp = square;

	do {
		if (temp != square) { squareCounter++; }
		temp = temp->neighbours[direction];
	} while (temp && temp->color == color);
	
	temp = square;

	do {
		if (temp != square) { squareCounter++; }
		temp = temp->neighbours[opdirection];
	} while (temp && temp->color == color);

	return squareCounter;
}

//Function to determine if a color has won a game.
bool Goboard::victory(BoardSquare* square, char & color) {
	if (stack.getLength() >= 9){
		int vertSeq = countConsecSquare(square, 0, 4, color );
		int horzSeq = countConsecSquare(square, 6, 2, color);
		int diaLSeq = countConsecSquare(square, 7, 3, color);
		int diaRSeq = countConsecSquare(square, 1, 5, color);
		if (vertSeq >= 5 || horzSeq >= 5 || diaLSeq >= 5 || diaRSeq >= 5) {
			return true;
		}
		else { return false; }
	}
	else { return false; }
}

//Function to determine when a game is over.
void Goboard::gameOver(BoardSquare* square, char & color) {
	if (stalemate()) {
		gameIsOver = true;
		print();
		cout << "Too bad... There is no winner" << endl;
	}
	else if (victory(square, color)) {
		gameIsOver = true;
		print();
		cout << "Congratulations, " << color << " has won the game!" << endl;
	}
}

//Empties the board.
void Goboard::emptyBoard() {
	BoardSquare* tempY = leftUpper, *tempX = leftUpper;
	while (tempY != NULL) {
		tempX = tempY;
		while (tempX != NULL) {
			tempX->color = EMPTY;
			tempX = tempX->neighbours[2];
		}
		tempY = tempY->neighbours[4];
	}
}

//Resets a Gomoku game.
void Goboard::reset() {
	emptyBoard();
	stack.empty();
	gameIsOver = false;
	playerCol = BLACK;
	gameType = 0;
}
