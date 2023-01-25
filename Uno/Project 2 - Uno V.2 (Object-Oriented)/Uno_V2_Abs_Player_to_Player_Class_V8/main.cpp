/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on May 22, 2021, 1:20 PM
 * Purpose: Throwing in an Abstract Player Class - Requirement.
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>
#include <ctime>
using namespace std;

//User Libraries
#include "Player.h"
#include "Deck.h"
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Random # Generator
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    cout<<"Eighth Program of Project 2: "<<endl;
    cout<<"How Many Cards Do You Wish To Generate [1-20]? ";
    int numCrds;
    cin>>numCrds;
    //Create our Double Pointer That Represents our Deck.
    Deck deck1(numCrds);
    Deck deck2(numCrds);
    //Set our Deck up w/ Random Cards.
    deck1.setDck();
    deck2.setDck();
    //Create our Player Objects.
    Player aamir("Aamir");
    Player mark("Mark");
    aamir.setDck(&deck1);
    mark.setDck(&deck2);
    //Create our First Match Card
    UnoCard match;  //Create the Match card.
    match.setCrd(); //Set it up.
    //Begin the Match...
    int opt;   //Card Chosen By Player.
    do{
        //First Player's Turn
        cout<<endl<<"Card To Match..."<<endl;
        match.dsply();  //Display the Card
        cout<<endl<<aamir.getName()<<"'s Cards To Choose From..."<<endl;
        aamir.prntDck();
        //Ask for a Card from the Player.
        do{
            cout<<"Choose a Card (Ex. 1 - Card 1): ";
            cin>>opt;
        }while(opt>deck1.getnCards()||opt<1);
        cout<<endl;
        //Check for a Match...
        //If we have a wild card that was used...
        if(deck1[opt-1].getDescr()=="Wild Card"){
            string clr;
            cout<<"A Wild Card Was Used!"<<endl;
            cout<<"Choose a new color to match (Red/Green/Blue/Yellow): ";
            cin>>clr;
            match.setClr(clr);
            //Copy the Last Card Into the Card That was Used.
            deck1[opt-1].cpyCrd(deck1[deck1.getnCards()-1]);
            deck1--; //Decrement the # of Cards we Have.
        }
        //If both are draw 1 cards -> match. If the the colors match -> match.
        else if(deck1[opt-1].getDescr()=="Draw 1"&&deck1.isMatch(match,opt)||deck1.isDrw1(match,opt)){
            cout<<"A Card Was Drawn..."<<endl;
            match.cpyCrd(deck1[opt-1]);
            //Copy the Last Card Into the Card That was Used.
            deck1[opt-1].cpyCrd(deck1[deck1.getnCards()-1]);
            deck1--;  //Decrement by one for the card used.
            if(aamir.getnCards()!=0)
                deck2+=1; //Increment the # of Cards we Have.
        }
        //If both are draw 2 cards -> match. If the the colors match -> match.
        else if(deck1[opt-1].getDescr()=="Draw 2"&&deck1.isMatch(match,opt)||deck1.isDrw2(match,opt)){
            cout<<"Two Cards Were Drawn..."<<endl;
            match.cpyCrd(deck1[opt-1]);
            //Copy the Last Card Into the Card That was Used.
            deck1[opt-1].cpyCrd(deck1[deck1.getnCards()-1]);
            deck1--;  //Decrement by one for the card used.
            if(aamir.getnCards()!=0)
                deck2+=2; //Increment the # of Cards we Have.
        }
        //If the colors or values match -> match.
        else if(deck1.isMatch(match,opt)){
            cout<<"Card was successfully matched!"<<endl;
            match.cpyCrd(deck1[opt-1]);
            //Copy the Last Card Into the Card That was Used.
            deck1[opt-1].cpyCrd(deck1[deck1.getnCards()-1]);
            deck1--; //Decrement the # of Cards we Have.
        }
        else cout<<"Card wasn't matched..."<<endl;
        if(aamir.getnCards()!=0){
            //Second Player's Turn...
            cout<<endl<<"Card To Match..."<<endl;
            match.dsply();  //Display the Card
            cout<<endl<<mark.getName()<<"'s Cards To Choose From..."<<endl;
            mark.prntDck();
            //Ask for a Card from the Player.
            do{
                cout<<"Choose a Card (Ex. 1 - Card 1): ";
                cin>>opt;
            }while(opt>deck2.getnCards()||opt<1);
            cout<<endl;
            //Check for a Match...
            //If we have a wild card that was used...
            if(deck2[opt-1].getDescr()=="Wild Card"){
                string clr;
                cout<<"A Wild Card Was Used!"<<endl;
                cout<<"Choose a new color to match (Red/Green/Blue/Yellow): ";
                cin>>clr;
                match.setClr(clr);
                //Copy the Last Card Into the Card That was Used.
                deck2[opt-1].cpyCrd(deck2[deck2.getnCards()-1]);
                deck2--; //Decrement the # of Cards we Have.
            }
            //If both are draw 1 cards -> match. If the the colors match -> match.
            else if(deck2[opt-1].getDescr()=="Draw 1"&&deck2.isMatch(match,opt)||deck2.isDrw1(match,opt)){
                cout<<"A Card Was Drawn..."<<endl;
                match.cpyCrd(deck2[opt-1]);
                //Copy the Last Card Into the Card That was Used.
                deck2[opt-1].cpyCrd(deck2[deck2.getnCards()-1]);
                deck2--;  //Decrement by one for the card used.
                if(mark.getnCards()!=0)
                    deck1+=1; //Increment the # of Cards we Have.
            }
            //If both are draw 2 cards -> match. If the the colors match -> match.
            else if(deck2[opt-1].getDescr()=="Draw 2"&&deck2.isMatch(match,opt)||deck2.isDrw2(match,opt)){
                cout<<"Two Cards Were Drawn..."<<endl;
                match.cpyCrd(deck2[opt-1]);
                //Copy the Last Card Into the Card That was Used.
                deck2[opt-1].cpyCrd(deck2[deck2.getnCards()-1]);
                deck2--;  //Decrement by one for the card used.
                if(mark.getnCards()!=0)
                    deck1+=2; //Increment the # of Cards we Have.
            }
            //If the colors or values match -> match.
            else if(deck2.isMatch(match,opt)){
                cout<<"Card was successfully matched!"<<endl;
                match.cpyCrd(deck2[opt-1]);
                //Copy the Last Card Into the Card That was Used.
                deck2[opt-1].cpyCrd(deck2[deck2.getnCards()-1]);
                deck2--; //Decrement the # of Cards we Have.
            }
            else cout<<"Card wasn't matched..."<<endl;
        }
    }while(aamir.getnCards()&&mark.getnCards());
    //Display the Winner!
    aamir.getnCards()==0?cout<<endl<<"Winner: "<<aamir.getName()
                        :cout<<endl<<"Winner: "<<mark.getName();
    //Exit the Program - Cleanup
    return 0;
}