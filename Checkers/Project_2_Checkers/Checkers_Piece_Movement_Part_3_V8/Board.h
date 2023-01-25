/* 
 * File:    Board.h
 * Author:  Aamir Khan
 * Created: Oct. 12, 2022, 1:50 PM
 * Purpose: Version 8 - Piece Movement Part 3.          
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
        //To determine whether a piece can move into at least 1 square.
        bool canMove(string,pair<int,int>);
        //To determine whether we can capture a piece or not.
        bool canCapture(string,pair<int,int>,pair<int,int> &);
        //To capture a piece. (Used together with the function above.)
        void capture(string,pair<int,int>,pair<int,int>);
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

