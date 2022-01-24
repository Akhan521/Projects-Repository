/* 
 * File:   DerPlayer.h
 * Author: Aamir Khan
 * Created on May 24, 2021, 12:15 PM
 * Purpose: DerPlayer Class Specification
 */

#ifndef DERPLAYER_H
#define DERPLAYER_H

#include "Player.h"

class DerPlayer; //Forward Declaration.

//Friend Function.
ostream &operator<<(ostream &,DerPlayer &);

class DerPlayer:public Player{
    protected:
        int age;
    public:
        //Constructor -> Calls Player Constructor.
        DerPlayer(string nme,int a):Player(nme){
            age=a;
        }
        //Overridden getName() Function.
        string getName(){
            string temp="Mr/s.";
            temp+=Player::getName();
            return temp;
        }
        //Getter Function
        int getAge(){return age;}
        //Friend Function.
        friend ostream &operator<<(ostream &,DerPlayer &);
}; 

//Friend Function Definition.
ostream &operator<<(ostream &out,DerPlayer &obj){
    out<<obj.name<<", Age:"<<obj.age<<endl;
    return out;
}

#endif /* DERPLAYER_H */

