/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 12, 2022, 12:55 PM
 * Purpose: Version 7 - Piece Movement Part 2. 
 * 
 *  Adding functionality to check whether a piece we've chosen can even move.
 *  If our chosen piece doesn't have any legal moves, we prompt the player
 *  to choose a different piece. We also ensure that the player moves into
 *  a square that is diagonally to the right/left. The player should not be
 *  able to jump any squares. 
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
    
    //Displaying our board.
    cout<<"A checkers board: "<<endl<<endl;
    board->dsplyBrd();
    
    //Moving 1 piece.
    board->move();
    board->dsplyBrd();
    
    //Moving another piece.
    board->move();
    board->dsplyBrd();
    
    //Moving a 3rd piece.
    board->move();
    board->dsplyBrd();
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}