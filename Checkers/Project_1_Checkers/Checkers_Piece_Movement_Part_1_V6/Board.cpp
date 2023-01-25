/* 
 * File:    Board.cpp
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 2:50 PM
 * Purpose: Version 6 - Piece Movement Part 1.          
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

//Moves a piece on our board.
void Board::move(){
    //To store the coordinates of the chosen piece.
    int x1=0,y1=0;
    //To jump to our chosen piece.
    list<Piece *>::iterator itr;
    //To store the piece that we've chosen.
    string ourPiece;
    //We keep prompting the user if they've chosen an invalid square...
    while(!isVldSquare(x1,y1)){
        //Prompt the user for which piece they'd like to move.
        cout<<"\nWhat piece would you like to move? (Row Column)\n";
        cout<<"EX: 4 5 would move the piece in row 4 column 5."<<endl;
        cin>>x1>>y1;
        //If we have an invalid square, we let the user know.
        if(!isVldSquare(x1,y1))
            cout<<"That is an invalid square!\n";
        else{
            //We jump to our chosen piece.
            itr=jumpTo(x1,y1);
            //We store the piece that we've chosen.
            ourPiece=(*itr)->getPiece();
            //We need to make sure that we're even able to move our piece.
            //If our piece is black...
            if(ourPiece==" B "){
                bool canMoveLeft=true;  //To hold whether we can move left or not.
                bool canMoveRight=true; //To hold whether we can move right or not.
                //We need to check the upper left and upper right diagonals.
                //If the upper left diagonal is a valid square.
                if(isVldSquare(x1-1,y1-1)){
                    //We jump to that square to check if it's empty.
                    list<Piece *>::iterator leftDiag=jumpTo(x1-1,y1-1);
                    //If it is not empty, that means we can't move into that square.
                    if((*leftDiag)->getPiece()!="   "){
                        //We can't move into this upper left square.
                        canMoveLeft=false;
                    }
                }
                //If it's not a valid square, we can't move into it.
                else canMoveLeft=false;
                //If the upper right diagonal is a valid square.
                if(isVldSquare(x1-1,y1+1)){
                    //We jump to that square to check if it's empty.
                    list<Piece *>::iterator rightDiag=jumpTo(x1-1,y1+1);
                    //If it is not empty, that means we can't move into that square.
                    if((*rightDiag)->getPiece()!="   "){
                        //We can't move into this upper right square.
                        canMoveRight=false;
                    }
                }
                //If it's not a valid square, we can't move into it.
                else canMoveRight=false;
                //If we can't move into any squares...
                //(If we can't move into either the upper left/right square...)
                if(!canMoveLeft&&!canMoveRight){
                    cout<<"Choose a different piece..."<<endl;
                    //Resetting it to two invalid positions.
                    x1=0;
                    y1=0;
                }
            }
            //If our piece is red...
            else if(ourPiece==" R "){
                bool canMoveLeft=true;  //To hold whether we can move left or not.
                bool canMoveRight=true; //To hold whether we can move right or not.
                //We need to check the lower left and lower right diagonals.
                //If the lower left diagonal is a valid square.
                if(isVldSquare(x1+1,y1-1)){
                    //We jump to that square to check if it's empty.
                    list<Piece *>::iterator leftDiag=jumpTo(x1+1,y1-1);
                    //If it is not empty, that means we can't move into that square.
                    if((*leftDiag)->getPiece()!="   "){
                        //We can't move into this lower left square.
                        canMoveLeft=false;
                    }
                }
                //If it's not a valid square, we can't move into it.
                else canMoveLeft=false;
                //If the lower right diagonal is a valid square.
                if(isVldSquare(x1+1,y1+1)){
                    //We jump to that square to check if it's empty.
                    list<Piece *>::iterator rightDiag=jumpTo(x1+1,y1+1);
                    //If it is not empty, that means we can't move into that square.
                    if((*rightDiag)->getPiece()!="   "){
                        //We can't move into this lower right square.
                        canMoveRight=false;
                    }
                }
                //If it's not a valid square, we can't move into it.
                else canMoveRight=false;
                //If we can't move into any squares...
                //(If we can't move into either the lower left/right square...)
                if(!canMoveLeft&&!canMoveRight){
                    cout<<"Choose a different piece..."<<endl;
                    //Resetting it to two invalid positions.
                    x1=0;
                    y1=0;
                }
            }
        }
    }
    //We set the square we're on as an empty piece since we're moving out of this square.
    (*itr)->setPiece("   ");
    //To store the coordinates of where we'd like to move our piece.
    int x2=0,y2=0;
    //We keep prompting the user if they've chosen an invalid square...
    while(!isVldSquare(x2,y2)){
        //Prompt the user for where they'd like to move their piece.
        cout<<"\nWhere would you like to move this piece? (Row Column)\n";
        cout<<"EX: 5 6 would mean that we move into the square in row 5 column 6."<<endl;
        //If we have a red piece...
        if(ourPiece==" R "){
            //We store where to move our piece.
            cin>>x2>>y2;
            //If we have an invalid square, we let the user know.
            if(!isVldSquare(x2,y2))
                cout<<"That is an invalid square!\n";
            //As a red piece, we HAVE to move DOWN on the board. This means that
            //the row we choose has to greater than that of our chosen piece.
            //The row we choose must also be the row just below our chosen piece.
            while(x2<x1||x2!=x1+1){
                //We output a message and reprompt the user.
                cout<<"\nYou have to move down on the board..."<<endl;
                cout<<"Where would you like to move this piece? (Row Column)\n";
                cin>>x2>>y2;
            }
        }
        //If we have a black piece...
        else if(ourPiece==" B "){
            //We store where to move our piece.
            cin>>x2>>y2;
            //If we have an invalid square, we let the user know.
            if(!isVldSquare(x2,y2))
                cout<<"That is an invalid square!\n";
            //As a black piece, we HAVE to move UP on the board. This means that
            //the row we choose has to be less than that of our chosen piece.
            //The row we choose must also be the row just above our chosen piece.
            while(x2>x1||x2!=x1-1){
                //We output a message and reprompt the user.
                cout<<"\nYou have to move up on the board..."<<endl;
                cout<<"Where would you like to move this piece? (Row Column)\n";
                cin>>x2>>y2;
            }
        }
    }
    //We jump to where we'd like to move our piece.
    itr=jumpTo(x2,y2);
    //We set it as our piece since we're moving into this square.
    (*itr)->setPiece(ourPiece);   
}