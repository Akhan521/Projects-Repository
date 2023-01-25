/** \class
 * File:    Player.h
 * Author:  Aamir Khan
 * Created: Oct. 16, 2022, 6:55 PM
 * Purpose: Version 13 - Starting my game.  
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"

/** \brief A player class. */
class Player{
    private:
        string name;     /**< Our name. */
        string ourPiece; /**< Our piece. (Red/Black). */
        Board *board;    /**< The board we're playing on. */
    public:
        /** \brief Our constructor to set our name. 
         * 
         * @param name Our name.
         */
        Player(string name){this->name=name;}
        /** \brief To set our board. 
         * 
         * @param board A board pointer object.
         */
        void setBoard(Board *board){this->board=board;}
        /** \brief To set our piece. 
         * 
         * @param ourPiece A string representing our piece.
         */
        void setPiece(string ourPiece){this->ourPiece=ourPiece;}
        /** \brief To get our piece. 
         * 
         * @return Our piece.
         */
        string getPiece(){return ourPiece;}
        /** \brief To get our name. 
         * 
         * @return Our name.
         */
        string getName(){return name;}
        /** \brief To make a move. 
         * 
         * We pass in a map, by reference, that will be used
         * to keep count of how many pieces we've captured.
         * @param captPces A map to keep count of captured pieces.
         */
        void makeMove(map<string,int> &captPces){
            board->move(ourPiece,captPces);
        }
};


#endif /* PLAYER_H */

