/* 
 * File:    Piece.cpp
 * Author:  Aamir Khan
 * Created: Oct. 15, 2022, 7:05 PM
 * Purpose: Version 12 - Adding a few algorithms into my game.         
 */

#include "Piece.h"

//Our constructor.
Piece::Piece(string pce,int x,int y){
    piece=pce;         //Setting the piece as red or black.
    this->setPos(x,y); //Setting its position.
}

//Setter for postition.
void Piece::setPos(int x,int y){
    pos=make_pair(x,y);
}

//Setter for piece description.
void Piece::setPiece(string pce){
    piece=pce;
}