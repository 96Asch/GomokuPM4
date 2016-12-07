// file gobord.cc
#include "goboard.h"
#include "stack.h"
#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
using namespace std;

//Definitions for colors and empty spaces.
#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

#define PVC 1

//Constructor for a board with a set height and width.
Goboard::Goboard ( ) {
	height = 5, width = 5;
	entrance = NULL, exit = NULL, leftUpper = NULL;
	gameType = 0;
	srand(height*width-height);
	gameIsOver = false, usedUndo = false;
	playerCol = EMPTY;
}//gobord::gobord

 //Constructor for a board with a given height and width.
Goboard::Goboard(int h, int w) {
	height = h, width = w;
	gameType = 0;
	entrance = NULL, exit = NULL, leftUpper = NULL;
	srand(width-height*width);
	gameIsOver = false, usedUndo = false;
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

//Returns true if the undoMove function has been used.
bool Goboard::undoUsed() {
	return usedUndo;
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
	if (!(stack).isEmpty()) {
		for (int i = 0; i < 2; i++) {
			stack.pop(y, x);
			squareC = getSquareAt(y, x);
			squareC->color = EMPTY;	
		}
		usedUndo = true;
	}
	else {
		cout << "No moves to undo" << endl;
	}
}

//Function to place a piece on a random position.
void Goboard::randomMove(char color, int & y, int & x, bool & succ) {
	succ = false;
	Sleep(1000);
	while (!succ) {
		y = rand() % height, x = rand() % width;
		move(color, y, x, succ);
	}
}

//Function to let a human player place a piece.
void Goboard::moveHuman(char color, int & i, int & j, bool & succ) {
		cout << "Enter x-coordinate ";
		j = readDigit(height-1);
		cout << "Enter y-coordinate ";
		i = readDigit(width-1);
		move(color, i, j, succ);
}

//A turn where a player or a computer can do a move.
void Goboard::turn(char & color, int & y, int & x, bool & succ) {
	usedUndo = false;
	if (getGameType() == 1 && !getGameStatus()) {
		if (playerCol == color) {
			cout << "Turn: " << stack.getLength()+1 << " -- " << color << "'s turn" << endl;
		}

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
		if (succ) {
			switchColor(color);
		}
	}
	else if (getGameType() == 2 && !getGameStatus()) {
		randomMove(color, y, x, succ);
		if (succ) {
			switchColor(color);
		}
	}
}

//Function to determine when a game has ended in a stalemate.
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

//Function to count the number of consecutive squares in each direction.
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
		else {
			return false;
		}
	}
	else {
		return false;
	}
}

//Function to determine when a game is over.
void Goboard::gameOver(BoardSquare* square, char & color) {
	if (stalemate()) {
		gameIsOver = true;
		cout << "Too bad... There is no winner" << endl;
	}
	else if (victory(square, color)) {
		gameIsOver = true;
		cout << "Congratulations, " << color << " has won the game!" << endl;
	}
}
