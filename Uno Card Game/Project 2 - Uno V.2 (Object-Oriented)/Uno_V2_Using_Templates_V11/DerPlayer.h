/* 
 * File:   DerPlayer.h
 * Author: Aamir Khan
 * Created on May 23, 2021, 3:05 PM
 * Purpose: DerPlayer Class Specification
 */

#ifndef DERPLAYER_H
#define DERPLAYER_H

#include "Player.h"

template <class T>
class DerPlayer:public Player<T>{
    protected:
        int age;
    public:
        DerPlayer(string nme,int a):Player<T>(nme){
            age=a;
        }
        string getName(){
            string temp="Mr/s.";
            temp+=Player<T>::getName();
            return temp;
        }
        int getAge(){return age;}
}; 

#endif /* DERPLAYER_H */

