/* 
 * File:    Piece.h
 * Author:  Aamir Khan
 * Created: Oct. 12, 2022, 10:50 PM
 * Purpose: Version 9 - Piece Movement Part 4.          
 */

#ifndef PIECE_H
#define PIECE_H

#include <utility> //Pairs.
#include <string>  //Strings.
using namespace std;

class Piece{
    private:
        string piece;      //Red of black piece.
        pair<int,int> pos; //The position of our piece.
    public:
        //Overloaded constructor.
        Piece(string,int,int);
        //Return our piece's position.
        pair<int,int> &getPos(){return pos;}
        //Set our piece's position.
        void setPos(int,int);
        //Get our piece.
        string getPiece(){return piece;}
        //Set our piece.
        void setPiece(string);
};

#endif /* PIECE_H */

