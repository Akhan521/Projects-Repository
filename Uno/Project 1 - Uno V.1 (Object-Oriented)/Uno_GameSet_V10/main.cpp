/* 
 * File:   main.cpp
 * Author: Aamir 
 * Created on April 17, 2021, 9:30 AM
 * Purpose: Implement a Structure within a Structure + Getting our first file.
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting
#include <fstream>   //File Objecs
#include <string>    //String Library
#include <cstring>   //For strcpy function
#include <ctime>     //For time function
using namespace std;

//User Libraries
#include "UnoPlayer.h"
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
UnoCard setCrd();
void dsply(UnoCard,int);            //Display a single structure variable
void copyCrd(UnoCard &,UnoCard &);  //Copy the contents of a structure variable
void drawCrd(UnoPlayer &,int);      //Draw 1 or 2 random cards and store them 
void takeTrn(UnoPlayer &,UnoPlayer &,UnoCard &);

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    fstream out; //To write the rules to a text file
    string flnme="UnoRules.txt";
    int cards=0; //To hold how many cards we start with
    //Open the txt file to write the rules to.
    out.open(flnme,ios::out);
    out<<"Rules for Uno:\n";
    out<<"The goal of the game is to match cards until either opponent runs out of cards.\n";
    out<<"Once a player finishes their deck of cards, the game ends and they win.\n";
    out<<"You can match cards either by color, value, or have a chance to sabotage your opponent by drawing\n";
    out<<"wild cards, draw 1's, or draw 2's. A wild card can be used to set a new color to match.\n";
    out<<"A draw 1 forces the opponent to draw 1 card, and a draw 2 works in a similar manner.\n";
    out<<"Wild cards can be used at anytime. However, draw 1's and 2's can only be used when colors match\n";
    out<<"or when the card that needs to be matched is also a draw 1/2 card.\n";
    out<<"Have Fun and Don't Sweat It If You Lose!";
    //End of Rules.
    cout<<"Tenth Program of My Uno Project 1."<<endl<<endl;
    cout<<"How many cards should each player start off with? ";
    cin>>cards;
    //Create 2 Players - Player/Opponent. Also, give both the same # of cards.
    UnoPlayer plyr;
    plyr.numCrds=cards;
    UnoPlayer oppt;
    oppt.numCrds=cards;
    //Player's Deck of Cards
    plyr.deck=new UnoCard[plyr.numCrds*3];
    //Opponent's Deck of Cards
    oppt.deck=new UnoCard[oppt.numCrds*3];
    //Map Inputs to Outputs -> Process
    //Set the Cards that we need.
    for(int i=0;i<plyr.numCrds;i++){ //Generating Random Cards
        plyr.deck[i]=setCrd();
        oppt.deck[i]=setCrd();
    }
    //First Card to Match
    UnoCard match=setCrd();
    //For looping as long as we need to.
    bool cont;
    //Begin Matching Cards and Taking Turns
    do{
        cont=true;
        //Player 1 Begins the Round.
        cout<<"Player's Turn"<<endl;
        takeTrn(plyr,oppt,match); 
        //If Player has no cards, he wins and the game stops.
        if(plyr.numCrds==0) cont=false;
        //If Player still has cards, this will execute.
        if(cont==true){
            //Opponent's Turn Follows After.
            cout<<"Opponent's Turn"<<endl;
            takeTrn(oppt,plyr,match);
            if(oppt.numCrds==0) cont=false;
        }
        //Keep Looping Until Either Finishes Their Cards
    }while(cont);
    //Announce the Winner Using a Ternary Op
    plyr.numCrds==0?cout<<"Player Wins!\n":cout<<"Opponent Wins!\n";
    cout<<"Player: "<<plyr.numCrds<<" Card/s Remaining."<<endl;
    cout<<"Opponent: "<<oppt.numCrds<<" Card/s Remaining."<<endl;
    //Deallocate the memory we set.
    delete [] plyr.deck;
    delete [] oppt.deck;
    //Close the files
    out.close();
    //Exit the Program - Cleanup
    return 0;
}
//Set Card Function - Generate a Random Card and Return It.
UnoCard setCrd(){
    UnoCard card;
    //To determine what colors the cards are assigned
    int x=rand()%9+1; //Between [1,9] to determine colors
    switch(x){
        case 1:
        case 2: card.color="Blue";break;
        case 3:
        case 4: card.color="Green";break;
        case 5:
        case 6: card.color="Red";break;
        case 7:
        case 8: card.color="Yellow";break;
        default:card.color="None";break;
    }
    if(card.color=="None"){
        strcpy(card.descr,"Wild Card");
    }
    else{
        card.value=rand()%11+1; //Values Between [1,11]
        if(card.value==10){
            strcpy(card.descr,"Draw 1");
        }
        else if(card.value==11){
            strcpy(card.descr,"Draw 2");
        }
    }
    return card;
}
//Displays the Card that was generated.
void dsply(UnoCard card,int i){
    //This will be a Wild Card or a Draw 1/2 Card.
    //If value = 10, Draw 1. If value = 11, Draw 2.
    if(card.color=="None"||card.value==10||card.value==11){
        cout<<"Card "<<i+1<<" = ["<<card.color<<" "<<setw(5)
                                  <<card.descr<<"]"<<endl;
    }
    else{
        cout<<"Card "<<i+1<<" = ["<<card.color<<" "<<setw(2)
                <<static_cast<int>(card.value)<<"]"<<endl;
    }
}
//The copy function copies the last card in the cleared card's slot,
//so that numbering still works and so there's not a jump in cards.
void copyCrd(UnoCard &card1,UnoCard &card2){
    //Copy over the values
    card2.color=card1.color;
    card2.value=card1.value;
    strcpy(card2.descr,card1.descr);
    //Clear the contents of the other card
    card1.color="";
    card1.value=0;
    strcpy(card1.descr,"");
}
void drawCrd(UnoPlayer &plyr,int draw){
    for(int i=plyr.numCrds;i<plyr.numCrds+draw;i++){
        plyr.deck[i]=setCrd();
    }
}
//Pass in the current player, their opponent, what to match, current player's cards, and oppt's cards.
//If cards are drawn, the opponent will be affected and we need their cards and structure array to do this.
void takeTrn(UnoPlayer &plyr,UnoPlayer &oppt,UnoCard &match){
    int option=0; //Card that is chosen
    cout<<"Card to Match: ";
        dsply(match,0);
        cout<<"Available Cards to Choose From..."<<endl;
        for(int i=0;i<plyr.numCrds;i++){
            dsply(plyr.deck[i],i);
        }
        cout<<"Which card do you choose? ";
        cin>>option;
        //We use strcmp to test the descr because it's a char array.
        if(plyr.deck[option-1].color=="None"&&strcmp(plyr.deck[option-1].descr,"Wild Card")==0){
            cout<<endl;
            cout<<"A Wild Card was Used."<<endl;
            plyr.numCrds--; //Once a match is made, the card is gone.
            //Set the new card to match for the next turn after choosing a color
            string clr; //The new color will be stored here.
            cout<<"Choose a new color (Red/Blue/Green/Yellow)"
                <<endl<<"and type it exactly as you see it: ";    
            cin>>clr;
            //Set the color that was picked as the new color to match.
            match.color=clr;
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyr.deck[plyr.numCrds],plyr.deck[option-1]);
        }
        //If both the option and what needs to be matched are draw 1's, a match is also made.
        //If we have a value of 10, that's a draw 1 card.
        else if(plyr.deck[option-1].value==10&&match.value==10){
            cout<<endl;
            cout<<"One Card was Drawn."<<endl;
            plyr.numCrds--;
            //Opponent draws a card.
            drawCrd(oppt,1);
            oppt.numCrds++;
            //Set the new card to match for the next turn
            copyCrd(plyr.deck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyr.deck[plyr.numCrds],plyr.deck[option-1]); 
        }
        //We use strcmp again...this time for draw 1.
        //If only the colors are matching and the option is a draw 1.
        else if(plyr.deck[option-1].value==10&&plyr.deck[option-1].color==match.color){
            cout<<endl;
            cout<<"Colors Matched and One Card was Drawn."<<endl;
            plyr.numCrds--;
            //If we use a card, but draw 1, they offset, so have no cards lost.
            //Draw a Card and store it at the end.
            drawCrd(oppt,1);
            oppt.numCrds++;
            //Set the new card to match for the next turn
            copyCrd(plyr.deck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyr.deck[plyr.numCrds],plyr.deck[option-1]); 
        }
        //If both the option and what needs to be matched are draw 2's, a match is also made.
        //If we have a value of 11, that's a draw 2 card.
        else if(plyr.deck[option-1].value==11&&match.value==11){
            cout<<endl;
            cout<<"Two Cards were Drawn."<<endl;
            plyr.numCrds--;
            //Draw 2 Cards and store them at the end.
            drawCrd(oppt,2);
            oppt.numCrds+=2;
            //Set the new card to match for the next turn
            copyCrd(plyr.deck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in.
            copyCrd(plyr.deck[plyr.numCrds],plyr.deck[option-1]); 
        }
        ////We use strcmp again...this time for draw 2.
        //If only the colors are matching and the option is a draw 2.
        else if(plyr.deck[option-1].value==11&&plyr.deck[option-1].color==match.color){
            cout<<endl;
            cout<<"Colors Matched and Two Cards were Drawn."<<endl;
            plyr.numCrds--;
            //Draw 2 Cards and store them at the end.
            drawCrd(oppt,2);
            oppt.numCrds+=2;
            //Set the new card to match for the next turn
            copyCrd(plyr.deck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in.
            copyCrd(plyr.deck[plyr.numCrds],plyr.deck[option-1]); 
        }
        //The color and value are tested against each other.
        else if(plyr.deck[option-1].color==match.color||plyr.deck[option-1].value==match.value){
            cout<<endl;
            cout<<"Successfully Matched."<<endl;
            plyr.numCrds--; //Once a match is made, the card is gone.
            //Set the new card to match for the next turn
            copyCrd(plyr.deck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyr.deck[plyr.numCrds],plyr.deck[option-1]); 
        }
        //Last Resort if nothing matches.
        else cout<<endl<<"Can't Match The Two."<<endl;
        //Display Inputs/Outputs
        cout<<"Cards Left After the Match"<<endl;
        for(int i=0;i<plyr.numCrds;i++){
            dsply(plyr.deck[i],i);
        }
        cout<<plyr.numCrds<<" Card/s left."<<endl<<endl;
        if(plyr.numCrds!=0){
            //If we have no cards that can be used to match, we draw a card.
            string drwCrd="";
            cout<<"Draw a Card (Yes/No)? ";
            cin>>drwCrd;
            if(drwCrd=="Yes"){
                drawCrd(plyr,1);
                plyr.numCrds++;
            }
        }
        cout<<endl;
}