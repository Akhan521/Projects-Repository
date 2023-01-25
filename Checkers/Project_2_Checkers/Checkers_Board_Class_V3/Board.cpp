/* 
 * File:    Board.cpp
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 12:00 PM
 * Purpose: Version 3 - Putting our board into a class.                    
 */

#include "Board.h"

Board::Board(){
    //Creates an empty checkers board.
    this->fillBrd();
}

void Board::fillBrd(){
    //Giving our board 8 rows and 8 columns.
    board=list<list<string>>(DIM,list<string>(DIM));
    //To keep count of what row and column we're on.
    int row,col;
    //We declare an iterator to work with our 2-D list.
    list<list<string>>::iterator it;
    //We iterate over our 2-D list and initialize it.
    for(it=board.begin(),row=1;it!=board.end();it++,row++){
        //We declare an iterator to work with each list in our board.
        list<string>::iterator itr;
        //Here, it points to each individual list.
        for(itr=it->begin(),col=1;itr!=it->end();itr++,col++){
            //Creating the checkerboard pattern:
            //If we're on a square that can have a piece, we leave it empty.
            if((row+col)%2)
                *itr="   ";
            //If we're on a square that can't have a piece, we mark it with X.
            else
                *itr=" X ";
            //In checkers, we're only allowed to have pieces on certain squares.
            //I mark invalid squares with an X to indicate that these squares
            //are not allowed to have pieces on them.
        }
    }
}

void Board::dsplyBrd(){
    //To keep count of what row we're on.
    int row;
    //We declare an iterator to work with our 2-D list.
    list<list<string>>::iterator it;
    //We now display our board:
    cout<<"  +---+---+---+---+---+---+---+---+"<<endl;
    //We go through each list in our board...
    for(it=this->board.begin(),row=1;it!=this->board.end();it++,row++){
        cout<<row<<" |"; //Displaying the row we're on.
        //We declare an iterator to traverse each list in our board.
        list<string>::iterator itr;
        //Here, it points to each individual list.
        for(itr=it->begin();itr!=it->end();itr++){
            //Displaying our list elements.
            cout<<*itr<<"|";
        }
        cout<<endl<<"  +---+---+---+---+---+---+---+---+"<<endl;
    }
    //Displaying our columns.
    cout<<"    1   2   3   4   5   6   7   8"<<endl;
}

list<string>::iterator Board::jumpTo(int r,int c){
    //To keep count of what row and column we're on.
    int row,col;
    //We only jump to a square if it's valid. (Not marked with an X.)
    //We also have to make sure that we're within the board's bounds.
    if(r>=0&&r<8&&c>=0&&c<8&&(r+c)%2){
        //We declare an iterator to work with our 2-D list.
        list<list<string>>::iterator it;
        //We iterate over our 2-D list and find the row and column specified.
        for(it=this->board.begin(),row=1;it!=this->board.end();it++,row++){
            //We declare an iterator to work with each list in our board.
            list<string>::iterator itr;
            //Here, it points to each individual list.
            for(itr=it->begin(),col=1;itr!=it->end();itr++,col++){
                //If we've found the row and column...
                if(row==r&&col==c)
                    //We return the position of this square.
                    return itr;
                    //itr points to the element in our board with
                    //the row and column we've specified.
            }
        }
    }
    //If the square is marked with an X or out of bounds:
    else{
        //If it's marked with an X...
        if((row+col)%2==0)
            cout<<"\nThis is an invalid square..."<<endl;
        else
            cout<<"\nOUT OF BOUNDS!"<<endl;
    }
    //If we have an invalid square, we return an iterator to the end of
    //the last list in our board. 
    return this->board.end()->end(); //The end of the last list in our board.
}