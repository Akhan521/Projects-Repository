/* 
 * File:    Piece.h
 * Author:  Aamir Khan
 * Created: Oct. 13, 2022, 7:10 PM
 * Purpose: Version 10 - Piece Movement Part 5.           
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
        bool isKing=false; //Whether we have a King piece or not.
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
        //Set our piece as a King piece.
        void setKing(bool status){isKing=status;}
        //Get our King status.
        bool getKingStatus(){return isKing;}
};

#endif /* PIECE_H */

