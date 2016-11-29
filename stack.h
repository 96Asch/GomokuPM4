/*
	Array-based implementation of a stack to store moves
 */

#ifndef STACK_H_
#define STACK_H_

struct Move {
	int moveTo;
	int moveFrom;
	Move* nextMove;
};

class Stack {

	public:
		Stack();
		~Stack();
		void push(int moveFrom, int moveTo);
		void pop(int & moveFrom, int & moveTo);
		bool isEmpty();
		Move peek();

	private:
		Move* lastMove;

};



#endif /* STACK_H_ */
