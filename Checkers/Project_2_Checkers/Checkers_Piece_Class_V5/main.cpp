/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 1:35 PM
 * Purpose: Version 5 - Creating a class for our pieces and using this
 *                      class to build our board out of Piece objects.              
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
    
    //Displaying the positions of all pieces.
    board->dsplyAllPos();
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}