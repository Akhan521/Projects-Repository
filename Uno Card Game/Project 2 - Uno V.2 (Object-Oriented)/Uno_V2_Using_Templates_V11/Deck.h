/* 
 * File:   Deck.h
 * Author: Aamir Khan
 * Created on May 23, 2021, 3:05 PM
 * Purpose: Deck Class Specification
 */

#ifndef DECK_H
#define DECK_H

#include "UnoCard.h"

template <class T>
class Deck{
    private:
        int nCards;   //Stores the # of Cards a Player Has.
        T **deck;     //The deck of cards that belong to the player.
    public:
        //Exception Class for Error Catching
        Deck(int); //Constructor that takes the size of the deck.
        ~Deck();   //Destructor (Reallocates our Memory).
        void setDck(); //Set Deck Function
        void dsply();  //Display Function for Deck Object
        //Getter Function.
        int &getnCards(){return nCards;}
        //Match Checking Functions
        bool isMatch(T,int);
        bool isDrw1(T,int);
        bool isDrw2(T,int);
        //Overloaded [] Operator
        T &operator[](int);
        //Overloaded -- Operator
        Deck<T> operator--(int);
        //Overloaded += Operator
        Deck<T> operator+=(int);
};

//Contructor
template <class T>
Deck<T>::Deck(int n){
    //Ternary Operator
    nCards=(n<=20?n:15);
    deck=new T*[nCards*2];
    for(int i=0;i<nCards*2;i++){
        deck[i]=new T;
    }
}
//Destructor
template <class T>
Deck<T>::~Deck(){
    //Reallocate our Memory.
    for(int i=0;i<nCards*2;i++){
        delete deck[i];
    }
    delete [] deck;
}
//Set Deck Function
template <class T>
void Deck<T>::setDck(){
    for(int i=0;i<nCards;i++){
        deck[i]->setCrd();
    }
}
//Display Function for a Deck Object
template <class T>
void Deck<T>::dsply(){
    for(int i=0;i<getnCards();i++){
        if(deck[i]->getClr()=="None"||deck[i]->getVal()==10||deck[i]->getVal()==11){
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
template <class T>
bool Deck<T>::isMatch(T match,int option){
    if(match.getClr()==deck[option-1]->getClr()||
       match.getVal()==deck[option-1]->getVal()){
        return true;
    }
    else return false;
}
//Testing to see if we have two draw cards that can be matched.
template <class T>
bool Deck<T>::isDrw1(T match,int option){
    if(match.getDescr()==deck[option-1]->getDescr()
       &&deck[option-1]->getDescr()=="Draw 1"){
        return true;
    }
    else return false;
}
//Testing to see if we have two draw cards that can be matched.
template <class T>
bool Deck<T>::isDrw2(T match,int option){
    if(match.getDescr()==deck[option-1]->getDescr()
       &&deck[option-1]->getDescr()=="Draw 2"){
        return true;
    }
    else return false;
}
//Returns an UnoCard.
//Overloaded [] Operator
template <class T>
T &Deck<T>::operator[](int sub){
    if(sub>=0&&sub<nCards){
        return *deck[sub];
    }
    return *deck[0];
}
//Overloaded -- Post-fix Operator
template <class T>
Deck<T> Deck<T>::operator--(int){
    Deck<T> deck(nCards--);
    return deck;
}
//Overloaded += Operator
template <class T>
Deck<T> Deck<T>::operator+=(int num){
     //Draw Our Cards.
    for(int i=getnCards();i<getnCards()+num;i++){
        deck[i]->setCrd();
    }
    //Return a Deck Object w/ the new nCards.
    Deck<T> deck(getnCards()+=num);
    return deck;
}
#endif /* DECK_H */

