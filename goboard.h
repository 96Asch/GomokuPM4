// file gobord.h
class boardSquare {
  public:
    char color;           //     7 0 1
    boardSquare* neighbours[8];  //     6   2
    boardSquare ( );        //     5 4 3
};// a square on the board

class goboard {
  private:
    boardSquare* ingang;
    int height, width;
    void rits (boardSquare* up, boardSquare* down);
    boardSquare* createRow (int amount);
    // TODO
  public:
    goboard ( );
    goboard (int height, int width);
    ~goboard ( );
    void createBoard ( );
    void randomMove (char color, int & i, int & j);
    void moveHuman (char color, int & i, int & j);
    void print ( );
    bool done ( );
    bool victory (char & color);
    void move (char color, int i, int j);
    // TODO
};//gobord
