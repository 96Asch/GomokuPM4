// file gobord.h
class BoardSquare {
  public:
    char color;          		 //     7 0 1
    BoardSquare* neighbours[8];  //     6   2
    BoardSquare ( );        	 //     5 4 3
};// a square on the board

class Goboard {
  private:
    BoardSquare* entrance;
    int height, width;
    void rits (BoardSquare* up, BoardSquare* down);
    BoardSquare* createRow (int amount);
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
