// file gobord.cc
#include "goboard.h"
#include "stack.h"
#include <iostream>
#include <cstdlib>
using namespace std;

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

Goboard::Goboard ( ) {
	height = minHeight;
	width = minWidth;
	entrance = NULL;
	exit = NULL;
	srand(height);
	gameIsOver = false;
	gameType = 0;
	playerCol = EMPTY;
}//gobord::gobord

Goboard::Goboard(int h, int w) {
	height = h;
	width = w;
	entrance = NULL;
	exit = NULL;
	srand(width);
	gameIsOver = false;
	gameType = 0;
	playerCol = EMPTY;
}//gobord::gobord

Goboard::~Goboard ( ) {
  // TODO
}//gobord::~gobord

bool Goboard::getGameStatus() {
	return gameIsOver;
}

void Goboard::setGameStatus(bool status) {
	gameIsOver = status;
}

int Goboard::getGameType() {
	return gameType;
}

void Goboard::setGameType(int gametype){
	gameType = gametype;
}

char Goboard::getPlayerCol() {
	return playerCol;
}

void Goboard::setPlayerCol(char color) {
	playerCol = color;
}

void Goboard::print ( ) {
	BoardSquare* ySquare = leftUpper, *xSquare = leftUpper;
	int counter = 0;
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
			cout  <<xSquare->color <<  "|";
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

void Goboard::createBoard(){
	createCols(height, width);
}

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
			cout << "Space is already occupied" << endl;
		}
	}
	else{
		cout << "Move out of bounds" << endl;
	}
}

void Goboard::turn(char & color, int & y, int & x, bool & succ) {
	if (getGameType() == 1 && !getGameStatus()) {
		if (playerCol == BLACK && stack.getLength() % 2 == 0)
			moveHuman(color, y, x, succ);
		else if (playerCol == WHITE && stack.getLength() % 2 == 1) {
			moveHuman(color, y, x, succ);
		}
		else if (playerCol == WHITE && stack.getLength() % 2 == 0) {
			randomMove(color, y, x, succ);
		}
		else if (playerCol == BLACK && stack.getLength() % 2 == 1) {
			randomMove(color, y, x, succ);
		}

		if (color == BLACK) {
			color = WHITE;
		}
		else {
			color = BLACK;
		}
	}
	else if (getGameType() == 2 && !getGameStatus()) {
		randomMove(color, y, x, succ);
		if (color == BLACK) {
			color = WHITE;
		}
		else {
			color = BLACK;
		}
	}
}

void Goboard::undoMove() {
	BoardSquare* squareC, *squareH;
	int y = 0, x = 0;
	if (!(stack).isEmpty()) {
		for (int i = 0; i < 2; i++) {
			stack.pop(y, x);
			squareC = getSquareAt(y, x);
			squareC->color = EMPTY;	
		}
	}
	else {
		cout << "No moves to undo" << endl;
	}
}

void Goboard::randomMove(char color, int & y, int & x, bool & succ) {
	y = rand() % height, x = rand() % width;
	succ = false;
	while (!succ) {
		move(color, y, x, succ);
	}
}

void Goboard::moveHuman(char color, int & i, int & j, bool & succ) {
	cout << "Enter x-coordinate ";
	cin >> j;
	cout << "Enter y-coordinate ";
	cin >> i;
	move(color, i, j, succ);
}

void Goboard::gameOver(BoardSquare* square, char & color) {
	if (stalemate()) {
		setGameStatus(true);
		cout << "Too bad... There is no winner" << endl;
	}
	else if (victory(square, color)) {
		setGameStatus(true);
		cout << "Congratulations, " << color << " has won the game!" << endl;
	}
}

bool Goboard::stalemate() {
	int totalMoves = 0;
	totalMoves = width * height;
	if (totalMoves == stack.getLength()) {
		return true;
	}
	else {
		return false; 
	}
}

int Goboard::countConsecSquare(BoardSquare* square, int direction, int opdirection, char color) {
	int squareCounter = 1;
	BoardSquare* temp = square;
	do  {
		if (temp != square) {
			squareCounter++;
		}
		temp = temp->neighbours[direction];

	} while (temp && temp->color == color);
	temp = square;
	do {
		if (temp != square) {
			squareCounter++;
		}
		temp = temp->neighbours[opdirection];
	} while (temp && temp->color == color);
	return squareCounter;
}


bool Goboard::victory(BoardSquare* square, char & color) {
	if (stack.getLength() >= 9){
		int vertSeq = countConsecSquare(square, 0, 4, color );
		int horzSeq = countConsecSquare(square, 6, 2, color);
		int diaLSeq = countConsecSquare(square, 7, 3, color);
		int diaRSeq = countConsecSquare(square, 1, 5, color);
		if (vertSeq >= 5 || horzSeq >= 5 || diaLSeq >= 5 || diaRSeq >= 5) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}







// TODO
