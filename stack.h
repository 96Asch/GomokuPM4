/*
	Array-based implementation of a stack to store moves
 */

#ifndef STACK_H_
#define STACK_H_

struct Move {
	int x,y;
	Move* nextMove;
};

class Stack {

	public:
		Stack();
		~Stack();
		void push(int y, int x);
		void pop(int & y, int & x);
		bool isEmpty();
		Move peek();

	private:
		Move* lastMove;

};



#endif /* STACK_H_ */
