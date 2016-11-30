// file gobord.h
#include <iostream>

struct BoardSquare {
    int color;          							 //      7 0 1
	BoardSquare* neighbours[8];						 //prev  6   2  next
						      						 //      5 4 3
}; // a square on the board

class Goboard {
  private:
	BoardSquare* entrance = NULL;
	BoardSquare* exit = NULL;
    int height, width;
    void rits (BoardSquare* up, BoardSquare* down);

    void addSquare(int color){
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
    };

    void createRow(int squares){
    	for(int i = 0; i < squares; i++){
    		addSquare(i);
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
