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
	BoardSquare* temp = entrance;
	while(temp!=NULL){
		cout << temp->color << " ";
		temp = temp->neighbours[2];
	}
}//gobord::print

void Goboard::createBoard(){
 createCols(3,3);
}

void rits(BoardSquare* up, BoardSquare* down){

}


// TODO
