/* 
 * File:   Player.h
 * Author: Aamir Khan
 * Created on May 22, 2021, 12:50 PM
 * Purpose: Player Class Specification
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "Deck.h"

class Player{
    private:
        string name;
        Deck *deck;
    public:
        //Constructor
        Player(string);
        ~Player(){delete deck;}
        //Getter Function
        string getName(){return name;}
        //Print Deck Function
        void prntDck();
        //Set Deck Function (Takes a Deck Object)
        void setDck(Deck *);
};

#endif /* PLAYER_H */

