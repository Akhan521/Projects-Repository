/* 
 * File:   main.cpp
 * Author: Aamir 
 * Created on April 11, 2021, 8:25 PM
 * Purpose: Adding Draw 1, Draw 2, and Wild Cards (3 More Card Options)
 */

//System Libraries
#include <iostream>  //I/O Library
#include <ctime>   
#include <string>
#include <cstring>
using namespace std;

//User Libraries

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables
    const int SIZE=21;      //Size of Char Array
    short numCrds=0;        //# of Cards to generate
    string color="";        //To hold a color or none
    char descr[SIZE]="";    //To hold a description if there's no color
    unsigned char value='0';//To hold a value if there's a color
    //Initialize Variables
    cout<<"Second Program of My Uno Project 1."<<endl;
    cout<<"How many cards do you want to generate [1-20]? ";
    cin>>numCrds;
    //A Ternary Op to limit cards generated.
    numCrds=(numCrds>20?20:numCrds);
    //Map Inputs to Outputs -> Process
    for(int i=0;i<numCrds;i++){ //Generating Random Cards
        //To determine what colors the cards are assigned
        int x=rand()%5+1; //Between [1,5] to determine colors
        switch(x){
            case 1: color="Blue";break;
            case 2: color="Green";break;
            case 3: color="Red";break;
            case 4: color="Yellow";break;
            //If a 5 is generated, the card will have no color.
            //Moreover, it will be either a draw 1/2 or wild card.
            default:color="None";break;
        }
        if(color=="None"){
            int special=rand()%3; //Between [0,2] to determine if draw 1/2 or wild card.
            switch(special){
                case 0: strcpy(descr,"Wild Card");break;
                case 1: strcpy(descr,"Draw 1");break;
                case 2: strcpy(descr,"Draw 2");break;
            }
            cout<<"Card "<<i+1<<" = ["<<color<<" "<<descr<<"]"<<endl;
        }
        else{
            value=rand()%9+1; //Values Between [1,9]
            cout<<"Card "<<i+1<<" = ["<<color<<" "<<
                      static_cast<int>(value)<<"]"<<endl;
        }
    }
    //Display Inputs/Outputs
    cout<<"Printed "<<numCrds<<" Random Uno Card/s.";
    //Exit the Program - Cleanup
    return 0;
}