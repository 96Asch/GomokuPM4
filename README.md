# GomokuPM4

/*
	AUTHORS:				      Andrew Huang & Micha de Jong
	STUDENTID:				    S1913999 & S1821784
	DATE OF COMPLETION:		--/--/2016
	ASSIGNMENT:				    4 "Gomoku"
  DESCRIPTION:          A fun and simple game of Gomoku
*/




FINISHED:

--

TODO:

FEATURES:

- Player may choose their own color, Black or White (Computer takes the other)
- Computer randomly places their pieces (OPTIONAL: Computer has some sort of AI to win a game)
- Modes are PvC and also CvC
- Changeable size of the board m x n
- On the players turn the board information is printed
- The game has to end and tell who the winner is

Players Turn:
- Player can place a piece 
- Reset their last turn (which also removes the last turn of the opponent)
- " het aantal mogelijke vervolgpartijen voor de huidige stand laten uitrekenen." (???)
- The player cannot place a piece on an already occupied space 

CODE RELEVANT:

- In the goboard contructor a pointer structure must be made where each space can point
  to it's direct neighbours and it's diagonal neighbours (array with size 8)
  (0 mid-top then clock-wise to 8 top-left )
- All moves must be recorded on a stack
- Recursive function possibleMoves which recursively calculates the number of possible moves a player
  can make (Basically a factorial function...)

