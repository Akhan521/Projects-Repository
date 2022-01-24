/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on January 25, 2021, 3:00 PM
 * Purpose:  Rolling 3 6-sided die -> LCR V.2
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting Library
#include <cstdlib>   //Rand # Generator
#include <ctime>     //Time set to seed
using namespace std;

//User Libraries

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0))); //Set Random # Generator
    //Declare Variables
    unsigned char max,min,die1,die2,die3, sum; //Max & Min # thrown and die rolled
    unsigned int count, numLps;//Counter to keep track of rolls and Loop control Var.
    unsigned int freq1,freq2,freq3,freq4,freq5,freq6,
                 freq7,freq8,freq9,freq10,freq11,freq12,
                 freq13,freq14,freq15,freq16,freq17,freq18;//# of times each value occurs
    //Initialize Variables
    sum = (rand()%6+1) + (rand()%6+1) + (rand()%6+1) ; //Range: [3,18]
    numLps = 2160;      //2160 loops (There are 216 possible combinations -> 6*6*6)
    max = min = sum;    //Set starting point for comparisons
    freq1 = freq2 = freq3 = freq4 = freq5 = freq6 = 0; //Initialize frequencies
    freq7 = freq8 = freq9 = freq10 = freq11 = freq12 = 0;
    freq13 = freq14 = freq15 = freq16 = freq17 = freq18 = 0;
    //Map Inputs to Outputs -> Process
    for (count=1;count<=numLps;count++){
        die1 = rand()%6+1; //Range: [1,6]
        die2 = rand()%6+1; //Range: [1,6]
        die3 = rand()%6+1; //Range: [1,6]
        sum = die1 + die2 + die3;
        if (sum < min)
            min = sum; //Set die values as newest low
        if (sum > max)
            max = sum; //Set die values as newest high
        //cout << "Roll #"<<count<< " Die 1 = "<<static_cast<int>(die1)<<endl;
        //cout << "Roll #"<<count<< " Die 2 = "<<static_cast<int>(die2)<<endl;
        //cout << "Roll #"<<count<< " Die 3 = "<<static_cast<int>(die3)<<endl;
        switch(die1){
            case 3: freq3++; break;
            case 4: freq4++; break;
            case 5: freq5++; break;
            case 6: freq6++; break;
            case 7: freq7++; break;
            case 8: freq8++; break;
            case 9: freq9++; break;
            case 10: freq10++; break;
            case 11: freq11++; break;
            case 12: freq12++; break;
            case 13: freq13++; break;
            case 14: freq14++; break;
            case 15: freq15++; break;
            case 16: freq16++; break;
            case 17: freq17++; break;
            case 18: freq18++; break;
        }
        switch(die2){
            case 3: freq3++; break;
            case 4: freq4++; break;
            case 5: freq5++; break;
            case 6: freq6++; break;
            case 7: freq7++; break;
            case 8: freq8++; break;
            case 9: freq9++; break;
            case 10: freq10++; break;
            case 11: freq11++; break;
            case 12: freq12++; break;
            case 13: freq13++; break;
            case 14: freq14++; break;
            case 15: freq15++; break;
            case 16: freq16++; break;
            case 17: freq17++; break;
            case 18: freq18++; break;
        }
        switch(die3){
            case 3: freq3++; break;
            case 4: freq4++; break;
            case 5: freq5++; break;
            case 6: freq6++; break;
            case 7: freq7++; break;
            case 8: freq8++; break;
            case 9: freq9++; break;
            case 10: freq10++; break;
            case 11: freq11++; break;
            case 12: freq12++; break;
            case 13: freq13++; break;
            case 14: freq14++; break;
            case 15: freq15++; break;
            case 16: freq16++; break;
            case 17: freq17++; break;
            case 18: freq18++; break;
        }
    }
    //Display Inputs/Outputs
    cout << "Max # Thrown    = " << static_cast<int>(max)<<endl;
    cout << "Min # Thrown    = " << static_cast<int>(min)<<endl;
    cout << "Frequency of 3  = " << freq3<<endl;
    cout << "Frequency of 4  = " << freq4<<endl;
    cout << "Frequency of 5  = " << freq5<<endl;
    cout << "Frequency of 6  = " << freq6<<endl;
    cout << "Frequency of 7  = " << freq7<<endl;
    cout << "Frequency of 8  = " << freq8<<endl;
    cout << "Frequency of 9  = " << freq9<<endl;
    cout << "Frequency of 10 = " << freq10<<endl;
    cout << "Frequency of 11 = " << freq11<<endl;
    cout << "Frequency of 12 = " << freq12<<endl;
    cout << "Frequency of 13 = " << freq13<<endl;
    cout << "Frequency of 14 = " << freq14<<endl;
    cout << "Frequency of 15 = " << freq15<<endl;
    cout << "Frequency of 16 = " << freq16<<endl;
    cout << "Frequency of 17 = " << freq17<<endl;
    cout << "Frequency of 18 = " << freq18<<endl;
    //Exit the Program - Cleanup
    return 0;
}
