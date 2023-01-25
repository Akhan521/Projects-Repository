/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on May 21, 2021, 11:30 AM
 * Purpose:  Card Matching Concepts + Basic Interactions
 *  Adding isMatch() to Deck.cpp + cpyCrd() to UnoCard.cpp
 *         + Throwing in some Overloaded Operators. 
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
    int opt; //Card Chosen by the User.
    cout<<"Fifth Program of Project 2: "<<endl;
    cout<<"How Many Cards Do You Wish To Generate [1-20]? ";
    int numCrds;
    cin>>numCrds;
    //Create our Double Pointer That Represents our Deck.
    Deck deck(numCrds);
    //Initialize Variables
    //Set our Deck up w/ Random Cards.
    deck.setDck();
    //Map Inputs to Outputs -> Process
    cout<<endl<<"First card to match..."<<endl;
    UnoCard match;  //Create the Match card.
    match.setCrd(); //Set it up.
    match.dsply();  //Display the Card
    //Display Outputs
    cout<<endl<<"Cards to choose from..."<<endl;
    deck.dsply();
    //Ask for a Card from the User.
    do{
        cout<<"Choose a Card (Ex. 1 - Card 1): ";
        cin>>opt;
    }while(opt>deck.getnCards()||opt<1);
    cout<<endl;
    //Check for a Match...
    if(deck.isMatch(match,opt)){
        cout<<"Card was successfully matched!"<<endl<<endl;
        match.cpyCrd(deck[opt-1]);
        cout<<"New Card to Match..."<<endl;
        match.dsply();
        //Copy the Last Card Into the Card That was Used.
        deck[opt-1].cpyCrd(deck[deck.getnCards()-1]);
        deck--; //Decrement the # of Cards we Have.
        cout<<endl<<"Cards Remaining After the Match..."<<endl;
        deck.dsply();
    }
    else if(deck[opt-1].getDescr()=="Wild Card"){
        string clr;
        cout<<"A Wild Card Was Used!"<<endl<<endl;
        cout<<"Choose a new color to match (Red/Green/Blue/Yellow): ";
        cin>>clr;
        match.setClr(clr);
        cout<<endl<<"New Card to Match..."<<endl;
        match.dsply();
        //Copy the Last Card Into the Card That was Used.
        deck[opt-1].cpyCrd(deck[deck.getnCards()-1]);
        deck--; //Decrement the # of Cards we Have.
        cout<<endl<<"Cards Remaining After the Match..."<<endl;
        deck.dsply();
    }
    else cout<<"Card wasn't matched..."<<endl;
    
    //Exit the Program - Cleanup
    return 0;
}