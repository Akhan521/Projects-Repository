/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 12, 2022, 10:50 PM
 * Purpose: Version 9 - Piece Movement Part 4. 
 * 
 *  Adding functionality to capture multiple pieces in a row, if 
 *  we can capture more than one piece in a turn. So far, we've been
 *  able to capture one piece at a time, but what if we can capture
 *  more than one piece? We need to keep capturing pieces if we can.
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
    cout<<"Demonstrating how multiple pieces can be captured:"<<endl;
    
    //Declaring an iterator that will allow us to get pieces from our board.
    list<Piece *>::iterator it;
    
    //Jumping to the square in row 3, column 2:
    it=board->jumpTo(3,2);
    //Setting it as a black piece, so we can capture it with a red one.
    (*it)->setPiece(" B ");
    (*it)->setPos(3,2);
    
    //Jumping to the square in row 5, column 4:
    it=board->jumpTo(5,4);
    //Setting it as a black piece, so we can capture it with a red one.
    (*it)->setPiece(" B ");
    (*it)->setPos(5,4);
    
    //Jumping to the square in row 5, column 2:
    it=board->jumpTo(5,2);
    //Setting it as a black piece, so we can capture it with a red one.
    (*it)->setPiece(" B ");
    (*it)->setPos(5,2);
    
    //Displaying our modified board.
    board->dsplyBrd();
    
    //Capturing 2 black pieces in a row.
    cout<<"\nUse the red piece in R2 C1 to capture the black piece in R3 C2.\n";
    cout<<"Then, choose between capturing the piece in R5 C2 or R5 C4:\n";
    board->move();
    board->dsplyBrd();
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}