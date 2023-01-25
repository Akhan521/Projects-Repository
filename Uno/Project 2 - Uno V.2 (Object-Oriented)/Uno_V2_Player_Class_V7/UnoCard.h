/* 
 * File:   UnoCard.h
 * Author: Aamir Khan
 * Created on May 22, 2021, 12:50 PM
 * Purpose:  UnoCard Class Specification
 */

#ifndef UNOCARD_H
#define UNOCARD_H

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

class UnoCard{
    private:
        string color;      //Color of Card
        string descr;      //Description of Card (For Special Cards)
        unsigned char val; //Numerical Value if Needed.
    public:
        UnoCard();     //Defaults Everything to 0 or "".
        void setCrd(); //Sets our Card up.
        void setClr(string); //Sets the color for when we use a wild card.
        //Getter Functions
        string getClr(){return color;}
        string getDescr(){return descr;}
        unsigned char getVal(){return val;}
        //Display Function for UnoCard Object
        void dsply();
        //Simple Copy Card Function for an UnoCard.
        void cpyCrd(UnoCard);
};


#endif /* UNOCARD_H */

