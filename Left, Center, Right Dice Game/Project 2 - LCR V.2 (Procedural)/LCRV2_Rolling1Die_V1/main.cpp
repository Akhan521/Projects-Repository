/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on February 2, 2021, 9:35 AM
 * Purpose:  Rolling a 6-sided die -> LCR V.1
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
    unsigned char max,min,die; //Max & Min # thrown and die rolled
    unsigned int count, numLps;//Counter to keep track of rolls and Loop control Var.
    unsigned int freq1,freq2,freq3,freq4,freq5,freq6; //# of times each value occurs
    //Initialize Variables
    die = rand()%6+1; //Range: [1,6]
    numLps = 360;      //36 loops
    max = min = die;  //Set starting point for comparisons
    freq1 = freq2 = freq3 = freq4 = freq5 = freq6 = 0; //Initialize frequencies
    //Map Inputs to Outputs -> Process
    for (count=1;count<=numLps;count++){
        die = rand()%6+1; //Range: [1,6]
        if (die < min)
            min = die; //Set die value as newest low
        if (die > max)
            max = die; //Set die value as newest high
        cout << "Roll #"<<count<< " = "<<static_cast<int>(die)<<endl;
        switch(die){
            case 1: freq1++; break;
            case 2: freq2++; break;
            case 3: freq3++; break;
            case 4: freq4++; break;
            case 5: freq5++; break;
            case 6: freq6++; break;
        }
    }
    //Display Inputs/Outputs
    cout << "Max # Thrown   = " << static_cast<int>(max)<<endl;
    cout << "Min # Thrown   = " << static_cast<int>(min)<<endl;
    cout << "Frequency of 1 = " << freq1<<endl;
    cout << "Frequency of 2 = " << freq2<<endl;
    cout << "Frequency of 3 = " << freq3<<endl;
    cout << "Frequency of 4 = " << freq4<<endl;
    cout << "Frequency of 5 = " << freq5<<endl;
    cout << "Frequency of 6 = " << freq6<<endl;
    //Exit the Program - Cleanup
    return 0;
}
