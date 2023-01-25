/** \class
 * File:    Board.h
 * Author:  Aamir Khan
 * Created: Nov. 23, 2022, 10:55 AM
 * Purpose: Version 16 - Adding recursion.            
 */

#ifndef BOARD_H
#define BOARD_H

#include <iostream>  //I/O Library.
#include <list>      //Lists.
#include <iterator>  //Iterators.
#include <set>       //Sets.
#include <vector>    //Vectors.
#include <map>       //Maps.
#include <algorithm> //Algorithms.
#include "Piece.h"   //Our Piece class.
#include "Tree.h"    //Our Tree class.

/** \brief A checkers board class. */
class Board{
    private:
        const int DIM=8;           /**< The dimensions of our board. */
        list<list<Piece *>> board; /**< A 2-D list of Piece * objects as our board. */
        /** \brief Creates an empty checkers board. */
        void fillBrd();
        /** \brief Determines whether a square is valid or not. 
         * 
         * @return True/False for whether a square is valid.
         */
        bool isVldSquare(int,int);
        /** \brief Places red and black pieces onto our board. */
        void putPieces();
        /** \brief To determine whether a piece can move into at least 1 square. 
         * 
         * @param ourPiece A string representing our piece.
         * @param pos Our piece's position.
         * @return True/False depending on whether our piece can move.
         */
        bool canMove(string,pair<int,int>);
        /** \brief To determine whether we can move a King piece into at least 1 square. 
         * 
         * @param pos Our King piece's position.
         * @return True/False depending on whether we can move our King piece.
         */
        bool canMoveKing(pair<int,int>);
        /** \brief To determine whether we can capture a piece or not. 
         * 
         * We also store the position of the captured piece and store 
         * whether we had the option to choose which piece to capture.
         * @param ourPiece Our piece.
         * @param pos Our piece's position.
         * @param cap The position of the piece we can capture.
         * @param chosen Whether we had the choice to choose a piece to capture.
         * @return True/False depending on whether we can capture a piece.
         */
        bool canCapture(string,pair<int,int>,pair<int,int> &,bool &);
        /** \brief To determine whether we can capture a piece with our King piece. 
         * 
         * We also store the position of the captured piece and store whether 
         * we had the option to choose which piece to capture.
         * @param ourPiece Our piece.
         * @param pos Our piece's position.
         * @param cap The position of the piece we can capture.
         * @param chosen Whether we had the choice to choose a piece to capture.
         * @return True/False depending on whether we can capture a piece with our King piece.
         */
        bool canCaptWithKng(string,pair<int,int>,pair<int,int> &,bool &);
        /** \brief To capture a piece. 
         * 
         * (Used together with canCapture() or canCaptWithKng() functions.) 
         * @param ourPiece Our piece.
         * @param pos Our piece's position.
         * @param newPos Our new position that we'll be in.
         * @param captured The position of the piece we'll be capturing.
         * @see canCapture(string,pair<int,int>)
         * @see canCaptWithKng(string,pair<int,int>,pair<int,int> &,bool &)
         */
        void capture(string,pair<int,int>,pair<int,int>,pair<int,int>);
        /** \brief To display all of our King pieces. 
         * 
         * @param ourPiece Our piece.
         */
        void dsplyKings(string);
        /** \brief To swap 2 pairs of integers. (Used in our quick-sort.)
         * 
         * The values of 2 pairs will be swapped.
         * 
         * @param p1 Our first pair.
         * @param p2 Our second pair.
         */
        void swap(pair<int,int> &,pair<int,int> &);
        /** \brief To partition a vector of pairs for our quick-sort algorithm.
         * 
         * @param v A vector of pairs.
         * @param start The starting index of our vector.
         * @param end The ending index of our vector. 
         * @return indx The correct index of our pivot.
         */
        int partition(vector<pair<int,int>> &,int,int);
        /** \brief To quick-sort a vector of pairs in descending order.
         * 
         * The vector of pairs is sorted in descending order based on the 
         * first values of the pairs. These pairs will not be sorted based
         * on their second values, only their first values.
         * 
         * @param v A vector of pairs (Each pair is a pair of integers).
         * @param start The starting index of our vector.
         * @param end The ending index of our vector. 
         */
        void quickSort(vector<pair<int,int>> &,int,int);
        /** \brief To determine whether we have to forfeit the game. 
         * 
         * We check if at least 1 of our pieces is able to move. If none of
         * our pieces are able to move, then we forfeit the game.
         * @param ourPiece Our piece.
         * @return True/False depending on whether we have to forfeit.
         */
        bool willForfeit(string);
    public:
        /** \brief Our constructor. */
        Board();
        /** \brief Our destructor. */
        ~Board();
        /** \brief Displays our board. */
        void dsplyBrd();
        /** \brief Jumps to a square on our board, if it's valid. 
         * 
         * @param x An integer representing our x-coordinate.
         * @param y An integer representing our y-coordinate.
         * @return An iterator to an element in a list of Piece * objects.
         */
        list<Piece *>::iterator jumpTo(int,int);
        /** \brief Moves a piece on our board. 
         * 
         * @param ourPiece Our piece.
         * @param captPces A map to keep count of captured pieces.
         * @param tree A tree to hold the pieces a player has captured.
         */
        void move(string,map<string,int> &,Tree *);
};


#endif /* BOARD_H */

