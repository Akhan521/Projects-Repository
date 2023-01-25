/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 15, 2022, 7:05 PM
 * Purpose: Version 12 - Adding a few algorithms into my game.
 * 
 *  Adding some basic implementations of a few STL algorithms. My game uses
 *  min(), max(), swap(), and find(). You'll find the implementations of the
 *  first 2 algorithms in main, to determine the minimum and maximum number
 *  of pieces captured. The other 2 algorithms are used in my Piece and 
 *  Board classes, respectively.  
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
    
    //Creating 2 player objects.
    Player *Aamir=new Player("Aamir");
    Player *Mark=new Player("Dr.Mark");
    
    //Setting pieces and our board.
    Aamir->setPiece(" B "); //We choose black as our color.
    Aamir->setBoard(board); 
    Mark->setPiece(" R ");  //The opponent will have red as their color.
    Mark->setBoard(board); 
    
    //Declaring a map to keep count of how many pieces each player captured.
    map<string,int> captPces;
    
    //Creating a red piece to capture.
    list<Piece *>::iterator it; //An iterator for a piece.
    it=board->jumpTo(6,7);      //Jumping to the square in R6 C7.
    (*it)->setPiece(" R ");     //Setting it as a red piece.
    (*it)->setPos(6,7);         //Setting its position.
    //Creating another red piece to capture.
    it=board->jumpTo(4,7);      //Jumping to the square in R4 C7.
    (*it)->setPiece(" R ");     //Setting it as a red piece.
    (*it)->setPos(4,7);         //Setting its position.
    //Creating a black piece to capture.
    it=board->jumpTo(3,2);      //Jumping to the square in R3 C2.
    (*it)->setPiece(" B ");     //Setting it as a red piece.
    (*it)->setPos(3,2);         //Setting its position.
    //Making the square in R3 C8 empty.
    it=board->jumpTo(3,8);      //Jumping to the square in R3 C8.
    (*it)->setPiece("   ");     //Setting it as an empty piece.
    (*it)->setPos(3,8);         //Setting its position.
    
    //Making a move with our player.
    cout<<"Use the black piece in R7 C8 to capture the red pieces in R6 C7 and R4 C7:\n";
    cout<<Aamir->getName()<<"'s Turn:\n";
    Aamir->makeMove(captPces);
    cout<<endl;
    
    //Making a move with our opponent.
    cout<<"Use the red piece in R2 C1 to capture the black piece in R3 C2:\n";
    cout<<Mark->getName()<<"'s Turn:\n";
    Mark->makeMove(captPces);
    cout<<endl;
    
    //Storing the maximum and minimum number of pieces captured.
    int maxCapt=max(captPces[Aamir->getPiece()],captPces[Mark->getPiece()]);
    int minCapt=min(captPces[Aamir->getPiece()],captPces[Mark->getPiece()]);
    //Displaying the maximum and minimum number of pieces captured.
    cout<<"Maximum number of pieces captured = "<<maxCapt<<endl;
    cout<<"Minimum number of pieces captured = "<<minCapt<<endl;
    
    //Exit the Program - Cleanup.
    delete board; //Deleting our board.
    delete Aamir; //Deleting our player.
    delete Mark;  //Deleting the opponent.
    return 0;
}