/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 12:45 PM
 * Purpose: Version 4 - Placing pieces onto our board.                 
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
    
    //Displaying some information.
    cout<<endl;
    cout<<"R - Red Piece."<<endl;
    cout<<"B - Black Piece."<<endl;
    cout<<"X - Invalid Square."<<endl;
    cout<<"\nYou can't move pieces to invalid squares. Moreover,"<<endl;
    cout<<"you can only move pieces diagonally into empty square."<<endl;
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}