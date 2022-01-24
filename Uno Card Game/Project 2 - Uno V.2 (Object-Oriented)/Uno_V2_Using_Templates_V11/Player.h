/* 
 * File:   Player.h
 * Author: Aamir Khan
 * Created on May 23, 2021, 3:05 PM
 * Purpose: Player Class Specification
 */

#ifndef PLAYER_H
#define PLAYER_H

#include "AbsPlayer.h"

template <class T>
class Player:public AbsPlayer<T>{
    protected:
        string name;
        Deck<T> *deck;
    public:
        //Constructor
        Player(string);
        //Getter Function
        string getName(){return name;}
        int getnCards();
        //Print Deck Function
        void prntDck();
        //Set Deck Function (Takes a Deck Object)
        void setDck(Deck<T> *);
};

//Constructor
template <class T>
Player<T>::Player(string nme){
    name=nme;
}
//Print Deck Function
template <class T>
void Player<T>::prntDck(){
    deck->dsply();
}
//Set Deck Function
template <class T>
void Player<T>::setDck(Deck<T> *d){
    deck=d;
}
//Get Cards Function
template <class T>
int Player<T>::getnCards(){
    return deck->getnCards();
}
#endif /* PLAYER_H */

