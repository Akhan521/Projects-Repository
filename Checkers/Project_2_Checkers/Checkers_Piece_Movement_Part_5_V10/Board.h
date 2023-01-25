/* 
 * File:    Board.h
 * Author:  Aamir Khan
 * Created: Oct. 13, 2022, 7:10 PM
 * Purpose: Version 10 - Piece Movement Part 5.           
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>  //I/O Library.
#include <list>      //Lists.
#include <iterator>  //Iterators.
#include <set>       //Sets.
#include <stack>     //Stacks.
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
        //To determine whether we can move a King piece into at least 1 square.
        bool canMoveKing(pair<int,int>);
        //To determine whether we can capture a piece or not only.
        bool canCapture(string,pair<int,int>);
        //To determine whether we can capture a piece or not, store the 
        //position of the captured piece, and store whether we had the 
        //option to choose which piece to capture.
        bool canCapture(string,pair<int,int>,pair<int,int> &,bool &);
        //To determine whether we can capture a piece with a King piece.
        bool canCaptWithKng(string,pair<int,int>);
        //To determine whether we can capture a piece with our King piece,
        //store the position of the captured piece, and store whether we had the 
        //option to choose which piece to capture.
        bool canCaptWithKng(string,pair<int,int>,pair<int,int> &,bool &);
        //To capture a piece. (Used together with the function above.)
        void capture(string,pair<int,int>,pair<int,int>,pair<int,int>,bool);
        //To display all of our King pieces.
        void dsplyKings(string);
        //To determine whether we have to forfeit the game.
        bool willForfeit(string);
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
        void move(string);
};


#endif /* BOARD_H */

