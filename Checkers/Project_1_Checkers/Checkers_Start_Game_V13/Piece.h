/** \class
 * File:    Piece.h
 * Author:  Aamir Khan
 * Created: Oct. 16, 2022, 6:55 PM
 * Purpose: Version 13 - Starting my game.         
 */

#ifndef PIECE_H
#define PIECE_H

#include <utility> //Pairs.
#include <string>  //Strings.
using namespace std;

/** \brief A checkers piece class. */
class Piece{
    private:
        string piece;      /**< Red of black piece. */
        pair<int,int> pos; /**< The position of our piece. */
        bool isKing=false; /**< Whether we have a King piece or not. */
    public:
        /** \brief Overloaded constructor. 
         * 
         * @param ourPiece A string representing our piece.
         * @param x An integer representing our x-coordinate.
         * @param y An integer representing our y-coordinate.
         */
        Piece(string,int,int);
        /** \brief Return our piece's position. 
         * 
         * @return Our piece's position.
         */
        pair<int,int> getPos(){return pos;}
        /** \brief Set our piece's position. 
         * 
         * @param x An integer representing our x-coordinate.
         * @param y An integer representing our y-coordinate.
         */
        void setPos(int,int);
        /** \brief Get our piece. 
         * 
         * @return Our piece.
         */
        string getPiece(){return piece;}
        /** \brief Set our piece. 
         * 
         * @param ourPiece A string representing our piece.
         */
        void setPiece(string);
        /** \brief Set our piece as a King piece. 
         * 
         * @param status Whether our piece is a King piece or not.
         */
        void setKing(bool status){isKing=status;}
        /** \brief Get our King status. 
         * 
         * @return True/False for our King status.
         */
        bool getKingStatus(){return isKing;}
        /** \brief To swap the position of our piece. 
         * 
         * @param newPos The position we're swapping ours with.
         */
        void swapPos(pair<int,int> newPos){swap(pos,newPos);}
};

#endif /* PIECE_H */

