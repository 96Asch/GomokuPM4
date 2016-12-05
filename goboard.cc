// file gobord.cc
#include "goboard.h"

#include <iostream>
using namespace std;

Goboard::Goboard ( ) {
	height = 5;
	width = 5;
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
			cout << xSquare->color << "|";
			//cout << xSquare <<  " ";
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
//createRow(3);
}




// TODO
