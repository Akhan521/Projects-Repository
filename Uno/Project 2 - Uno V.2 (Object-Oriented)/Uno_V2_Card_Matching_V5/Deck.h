/* 
 * File:   Deck.h
 * Author: Aamir Khan
 * Created on May 21, 2021, 11:30 AM
 * Purpose: Deck Class Specification
 */

#ifndef DECK_H
#define DECK_H

#include "UnoCard.h"

class Deck{
    private:
        int nCards;     //Stores the # of Cards a Player Has.
        UnoCard **deck; //The deck of cards that belong to the player.
    public:
        //Exception Class for Error Catching
        Deck(int); //Constructor that takes the size of the deck.
        ~Deck();   //Destructor (Reallocates our Memory).
        void setDck(); //Set Deck Function
        void dsply();  //Display Function for Deck Object
        //Getter Function.
        int &getnCards(){return nCards;}
        //Match Checking Function
        bool isMatch(UnoCard,int);
        //Overloaded [] Operator
        UnoCard &operator[](int);
        //Overloaded -- Operator
        Deck operator--(int);
};

#endif /* DECK_H */

