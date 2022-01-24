/* 
 * File:   Player.h
 * Author: Aamir Khan
 * Created on May 23, 2021, 12:20 PM
 * Purpose: Player Class Specification
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"
#include "AbsPlayer.h"

class Player:public AbsPlayer{
    protected:
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
};

#endif /* PLAYER_H */

