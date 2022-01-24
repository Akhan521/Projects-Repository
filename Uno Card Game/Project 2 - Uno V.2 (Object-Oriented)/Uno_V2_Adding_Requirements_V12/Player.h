/* 
 * File:   Player.h
 * Author: Aamir Khan
 * Created on May 23, 2021, 6:30 PM
 * Purpose: Player Class Specification
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include "AbsPlayer.h"

class Player:public AbsPlayer{
    protected:
        static int nPlyr;
        string name;
        Deck *deck;
    public:
        //Constructor
        Player(string);
        //Getter Function
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

