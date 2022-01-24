/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on May 21, 2021, 10:30 AM
 * Purpose:  Implementing a Deck Class
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Deck.h"
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Random # Generator
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    cout<<"Fourth Program of Project 2: "<<endl;
    cout<<"How Many Cards Do You Wish To Generate [1-20]? ";
    int nCards;
    cin>>nCards;
    //Create our Double Pointer That Represents our Deck.
    Deck deck(nCards);
    //Initialize Variables
    //Set our Deck up w/ Random Cards.
    deck.setDck();
    //Map Inputs to Outputs -> Process
    
    //Display Outputs
    deck.dsply();
    //Exit the Program - Cleanup
    return 0;
}