// file gobord.h
#include <iostream>

struct BoardSquare {								//		   U
    int color;          							 //      7 0 1
	BoardSquare* neighbours[8];						 //prev  6   2  next
						      						 //      5 4 3
}; // a square on the board                                    D

class Goboard {
  private:
	BoardSquare* entrance, *exit, *up, *down;
    int height, width;
    void rits (BoardSquare* up, BoardSquare* down);

    void connectVert(BoardSquare* downPtr, BoardSquare* upPtr){
    	BoardSquare* temp = downPtr ;
    	int x = 0;
    	while(temp!=NULL){
    		//temp->neighbours[0] = NULL;
    		std::cout << temp->color << " k";
    		temp = temp->neighbours[2];
    		x++;
    	}
    	std::cout << " " << x;
    }

    BoardSquare* addSquare(int color){
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
    	BoardSquare* leftSquare;
    	for(int i = 0; i < squares; i++){
    		leftSquare = addSquare(i);
    	}
    	entrance = NULL;
    	exit = NULL;
    	return leftSquare;
    };

    void createCols(int height, int width){
    	BoardSquare* leftSquarePrev, *leftSquareNext;
    	for(int i = 0; i < height; i++){
    		leftSquarePrev = leftSquareNext;
    		leftSquareNext = createRow(width);
    		connectVert(leftSquarePrev, leftSquareNext);
    		std::cout << std::endl;
    	//	if(i>1){

    	//	}
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
