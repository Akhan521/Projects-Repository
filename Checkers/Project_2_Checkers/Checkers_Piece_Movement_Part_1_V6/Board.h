/* 
 * File:    Board.h
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 2:50 PM
 * Purpose: Version 6 - Piece Movement Part 1.          
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>  //I/O Library.
#include <list>      //Lists.
#include <iterator>  //Iterators.
#include "Piece.h"   //Our Piece class.

class Board{
    private:
        //The dimensions of our board.
        int DIM=8;
        //A 2-D list of Piece * objects as our board.
        list<list<Piece *>> board;
        //Creates an empty checkers board.
        void fillBrd();
        //Determines whether a square is valid or not.
        bool isVldSquare(int,int);
        //Places red and black pieces onto our board.
        void putPieces();
    public:
        //Our constructor.
        Board();
        //Our destructor.
        ~Board();
        //Displays our board.
        void dsplyBrd();
        //Jumps to a square in our board, if it's valid.
        list<Piece *>::iterator jumpTo(int,int);
        //Moves a piece on our board.
        void move();
};


#endif /* BOARD_H */

