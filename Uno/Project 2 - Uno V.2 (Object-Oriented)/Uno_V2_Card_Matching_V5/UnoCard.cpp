/* 
 * File:   UnoCard.cpp
 * Author: Aamir Khan
 * Created on May 21, 2021, 11:30 AM
 * Purpose:  UnoCard Class Implementation
 */

#include "UnoCard.h"
using namespace std;

//Default Constructor
UnoCard::UnoCard(){
    color="";
    descr="";
    val=0;
}
void UnoCard::setClr(string clr){
    color=clr;
}
//Card Setting Function
void UnoCard::setCrd(){
    //To determine what colors the cards are assigned.
    int x=rand()%5+1; //Between [1,5] to determine colors
    switch(x){
        case 1: color="Blue";break;
        case 2: color="Green";break;
        case 3: color="Red";break;
        case 4: color="Yellow";break;
        //If a 5 is generated, the card will have no color.
        //Moreover, it will be either a draw 1/2 or wild card.
        default:color="None";break;
    }
    if(color=="None"){
        int special=rand()%3; //Between [0,2] to determine if draw 1/2 or wild card.
        switch(special){
            case 0: descr="Wild Card";break;
            case 1: descr="Draw 1";break;
            case 2: descr="Draw 2";break;
        }
    }
    else{
        val=rand()%9+1; //Values Between [1,9]
    }
}
//Display Function for an UnoCard Object.
void UnoCard::dsply(){
    if(getClr()=="None"){
            cout<<"Card "<<1<<" = ["<<getClr()<<" "<<setw(5)
                                      <<getDescr()<<"]"<<endl;
        }
        else{
            cout<<"Card "<<1<<" = ["<<getClr()<<" "<<setw(2)
                         <<static_cast<int>(getVal())<<"]"<<endl;
        }
}
//Copy Card Function for an UnoCard Object
void UnoCard::cpyCrd(UnoCard card){
    //Copy Over the Contents
    color=card.getClr();
    descr=card.getDescr();
    val=card.getVal();
}
