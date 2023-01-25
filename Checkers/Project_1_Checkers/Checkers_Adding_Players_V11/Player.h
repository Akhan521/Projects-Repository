/* 
 * File:    Player.h
 * Author:  Aamir Khan
 * Created: Oct. 15, 2022, 2:45 PM
 * Purpose: Version 11 - Adding players + Captured pieces count. 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player{
    private:
        //Our piece. (Red/Black).
        string ourPiece;
        //The board we're playing on.
        Board *board;
    public:
        //To set our board.
        void setBoard(Board *board){this->board=board;}
        //To set our piece.
        void setPiece(string ourPiece){this->ourPiece=ourPiece;}
        //To get our piece.
        string getPiece(){return ourPiece;}
        //To make a move. We pass in a map, by reference, that will be used
        //to keep count of how many pieces we've captured.
        void makeMove(map<string,int> &captPces){board->move(ourPiece,captPces);}
};


#endif /* PLAYER_H */

