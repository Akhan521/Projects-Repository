/* 
 * File:    Board.cpp
 * Author:  Aamir Khan
 * Created: Nov. 22, 2022, 2:05 PM
 * Purpose: Version 15 - Adding hashing.          
 */

#include "Board.h"

/** \brief Our constructor. */
Board::Board(){
    //Creates an empty checkers board.
    this->fillBrd();
    //Places pieces onto our board.
    this->putPieces();
}

/** \brief Our destructor. */
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

/** \brief Fills our board. */
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

/** \brief Checks whether we have a valid square. */
bool Board::isVldSquare(int r,int c){
    //The row and column must be within bounds of our board.
    //It must also not be marked with an X.
    //The portion "(r+c)%2" accounts for squares that are marked with
    //an X. If that portion returns a 1, the square is valid. Otherwise,
    //the square is invalid or it's marked with an X.
    return (r>0&&r<=DIM&&c>0&&c<=DIM&&(r+c)%2);
}

/** \brief Places pieces onto our board. */
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
            //Place red pieces in the first 3 rows.
            if(row==1||row==2||row==3){
                //We only place pieces on valid squares.
                if(isVldSquare(row,col)){
                    (*itr)->setPiece(" R "); //Red piece.
                    (*itr)->setPos(row,col); //Its position.
                }
            }
            //Place black pieces in the last 3 rows.
            else if(row==6||row==7||row==8){
                //We only place pieces on valid squares.
                if(isVldSquare(row,col)){
                    (*itr)->setPiece(" B "); //Black piece.
                    (*itr)->setPos(row,col); //Its position.
                }
            }
        }
    }
}

