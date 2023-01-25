/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on May 22, 2021, 12:50 PM
 * Purpose: Adding a Player Class that Uses Previous Classes
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Deck.h"
#include "Player.h"
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Random # Generator
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    int opt; //Card Chosen by the User.
    cout<<"Seventh Program of Project 2: "<<endl;
    cout<<"How Many Cards Do You Wish To Generate [1-20]? ";
    int numCrds;
    cin>>numCrds;
    //Create our Double Pointer That Represents our Deck.
    Deck deck(numCrds);
    //Set our Deck up w/ Random Cards.
    deck.setDck();
    //Create our Player Object.
    Player aamir("Aamir");
    aamir.setDck(&deck);
    //Create our First Match Card
    UnoCard match;  //Create the Match card.
    match.setCrd(); //Set it up.
    //Display Outputs.
    //Start of Our Matching Loop
    do{
        cout<<endl<<"Card To Match..."<<endl;
        match.dsply();  //Display the Card
        cout<<endl<<aamir.getName()<<"'s Cards To Choose From..."<<endl;
        aamir.prntDck();
        //Ask for a Card from the Player.
        do{
            cout<<"Choose a Card (Ex. 1 - Card 1): ";
            cin>>opt;
        }while(opt>deck.getnCards()||opt<1);
        cout<<endl;
        //Check for a Match...
        //If we have a wild card that was used...
        if(deck[opt-1].getDescr()=="Wild Card"){
            string clr;
            cout<<"A Wild Card Was Used!"<<endl;
            cout<<"Choose a new color to match (Red/Green/Blue/Yellow): ";
            cin>>clr;
            match.setClr(clr);
            //Copy the Last Card Into the Card That was Used.
            deck[opt-1].cpyCrd(deck[deck.getnCards()-1]);
            deck--; //Decrement the # of Cards we Have.
        }
        //If both are draw 1 cards -> match. If the the colors match -> match.
        else if(deck[opt-1].getDescr()=="Draw 1"&&deck.isMatch(match,opt)||deck.isDrw1(match,opt)){
            cout<<"A Card Was Drawn..."<<endl;
            match.cpyCrd(deck[opt-1]);
            //Copy the Last Card Into the Card That was Used.
            deck[opt-1].cpyCrd(deck[deck.getnCards()-1]);
            deck--;  //Decrement by one for the card used.
            deck+=1; //Increment the # of Cards we Have.
        }
        //If both are draw 2 cards -> match. If the the colors match -> match.
        else if(deck[opt-1].getDescr()=="Draw 2"&&deck.isMatch(match,opt)||deck.isDrw2(match,opt)){
            cout<<"Two Cards Were Drawn..."<<endl;
            match.cpyCrd(deck[opt-1]);
            //Copy the Last Card Into the Card That was Used.
            deck[opt-1].cpyCrd(deck[deck.getnCards()-1]);
            deck--;  //Decrement by one for the card used.
            deck+=2; //Increment the # of Cards we Have.
        }
        //If the colors or values match -> match.
        else if(deck.isMatch(match,opt)){
            cout<<"Card was successfully matched!"<<endl;
            match.cpyCrd(deck[opt-1]);
            //Copy the Last Card Into the Card That was Used.
            deck[opt-1].cpyCrd(deck[deck.getnCards()-1]);
            deck--; //Decrement the # of Cards we Have.
        }
        else cout<<"Card wasn't matched..."<<endl;
    }while(deck.getnCards());
    //Exit the Program - Cleanup
    return 0;
}