/* 
 * File:   Player.cpp
 * Author: Aamir Khan
 * Created on May 22, 2021, 1:20 PM
 * Purpose: Player Class Specification
 */

#include "Player.h"

//Constructor
Player::Player(string nme){
    name=nme;
}
//Print Deck Function
void Player::prntDck(){
    deck->dsply();
}
//Set Deck Function
void Player::setDck(Deck *d){
    deck=d;
}
int Player::getnCards(){
    return deck->getnCards();
}
  