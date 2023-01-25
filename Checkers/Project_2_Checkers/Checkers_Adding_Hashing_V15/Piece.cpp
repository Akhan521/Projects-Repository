/* 
 * File:    Piece.cpp
 * Author:  Aamir Khan
 * Created: Nov. 22, 2022, 2:05 PM
 * Purpose: Version 15 - Adding hashing.           
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