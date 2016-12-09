
#include "huangdejongstack4.h"
#include <iostream>
using namespace std;


//Constructor of the stack
Stack::Stack(){
	size = 0;
	lastMove = NULL;
}

//Destructor of the stack (empty the stack)
Stack::~Stack(){
	int from, to;
	while(!isEmpty()){
		pop(from, to);
	}
	//cout << "Stack is empty" << endl;
}

//Empties the stack.
void Stack::empty() {
	int from, to;
	while (!isEmpty()) {
		pop(from, to);
	}
}

//Add an integer to the stack
void Stack::push(int y, int x){
	Move* newMove = new Move;
	newMove->y = y;
	newMove->x = x;
	newMove->nextMove = lastMove;
	lastMove = newMove;
	size++;
	//cout << "Pushed Move: " << newMove << " into stack with coordinates: (" << newMove->y << ", " << newMove->x << ")." << endl;
}

//Remove last added integer from the stack
void Stack::pop(int & y, int & x){
	Move* removedMove = lastMove;
	y = removedMove->y;
	x = removedMove->x;
	lastMove = lastMove->nextMove;
	size--;
	//cout << "Popped Move: " << removedMove << " from stack with coordinates: (" << removedMove->y << ", " << removedMove->x << ")." << endl;
	delete removedMove;
}

//Returns true when the stack is empty.
bool Stack::isEmpty(){
	return(lastMove == NULL);
}

//Returns the size of the stack.
int Stack::getLength() {
	return size;
}




