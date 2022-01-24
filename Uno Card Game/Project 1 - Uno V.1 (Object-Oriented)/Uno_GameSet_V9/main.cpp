/* 
 * File:   main.cpp
 * Author: Aamir 
 * Created on April 15, 2021, 1:30 PM
 * Purpose: Adding an Opponent + Creating a Function For Taking Turns
 *    Just for the sake of it, I threw in an enumerated data type.
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting
#include <string>    //String Library
#include <cstring>   //For strcpy function
#include <ctime>     //For time function
using namespace std;

//User Libraries
#include "UnoCard.h"
enum nums{ZERO,ONE,TWO,THREE,FOUR,FIVE,SIX,SEVEN,EIGHT,NINE,TEN,ELEVEN};
//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
UnoCard setCrd();
void dsply(UnoCard,int);            //Display a single structure variable
void copyCrd(UnoCard &,UnoCard &);  //Copy the contents of a structure variable
void drawCrd(UnoCard *,short,int);  //Draw 1 or 2 random cards and store them 
void takeTrn(UnoCard *,UnoCard *,UnoCard &,short &,short &);

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    short plyrCrds,      //The # of Cards we Begin With
          opptCrds;
    //Initialize Variables
    plyrCrds=opptCrds=SEVEN; //Each starts out with 7 Cards
    cout<<"Ninth Program of My Uno Project 1."<<endl<<endl;
    //Player's Deck of Cards
    UnoCard *plyrDck=new UnoCard[plyrCrds*TWO];
    //Opponent's Deck of Cards
    UnoCard *opptDck=new UnoCard[opptCrds*TWO];
    //Map Inputs to Outputs -> Process
    //Initialize All The Cards
    for(int i=ZERO;i<plyrCrds*TWO;i++){
        //For Player
        (plyrDck+i)->color="";
        strcpy((plyrDck+i)->descr,"");
        (plyrDck+i)->value=0;
        //For Opponent
        opptDck[i].color="";
        strcpy(opptDck[i].descr,"");
        opptDck[i].value=0;
    }
    //Set the Cards that we need.
    for(int i=ZERO;i<plyrCrds;i++){ //Generating Random Cards
        *(plyrDck+i)=setCrd();
        *(opptDck+i)=setCrd();
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
        takeTrn(plyrDck,opptDck,match,plyrCrds,opptCrds); 
        //If Player has no cards, he wins and the game stops.
        if(plyrCrds==ZERO) cont=false;
        //If Player still has cards, this will execute.
        if(cont==true){
            //Opponent's Turn Follows After.
            cout<<"Opponent's Turn"<<endl;
            takeTrn(opptDck,plyrDck,match,opptCrds,plyrCrds);
            if(opptCrds==ZERO) cont=false;
        }
        //Keep Looping Until Either Finishes Their Cards
    }while(cont);
    //Deallocate the memory we set.
    delete [] plyrDck;
    delete [] opptDck;
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
        card.value=rand()%ELEVEN+ONE; //Values Between [1,11]
        if(card.value==TEN){
            strcpy(card.descr,"Draw 1");
        }
        else if(card.value==ELEVEN){
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
void drawCrd(UnoCard *card,short numCrds,int draw){
    for(int i=numCrds;i<numCrds+draw;i++){
        card[i]=setCrd();
    }
}
//Pass in the current player, their opponent, what to match, current player's cards, and oppt's cards.
//If cards are drawn, the opponent will be affected and we need their cards and structure array to do this.
void takeTrn(UnoCard *plyrDck,UnoCard *opptDck,UnoCard &match,short &numCrds,short &opptCrds){
    short option=0; //Card that is chosen
    cout<<"Card to Match: ";
        dsply(match,0);
        cout<<"Available Cards to Choose From..."<<endl;
        for(int i=0;i<numCrds;i++){
            dsply(*(plyrDck+i),i);
        }
        cout<<"Which card do you choose? ";
        cin>>option;
        //We use strcmp to test the descr because it's a char array.
        if(plyrDck[option-1].color=="None"&&strcmp(plyrDck[option-1].descr,"Wild Card")==0){
            cout<<endl;
            cout<<"A Wild Card was Used."<<endl;
            numCrds--; //Once a match is made, the card is gone.
            //Set the new card to match for the next turn after choosing a color
            string clr; //The new color will be stored here.
            cout<<"Choose a new color (Red/Blue/Green/Yellow)"
                <<endl<<"and type it exactly as you see it: ";    
            cin>>clr;
            //Set the color that was picked as the new color to match.
            match.color=clr;
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(*(plyrDck+numCrds),*(plyrDck+option-1));
        }
        //If both the option and what needs to be matched are draw 1's, a match is also made.
        else if(strcmp((plyrDck+option-1)->descr,"Draw 1")==0&&strcmp(match.descr,"Draw 1")==0){
            cout<<endl;
            cout<<"One Card was Drawn."<<endl;
            numCrds--;
            //Opponent draws a card.
            drawCrd(opptDck,opptCrds,1);
            opptCrds++;
            //Set the new card to match for the next turn
            copyCrd(plyrDck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyrDck[numCrds],plyrDck[option-1]); 
        }
        //We use strcmp again...this time for draw 1.
        //If only the colors are matching and the option is a draw 1.
        else if(plyrDck[option-1].color==match.color&&strcmp(plyrDck[option-1].descr,"Draw 1")==0){
            cout<<endl;
            cout<<"Colors Matched and One Card was Drawn."<<endl;
            numCrds--;
            //If we use a card, but draw 1, they offset, so have no cards lost.
            //Draw a Card and store it at the end.
            drawCrd(opptDck,opptCrds,1);
            opptCrds++;
            //Set the new card to match for the next turn
            copyCrd(plyrDck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyrDck[numCrds],plyrDck[option-1]); 
        }
        //If both the option and what needs to be matched are draw 2's, a match is also made.
        else if(strcmp((plyrDck+option-1)->descr,"Draw 2")==0&&strcmp(match.descr,"Draw 2")==0){
            cout<<endl;
            cout<<"Two Cards were Drawn."<<endl;
            numCrds--;
            //Draw 2 Cards and store them at the end.
            drawCrd(opptDck,opptCrds,2);
            opptCrds+=2;
            //Set the new card to match for the next turn
            copyCrd(*(plyrDck+option-1),match);
            //Copy the last card info into the empty card slot to fill it in.
            copyCrd(plyrDck[numCrds],plyrDck[option-1]); 
        }
        ////We use strcmp again...this time for draw 2.
        //If only the colors are matching and the option is a draw 2.
        else if((plyrDck+option-1)->color==match.color&&strcmp(plyrDck[option-1].descr,"Draw 2")==0){
            cout<<endl;
            cout<<"Colors Matched and Two Cards were Drawn."<<endl;
            numCrds--;
            //Draw 2 Cards and store them at the end.
            drawCrd(opptDck,opptCrds,2);
            opptCrds+=2;
            //Set the new card to match for the next turn
            copyCrd(plyrDck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in.
            copyCrd(*(plyrDck+numCrds),plyrDck[option-1]); 
        }
        //The color and value are tested against each other.
        else if(plyrDck[option-1].color==match.color||plyrDck[option-1].value==match.value){
            cout<<endl;
            cout<<"Successfully Matched."<<endl;
            numCrds--; //Once a match is made, the card is gone.
            //Set the new card to match for the next turn
            copyCrd(*(plyrDck+option-1),match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyrDck[numCrds],*(plyrDck+option-1)); 
        }
        //Last Resort if nothing matches.
        else cout<<endl<<"Can't Match The Two."<<endl;
        //Display Inputs/Outputs
        cout<<"Cards Left After the Match"<<endl;
        for(int i=0;i<numCrds;i++){
            dsply(*(plyrDck+i),i);
        }
        cout<<numCrds<<" Card/s left."<<endl<<endl;
        //If we have no cards that can be used to match, we draw a card.
        string drwCrd="";
        cout<<"Draw a Card (Yes/No)? ";
        cin>>drwCrd;
        if(drwCrd=="Yes"){
            drawCrd(plyrDck,numCrds,1);
            numCrds++;
        }
        cout<<endl;
}