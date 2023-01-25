/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 12:00 PM
 * Purpose: Version 3 - Putting our board into a class.                    
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
    cout<<"An empty checkers board: "<<endl;
    board->dsplyBrd();
    
    //Demonstrating our jumpTo() function which allows us to jump to a square
    //on our board if it's valid. (Not marked with an X and in bounds.)
    list<string>::iterator itr=board->jumpTo(4,5); //Row 4, Col 5.
    //Changing the value at the square we've jumped to.
    *itr=" O "; //Marking it with an O.
    
    //Displaying our board again.
    cout<<"\nAfter jumping to Row 4, Col 5 and marking it w/ an O: "<<endl;
    board->dsplyBrd();
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}