/* 
 * File:   Deck.cpp
 * Author: Aamir Khan
 * Created on May 21, 2021, 11:30 AM
 * Purpose: Deck Class Implementation
 */

#include "Deck.h"

//Contructor
Deck::Deck(int n){
    //Ternary Operator
    nCards=(n<=20?n:15);
    deck=new UnoCard*[nCards*2];
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
//Display Function for a Deck Object
void Deck::dsply(){
    for(int i=0;i<getnCards();i++){
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
//Function for Checking Matches
bool Deck::isMatch(UnoCard match,int option){
    if(match.getClr()==deck[option-1]->getClr()||
       match.getVal()==deck[option-1]->getVal()){
        return true;
    }
    else return false;
}
//Returns an UnoCard.
//Overloaded [] Operator 
UnoCard &Deck::operator[](int sub){
    if(sub>=0&&sub<nCards){
        return *deck[sub];
    }
}
//Overloaded -- Post-fix Operator
Deck Deck::operator--(int){
    Deck deck(nCards--);
    return deck;
}


