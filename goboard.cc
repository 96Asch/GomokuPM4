// file gobord.cc
#include "goboard.h"
#include "stack.h"
#include <cstdlib>
#include <iostream>
using namespace std;

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

Goboard::Goboard ( ) {
	height = minHeight;
	width = minWidth;
	entrance = NULL;
	exit = NULL;
}//gobord::gobord

Goboard::Goboard(int h, int w) {
	height = h;
	width = w;
	entrance = NULL;
	exit = NULL;
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

void Goboard::move(char color, int i, int j) {
	BoardSquare* square;
	square = getSquareAt(i,j);
	if (square->color != WHITE && square->color != BLACK) {
		square->color = color;
		stack.push(i,j);

	}
	else {
		cout << "Space is already occupied" << endl;
	}
}

void Goboard::undoMove() {
	BoardSquare* squareC, *squareH;
	int y = 0, x = 0;
	if (!(stack).isEmpty()) {
		stack.pop(y, x);
		squareC = getSquareAt(y, x);
		squareC->color = EMPTY;
		stack.pop(y, x);

	}
	else {
		cout << "No moves to undo" << endl;
	}
}

void Goboard::randomMove(char color, int & i, int & j) {
	
}

void Goboard::moveHuman(char color, int & i, int & j) {

}




// TODO
