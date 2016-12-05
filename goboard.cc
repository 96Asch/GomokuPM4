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
}//gobord::gobord

Goboard::Goboard(int h, int w) {
	height = h;
	width = w;
	entrance = NULL;
	exit = NULL;
	srand(width);
}//gobord::gobord

Goboard::~Goboard ( ) {
  // TODO
}//gobord::~gobord

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
	BoardSquare* square;
	square = getSquareAt(i,j);
	if (!isOccupied(square)) {
		square->color = color;
		stack.push(i,j);
		success = true;

	}
	else {
		cout << "Space is already occupied" << endl;
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

void Goboard::randomMove(char color, int & y, int & x) {
	y = rand() % height, x = rand() % width;
	bool success = false;
	while (!success) {
		move(color, y, x, success);
	}
}

void Goboard::moveHuman(char color, int & i, int & j) {

}




// TODO
