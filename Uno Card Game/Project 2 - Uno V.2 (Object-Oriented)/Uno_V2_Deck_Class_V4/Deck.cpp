/* 
 * File:   Deck.cpp
 * Author: Aamir Khan
 * Created on May 21, 2021, 10:30 AM
 * Purpose: Deck Class Implementation
 */

#include "Deck.h"
#include <iostream>

//Contructor
Deck::Deck(int n){
    //Ternary Operator
    nCards=(n<=20?n:15);
    deck=new UnoCard*[nCards];
    for(int i=0;i<nCards;i++){
        deck[i]=new UnoCard;
    }
}
//Destructor
Deck::~Deck(){
    //Reallocate our Memory.
    for(int i=0;i<nCards;i++){
        delete deck[i];
    }
    delete [] deck;
}
//Set Deck Function
void Deck::setDck(){
    for(int i=0;i<nCards;i++){
        deck[i]->setCrd();
    }
}
//Display Function
void Deck::dsply(){
    for(int i=0;i<nCards;i++){
        if(deck[i]->getClr()=="None"){
                cout<<"Card "<<i+1<<" = ["<<deck[i]->getClr()<<" "<<setw(5)
                                          <<deck[i]->getDescr()<<"]"<<endl;
            }
            else{
                cout<<"Card "<<i+1<<" = ["<<deck[i]->getClr()<<" "<<setw(2)
                             <<static_cast<int>(deck[i]->getVal())<<"]"<<endl;
            }
    }
}