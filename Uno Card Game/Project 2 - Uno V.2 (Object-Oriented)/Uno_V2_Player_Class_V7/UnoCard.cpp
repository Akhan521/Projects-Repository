/* 
 * File:   UnoCard.cpp
 * Author: Aamir Khan
 * Created on May 22, 2021, 12:50 PM
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
    int x=rand()%9+1; //Between [1,9] to determine colors
    switch(x){
        case 1:
        case 2: color="Blue";break;
        case 3:
        case 4: color="Green";break;
        case 5:
        case 6: color="Red";break;
        case 7:
        case 8: color="Yellow";break;
        default:color="None";break;
    }
    if(color=="None"){
        descr="Wild Card";
    }
    else{
        val=rand()%11+1; //Values Between [1,11]
        if(val==10){
            descr="Draw 1";
        }
        else if(val==11){
            descr="Draw 2";
        }
    }
}
//Display Function for an UnoCard Object.
void UnoCard::dsply(){
    //10-Draw 1, 11- Draw 2, or a Wild Card.
    if(getClr()=="None"||getVal()==10||getVal()==11){
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
