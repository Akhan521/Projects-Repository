/* 
 * File:   main.cpp
 * Author: Aamir 
 * Created on April 11, 2021, 8:05 PM
 * Purpose: Generating Uno Cards Using a Rand # Generator 
 */

//System Libraries
#include <iostream>  //I/O Library
#include <ctime>   
#include <string>
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
    short numCrds=0;
    string color="";
    unsigned char value='0';
    //Initialize Variables
    cout<<"First Program of My Uno Project 1."<<endl;
    cout<<"How many cards do you want to generate [1-20]? ";
    cin>>numCrds;
    //A Ternary Op to limit cards generated.
    numCrds=(numCrds>20?20:numCrds);
    //Map Inputs to Outputs -> Process
    for(int i=0;i<numCrds;i++){ //Generating Random Cards
        value=rand()%9+1; //Values Between [1,9]
        //To determine what colors the cards are assigned
        int x=rand()%4+1; //Between [1,4] to determine colors
        switch(x){
            case 1: color="Blue";break;
            case 2: color="Green";break;
            case 3: color="Red";break;
            default:color="Yellow";break;
        }
        cout<<"Card "<<i+1<<" = ["<<color<<" "<<
                  static_cast<int>(value)<<"]"<<endl;
    }
    //Display Inputs/Outputs
    cout<<"Printed "<<numCrds<<" Random Uno Card/s.";
    //Exit the Program - Cleanup
    return 0;
}