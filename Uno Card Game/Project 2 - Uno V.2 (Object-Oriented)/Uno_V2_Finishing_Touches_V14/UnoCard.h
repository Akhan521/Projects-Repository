/* 
 * File:   UnoCard.h
 * Author: Aamir Khan
 * Created on May 24, 2021, 12:15 PM
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
        string color;      //Color of a Card
        string descr;      //Description of a Card (For Special Cards)
        unsigned char val; //Numerical Card Value if Needed.
    public:
        //Constructor
        UnoCard();     //Defaults Everything to 0 or "".
        //Setter Functions.
        void setCrd(); //Sets our Card up.
        void setClr(string); //Sets the color for when we use a wild card.
        void setVal(unsigned char);
        void setDescr(string);
        //Getter Functions
        string getClr(){return color;}
        string getDescr(){return descr;}
        unsigned char getVal(){return val;}
        //Display Function for UnoCard Object
        void dsply();
        //Simple Copy Card Function for an UnoCard.
        void cpyCrd(UnoCard &);
};


#endif /* UNOCARD_H */

