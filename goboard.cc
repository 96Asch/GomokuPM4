// file gobord.cc
#include "goboard.h"

#include <iostream>
using namespace std;

Goboard::Goboard ( ) {
  // TODO
}//gobord::gobord

Goboard::~Goboard ( ) {
  // TODO
}//gobord::~gobord

void Goboard::print ( ) {
	int i = 0;
	while(entrance){
		entrance = entrance->neighbours[6];
		i++;
		cout << "Square" << i << " Color = " << entrance->color << endl;
		if(entrance->neighbours[6] == NULL){
			cout << "End of Board" << endl;
		}

	}

}//gobord::print

void Goboard::createBoard(){
 createRow(1);
}

void rits(BoardSquare* up, BoardSquare* down){

}


// TODO
