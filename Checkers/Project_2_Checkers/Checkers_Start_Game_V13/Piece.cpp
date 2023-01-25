/* 
 * File:    Piece.cpp
 * Author:  Aamir Khan
 * Created: Oct. 16, 2022, 6:55 PM
 * Purpose: Version 13 - Starting my game.           
 */

#include "Piece.h"

/** \brief Our constructor. */
Piece::Piece(string pce,int x,int y){
    piece=pce;         //Setting the piece as red or black.
    this->setPos(x,y); //Setting its position.
}

/** \brief Setter for position. */
void Piece::setPos(int x,int y){
    pos=make_pair(x,y);
}

/** \brief Setter for piece description. */
void Piece::setPiece(string pce){
    piece=pce;
}