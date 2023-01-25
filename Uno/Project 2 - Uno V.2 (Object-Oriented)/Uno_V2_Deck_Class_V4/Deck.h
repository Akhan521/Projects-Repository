/* 
 * File:   Deck.h
 * Author: Aamir Khan
 * Created on May 21, 2021, 10:30 AM
 * Purpose: Deck Class Specification
 */

#ifndef DECK_H
#define DECK_H

#include "UnoCard.h"
#include <iomanip>

class Deck{
    private:
        int nCards;     //Stores the # of Cards a Player Has.
        UnoCard **deck; //The deck of cards that belong to the player.
    public:
        //Exception Class for Error Catching
        Deck(int); //Constructor that takes the size of the deck.
        ~Deck();   //Destructor (Reallocates our Memory).
        //Set Deck Function
        void setDck();
        //Display Function
        void dsply();
        //Getter Function
        int getnCards(){return nCards;}
};

#endif /* DECK_H */

