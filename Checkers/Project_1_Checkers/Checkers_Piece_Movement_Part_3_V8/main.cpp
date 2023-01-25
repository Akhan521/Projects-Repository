/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 12, 2022, 1:50 PM
 * Purpose: Version 8 - Piece Movement Part 3. 
 * 
 *  Adding functionality to capture pieces on our board. If we can jump a 
 *  piece, we capture it. This is, by far, the most important functionality 
 *  since it defines how players can capture opponent pieces and win the game.
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
    cout<<"Demonstrating how pieces can be captured:"<<endl<<endl;
    
    //Declaring an iterator that will allow us to get pieces from our board.
    list<Piece *>::iterator it;
    
    //Jumping to the square in row 3, column 2:
    it=board->jumpTo(3,2);
    //Setting it as a black piece, so we can capture it with a red one.
    (*it)->setPiece(" B ");
    (*it)->setPos(3,2);
    
    //Jumping to the square in row 6, column 7:
    it=board->jumpTo(6,7);
    //Setting it as a red piece, so we can capture it with a black one.
    (*it)->setPiece(" R ");
    (*it)->setPos(6,7);
    
    //Displaying our modified board.
    board->dsplyBrd();
    
    //Capturing 1 piece.
    cout<<"\nUse the red piece in R 2, C 1 to capture the black piece in R3, C2:\n";
    board->move();
    board->dsplyBrd();
    
    //Capturing another piece.
    cout<<"\nUse the black piece in R 7, C 8 to capture the red piece in R6, C7:\n";
    board->move();
    board->dsplyBrd();
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}