/** \brief Displays our board. */
void Board::dsplyBrd(){
    cout<<endl;
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

/** \brief Jumps to a piece in our board. */
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

/**Moves a piece on our board. We pass in our piece (Red/Black).
 * We need to pass our piece in, so that we can ensure we only
 * choose to move a piece that's ours. We also pass in a map that will
 * be used to keep count of how many pieces we've captured. The key for the
 * map will be our piece, and the value will be how many pieces we've captured.
 * Lastly, we pass in a tree that will hold the pieces we've captured.
 */
void Board::move(string ourPiece,map<string,int> &captPces,Tree *tree){
    //Storing our opponent's piece.
    string opptPiece=ourPiece==" B "?" R ":" B ";
    //The total number of pieces that a player can capture.
    int allPces=12; 
    //If our opponent has captured all 12 of our pieces...
    if(captPces[opptPiece]==allPces){
        cout<<"\nYou have no pieces to make a move with...\n";
    }
    //If we have no legal moves to make, we have to forfeit the game.
    else if(willForfeit(ourPiece)){
        cout<<"\nYou have no legal moves to make. You forfeit the match...\n";
        //Since we forfeit, the opponent wins the game. 
        captPces[opptPiece]=allPces; //Our opponent gets all of our pieces.
    }
    //If we have at least 1 legal move to make...
    else{
        //Displaying our board.
        dsplyBrd();
        //If we have any King pieces, we display them.
        dsplyKings(ourPiece);
        //To store the coordinates of the chosen piece.
        int x1=0,y1=0;
        //The position of the piece we'll be capturing, if capturing is an option.
        pair<int,int> capPos;
        //To jump to our chosen piece.
        list<Piece *>::iterator itr;
        //To hold whether we had the option to choose what piece to capture.
        bool chosen;
        //To hold whether we can move a piece or not.
        bool canMove; 
        //To hold whether we can capture a piece or not.
        bool canCapt; 
        //We keep prompting the user if they've chosen an invalid square...
        while(!isVldSquare(x1,y1)){
            //We need to make sure that the piece we choose to move is our piece.
            string chsnPce; //The piece we've chosen to move.
            do{
                //Prompt the user for which piece they'd like to move.
                cout<<"\nWhat piece would you like to move? (Row Column)\n";
                cout<<"EX: 4 5 would move the piece in row 4 column 5."<<endl;
                cin>>x1>>y1;
                //We need to check whether the piece we've chosen is ours.
                if(isVldSquare(x1,y1)){ //If we have a valid square...
                    itr=jumpTo(x1,y1);  //We jump to the chosen piece.
                    //We store the piece we chose (Red/Black).
                    chsnPce=(*itr)->getPiece();
                }
                //If we don't have a valid square...
                else{
                    //We display an error message.
                    cout<<"That is an invalid square!\n";
                }
                //If we chose a piece that isn't ours, we display a message.
                //We display this message only if we've chosen a valid square.
                if(chsnPce!=ourPiece&&isVldSquare(x1,y1))
                    cout<<"You have to choose your own piece. TRY CHOOSING AGAIN...\n";
                //We keep looping until the piece we choose is ours.
            }while(ourPiece!=chsnPce);
            //We jump to our chosen piece.
            itr=jumpTo(x1,y1);
            //We need to make sure that we're even able to move our piece.
            //There must be at least 1 square that our piece can move into
            //for it to be considered a valid piece for us to choose.
            //We call the canMove() function, passing our piece and its position.
            //If we have a King piece...
            if((*itr)->getKingStatus()){
                //Checking to see if the King piece can move.
                canMove=this->canMoveKing((*itr)->getPos());
                //Checking to see if the King piece can capture a piece.
                canCapt=this->canCaptWithKng(ourPiece,(*itr)->getPos(),capPos,chosen);
            }
            else{
                //Checking to see if a regular piece can move.
                canMove=this->canMove(ourPiece,(*itr)->getPos());
                //Checking to see if a regular piece can capture another piece.
                canCapt=this->canCapture(ourPiece,(*itr)->getPos(),capPos,chosen);
            }
            //If we can't move into any squares and we can't capture any pieces...
            if(!canMove&&!canCapt){
                cout<<"Choose a different piece..."<<endl;
                //Resetting it to two invalid positions.
                x1=0;
                y1=0;
            }
        }
        //We need to know if our piece is a King piece.
        bool isKing=(*itr)->getKingStatus();
        //To store the coordinates of where we'd like to move our piece.
        int x2=0,y2=0;
        //We keep prompting the user if they've chosen an invalid square...
        while(!isVldSquare(x2,y2)){
            //Prompt the user for where they'd like to move their piece.
            cout<<"\nWhere would you like to move your piece? (Row Column)\n";
            cout<<"EX: 5 6 would mean that we move into the square in row 5 column 6."<<endl;
            //If we have a King piece...
            if(isKing){
                //We store where to move our piece.
                cin>>x2>>y2;
                //If we have an invalid square, we let the user know.
                if(!isVldSquare(x2,y2))
                    cout<<"That is an invalid square!\n";
                else{
                    //If a piece can't be captured, we need to make sure that an 
                    //appropriate square is chosen that is directly to the left/right.
                    if(!canCapt){
                        //A King piece is allowed to move either up or down diagonally.
                        //The column we choose must also be directly to the left/right.
                        while((x2!=x1+1&&x2!=x1-1)||(y2!=y1-1&&y2!=y1+1)){
                            //We output a message and reprompt the user.
                            cout<<"\nAs a King piece, you can move up or down diagonally..."<<endl;
                            cout<<"You have to move your piece either to the left/right diagonally.\n";
                            cout<<"Where would you like to move your piece? (Row Column)\n";
                            cin>>x2>>y2;
                        }
                    }
                    //If we can capture a piece...
                    else{
                        //If we're capturing a piece, we need to make sure that the
                        //square we choose is directly after the piece that we'll be capturing.
                        while((x2!=capPos.first-1&&x2!=capPos.first+1)||(y2!=capPos.second-1&&y2!=capPos.second+1)){
                            //We output a message and reprompt the user.
                            cout<<"\nYou have to jump into the square after the piece \n";
                            cout<<"you'll be capturing. The square must be valid. \n";
                            cout<<"Where would you like to move your piece? (Row Column)\n";
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
            //If we don't have a King piece...
            else{
                //If we have a red piece...
                if(ourPiece==" R "){
                    //We store where to move our piece.
                    cin>>x2>>y2;
                    //If we have an invalid square, we let the user know.
                    if(!isVldSquare(x2,y2))
                        cout<<"That is an invalid square!\n";
                    else{
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
                                cout<<"Where would you like to move your piece? (Row Column)\n";
                                cin>>x2>>y2;
                            }
                        }
                        //If we can capture a piece...
                        else{
                            //We need to make sure that the square we choose is directly
                            //after the piece that we'll be capturing.
                            while(x2!=capPos.first+1||(y2!=capPos.second-1&&y2!=capPos.second+1)){
                                //We output a message and reprompt the user.
                                cout<<"\nYou have to jump into the square after the piece \n";
                                cout<<"you'll be capturing. The square must be valid. \n";
                                cout<<"Where would you like to move your piece? (Row Column)\n";
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
                                cout<<"Where would you like to move your piece? (Row Column)\n";
                                cin>>x2>>y2;
                            }
                        }
                        //If we can capture a piece...
                        else{
                            //We need to make sure that the square we choose is directly
                            //after the piece that we'll be capturing.
                            while(x2!=capPos.first-1||(y2!=capPos.second-1&&y2!=capPos.second+1)){
                                //We output a message and reprompt the user.
                                cout<<"\nYou have to jump into the square after the piece \n";
                                cout<<"you'll be capturing. The square must be valid. \n";
                                cout<<"Where would you like to move your piece? (Row Column)\n";
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
        }
        //We need to check whether we can capture a piece or not.
        //If we have a King piece...
        if(isKing){
            //If we can capture a piece with our King piece...
            if(canCapt){
                //We go ahead and capture it.
                capture(ourPiece,make_pair(x1,y1),make_pair(x2,y2),capPos);
                //Since we've captured a piece, we increment our captured pieces count.
                captPces[ourPiece]++;
                //We insert the piece we've captured into our tree.
                tree->insert(captPces[ourPiece]);
                //We need to check whether we can capture more pieces...
                //We begin by trying to see if we can capture another piece from our current position.
                int tryX=x2,tryY=y2;
                while(canCaptWithKng(ourPiece,make_pair(tryX,tryY),capPos,chosen)){
                    dsplyBrd(); //Displaying our board.
                    cout<<"\nYou can still capture a piece.\n"
                        <<"Make sure to capture all possible pieces..."<<endl;
                    //We keep prompting the user if they've chosen an invalid square...
                    //We want them to choose the square they'll be jumping to, after
                    //they've captured a piece.
                    x2=0,y2=0; //To store where we'll be jumping to.
                    while(!isVldSquare(x2,y2)){
                        //Prompt the user for where they'd like to move their piece.
                        cout<<"\nWhere would you like to move your piece now? (Row Column)\n";
                        cout<<"EX: 5 6 would mean that we move into the square in row 5 column 6."<<endl;
                        //We store where to move our piece.
                        cin>>x2>>y2;
                        //If we have an invalid square, we let the user know.
                        if(!isVldSquare(x2,y2))
                            cout<<"That is an invalid square!\n";
                        else{
                            while(x2!=capPos.first-1&&x2!=capPos.first+1||(y2!=capPos.second-1&&y2!=capPos.second+1)){
                                //If we have already chosen what piece to capture...
                                if(chosen){
                                    cout<<"\nYou have already chosen what piece to capture."<<endl;
                                    cout<<"Make sure you jump into the square that's after"<<endl;
                                    cout<<"the piece you chose to capture..."<<endl;
                                }
                                //If we didn't choose what piece to capture...
                                else{
                                    //We output a message and reprompt the user.
                                    cout<<"\nYou have to jump into the square after the piece \n";
                                    cout<<"you'll be capturing. The square must be valid. \n";         
                                }
                                cout<<"Where would you like to move your piece? (Row Column)\n";
                                cin>>x2>>y2;
                            }
                            //We jump to the square on our board that we chose.
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
                    //Now that we have a valid square to jump to after capturing a piece...
                    //We can go ahead and capture the piece we'll be jumping.
                    capture(ourPiece,make_pair(tryX,tryY),make_pair(x2,y2),capPos);
                    //Since we've captured a piece, we increment our captured pieces count.
                    captPces[ourPiece]++;
                    //We insert the piece we've captured into our tree.
                    tree->insert(captPces[ourPiece]);
                    //We now want to update our current position.
                    //If we can still capture a piece from our updated position, the next iteration
                    //of the while loop will repeat the steps above to capture another piece.
                    tryX=x2,tryY=y2;
                }
            }
            //Otherwise, we just move our piece into our chosen square.
            else{
                //We jump to the square we're moving from and set it as an empty piece.
                itr=jumpTo(x1,y1);
                //Storing whether we have a King piece.
                isKing=(*itr)->getKingStatus();
                (*itr)->setPiece("   "); //Setting it as an empty piece.
                (*itr)->setPos(0,0);     //Resetting its position.
                (*itr)->setKing(false);  //Resetting its King status.
                //We now jump to where our piece will be after we move it.
                itr=jumpTo(x2,y2);
                //We set it as our piece. (Since we're moving into this square.)
                (*itr)->setPiece(ourPiece);
                //We now need to set the position of our piece.
                (*itr)->setPos(x2,y2); 
                //We also need to set its King status.
                (*itr)->setKing(isKing);
            }
        }
        //If we don't have a King piece...
        else{
            //If we can capture a piece...
            if(canCapt){
                //We go ahead and capture it.
                capture(ourPiece,make_pair(x1,y1),make_pair(x2,y2),capPos);
                //Since we've captured a piece, we increment our captured pieces count.
                captPces[ourPiece]++;
                //We insert the piece we've captured into our tree.
                tree->insert(captPces[ourPiece]);
                //If we've reached the opposite end of the board, our piece becomes a King.
                if(ourPiece==" R "&&x2==8){      //If a red piece has reached the bottom...
                    //We jump to our piece.
                    list<Piece *>::iterator piece=jumpTo(x2,y2);
                    //Then, we set it as a King piece.
                    isKing=true;
                    (*piece)->setKing(isKing);
                    cout<<"\nThis piece is now a King piece!\n";
                }
                else if(ourPiece==" B "&&x2==1){ //If a black piece has reached the top...
                    //We jump to our piece.
                    list<Piece *>::iterator piece=jumpTo(x2,y2);
                    //Then, we set it as a King piece.
                    isKing=true;
                    (*piece)->setKing(isKing);
                    cout<<"\nThis piece is now a King piece!\n";
                }
                //We need to check whether we can capture more pieces...
                //We begin by trying to see if we can capture another piece from our current position.
                int tryX=x2,tryY=y2;
                while(canCapture(ourPiece,make_pair(tryX,tryY),capPos,chosen)){
                    dsplyBrd(); //Displaying our board.
                    cout<<"\nYou can still capture a piece.\n"
                        <<"Make sure to capture all possible pieces..."<<endl;
                    //We keep prompting the user if they've chosen an invalid square...
                    //We want them to choose the square they'll be jumping to, after
                    //they've captured a piece.
                    x2=0,y2=0; //To store where we'll be jumping to.
                    while(!isVldSquare(x2,y2)){
                        //Prompt the user for where they'd like to move their piece.
                        cout<<"\nWhere would you like to move your piece now? (Row Column)\n";
                        cout<<"EX: 5 6 would mean that we move into the square in row 5 column 6."<<endl;
                        //If we have a red piece...
                        if(ourPiece==" R "){
                            //We store where to move our piece.
                            cin>>x2>>y2;
                            //If we have an invalid square, we let the user know.
                            if(!isVldSquare(x2,y2))
                                cout<<"That is an invalid square!\n";
                            else{
                                while(x2!=capPos.first+1||(y2!=capPos.second-1&&y2!=capPos.second+1)){
                                    //If we have already chosen what piece to capture...
                                    if(chosen){
                                        cout<<"\nYou have already chosen what piece to capture."<<endl;
                                        cout<<"Make sure you jump into the square that's after"<<endl;
                                        cout<<"the piece you chose to capture..."<<endl;
                                    }
                                    //If we didn't choose what piece to capture...
                                    else{
                                        //We output a message and reprompt the user.
                                        cout<<"\nYou have to jump into the square after the piece \n";
                                        cout<<"you'll be capturing. The square must be valid. \n";         
                                    }
                                    cout<<"Where would you like to move your piece? (Row Column)\n";
                                    cin>>x2>>y2;
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
                                while(x2!=capPos.first-1||(y2!=capPos.second-1&&y2!=capPos.second+1)){
                                    //If we have already chosen what piece to capture...
                                    if(chosen){
                                        cout<<"\nYou have already chosen what piece to capture."<<endl;
                                        cout<<"Make sure you jump into the square that's after"<<endl;
                                        cout<<"the piece you chose to capture..."<<endl;
                                    }
                                    //If we didn't choose what piece to capture...
                                    else{
                                        //We output a message and reprompt the user.
                                        cout<<"\nYou have to jump into the square after the piece \n";
                                        cout<<"you'll be capturing. The square must be valid. \n";         
                                    }
                                    cout<<"Where would you like to move your piece? (Row Column)\n";
                                    cin>>x2>>y2;
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
                    //Now that we have a valid square to jump to after capturing a piece...
                    //We can go ahead and capture the piece we'll be jumping.
                    capture(ourPiece,make_pair(tryX,tryY),make_pair(x2,y2),capPos);
                    //Since we've captured a piece, we increment our captured pieces count.
                    captPces[ourPiece]++;
                    //We insert the piece we've captured into our tree.
                    tree->insert(captPces[ourPiece]);
                    //If we've reached the opposite end of the board, our piece becomes a King.
                    if(ourPiece==" R "&&x2==8){      //If a red piece has reached the bottom...
                        //We jump to our piece.
                        list<Piece *>::iterator piece=jumpTo(x2,y2);
                        //Then, we set it as a King piece.
                        isKing=true;
                        (*piece)->setKing(isKing);
                        cout<<"\nThis piece is now a King piece!\n";
                    }
                    else if(ourPiece==" B "&&x2==1){ //If a black piece has reached the top...
                        //We jump to our piece.
                        list<Piece *>::iterator piece=jumpTo(x2,y2);
                        //Then, we set it as a King piece.
                        isKing=true;
                        (*piece)->setKing(isKing);
                        cout<<"\nThis piece is now a King piece!\n";
                    }
                    //We now want to update our current position.
                    //If we can still capture a piece from our updated position, the next iteration
                    //of the while loop will repeat the steps above to capture another piece.
                    tryX=x2,tryY=y2;
                }
            }
            //Otherwise, we just move our piece into our chosen square.
            else{
                //We jump to the square we're moving from and set it as an empty piece.
                itr=jumpTo(x1,y1);
                (*itr)->setPiece("   "); //Setting it as an empty piece.
                (*itr)->setPos(0,0);     //Resetting its position.
                //We now jump to where our piece will be after we move it.
                itr=jumpTo(x2,y2);
                //We set it as our piece. (Since we're moving into this square.)
                (*itr)->setPiece(ourPiece);
                //We now need to set the position of our piece.
                (*itr)->setPos(x2,y2); 
                //If we've reached the opposite end of the board, our piece becomes a King.
                if(ourPiece==" R "&&x2==8){      //If a red piece has reached the bottom...
                    //We jump to our piece.
                    list<Piece *>::iterator piece=jumpTo(x2,y2);
                    //Then, we set it as a King piece.
                    isKing=true;
                    (*piece)->setKing(isKing);
                    cout<<"\nThis piece is now a King piece!\n";
                }
                else if(ourPiece==" B "&&x2==1){ //If a black piece has reached the top...
                    //We jump to our piece.
                    list<Piece *>::iterator piece=jumpTo(x2,y2);
                    //Then, we set it as a King piece.
                    isKing=true;
                    (*piece)->setKing(isKing);
                    cout<<"\nThis piece is now a King piece!\n";
                }
            }
        }
        //Displaying the board after our move.
        dsplyBrd();
    }
}

/**To determine whether we can move a piece. The first parameter is our piece.
 * The second parameter is the position of our piece. We check diagonals.
 */
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

/**To determine whether we can move a King piece or not. In this function,
 * we check all diagonals to see if there is at least one square that we 
 * can move our King piece into.
 */
bool Board::canMoveKing(pair<int,int> pos){
    int x=pos.first;  //The row of our piece.
    int y=pos.second; //The col of our piece.
    bool cnMveUprLeft=true;  //To hold whether we can move to the upper left.
    bool cnMveUprRight=true; //To hold whether we can move to the upper right.
    bool cnMveLwrLeft=true;  //To hold whether we can move to the lower left.
    bool cnMveLwrRight=true; //To hold whether we can move to the lower right.
    //We need to check the upper left and upper right diagonals.
    //If the upper left diagonal is a valid square.
    if(isVldSquare(x-1,y-1)){
        //We jump to that square to check if it's empty.
        list<Piece *>::iterator uprLeftDiag=jumpTo(x-1,y-1);
        //If it is not empty, that means we can't move into that square.
        if((*uprLeftDiag)->getPiece()!="   "){
            //We can't move into this upper left square.
            cnMveUprLeft=false;
        }
    }
    //If it's not a valid square, we can't move into it.
    else cnMveUprLeft=false;
    //If the upper right diagonal is a valid square.
    if(isVldSquare(x-1,y+1)){
        //We jump to that square to check if it's empty.
        list<Piece *>::iterator uprRightDiag=jumpTo(x-1,y+1);
        //If it is not empty, that means we can't move into that square.
        if((*uprRightDiag)->getPiece()!="   "){
            //We can't move into this upper right square.
            cnMveUprRight=false;
        }
    }
    //If it's not a valid square, we can't move into it.
    else cnMveUprRight=false;
    //We need to check the lower left and lower right diagonals.
    //If the lower left diagonal is a valid square.
    if(isVldSquare(x+1,y-1)){
        //We jump to that square to check if it's empty.
        list<Piece *>::iterator lwrLeftDiag=jumpTo(x+1,y-1);
        //If it is not empty, that means we can't move into that square.
        if((*lwrLeftDiag)->getPiece()!="   "){
            //We can't move into this lower left square.
            cnMveLwrLeft=false;
        }
    }
    //If it's not a valid square, we can't move into it.
    else cnMveLwrLeft=false;
    //If the lower right diagonal is a valid square.
    if(isVldSquare(x+1,y+1)){
        //We jump to that square to check if it's empty.
        list<Piece *>::iterator lwrRightDiag=jumpTo(x+1,y+1);
        //If it is not empty, that means we can't move into that square.
        if((*lwrRightDiag)->getPiece()!="   "){
            //We can't move into this lower right square.
            cnMveLwrRight=false;
        }
    }
    //If it's not a valid square, we can't move into it.
    else cnMveLwrRight=false;
    //Returning whether we can move into at least 1 square.
    return cnMveUprLeft||cnMveUprRight||cnMveLwrLeft||cnMveLwrRight;
}

/**To determine whether we can capture a piece or not. The first parameter is our piece.
 * The second parameter is the position of our piece. The third parameter is used to 
 * hold the position of a piece we can capture. The 4th parameter is used to hold 
 * whether we had the option to choose what piece to capture. If we were able to 
 * choose what piece to capture, the 4th parameter is set to true. 
 */
bool Board::canCapture(string ourPiece,pair<int,int> pos,pair<int,int> &cap,bool &chosen){
    bool canCaptLeft=false;     //To hold whether we can capture from the left.
    bool canCaptRight=false;    //To hold whether we can capture from the right.
    int x=pos.first;            //The row of our piece.
    int y=pos.second;           //The col of our piece.
    set<pair<int,int>> capPces; //To hold the positions of pieces we can capture.
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
                        capPces.insert((*uprLeft)->getPos());
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
                        capPces.insert((*uprRight)->getPos());
                    }
                }
            }
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
                        capPces.insert((*lwrLeft)->getPos());
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
                        capPces.insert((*lwrRight)->getPos());
                    }
                }
            }
        }
    }
    //If we can capture 2 pieces, we let the player choose.
    if(capPces.size()==2){
        //We ask the player what piece they'd like to capture.
        cout<<"\nWhich piece would you like to capture? "<<endl;
        //We output the position of every piece we can capture.
        for(pair<int,int> pos:capPces){
            cout<<"("<<pos.first<<" "<<pos.second<<") ";
        }
        cout<<endl;
        //To store which piece we'd like to capture.
        pair<int,int> capture(0,0);
        //We keep looping if we choose any position that isn't in our set.
        //If the position isn't found, an iterator to the end of the set is returned.
        while(capPces.find(capture)==capPces.end()){
            cout<<"\nEnter the position of the piece you'd like to capture... (Row Column)\n";
            cin>>capture.first>>capture.second;
        }
        //Once we've chosen a piece, we store its position.
        cap=capture;
        //Since we were able to choose...
        chosen=true;
    }
    //If we can only capture one piece...
    else cap=*(capPces.begin()); //We store the only element in our set.
    //Returning whether we can capture from the left or the right.
    return canCaptLeft||canCaptRight;
}

/**To determine whether we can capture a piece or not. The first parameter is our piece.
 * The second parameter is the position of our piece. The third parameter is used to 
 * hold the position of a piece we can capture. The 4th parameter is used to hold 
 * whether we had the option to choose what piece to capture. If we were able to 
 * choose what piece to capture, the 4th parameter is set to true.
 */
bool Board::canCaptWithKng(string ourPiece,pair<int,int> pos,pair<int,int> &cap,bool &chosen){
    int x=pos.first;  //The row of our piece.
    int y=pos.second; //The column of our piece.
    //To hold whether we can capture from the upper left.
    bool canCaptUprLeft=false; 
    //To hold whether we can capture from the upper right.
    bool canCaptUprRight=false;
    //To hold whether we can capture from the lower left.
    bool canCaptLwrLeft=false;  
    //To hold whether we can capture from the lower right.
    bool canCaptLwrRight=false; 
    //To hold the positions of pieces we can capture.
    set<pair<int,int>> capPces;
    //To hold our opponent's piece.
    string opptPce=(ourPiece==" B "?" R ":" B ");
    //We need to check all diagonals:
    //If the upper left diagonal is a valid square:
    if(isVldSquare(x-1,y-1)){
        //We want to check to see if the piece is a red piece.
        list<Piece *>::iterator uprLeft=jumpTo(x-1,y-1);
        //If it is a piece that we can possibly capture...
        if((*uprLeft)->getPiece()==opptPce){
            //We check to see if we can jump the piece.
            //If the square past it is a valid square...
            if(isVldSquare(x-2,y-2)){
                //We check to see if the square is empty.
                list<Piece *>::iterator itr=jumpTo(x-2,y-2);
                //If it's empty, we can capture the red piece.
                if((*itr)->getPiece()=="   "){
                    canCaptUprLeft=true;
                    //We store the position of the piece we can capture.
                    capPces.insert((*uprLeft)->getPos());
                }
            }
        }
    }
    //If the upper right diagonal is a valid square:
    if(isVldSquare(x-1,y+1)){
        //We want to check to see if the piece is a red piece.
        list<Piece *>::iterator uprRight=jumpTo(x-1,y+1);
        //If it is a piece that we can possibly capture...
        if((*uprRight)->getPiece()==opptPce){
            //We check to see if we can jump the piece.
            //If the square past it is a valid square...
            if(isVldSquare(x-2,y+2)){
                //We check to see if the square is empty.
                list<Piece *>::iterator itr=jumpTo(x-2,y+2);
                //If it's empty, we can capture the red piece.
                if((*itr)->getPiece()=="   "){
                    canCaptUprRight=true;
                    //We store the position of the piece we can capture.
                    capPces.insert((*uprRight)->getPos());
                }
            }
        }
    }
    //If the lower left diagonal is a valid square:
    if(isVldSquare(x+1,y-1)){
        //We want to check to see if the piece is a red piece.
        list<Piece *>::iterator lwrLeft=jumpTo(x+1,y-1);
        //If it is a piece that we can possibly capture...
        if((*lwrLeft)->getPiece()==opptPce){
            //We check to see if we can jump the piece.
            //If the square past it is a valid square...
            if(isVldSquare(x+2,y-2)){
                //We check to see if the square is empty.
                list<Piece *>::iterator itr=jumpTo(x+2,y-2);
                //If it's empty, we can capture the black piece.
                if((*itr)->getPiece()=="   "){
                    canCaptLwrLeft=true;
                    //We store the position of the piece we can capture.
                    capPces.insert((*lwrLeft)->getPos());
                }
            }
        }
    }
    //If the lower right diagonal is a valid square:
    if(isVldSquare(x+1,y+1)){
        //We want to check to see if the piece is a red piece.
        list<Piece *>::iterator lwrRight=jumpTo(x+1,y+1);
        //If it is a piece that we can possibly capture...
        if((*lwrRight)->getPiece()==opptPce){
            //We check to see if we can jump the piece.
            //If the square past it is a valid square...
            if(isVldSquare(x+2,y+2)){
                //We check to see if the square is empty.
                list<Piece *>::iterator itr=jumpTo(x+2,y+2);
                //If it's empty, we can capture the black piece.
                if((*itr)->getPiece()=="   "){
                    canCaptLwrRight=true;
                    //We store the position of the piece we can capture.
                    capPces.insert((*lwrRight)->getPos());
                }
            }
        }
    }
    //If we can capture more than one piece...
    if(capPces.size()>=2){
        //We ask the player what piece they'd like to capture.
        cout<<"\nWhich piece would you like to capture? "<<endl;
        //We output the position of every piece we can capture.
        for(pair<int,int> pos:capPces){
            cout<<"("<<pos.first<<" "<<pos.second<<") ";
        }
        cout<<endl;
        //To store which piece we'd like to capture.
        pair<int,int> capture(0,0);
        //We keep looping if we choose any position that isn't in our set.
        //If the position isn't found, an iterator to the end of the set is returned.
        while(capPces.find(capture)==capPces.end()){
            cout<<"\nEnter the position of the piece you'd like to capture... (Row Column)\n";
            cin>>capture.first>>capture.second;
        }
        //Once we've chosen a piece, we store it in our 3rd parameter.
        cap=capture;
        //Since we were able to choose...
        chosen=true;
    }
    //If we can only capture one piece...
    else cap=*(capPces.begin()); //We store the only element in our set.
    //Returning whether we can capture at least 1 piece.
    return canCaptUprLeft||canCaptUprRight||canCaptLwrLeft||canCaptLwrRight;
}

/**To capture a piece. The first parameter is our piece. (Red or Black.)
 * The second parameter is the current position our piece. The third parameter 
 * is the position our piece will be in after it has jumped the opponent piece.
 * The fourth parameter is the position of the piece we'll be capturing. 
 */
void Board::capture(string ourPiece,pair<int,int> pos,pair<int,int> newPos,pair<int,int> captured){
    //We begin by jumping to our current square to set it as an empty piece, since we're leaving it.
    list<Piece *>::iterator itr=jumpTo(pos.first,pos.second);
    //To hold whether we have a King piece.
    bool isKing=(*itr)->getKingStatus();
    //Setting it as an empty piece and resetting it's position and King status:
    (*itr)->setPiece("   ");
    //Swapping the position of the piece with (0,0) to reset it.
    (*itr)->swapPos(make_pair(0,0));
    (*itr)->setKing(false);
    //We then need to go to the piece we'll be capturing and set it as an empty piece.
    itr=jumpTo(captured.first,captured.second);
    //Setting it as an empty piece and resetting it's position and King status.
    (*itr)->setPiece("   ");
    //Swapping the position of the piece with (0,0) to reset it.
    (*itr)->swapPos(make_pair(0,0));
    (*itr)->setKing(false);
    //Lastly, we go to where our piece will be after it has captured the other piece.
    itr=jumpTo(newPos.first,newPos.second);
    //We set it as our piece and set its position.
    (*itr)->setPiece(ourPiece);
    //Swapping the position of the piece with its new position to update it.
    (*itr)->swapPos(make_pair(newPos.first,newPos.second));
    //If we have a King piece, we need to set our status as a King.
    if(isKing){
        (*itr)->setKing(isKing);
    }
}

/**To display all of our King pieces. We input our piece and use a stack to 
 * output all of our King pieces.
 */
void Board::dsplyKings(string ourPiece){
    //To hold the positions of our King pieces.
    stack<pair<int,int>> kngPos;
    //We declare an iterator to work with our 2-D list.
    list<list<Piece *>>::iterator it;
    //We iterate over our 2-D list.
    for(it=board.begin();it!=board.end();it++){
        //We declare an iterator to work with each list in our board.
        list<Piece *>::iterator itr;
        //itr will point to each piece on our board.
        for(itr=it->begin();itr!=it->end();itr++){
            //If we have a King piece and it's our piece...
            if((*itr)->getKingStatus()&&(*itr)->getPiece()==ourPiece)
                //We store the position in our stack.
                kngPos.push((*itr)->getPos());
        }
    }
    //To store the size of our stack.
    int size=kngPos.size(); 
    //We now want to display all of our King pieces.
    if(size>0){ //If we have at least 1 King piece...
        cout<<"\nHere are your King pieces...\n";
    }
    while(!kngPos.empty()){
        //We store the position at the top of our stack.
        pair<int,int> pos=kngPos.top();
        //We output the position.
        cout<<"("<<pos.first<<" "<<pos.second<<") ";
        //We pop the position we've displayed from our stack.
        kngPos.pop();
    }
    //If we had at least 1 King piece, we output a newline.
    if(size>0) 
        cout<<endl;
}

/**This function will test to see if we have at least 1 legal move to make. If
 * there are no legal moves that we can make, then we have to forfeit the game.
 */
bool Board::willForfeit(string ourPiece){
    //To hold whether we have to forfeit or not.
    bool willForfeit=true;
    //We declare an iterator to work with our 2-D list.
    list<list<Piece *>>::iterator it;
    //We iterate over our 2-D list.
    for(it=board.begin();it!=board.end();it++){
        //We declare an iterator to work with each list in our board.
        list<Piece *>::iterator itr;
        //itr will point to each piece on our board.
        for(itr=it->begin();itr!=it->end();itr++){
            //Whether we have a King piece.
            bool isKing=(*itr)->getKingStatus();
            //If the piece is ours...
            if((*itr)->getPiece()==ourPiece){
                //If we have a King piece and we can move at least 1 of our King pieces...
                if(isKing&&canMoveKing((*itr)->getPos())){
                    //Since we can move 1 of our pieces, we don't have to forfeit.
                    willForfeit=false;
                }
                //If we have a regular piece and we can move at least 1 of our pieces...
                else if(canMove(ourPiece,(*itr)->getPos())){
                    //Since we can move 1 of our pieces, we don't have to forfeit.
                    willForfeit=false;
                }
            }
        }
    }
    //Returning whether we have to forfeit or not.
    return willForfeit;
}