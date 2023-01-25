/* 
 * File:    Board.cpp
 * Author:  Aamir Khan
 * Created: Oct. 12, 2022, 1:50 PM
 * Purpose: Version 8 - Piece Movement Part 3.          
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
                //Creating an empty piece and initializing its position to nothing.
                *itr=new Piece("   ",0,0); 
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
                    (*itr)->setPos(row,col); //Its position.
                }
            }
            //Place black pieces in the last 2 rows.
            else if(row==7||row==8){
                //We only place pieces on valid squares.
                if(isVldSquare(row,col)){
                    (*itr)->setPiece(" B "); //Black piece.
                    (*itr)->setPos(row,col); //Its position.
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
    //The position of the piece we'll be capturing, if capturing is an option.
    pair<int,int> capPos;
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
            //There must be at least 1 square that our piece can move into
            //for it to be considered a valid piece for us to choose.
            //We call the canMove() function, passing our piece and its position.
            bool canMove=this->canMove(ourPiece,(*itr)->getPos());
            bool canCapt=this->canCapture(ourPiece,(*itr)->getPos(),capPos);
            //If we can't move into any squares and we can't capture any pieces...
            if(!canMove&&!canCapt){
                cout<<"Choose a different piece..."<<endl;
                //Resetting it to two invalid positions.
                x1=0;
                y1=0;
            }
        }
    }
    //We set the square we're on as an empty piece since we're moving out of this square.
    (*itr)->setPiece("   ");
    //Since we now have an empty piece, we need to reset the position to nothing.
    (*itr)->setPos(0,0);
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
            else{
                //To hold whether we can capture a piece or not.
                bool canCapt=this->canCapture(ourPiece,make_pair(x1,y1),capPos);
                //If a piece can't be captured, we need to make sure that an 
                //appropriate square is chosen that is directly to the left/right.
                if(!canCapt){
                    //As a red piece, we HAVE to move DOWN on the board. This means that
                    //the row we choose has to greater than that of our chosen piece.
                    //The row we choose must also be the row just below our chosen piece.
                    //The column we choose must also be directly to the left/right.
                    while((x2<x1||x2!=x1+1)||(y2!=y1-1&&y2!=y1+1)){
                        //We output a message and reprompt the user.
                        cout<<"\nYou have to move down on the board..."<<endl;
                        cout<<"You can only move to the left/right diagonally.\n";
                        cout<<"Where would you like to move this piece? (Row Column)\n";
                        cin>>x2>>y2;
                    }
                }
                //If we can capture a piece...
                else{
                    //We need to make sure that the square we choose is directly
                    //after the piece that we'll be capturing.
                    while(((x2<x1||x2!=x1+2)||(y2!=y1-2&&y2!=y1+2))){
                        //We output a message and reprompt the user.
                        cout<<"\nYou have to jump into the square after the piece \n";
                        cout<<"you'll be capturing. The square must be valid. \n";
                        cout<<"Where would you like to move this piece? (Row Column)\n";
                        cin>>x2>>y2;
                    }
                }
                //We jump to where we'd like to move our piece.
                itr=jumpTo(x2,y2);
                //If it is not empty, we have to choose another square.
                if((*itr)->getPiece()!="   "){
                    cout<<"Choose a different square..."<<endl;
                    //We reset our coordinates, in order to choose a different square.
                    x2=0;
                    y2=0;
                }
            }
        }
        //If we have a black piece...
        else if(ourPiece==" B "){
            //We store where to move our piece.
            cin>>x2>>y2;
            //If we have an invalid square, we let the user know.
            if(!isVldSquare(x2,y2))
                cout<<"That is an invalid square!\n";
            else{
                //To hold whether we can capture a piece or not.
                bool canCapt=this->canCapture(ourPiece,make_pair(x1,y1),capPos);
                //If a piece can't be captured, we need to make sure that an 
                //appropriate square is chosen that is directly to the left/right.
                if(!canCapt){
                    //As a black piece, we HAVE to move UP on the board. This means that
                    //the row we choose has to be less than that of our chosen piece.
                    //The row we choose must also be the row just above our chosen piece.
                    //The column we choose must also be directly to the left/right.
                    while(((x2>x1||x2!=x1-1)||(y2!=y1-1&&y2!=y1+1))){
                        //We output a message and reprompt the user.
                        cout<<"\nYou have to move up on the board..."<<endl;
                        cout<<"You can only move to the left/right diagonally.\n";
                        cout<<"Where would you like to move this piece? (Row Column)\n";
                        cin>>x2>>y2;
                    }
                }
                //If we can capture a piece...
                else{
                    //We need to make sure that the square we choose is directly
                    //after the piece that we'll be capturing.
                    while(((x2>x1||x2!=x1-2)||(y2!=y1-2&&y2!=y1+2))){
                        //We output a message and reprompt the user.
                        cout<<"\nYou have to jump into the square after the piece \n";
                        cout<<"you'll be capturing. The square must be valid. \n";
                        cout<<"Where would you like to move this piece? (Row Column)\n";
                        cin>>x2>>y2;
                    }
                }
                //We jump to where we'd like to move our piece.
                itr=jumpTo(x2,y2);
                //If it is not empty, we have to choose another square.
                if((*itr)->getPiece()!="   "){
                    cout<<"Choose a different square..."<<endl;
                    //We reset our coordinates, in order to choose a different square.
                    x2=0;
                    y2=0;
                }
            }
        }
    }
    //We need to check whether we can capture a piece or not.
    //If we can capture a piece...
    if(canCapture(ourPiece,make_pair(x1,y1),capPos)){
        //We go ahead and capture it.
        capture(ourPiece,make_pair(x2,y2),capPos);
    }
    //Otherwise, we just move our piece into our chosen square.
    else{
        //Once we have chosen a valid square to move our piece into,
        //we set it as our piece. (Since we're moving into this square.)
        (*itr)->setPiece(ourPiece);
        //We now need to set the position of our piece.
        (*itr)->setPos(x2,y2); //Where we moved our piece.
    }
}

//To determine whether we can move a piece. The first parameter is our piece.
//The second parameter is the position of our piece. We check diagonals.
bool Board::canMove(string ourPiece,pair<int,int> pos){
    int x=pos.first;  //The row of our piece.
    int y=pos.second; //The col of our piece.
    bool canMove;     //To hold whether we can move into at least 1 square.
    //If our piece is black...
    if(ourPiece==" B "){
        bool canMoveLeft=true;  //To hold whether we can move left or not.
        bool canMoveRight=true; //To hold whether we can move right or not.
        //We need to check the upper left and upper right diagonals.
        //If the upper left diagonal is a valid square.
        if(isVldSquare(x-1,y-1)){
            //We jump to that square to check if it's empty.
            list<Piece *>::iterator leftDiag=jumpTo(x-1,y-1);
            //If it is not empty, that means we can't move into that square.
            if((*leftDiag)->getPiece()!="   "){
                //We can't move into this upper left square.
                canMoveLeft=false;
            }
        }
        //If it's not a valid square, we can't move into it.
        else canMoveLeft=false;
        //If the upper right diagonal is a valid square.
        if(isVldSquare(x-1,y+1)){
            //We jump to that square to check if it's empty.
            list<Piece *>::iterator rightDiag=jumpTo(x-1,y+1);
            //If it is not empty, that means we can't move into that square.
            if((*rightDiag)->getPiece()!="   "){
                //We can't move into this upper right square.
                canMoveRight=false;
            }
        }
        //If it's not a valid square, we can't move into it.
        else canMoveRight=false;
        //If we can move into at least 1 square...
        canMove=(canMoveLeft||canMoveRight);
    }
    //If our piece is red...
    else if(ourPiece==" R "){
        bool canMoveLeft=true;  //To hold whether we can move left or not.
        bool canMoveRight=true; //To hold whether we can move right or not.
        //We need to check the lower left and lower right diagonals.
        //If the lower left diagonal is a valid square.
        if(isVldSquare(x+1,y-1)){
            //We jump to that square to check if it's empty.
            list<Piece *>::iterator leftDiag=jumpTo(x+1,y-1);
            //If it is not empty, that means we can't move into that square.
            if((*leftDiag)->getPiece()!="   "){
                //We can't move into this lower left square.
                canMoveLeft=false;
            }
        }
        //If it's not a valid square, we can't move into it.
        else canMoveLeft=false;
        //If the lower right diagonal is a valid square.
        if(isVldSquare(x+1,y+1)){
            //We jump to that square to check if it's empty.
            list<Piece *>::iterator rightDiag=jumpTo(x+1,y+1);
            //If it is not empty, that means we can't move into that square.
            if((*rightDiag)->getPiece()!="   "){
                //We can't move into this lower right square.
                canMoveRight=false;
            }
        }
        //If it's not a valid square, we can't move into it.
        else canMoveRight=false;
        //If we can move into at least 1 square...
        canMove=(canMoveLeft||canMoveRight);
    }
    //Returning whether we can move into at least 1 square.
    return canMove;
}

//To determine whether we can capture a piece or not. The first parameter is our piece.
//The second parameter is the position of our piece. The third parameter is used to 
//hold the position of a piece we can capture. 
bool Board::canCapture(string ourPiece,pair<int,int> pos,pair<int,int> &cap){
    bool canCaptLeft=false;  //To hold whether we can capture from the left.
    bool canCaptRight=false; //To hold whether we can capture from the right.
    int x=pos.first;         //The row of our piece.
    int y=pos.second;        //The col of our piece.
    //If our piece is black...
    if(ourPiece==" B "){
        //If the upper left diagonal is a valid square:
        if(isVldSquare(x-1,y-1)){
            //We want to check to see if the piece is a red piece.
            list<Piece *>::iterator uprLeft=jumpTo(x-1,y-1);
            //If it is a piece that we can possibly capture...
            if((*uprLeft)->getPiece()==" R "){
                //We check to see if we can jump the piece.
                //If the square past it is a valid square...
                if(isVldSquare(x-2,y-2)){
                    //We check to see if the square is empty.
                    list<Piece *>::iterator itr=jumpTo(x-2,y-2);
                    //If it's empty, we can capture the red piece.
                    if((*itr)->getPiece()=="   "){
                        canCaptLeft=true;
                        //We store the position of the red piece.
                        cap=(*uprLeft)->getPos();
                    }
                }
            }
        }
        //If the upper right diagonal is a valid square:
        if(isVldSquare(x-1,y+1)){
            //We want to check to see if the piece is a red piece.
            list<Piece *>::iterator uprRight=jumpTo(x-1,y+1);
            //If it is a piece that we can possibly capture...
            if((*uprRight)->getPiece()==" R "){
                //We check to see if we can jump the piece.
                //If the square past it is a valid square...
                if(isVldSquare(x-2,y+2)){
                    //We check to see if the square is empty.
                    list<Piece *>::iterator itr=jumpTo(x-2,y+2);
                    //If it's empty, we can capture the red piece.
                    if((*itr)->getPiece()=="   "){
                        canCaptRight=true;
                        //We store the position of the red piece.
                        cap=(*uprRight)->getPos();
                    }
                }
            }
        }
        //If we can capture a piece from both the left and right,
        //we let the player decide what piece they'd like to capture.
        if(canCaptLeft&&canCaptRight){
            int capX=0,capY=0; //To hold the position of the captured piece.
            while(capX!=x-1||(capY!=y-1&&capY!=y+1)){
            cout<<"Would you like to capture ("<<x-1<<" "<<y-1<<") or ("
                                               <<x-1<<" "<<y+1<<")? \n";
            cin>>capX>>capY;
            }
            //We store the position of the piece we'd like to capture.
            cap=make_pair(capX,capY);
        }
    }
    //If our piece is red...
    else if(ourPiece==" R "){
        //If the lower left diagonal is a valid square:
        if(isVldSquare(x+1,y-1)){
            //We want to check to see if the piece is a black piece.
            list<Piece *>::iterator lwrLeft=jumpTo(x+1,y-1);
            //If it is a piece that we can possibly capture...
            if((*lwrLeft)->getPiece()==" B "){
                //We check to see if we can jump the piece.
                //If the square past it is a valid square...
                if(isVldSquare(x+2,y-2)){
                    //We check to see if the square is empty.
                    list<Piece *>::iterator itr=jumpTo(x+2,y-2);
                    //If it's empty, we can capture the black piece.
                    if((*itr)->getPiece()=="   "){
                        canCaptLeft=true;
                        //We store the position of the black piece.
                        cap=(*lwrLeft)->getPos();
                    }
                }
            }
        }
        //If the lower right diagonal is a valid square:
        if(isVldSquare(x+1,y+1)){
            //We want to check to see if the piece is a black piece.
            list<Piece *>::iterator lwrRight=jumpTo(x+1,y+1);
            //If it is a piece that we can possibly capture...
            if((*lwrRight)->getPiece()==" B "){
                //We check to see if we can jump the piece.
                //If the square past it is a valid square...
                if(isVldSquare(x+2,y+2)){
                    //We check to see if the square is empty.
                    list<Piece *>::iterator itr=jumpTo(x+2,y+2);
                    //If it's empty, we can capture the black piece.
                    if((*itr)->getPiece()=="   "){
                        canCaptRight=true;
                        //We store the position of the black piece.
                        cap=(*lwrRight)->getPos();
                    }
                }
            }
        }
        //If we can capture a piece from both the left and right,
        //we let the player decide what piece they'd like to capture.
        if(canCaptLeft&&canCaptRight){
            int capX=0,capY=0; //To hold the position of the captured piece.
            while(capX!=x+1||(capY!=y-1&&capY!=y+1)){
            cout<<"Would you like to capture ("<<x+1<<" "<<y-1<<") or ("
                                               <<x+1<<" "<<y+1<<")? \n";
            cin>>capX>>capY;
            }
            //We store the position of the piece we'd like to capture.
            cap=make_pair(capX,capY);
        }
    }
    //Returning whether we can capture from the left or the right.
    return canCaptLeft||canCaptRight;
}

//To capture a piece. The first parameter is our piece. (Red or Black.)
//The second parameter is the position our piece will be in after it has 
//captured a piece. The third parameter is the position of the piece
//we'll be capturing. We need to make sure that we capture the correct piece.
void Board::capture(string ourPiece,pair<int,int> pos,pair<int,int> captured){
    //We first need to go to the piece we'll be capturing and set it as an empty piece.
    list<Piece *>::iterator itr=jumpTo(captured.first,captured.second);
    //Setting it as an empty piece and resetting it's position to nothing.
    (*itr)->setPiece("   ");
    (*itr)->setPos(0,0);
    //We then go to where our piece will be after it has captured the other piece.
    itr=jumpTo(pos.first,pos.second);
    //We set it as our piece and set its position.
    (*itr)->setPiece(ourPiece);
    (*itr)->setPos(pos.first,pos.second);
}