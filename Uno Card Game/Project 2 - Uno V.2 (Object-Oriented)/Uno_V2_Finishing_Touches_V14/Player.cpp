/* 
 * File:   Player.cpp
 * Author: Aamir Khan
 * Created on May 24, 2021, 12:15 PM
 * Purpose: Player Class Specification
 */

#include "Player.h"

int Player::nPlyr=0;
//Constructor
Player::Player(string nme){
    name=nme;
    //Increment the # of Players we Have.
    nPlyr++; //Static Variable.
}
//Print Deck Function
void Player::prntDck(){
    deck->dsply();
}
//Set Deck Function
void Player::setDck(Deck *d){
    deck=d;
}
//Get nCards Function
int Player::getnCards(){
    return deck->getnCards();
}
  