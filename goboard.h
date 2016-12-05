// file gobord.h
#include <iostream>
#include "stack.h"
using namespace std;

#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

struct Player {
	char color;
};

struct BoardSquare {
    char color;          							 //			  7 0 1
	BoardSquare* neighbours[8] = {NULL};			 //Entrance   6   2    Exit
						      						 //			  5 4 3
	
}; // a square on the board

class Goboard {
  private:
	BoardSquare* entrance;
	BoardSquare* exit;
	BoardSquare* leftUpper;
	
	int height, width, minHeight = 15, minWidth = 15;
	Stack stack;
	Stack* st = &stack;
	void zip(BoardSquare* prevSquare, BoardSquare* nextSquare) {
		BoardSquare* temp = prevSquare;
		int countWidth = 1;
		while (prevSquare != NULL && nextSquare != NULL) {
			nextSquare->neighbours[7] = prevSquare->neighbours[6];
			nextSquare->neighbours[1] = prevSquare->neighbours[2];
			if (countWidth == 1) {
				prevSquare->neighbours[2]->neighbours[5] = nextSquare;
			}
			else if (countWidth == width) {
				prevSquare->neighbours[6]->neighbours[3] = nextSquare;
			}
			else {
				prevSquare->neighbours[2]->neighbours[5] = nextSquare;
				prevSquare->neighbours[6]->neighbours[3] = nextSquare;
			}
			countWidth++;
			prevSquare = prevSquare->neighbours[2];
			nextSquare = nextSquare->neighbours[2];
		}
	};

	void connectVert(BoardSquare* prevSquare, BoardSquare* nextSquare) {
		BoardSquare* temp = prevSquare;
		while (prevSquare != NULL && nextSquare != NULL) {
			prevSquare->neighbours[4] = nextSquare;
			nextSquare->neighbours[0] = prevSquare;
			prevSquare = prevSquare->neighbours[2];
			nextSquare = nextSquare->neighbours[2];
		}
	};

    BoardSquare* addSquare(char color){
    	BoardSquare* temp = new BoardSquare;
    	temp->color = color;
    	temp->neighbours[2] = entrance;
    	temp->neighbours[6] = NULL;
    	if(entrance!=NULL){
    		entrance->neighbours[6] = temp;
    	}
    	else{
    		exit = temp;
    	}
    	entrance = temp;
		return temp;
    };

    BoardSquare* createRow(int squares){
		BoardSquare* temp;
		entrance = NULL;
		exit = NULL;
    	for(int i = 0; i < squares; i++){
    		temp = addSquare(EMPTY);
    	}
		return temp;
    };

	void createCols(int h, int w) {
		BoardSquare* prev, *next = NULL;
		for (int i = 0; i < h; i++) {
			prev = next;
			next = createRow(w);
			if (i == 0) {
				leftUpper = next;
			}
			if (i >= 1) {
				connectVert(prev, next);
				zip(prev, next);
			}					
		}
	};

	BoardSquare* getSquareAt(int x, int y) {
		BoardSquare* square = leftUpper;	
		for (int i = 0; i < x; i++) {
			square = square->neighbours[4];
		}
		for (int i = 0; i < y; i++) {
			square = square->neighbours[2];
		}
		return square;
		
	};

	bool isOccupied(BoardSquare* square) {
		return(square->color == WHITE || square->color == BLACK);
	};

  public:
    Goboard ( );
    Goboard (int height, int width);
    ~Goboard ( );
    void createBoard ( );
    void randomMove (char color, int & i, int & j);
    void moveHuman (char color, int & i, int & j);
    void print ( );
    bool done ( );
    bool victory (char & color);
    void move (char color, int i, int j, bool & succes);
	void undoMove ( );
    // TODO
};//gobord
