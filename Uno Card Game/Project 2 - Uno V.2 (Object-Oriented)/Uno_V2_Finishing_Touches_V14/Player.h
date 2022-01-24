/* 
 * File:   Player.h
 * Author: Aamir Khan
 * Created on May 24, 2021, 12:15 PM
 * Purpose: Player Class Specification
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include "AbsPlayer.h"

class Player:public AbsPlayer{
    protected:
        static int nPlyr; //The # of Players throughout our program.
        string name;      //Name of the Player
        Deck *deck;       //Their deck of cards.
    public:
        //Constructor
        Player(string);
        //Getter Functions
        string getName(){return name;}
        int getnCards();
        //Print Deck Function
        void prntDck();
        //Set Deck Function (Takes a Deck Object)
        void setDck(Deck *);
        //Static Member Functions
        static int getnPlyrs(){return nPlyr;}
};

#endif /* PLAYER_H */

