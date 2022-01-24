/* 
 * File:   Player.cpp
 * Author: Aamir Khan
 * Created on May 24, 2021, 9:15 AM
 * Purpose: Player Class Specification
 */

#include "Player.h"

int Player::nPlyr=0;
//Constructor
Player::Player(string nme){
    name=nme;
    nPlyr++;
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
  