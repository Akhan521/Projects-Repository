/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on May 21, 2021, 9:30 AM
 * Purpose:  Card Class w/ Program
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "UnoCard.h"
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Random # Generator
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    cout<<"Second Program of Project 2: "<<endl;
    cout<<"How Many Cards Do You Wish To Generate? ";
    int nCards;
    cin>>nCards;
    //Keep it Between 1-20
    nCards=nCards<=20?nCards:20;
    for(int i=0;i<nCards;i++){
        UnoCard card;
        //Set our Card.
        card.setCrd();
        //Display Our Card.
        if(card.getClr()=="None"){
            cout<<"Card "<<i+1<<" = ["<<card.getClr()<<" "<<setw(5)
                                      <<card.getDescr()<<"]"<<endl;
        }
        else{
            cout<<"Card "<<i+1<<" = ["<<card.getClr()<<" "<<setw(3)
                         <<static_cast<int>(card.getVal())<<"]"<<endl;
        }
    }
    //Initialize Variables
    
    //Map Inputs to Outputs -> Process
    
    //Display Inputs/Outputs
    
    //Exit the Program - Cleanup
    return 0;
}