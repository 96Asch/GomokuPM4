// file gobord.h
#include <iostream>

struct BoardSquare {
    char color;          							 //     7 0 1
	BoardSquare* neighbours[8];						 //     6   2
						      						 //     5 4 3
}; // a square on the board

class Goboard {
  private:
	BoardSquare* entrance;
    int height, width;
    void rits (BoardSquare* up, BoardSquare* down);

    void addSquare(char col){
		BoardSquare* square;
		square = new BoardSquare;
    	square->color = col;
    	square->neighbours[6] = entrance;
    	square->neighbours[2] = square;

    	entrance = square;
    };

    void createRow (int amount){
    	for(int i = 1; i <= amount; i++){
    	if(i%2==0){
    		addSquare('T');
    	}
    	else{
    		addSquare('F');
    	}
    	std::cout << "it: " << i << " Square was made" << std::endl;
    	}

    };
    // TODO

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
