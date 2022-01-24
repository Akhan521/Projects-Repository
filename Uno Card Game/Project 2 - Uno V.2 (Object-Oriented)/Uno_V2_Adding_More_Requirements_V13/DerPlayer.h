/* 
 * File:   DerPlayer.h
 * Author: Aamir Khan
 * Created on May 24, 2021, 9:15 AM
 * Purpose: DerPlayer Class Specification
 */

#ifndef DERPLAYER_H
#define DERPLAYER_H

#include "Player.h"

ostream &operator<<(ostream &,Player &);

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
        friend ostream &operator<<(ostream &,DerPlayer &);
}; 

ostream &operator<<(ostream &out,DerPlayer &obj){
    cout<<obj.name<<", Age:"<<obj.age<<endl;
    return out;
}

#endif /* DERPLAYER_H */

