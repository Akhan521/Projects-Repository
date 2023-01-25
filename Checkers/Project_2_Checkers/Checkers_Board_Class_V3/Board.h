/* 
 * File:    Board.h
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 12:00 PM
 * Purpose: Version 3 - Putting our board into a class.                    
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>  //I/O Library.
#include <string>    //Strings.
#include <list>      //Lists.
#include <iterator>  //Iterators.
using namespace std;

class Board{
    private:
        //The dimensions of our board.
        int DIM=8;
        //A 2-D list of strings as our board.
        list<list<string>> board;
        //Creates an empty checkers board.
        void fillBrd();
    public:
        //Our constructor.
        Board();
        //Displays our board.
        void dsplyBrd();
        //Jumps to a square in our board, if it's valid.
        list<string>::iterator jumpTo(int,int);
};


#endif /* BOARD_H */

