/* 
 * File:    Board.cpp
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 1:35 PM
 * Purpose: Version 5 - Creating a class for our pieces.              
 */

#include "Board.h"

//Our constructor.
Board::Board(){
    //Creates an empty checkers board.
    this->fillBrd();
    //Places pieces onto our board.
    this->putPieces();
}

//Our destructor.
Board::~Board(){
    //We declare an iterator to span our 2-D list.
    list<list<Piece *>>::iterator it;
    //We iterate over our 2-D list and destroy each piece.
    for(it=board.begin();it!=board.end();it++){
        //We declare an iterator to work with each list in our board.
        list<Piece *>::iterator itr;
        //Here, it points to each individual list.
        for(itr=it->begin();itr!=it->end();itr++){
            //Deleting each piece;
            delete *itr;
        }
    }
}

//Fills our board.
void Board::fillBrd(){
    //Giving our board 8 rows and 8 columns.
    board=list<list<Piece *>>(DIM,list<Piece *>(DIM));
    //To keep count of what row and column we're on.
    int row,col;
    //We declare an iterator to work with our 2-D list.
    list<list<Piece *>>::iterator it;
    //We iterate over our 2-D list and initialize it.
    for(it=board.begin(),row=1;it!=board.end();it++,row++){
        //We declare an iterator to work with each list in our board.
        list<Piece *>::iterator itr;
        //Here, it points to each individual list.
        for(itr=it->begin(),col=1;itr!=it->end();itr++,col++){
            //If we're on a square that can have a piece, we create an empty piece.
            if((row+col)%2)
                //Creating an empty piece and setting its position.
                *itr=new Piece("   ",row,col); 
            //If we're on a square that can't have a piece, we mark it with X.
            else
                //We create a piece with an X to indicate an invalid square.
                *itr=new Piece(" X ",row,col);
            //In checkers, we're only allowed to have pieces on certain squares.
            //I mark invalid squares with an X to indicate that these squares
            //are not allowed to have pieces on them.
        }
    }
}

//Checks whether we have a valid square.
bool Board::isVldSquare(int r,int c){
    //The row and column must be within bounds of our board.
    //It must also not be marked with an X.
    //The portion "(r+c)%2" accounts for squares that are marked with
    //an X. If that portion returns a 1, the square is valid. Otherwise,
    //the square is invalid or it's marked with an X.
    return (r>0&&r<=DIM&&c>0&&c<=DIM&&(r+c)%2);
}

//Places pieces onto our board.
void Board::putPieces(){
    //To keep count of what row and column we're on.
    int row,col;
    //We declare an iterator to work with our 2-D list.
    list<list<Piece *>>::iterator it;
    //We iterate over our 2-D list and place our pieces.
    for(it=board.begin(),row=1;it!=board.end();it++,row++){
        //We declare an iterator to work with each list in our board.
        list<Piece *>::iterator itr;
        //Here, it points to each individual list.
        for(itr=it->begin(),col=1;itr!=it->end();itr++,col++){
            //Place red pieces in the first 2 rows.
            if(row==1||row==2){
                //We only place pieces on valid squares.
                if(isVldSquare(row,col)){
                    (*itr)->setPiece(" R "); //Red piece.
                }
            }
            //Place black pieces in the last 2 rows.
            else if(row==7||row==8){
                //We only place pieces on valid squares.
                if(isVldSquare(row,col)){
                    (*itr)->setPiece(" B "); //Black piece.
                }
            }
        }
    }
}

//Displays our board.
void Board::dsplyBrd(){
    //To keep count of what row we're on.
    int row;
    //We declare an iterator to work with our 2-D list.
    list<list<Piece *>>::iterator it;
    //We now display our board:
    cout<<"  +---+---+---+---+---+---+---+---+"<<endl;
    //We go through each list in our board...
    for(it=board.begin(),row=1;it!=board.end();it++,row++){
        cout<<row<<" |"; //Displaying the row we're on.
        //We declare an iterator to traverse each list in our board.
        list<Piece *>::iterator itr;
        //Here, it points to each individual list.
        for(itr=it->begin();itr!=it->end();itr++){
            //Displaying our list elements.
            cout<<(*itr)->getPiece()<<"|";
        }
        cout<<endl<<"  +---+---+---+---+---+---+---+---+"<<endl;
    }
    //Displaying our columns.
    cout<<"    1   2   3   4   5   6   7   8"<<endl;
}

//Jumps to a piece in our board.
list<Piece *>::iterator Board::jumpTo(int r,int c){
    //To keep count of what row and column we're on.
    int row,col;
    //We only jump to a square if it's valid. (Not marked with an X.)
    //We also have to make sure that we're within the board's bounds.
    if(isVldSquare(r,c)){
        //We declare an iterator to work with our 2-D list.
        list<list<Piece *>>::iterator it;
        //We iterate over our 2-D list and find the row and column specified.
        for(it=board.begin(),row=1;it!=board.end();it++,row++){
            //We declare an iterator to work with each list in our board.
            list<Piece *>::iterator itr;
            //Here, it points to each individual list.
            for(itr=it->begin(),col=1;itr!=it->end();itr++,col++){
                //If we've found the row and column...
                if(row==r&&col==c)
                    //We return the position of this square.
                    return itr;
                    //itr points to the piece in our board with
                    //the row and column we've specified.
            }
        }
    }
    //If the square is marked with an X or out of bounds:
    else{
        cout<<"\nThis is an invalid square..."<<endl;
    }
    //If we have an invalid square, we return an iterator to the end of
    //the last list in our board. 
    return board.end()->end(); //The end of the last list in our board.
}

//Displays the positions of all pieces.
void Board::dsplyAllPos(){
    cout<<endl<<endl<<"All Positions:"<<endl;
    cout<<"----------------"<<endl;
    //Declaring an iterator to span our board.
    list<list<Piece *>>::iterator it;
    for(it=board.begin();it!=board.end();it++){
        //Declaring an iterator for each list in our board.
        list<Piece *>::iterator itr;
        for(itr=it->begin();itr!=it->end();itr++){
            //If we're on a red piece, we display it's position.
            if((*itr)->getPiece()==" R ")
                //first is used to get the row value.
                //second is used to get the column value.
                cout<<"RED  : R: "<<(*itr)->getPos().first<<
                            " C: "<<(*itr)->getPos().second<<endl;
            //If we're on a black piece, we display it's position.
            else if((*itr)->getPiece()==" B ")
                //first is used to get the row value.
                //second is used to get the column value.
                cout<<"Black: R: "<<(*itr)->getPos().first<<
                            " C: "<<(*itr)->getPos().second<<endl;
        }
    }
}