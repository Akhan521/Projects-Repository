/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on May 24, 2021, 12:15 PM
 * Purpose: Adding Some Finishing Touches + Trying to Increase Line Count.
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //rand function
#include <ctime>     //time function
#include <new>       //bad_alloc exception
using namespace std;

//User Libraries
#include "DerPlayer.h"
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
void cleanUp(Player **,int); //Recovers Memory.
void menu();                 //Displays the Menu at the Start.
void game(int &);            //Starts an Uno game.
//The int & passed in would hold the # of times Player 1 won.
//Execution Begins Here
int main(int argc, char** argv) {
    //Random # Generator
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    cout<<"Fourteenth Program of Project 2:"<<endl<<endl;
    char option; //To Hold Our Option.
    int nWins=0; //To Hold the # of Wins Player 1 Has.
    menu();      //Display the Menu.
    cin>>option;
    switch(option){
        case '1':{
            unsigned int beg=time(0); //Beginning Time
            //First Game.
            game(nWins);
            //Second Game.
            char ch;
            cout<<endl<<"Play a Second Game (Y/N)? ";
            cin>>ch;
            if(ch=='Y'||ch=='y'){
                game(nWins);
            }
            //Third Game.
            cout<<endl<<"Play a Third Game (Y/N)? ";
            cin>>ch;
            if(ch=='Y'||ch=='y'){
                game(nWins);
            }
            unsigned int end=time(0);  //End Time
            //Display the # of times Player 1 won.
            cout<<endl<<"Games took "<<end-beg<<" seconds."<<endl;
            if(nWins==1) //I'm a stickler when it comes to grammar.
                cout<<"Player 1 won "<<nWins<<" time throughout this program.";
            else 
                cout<<"Player 1 won "<<nWins<<" times throughout this program.";
            break;
        }
        default: cout<<"Quitting Program...";
    }
    return 0;
}
//Cleans up after ourself.
void cleanUp(Player **plyrs,int nPlyrs){
    //Recover the Memory we Used.
    for(int i=0;i<nPlyrs-1;i++){
        delete plyrs[i];
    }
    delete [] plyrs;
}
//Menu Function.
void menu(){
    cout<<"Welcome to the World of Uno..."<<endl;
    cout<<"Uno is a card game all about matching cards through colors, values, \n"
        <<"and even playing a little dirty. Players have to compete to see who \n"
        <<"can finish with their deck of cards first. Players can force \n"
        <<"opponents to draw cards by pulling Draw 1 or 2 Cards. Furthermore, \n"
        <<"Players can set new colors to match by pulling Wild Cards. A match \n"
        <<"can be made by using cards with the same color, number, or description.\n"
        <<"Descriptions include: Draw 1's, Draw 2's, and Wild Cards.\n\n";
    cout<<"Choose an Option: "<<endl;
    cout<<"Option 1: Play Game."<<endl;
    cout<<"Default: Quit Program."<<endl;
}
//Game Function that Runs a Single Uno Game.
void game(int &nWins){
    cin.ignore();
    string name1,name2; //Names of the Players
    cout<<"Enter Player's Name: ";
    getline(cin,name1);
    int age;            //Opponent's Age
    cout<<"Enter Opponent's Name: ";
    getline(cin,name2);
    cout<<"Enter the Opponent's age: ";
    cin>>age;
    int numCrds=0; //To Hold The # of Cards We Begin With
    while(numCrds==0){
        cout<<"How Many Cards Do You Wish To Generate [1-15]? ";
        cin>>numCrds;
    }
    //Throwing bad_alloc exception if memory can't be allocated.
    try{
        //Create our Double Pointer That Represents our Deck.
        Deck deck1(numCrds); //For Our First Player
        Deck deck2(numCrds); //For Our Second Player
        //Set our Deck up w/ Random Cards.
        deck1.setDck();
        deck2.setDck();
        //Create our Player Objects.
        int nPlyrs=2;
        //A Derived Player that's Used as a Player Object.
        DerPlayer oppt(name2,age);
        //An Array of Player Objects.
        Player **plyrs=new Player *[nPlyrs];
        //The first object is us.
        plyrs[0]=new Player(name1);
        //This showcases polymorphic behavior.
        plyrs[1]=&oppt;
        //We set our deck members w/ our data.
        plyrs[0]->setDck(&deck1);
        plyrs[1]->setDck(&deck2);
        //Create our First Match Card
        UnoCard match; //Create the Match card.
        //We don't want our first match card to be a wild card.
        do{
            match.setCrd(); //Set it up.
        }while(match.getClr()=="None");
        //Begin the Match...
        int opt;   //Card Chosen By Player.
        do{
            //First Player's Turn
            cout<<endl<<"Card To Match..."<<endl;
            match.dsply();  //Display the Card
            cout<<endl<<plyrs[0]->getName()<<"'s Cards To Choose From..."<<endl;
            plyrs[0]->prntDck();
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
                cout<<"Card Was Drawn By "<<plyrs[1]->getName()<<"..."<<endl;
                match.cpyCrd(deck1[opt-1]);
                //Copy the Last Card Into the Card That was Used.
                deck1[opt-1].cpyCrd(deck1[deck1.getnCards()-1]);
                deck1--;  //Decrement by one for the card used.
                if(plyrs[0]->getnCards()!=0)
                    deck2+=1; //Increment the # of Cards we Have.
            }
            //If both are draw 2 cards -> match. If the the colors match -> match.
            else if(deck1[opt-1].getDescr()=="Draw 2"&&deck1.isMatch(match,opt)||deck1.isDrw2(match,opt)){
                cout<<"Two Card Were Drawn By "<<plyrs[1]->getName()<<"..."<<endl;
                match.cpyCrd(deck1[opt-1]);
                //Copy the Last Card Into the Card That was Used.
                deck1[opt-1].cpyCrd(deck1[deck1.getnCards()-1]);
                deck1--;  //Decrement by one for the card used.
                if(plyrs[0]->getnCards()!=0)
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
            if(plyrs[0]->getnCards()!=0){
                //Ask for whether the 1st player want to draw a card.
                cout<<"Do You Want to Draw a Card (Y/N)? ";
                char choice;
                cin>>choice;
                if(choice=='Y'||choice=='y'){
                    deck1+=1;
                    cout<<plyrs[0]->getName()<<" Drew a Card..."<<endl;
                }
            }
            //Second Player's Turn...
            if(plyrs[0]->getnCards()!=0){
                cout<<endl<<"Card To Match..."<<endl;
                match.dsply();  //Display the Card
                cout<<endl<<plyrs[1]->getName()<<"'s Cards To Choose From..."<<endl;
                plyrs[1]->prntDck();
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
                    cout<<"Card Was Drawn By "<<plyrs[0]->getName()<<"..."<<endl;
                    match.cpyCrd(deck2[opt-1]);
                    //Copy the Last Card Into the Card That was Used.
                    deck2[opt-1].cpyCrd(deck2[deck2.getnCards()-1]);
                    deck2--;  //Decrement by one for the card used.
                    if(plyrs[1]->getnCards()!=0)
                        deck1+=1; //Increment the # of Cards we Have.
                }
                //If both are draw 2 cards -> match. If the the colors match -> match.
                else if(deck2[opt-1].getDescr()=="Draw 2"&&deck2.isMatch(match,opt)||deck2.isDrw2(match,opt)){
                    cout<<"Two Cards Were Drawn By "<<plyrs[0]->getName()<<"..."<<endl;
                    match.cpyCrd(deck2[opt-1]);
                    //Copy the Last Card Into the Card That was Used.
                    deck2[opt-1].cpyCrd(deck2[deck2.getnCards()-1]);
                    deck2--;  //Decrement by one for the card used.
                    if(plyrs[1]->getnCards()!=0)
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
                if(plyrs[1]->getnCards()!=0){
                    //Ask for whether the 2nd player want to draw a card.
                    cout<<"Do You Want to Draw a Card (Y/N)? ";
                    char choice;
                    cin>>choice;
                    if(choice=='Y'||choice=='y'){
                        deck2+=1;
                        cout<<plyrs[1]->getName()<<" Drew a Card..."<<endl;
                    }
                }
            }
        }while(plyrs[0]->getnCards()&&plyrs[1]->getnCards());
        //Display the Winner!
        plyrs[0]->getnCards()==0?cout<<endl<<"Winner: "<<plyrs[0]->getName()
                                //cout mark(DerPlayer) using a friend function.
                                :cout<<endl<<"Winner: "<<oppt;
        //To keep track of how many times Player 1 won.
        if(plyrs[0]->getnCards()==0)nWins++;
        //Checking how many Player Objects we created through our static member.
        cout<<endl<<"There were "<<Player::getnPlyrs()<<" Players in this Program. (Static Member)"<<endl<<endl;
        //Exit the Program - Cleanup
        cleanUp(plyrs,nPlyrs);
    }
    //For Catching Memory Errors
    catch(bad_alloc){
        cout<<"ERROR: Memory Could Not Be Allocated.\n";
    }
    //For Catching BadnCrds Errors - Having More than 15 Cards.
    catch(Deck::BadnCrds){
        cout<<"ERROR: Too Many Cards. Card Range [1-15]. \n";
    }
}