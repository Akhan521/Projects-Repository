/* 
 * File:   main.cpp
 * Author: Aamir 
 * Created on April 12, 2021, 9:00 AM
 * Purpose: Working Out How to Match Cards (Color/Number)
 *          + Display Function + Clear Card Function
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>  
#include <string>
#include <cstring>
#include <ctime>
using namespace std;

//User Libraries
#include "UnoCard.h"
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
UnoCard setCrd();
void dsply(UnoCard,int);
void clrCrd(UnoCard &);
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    short numCrds=7;        //# of Cards to generate
    short option;           //Card that is chosen
    //Initialize Variables
    cout<<"Fifth Program of My Uno Project 1."<<endl;
    //Create an array of structures with a specified size
    UnoCard plyrDck[numCrds];
    //Map Inputs to Outputs -> Process
    //Set The Cards
    for(int i=0;i<numCrds;i++){ //Generating Random Cards
        plyrDck[i]=setCrd();
    }
    //Find One Match
    UnoCard match=setCrd();
    cout<<"Card to Match: ";
    dsply(match,0);
    cout<<"Available Cards to Choose From..."<<endl;
    for(int i=0;i<numCrds;i++){
        if(plyrDck[i].color!=""){
            dsply(plyrDck[i],i);
        }
    }
    cout<<"Which card do you choose? ";
    cin>>option;
    if(plyrDck[option-1].color==match.color||plyrDck[option-1].value==match.value){
        cout<<"Successfully Matched."<<endl;
        clrCrd(plyrDck[option-1]); //Clear the card's contents
    }
    else cout<<"Can't Match The Two."<<endl;
    //Display Inputs/Outputs
    cout<<endl;
    cout<<"The card that was cleared."<<endl;
    dsply(plyrDck[option-1],option-1);
    cout<<"Printed "<<numCrds<<" Random Uno Card/s.";
    //Exit the Program - Cleanup
    return 0;
}
//Set Card Function - Generate a Random Card and Return It.
UnoCard setCrd(){
    UnoCard card;
    //To determine what colors the cards are assigned
    int x=rand()%5+1; //Between [1,5] to determine colors
    switch(x){
        case 1: card.color="Blue";break;
        case 2: card.color="Green";break;
        case 3: card.color="Red";break;
        case 4: card.color="Yellow";break;
        //If a 5 is generated, the card will have no color.
        //Moreover, it will be either a draw 1/2 or wild card.
        default:card.color="None";break;
    }
    if(card.color=="None"){
        int special=rand()%3; //Between [0,2] to determine if draw 1/2 or wild card.
        switch(special){
            case 0: strcpy(card.descr,"Wild Card");break;
            case 1: strcpy(card.descr,"Draw 1");break;
            case 2: strcpy(card.descr,"Draw 2");break;
        }
    }
    else{
        card.value=rand()%9+1; //Values Between [1,9]
    }
    return card;
}
void dsply(UnoCard card,int i){
    if(card.color=="None"){
        cout<<"Card "<<i+1<<" = ["<<card.color<<" "<<setw(5)
                                  <<card.descr<<"]"<<endl;
    }
    else{
        cout<<"Card "<<i+1<<" = ["<<card.color<<" "<<setw(2)
                <<static_cast<int>(card.value)<<"]"<<endl;
    }
}
void clrCrd(UnoCard &card){
    card.color="";
    card.value=0;
    strcpy(card.descr,"");
}