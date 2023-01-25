/* 
 * File:    Player.h
 * Author:  Aamir Khan
 * Created: Oct. 15, 2022, 7:05 PM
 * Purpose: Version 12 - Adding a few algorithms into my game. 
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

class Player{
    private:
        //Our name.
        string name;
        //Our piece. (Red/Black).
        string ourPiece;
        //The board we're playing on.
        Board *board;
    public:
        //Our constructor.
        Player(string name){this->name=name;}
        //To set our board.
        void setBoard(Board *board){this->board=board;}
        //To set our piece.
        void setPiece(string ourPiece){this->ourPiece=ourPiece;}
        //To get our piece.
        string getPiece(){return ourPiece;}
        //To get our name.
        string getName(){return name;}
        //To make a move. We pass in a map, by reference, that will be used
        //to keep count of how many pieces we've captured.
        void makeMove(map<string,int> &captPces){
            board->move(ourPiece,captPces);
        }
};


#endif /* PLAYER_H */

