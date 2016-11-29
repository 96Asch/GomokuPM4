
#include "stack.h"
#include <iostream>
using namespace std;


//Constructor of the stack
Stack::Stack(){
	lastMove = NULL;
}

//Destructor of the stack (empty the stack)
Stack::~Stack(){
	int from, to;
	while(!isEmpty()){
		pop(from, to);
		cout << from << ", " << to << endl;
	}
	cout << "Stack is destroyed" << endl;
}

//Add an integer to the stack
void Stack::push(int moveFrom, int moveTo){
	Move* newMove = new Move;
	newMove->moveFrom = moveFrom;
	newMove->moveTo = moveTo;
	newMove->nextMove = lastMove;
	lastMove = newMove;
	cout << "Pushed " << newMove << " into stack with: " << newMove->moveFrom << ", " << newMove->moveTo << endl;
}

//Remove last added integer from the stack
void Stack::pop(int & moveFrom, int & moveTo){
	Move* removedMove = lastMove;
	moveFrom = removedMove->moveFrom;
	moveTo = removedMove->moveTo;
	lastMove = lastMove->nextMove;
	cout << "Popped " << removedMove << " from stack with: " << removedMove->moveFrom << ", " << removedMove->moveTo << endl;
	delete removedMove;
}

bool Stack::isEmpty(){
	return(lastMove == NULL);
}





