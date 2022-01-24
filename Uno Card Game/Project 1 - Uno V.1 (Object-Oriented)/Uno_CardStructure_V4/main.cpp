/* 
 * File:   main.cpp
 * Author: Aamir 
 * Created on April 11, 2021, 8:55 PM
 * Purpose: Working with a Structure Array + Set Card Function 
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
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    short numCrds=0;        //# of Cards to generate
    //Initialize Variables
    cout<<"Fourth Program of My Uno Project 1."<<endl;
    cout<<"How many cards do you want to generate [1-20]? ";
    cin>>numCrds;
    //A Ternary Op to limit cards generated.
    numCrds=(numCrds>20?20:numCrds);
    //Create an array of structures with a specified size
    UnoCard plyrDck[numCrds];
    //Map Inputs to Outputs -> Process
    for(int i=0;i<numCrds;i++){ //Generating Random Cards
        plyrDck[i]=setCrd();
        if(plyrDck[i].color=="None"){
            cout<<"Card "<<i+1<<" = ["<<plyrDck[i].color<<" "<<setw(5)
                                      <<plyrDck[i].descr<<"]"<<endl;
        }
        else{
            cout<<"Card "<<i+1<<" = ["<<plyrDck[i].color<<" "<<setw(2)
                    <<static_cast<int>(plyrDck[i].value)<<"]"<<endl;
        }
    }
    //Display Inputs/Outputs
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