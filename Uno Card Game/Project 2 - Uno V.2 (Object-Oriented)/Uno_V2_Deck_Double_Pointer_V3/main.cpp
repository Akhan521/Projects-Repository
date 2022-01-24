/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on May 21, 2021, 9:30 AM
 * Purpose:  Double Pointer Deck of Cards
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
    cout<<"Third Program of Project 2: "<<endl;
    cout<<"How Many Cards Do You Wish To Generate [1-20]? ";
    int nCards;
    cin>>nCards;
    //Keep it Between 1-20
    nCards=nCards<=20?nCards:20;
    //Create our Double Pointer That Represents our Deck.
    UnoCard **deck;
    deck=new UnoCard*[nCards];
    //Set our Cards and Display Them
    for(int i=0;i<nCards;i++){
        deck[i]=new UnoCard;
        //Set our Card.
        deck[i]->setCrd();
        //Display Our Card.
        if(deck[i]->getClr()=="None"){
            cout<<"Card "<<i+1<<" = ["<<deck[i]->getClr()<<" "<<setw(5)
                                      <<deck[i]->getDescr()<<"]"<<endl;
        }
        else{
            cout<<"Card "<<i+1<<" = ["<<deck[i]->getClr()<<" "<<setw(3)
                         <<static_cast<int>(deck[i]->getVal())<<"]"<<endl;
        }
    }
    //Initialize Variables
    
    //Map Inputs to Outputs -> Process
    
    //Reallocate our Memory.
    for(int i=0;i<nCards;i++){
        delete deck[i];
    }
    delete [] deck;
    //Exit the Program - Cleanup
    return 0;
}