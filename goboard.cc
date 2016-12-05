// file gobord.cc
#include "goboard.h"

#include <iostream>
using namespace std;

Goboard::Goboard ( ) {
	entrance = NULL;
	exit = NULL;
}//gobord::gobord

Goboard::~Goboard ( ) {
  // TODO
}//gobord::~gobord

void Goboard::print ( ) {
	BoardSquare* ySquare = leftUpper, *xSquare = leftUpper;
	while (ySquare != NULL) {
		xSquare = ySquare;
		while (xSquare != NULL) {
			cout << xSquare->color << " ";
			xSquare = xSquare->neighbours[2];
		}
		ySquare = ySquare->neighbours[4];
		cout << endl;
		}
}//gobord::print

void Goboard::createBoard(){
 createCols(height, width);
//createRow(3);
}

void rits(BoardSquare* up, BoardSquare* down){

}


// TODO
