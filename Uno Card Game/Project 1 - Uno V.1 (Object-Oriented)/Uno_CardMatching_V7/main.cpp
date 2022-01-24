/* 
 * File:   main.cpp
 * Author: Aamir 
 * Created on April 13, 2021, 12:00 PM
 * Purpose: Working out a Draw Card Function + Wild Card Mechanics
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
void dsply(UnoCard,int);           //Display a single structure variable
void copyCrd(UnoCard &,UnoCard &); //Copy the contents of a structure variable
void drawCrd(UnoCard [],int,int);  //Draw 1 or 2 random cards and store them 

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    short numCrds=7;        //# of Cards to generate
    short option;           //Card that is chosen
    //Initialize Variables
    cout<<"Seventh Program of My Uno Project 1."<<endl;
    //Create an array of structures with twice the size for extra space
    //This space is for when we draw 1/2 cards if we happen to do so.
    UnoCard plyrDck[numCrds*2];
    //Map Inputs to Outputs -> Process
    //Set The Cards
    for(int i=0;i<numCrds*2;i++){
        plyrDck[i].color="";
        strcpy(plyrDck[i].descr,"");
        plyrDck[i].value=0;
    }
    for(int i=0;i<numCrds;i++){ //Generating Random Cards
        plyrDck[i]=setCrd();
    }
    //First Card to Match
    UnoCard match=setCrd();
    bool cont; //Used to keep looping for as long as we have matches
    do{
        cout<<"Card to Match: ";
        dsply(match,0);
        cont=false;
        cout<<"Available Cards to Choose From..."<<endl;
        for(int i=0;i<numCrds;i++){
            dsply(plyrDck[i],i);
        }
        cout<<"Which card do you choose? ";
        cin>>option;
        //We use strcmp to test the descr because it's a char array.
        if(plyrDck[option-1].color=="None"&&(strcmp(plyrDck[option-1].descr,"Wild Card")==0)){
            cout<<endl;
            cout<<"A Wild Card was Used."<<endl;
            cont=true; //Set it to true for another loop.
            numCrds--; //Once a match is made, the card is gone.
            //Set the new card to match for the next turn after choosing a color
            string clr; //The new color will be stored here.
            cout<<"Choose a new color (Red/Blue/Green/Yellow)"
                <<endl<<"and type it exactly as you see it: ";    
            cin>>clr;
            //Set the color that was picked as the new color to match.
            match.color=clr;
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyrDck[numCrds],plyrDck[option-1]);
        }
        //If both the option and what needs to be matched are draw 1's, a match is also made.
        else if((strcmp(plyrDck[option-1].descr,"Draw 1")==0)&&(strcmp(match.descr,"Draw 1")==0)){
            cout<<endl;
            cout<<"One Card was Drawn."<<endl;
            cont=true; //Set it to true for another loop.
            //If we use a card, but draw 1, they offset, so have no cards lost.
            //Draw a Card and store it at the end.
            drawCrd(plyrDck,numCrds,1);
            //Set the new card to match for the next turn
            copyCrd(plyrDck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyrDck[numCrds],plyrDck[option-1]); 
        }
        //We use strcmp again...this time for draw 1.
        //If only the colors are matching and the option is a draw 1.
        else if(plyrDck[option-1].color==match.color&&(strcmp(plyrDck[option-1].descr,"Draw 1")==0)){
            cout<<endl;
            cout<<"One Card was Drawn."<<endl;
            cont=true; //Set it to true for another loop.
            //If we use a card, but draw 1, they offset, so have no cards lost.
            //Draw a Card and store it at the end.
            drawCrd(plyrDck,numCrds,1);
            //Set the new card to match for the next turn
            copyCrd(plyrDck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyrDck[numCrds],plyrDck[option-1]); 
        }
        //If both the option and what needs to be matched are draw 2's, a match is also made.
        else if((strcmp(plyrDck[option-1].descr,"Draw 2")==0)&&(strcmp(match.descr,"Draw 2")==0)){
            cout<<endl;
            cout<<"Two Cards were Drawn."<<endl;
            cont=true; //Set it to true for another loop.
            //Draw 2 Cards and store them at the end.
            drawCrd(plyrDck,numCrds,2);
            //Set the new card to match for the next turn
            copyCrd(plyrDck[option-1],match);
            //We used 1 card and drew 2, so we have an additional card leftover.
            numCrds++;
            //Copy the last card info into the empty card slot to fill it in.
            //For ex. If we had 7 cards and now 9, the last card would be at the index 9-1=8
            copyCrd(plyrDck[numCrds],plyrDck[option-1]); 
        }
        ////We use strcmp again...this time for draw 2.
        //If only the colors are matching and the option is a draw 2.
        else if((plyrDck[option-1].color==match.color)&&(strcmp(plyrDck[option-1].descr,"Draw 2")==0)){
            cout<<endl;
            cout<<"Two Cards were Drawn."<<endl;
            cont=true; //Set it to true for another loop.
            //Draw 2 Cards and store them at the end.
            drawCrd(plyrDck,numCrds,2);
            //Set the new card to match for the next turn
            copyCrd(plyrDck[option-1],match);
            //We used 1 card and drew 2, so we have an additional card leftover.
            numCrds++;
            //Copy the last card info into the empty card slot to fill it in.
            //For ex. If we had 7 cards and now 9, the last card would be at the index 9-1=8
            copyCrd(plyrDck[numCrds],plyrDck[option-1]); 
        }
        //If everything else fails, the color and value are tested against each other.
        else if(plyrDck[option-1].color==match.color||plyrDck[option-1].value==match.value){
            cout<<endl;
            cout<<"Successfully Matched."<<endl;
            cont=true; //Set it to true for another loop.
            numCrds--; //Once a match is made, the card is gone.
            //Set the new card to match for the next turn
            copyCrd(plyrDck[option-1],match);
            //Copy the last card info into the empty card slot to fill it in. 
            copyCrd(plyrDck[numCrds],plyrDck[option-1]); 
        }
        //Last Resort if nothing matches.
        else cout<<endl<<"Can't Match The Two."<<endl;
        //Display Inputs/Outputs
        cout<<"Cards Left After the Match"<<endl;
        for(int i=0;i<numCrds;i++){
            dsply(plyrDck[i],i);
        }
        cout<<numCrds<<" Card/s left."<<endl<<endl;
    }while(cont);
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
    if(card.color=="None"){
        cout<<"Card "<<i+1<<" = ["<<card.color<<" "<<setw(5)
                                  <<card.descr<<"]"<<endl;
    }
    else if(static_cast<int>(card.value)==10||static_cast<int>(card.value)==11){
        cout<<"Card "<<i+1<<" = ["<<card.color<<" "<<setw(5)
                                  <<card.descr<<"]"<<endl;
    }
    else{
        cout<<"Card "<<i+1<<" = ["<<card.color<<" "<<setw(2)
                <<static_cast<int>(card.value)<<"]"<<endl;
    }
}
//The copy function copies the last filled card in the cleared card's slot,
//so that numbering still works.
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
void drawCrd(UnoCard card[],int numCrds,int draw){
    for(int i=numCrds;i<numCrds+draw;i++){
        card[i]=setCrd();
    }
}