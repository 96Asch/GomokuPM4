/*
	A pointer-based Gomoku boardgame.
*/
#include <iostream>
#include "stack.h"
using namespace std;

//Definitions for colors and empty spaces.
#define BLACK 'B'
#define WHITE 'W'
#define EMPTY ' '

//Struct for a square on the board.
struct BoardSquare {
	char color;          							 //			  7 0 1
	BoardSquare* neighbours[8] = {NULL};			 //Entrance   6   2    Exit
};						      						 //			  5 4 3	


//Class for a goboard.
class Goboard {
  private:
	BoardSquare* entrance;
	BoardSquare* exit;
	BoardSquare* leftUpper;
	int height, width;
	Stack stack;
	bool gameIsOver;
	int gameType;
	char playerCol;
	bool usedUndo;
	
	//Adds a square and connects it to other squares.
	BoardSquare* addSquare(char color) {
		BoardSquare* temp = new BoardSquare;
		temp->color = color;
		temp->neighbours[2] = entrance;
		temp->neighbours[6] = NULL;
		if (entrance != NULL) {
			entrance->neighbours[6] = temp;
		}
		else {
			exit = temp;
		}
		entrance = temp;
		return temp;
	};

	//Creates a row of connected squares.
	BoardSquare* createRow(int squares) {
		BoardSquare* temp;
		entrance = NULL;
		exit = NULL;
		for (int i = 0; i < squares; i++) {
			temp = addSquare(EMPTY);
		}
		return temp;
	};

	//Creates columns of rows.
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

	//Function to connect vertical squares with eachother.
	void connectVert(BoardSquare* prevSquare, BoardSquare* nextSquare) {
		while (prevSquare != NULL && nextSquare != NULL) {
			prevSquare->neighbours[4] = nextSquare;
			nextSquare->neighbours[0] = prevSquare;
			prevSquare = prevSquare->neighbours[2];
			nextSquare = nextSquare->neighbours[2];
		}
	};

	//Function to connect diagonal squares with eachother.
	void zip(BoardSquare* prevSquare, BoardSquare* nextSquare) {
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

	//Returns a square at a particular coordinate.
	BoardSquare* getSquareAt(int y, int x) {
		BoardSquare* square = leftUpper;	
		for (int i = 0; i < y; i++) {
			square = square->neighbours[4];
		}
		for (int i = 0; i < x; i++) {
			square = square->neighbours[2];
		}
		return square;
		
	};

	//Returns true when a square is occupied.
	bool isOccupied(BoardSquare* square) {
		return(square->color == BLACK || square->color == WHITE);
	};

	//Function to switch the color of a player.
	void switchColor(char & color) {
		if (color == BLACK) {
			color = WHITE;
		}
		else {
			color = BLACK;
		}
	};

	// Converts a stream chars into a single int.
	void convertCharstoInt(char letter, int & numberToCheck) {
		int temp = letter - '0';
		numberToCheck *= 10;
		numberToCheck += temp;
	}

	// Returns the digits of a stream of chars up to maxNumber.
	int readDigit(int maxNumber) {
		int res = 0;
		char ch = '\n';
		while (!isdigit(ch)) {
			cin.get(ch);
		}
		convertCharstoInt(ch, res);
		while (ch != '\n') {
			cin.get(ch);
			if (isdigit(ch) && res < maxNumber) {
				convertCharstoInt(ch, res);
			}
		}
		if (res > maxNumber) {
			res /= 10;
		}
		cout << "You entered: " << res << endl;
		return res;
	}

  public:
    Goboard ( );
    Goboard (int height, int width);
    ~Goboard ( );
    void createBoard ( );
	bool getGameStatus();
	int getGameType();
	void setGameType(int gametype);
	char getPlayerCol();
	void setPlayerCol(char color);
	bool undoUsed();
    void randomMove (char color, int & i, int & j, bool & succ);
    void moveHuman (char color, int & i, int & j, bool & succ, bool & undo, char option);
	void turn(char & color, int & y, int & x, bool & succ, char & opt);
    void print ( );
    bool victory (BoardSquare* square, char & color);
	int countConsecSquare(BoardSquare* square, int dir, int opdir, char color);
	void gameOver(BoardSquare* square, char & color);
	bool stalemate();
    void move (char color, int i, int j, bool & succes);
	void undoMove ( );
    // TODO
};//gobord
