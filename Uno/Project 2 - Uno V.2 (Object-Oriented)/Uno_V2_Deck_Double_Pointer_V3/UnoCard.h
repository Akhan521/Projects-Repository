/* 
 * File:   UnoCard.h
 * Author: Aamir Khan
 * Created on May 21, 2021, 9:30 AM
 * Purpose:  Card Class w/ Program
 */

#ifndef UNOCARD_H
#define UNOCARD_H

const int SIZE=11;
#include <string>
#include <cstring>
using namespace std;

class UnoCard{
    private:
        string color;      //Color of Card
        char descr[SIZE];  //Description of Card (For Special Cards)
        unsigned char val; //Numerical Value if Needed.
    public:
        UnoCard();     //Defaults Everything to 0 or "".
        void setCrd(); //Sets our Card up.
        //Getter Functions
        string getClr(){return color;}
        char *getDescr(){return descr;}
        unsigned char getVal(){return val;}
};


#endif /* UNOCARD_H */

