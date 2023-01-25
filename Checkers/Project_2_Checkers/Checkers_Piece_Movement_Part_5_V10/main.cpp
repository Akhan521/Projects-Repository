/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 13, 2022, 7:10 PM
 * Purpose: Version 10 - Piece Movement Part 5. 
 * 
 *  Adding in King pieces that can move in both directions (up/down).
 *  When a piece reaches the opposite end of the board, it becomes a
 *  King piece that can move both up and down. Capturing a King piece
 *  is the same as capturing any other piece. Additionally, I add a 
 *  function to test whether we need to forfeit the game. If no legal
 *  moves are available, we have to forfeit the game.
 */

//System Libraries:

//User Libraries:
#include "Board.h"

//Global Constants.
//Math, Science, Universal, Conversions, High Dimensioned Arrays.

//Function Prototypes:

//Execution Begins Here:
int main(int argc, char** argv) {
    //Initialize the Random Number Seed.
    
    //Creating a board object.
    Board *board=new Board();
    
    //Displaying our purpose.
    cout<<"Demonstrating how multiple pieces can be captured with a King piece:"<<endl;
    
    //Declaring an iterator that will allow us to get pieces from our board.
    list<Piece *>::iterator it;
    
    //Jumping to the square in row 3, column 4:
    it=board->jumpTo(3,4);
    //Setting it as a black King piece:
    (*it)->setPiece(" B ");
    (*it)->setPos(3,4);
    //Setting it as a king piece.
    (*it)->setKing(true);
    
    //Jumping to the square in row 4, column 5:
    it=board->jumpTo(4,5);
    //Setting it as a red piece, so we can capture it with a black one.
    (*it)->setPiece(" R ");
    (*it)->setPos(4,5);
    
    //Jumping to the square in row 4, column 7:
    it=board->jumpTo(4,7);
    //Setting it as a red piece, so we can capture it with a black one.
    (*it)->setPiece(" R ");
    (*it)->setPos(4,7);
    
    //Displaying our board.
    cout<<"\nUse the black King piece in R3 C4 to capture the red piece in R4 C5."<<endl;
    cout<<"Then, use that same black King piece to capture the red piece in R4 C7."<<endl;
    cout<<"This demonstrates how a King piece can move both up and down on the board."<<endl;
    board->dsplyBrd();
    
    //Capturing 2 red pieces in a row with a black King piece.
    board->move(" B ");
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}