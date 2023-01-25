/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 15, 2022, 2:45 PM
 * Purpose: Version 11 - Adding players + Captured pieces count. 
 * 
 *  Adding players into our game. These players are capable of choosing
 *  whether they'd like to play with red pieces or black pieces. 
 *  Additionally, I utilize a map to keep count of how many pieces
 *  a player has captured. The map uses a player's piece as its key and
 *  it stores the number of pieces the given player has captured as its value.
 */

//System Libraries:

//User Libraries:
#include "Player.h"

//Global Constants.
//Math, Science, Universal, Conversions, High Dimensioned Arrays.

//Function Prototypes:

//Execution Begins Here:
int main(int argc, char** argv) {
    //Initialize the Random Number Seed.
    
    //Creating a board object.
    Board *board=new Board();
    
    //Creating a player object.
    Player Aamir;
    
    //Setting our piece and our board.
    Aamir.setPiece(" B "); //We choose black as our color.
    Aamir.setBoard(board); 
    
    //Declaring a map to keep count of how many pieces we've captured.
    map<string,int> captPces;
    
    //Creating a red piece to capture.
    list<Piece *>::iterator it; //An iterator for a piece.
    it=board->jumpTo(6,7);      //Jumping to the square in R6 C7.
    (*it)->setPiece(" R ");     //Setting it as a red piece.
    (*it)->setPos(6,7);         //Setting its position.
    
    //Displaying our purpose.
    cout<<"Showcasing our Player object and captured pieces count:\n\n";
    cout<<"Use the black piece in R7 C8 to capture the red piece in R6 C7.\n";
    
    //Making a move with our player.
    Aamir.makeMove(captPces);
    
    //Displaying how many pieces we've captured.
    cout<<"\nNumber of Captured Pieces: "<<captPces[Aamir.getPiece()]<<endl;
    
    //Exit the Program - Cleanup.
    delete board;
    return 0;
}