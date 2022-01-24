/* 
 * File:   UnoCard.cpp
 * Author: Aamir Khan
 * Created on May 24, 2021, 9:15 AM
 * Purpose:  UnoCard Class Implementation
 */

#include "UnoCard.h"
#include <vector>    //For Vectors.
#include <algorithm> //For random_shuffle Algo.
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
    vector<int> vect1;        //Create a Vector of Ints
    for(int i=0;i<9;i++){     //Push the Values 1-9
        vect1.push_back(i+1); //Into our Vector.
    }
    //Randomize The Elements For Truly Random #'s
    random_shuffle(vect1.begin(),vect1.end());
    switch(vect1[rand()%9]){  //Values Between [1-9] Will Be Used.
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
        vector<int> vect2;        //Create a Vector of Ints
        for(int i=0;i<11;i++){    //Push the Values 1-11
            vect2.push_back(i+1); //Into our Vector.
        }
        //Randomize The Elements For Truly Random #'s
        random_shuffle(vect2.begin(),vect2.end());
        val=vect2[rand()%11];  //Values Between [1,11] Will Be Used.
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
