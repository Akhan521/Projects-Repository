/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 2:50 PM
 * Purpose: Version 6 - Piece Movement Part 1. 
 *              Basic movement for pieces.       
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
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}