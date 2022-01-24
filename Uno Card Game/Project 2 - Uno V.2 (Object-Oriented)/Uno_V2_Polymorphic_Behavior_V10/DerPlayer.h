/* 
 * File:   DerPlayer.h
 * Author: Aamir Khan
 * Created on May 23, 2021, 12:20 PM
 * Purpose: DerPlayer Class Specification
 */

#ifndef DERPLAYER_H
#define DERPLAYER_H

#include "Player.h"

class DerPlayer:public Player{
    protected:
        int age;
    public:
        DerPlayer(string nme,int a):Player(nme){
            age=a;
        }
        string getName(){
            string temp="Mr/s.";
            temp+=Player::getName();
            return temp;
        }
        int getAge(){return age;}
}; 

#endif /* DERPLAYER_H */

