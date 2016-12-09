/*
	Pointer-based implementation of a stack to store moves
 */

#ifndef STACK_H_
#define STACK_H_

//Struct of a move.
struct Move {
	int x,y;
	Move* nextMove;
};

class Stack {

	public:
		Stack();
		~Stack();
		void empty();
		void push(int y, int x);
		void pop(int & y, int & x);
		bool isEmpty();
		int getLength();

	private:
		Move* lastMove;
		int size;

};



#endif /* STACK_H_ */
