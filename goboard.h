// file gobord.h
#include <iostream>
using namespace std;
struct BoardSquare {
    char color;          							 //      7 0 1
	BoardSquare* neighbours[8];						 //prev  6   2  next
						      						 //      5 4 3
}; // a square on the board

class Goboard {
  private:
	BoardSquare* entrance = NULL;
	BoardSquare* exit = NULL;
    int height, width;
	
	void zip(BoardSquare* prevSquare, BoardSquare* nextSquare) {
		BoardSquare* temp = prevSquare;
		while (prevSquare != NULL && nextSquare != NULL) {
			nextSquare->neighbours[7] = prevSquare->neighbours[6];
			nextSquare->neighbours[1] = prevSquare->neighbours[2];
//			prevSquare->neighbours[6]->neighbours[3] = nextSquare;
//			prevSquare->neighbours[2]->neighbours[5] = nextSquare;
			prevSquare = prevSquare->neighbours[2];
			nextSquare = nextSquare->neighbours[2];
		}
	
	};

	void connectVert(BoardSquare* prevSquare, BoardSquare* nextSquare) {
		BoardSquare* temp = prevSquare;
		while (prevSquare != NULL && nextSquare != NULL) {

			prevSquare->neighbours[4] = nextSquare;
			nextSquare->neighbours[0] = prevSquare;

			cout << " " << temp->color << " ";
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
    	for(int i = 0; i < squares; i++){
    		temp = addSquare('X');
    	}
		entrance = NULL;
		exit = NULL;
		return temp;
    };

	void createCols(int h, int w) {
		BoardSquare* prev, *next = NULL;
		for (int i = 0; i <= h; i++) {
			prev = next;
			next = createRow(w);
			if (i >= 1) {
				connectVert(prev, next);
				zip(prev, next);
				cout << endl;
			}	
		}
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
    void move (char color, int i, int j);
    // TODO
};//gobord
