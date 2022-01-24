/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on January 25, 2021, 3:00 PM
 * Purpose:  Token Counter For 1 Player -> LCR V.3
 *   Basic Idea using For Loop and Dependent Ifs 
 *   Taking into account when counter goes below 3 + some data on # of times 4,5,6 rolled
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
    unsigned char die,freq4,freq5,freq6;     //Dices rolled by player 1 & # of times 4,5,6 are rolled
    unsigned short tknCnt1,tknLim, numLps;   //Basic token counter for player 1 + loop control vars.
    //Initialize Variables
    numLps=10;
    for(int loop=1;loop<=numLps;loop++){ //Lets loop 10 times for player 1
        tknCnt1 = tknLim = 3; //Start with 3 tokens
        //Player 1's Turn
        cout << "Player 1's Turn: Press Enter to start rolling...\n";
        cin.get();
        if(tknCnt1<tknLim){ //for when the counter goes below 3
            for (int count=0;count<tknCnt1;count++){ //Either 2 or 1 rolls based on the # of tokens you have
                die = rand()%6+1; //Range: [1,6]
                cout << "Roll "<<(count+1)<< " = " << die<<endl;
                if (die==4){tknCnt1--;freq4++;}        //Token is given to the left or Player 2
                else if (die==5) {tknCnt1--;freq5++;}  //Token is placed in the center and is lost for good
                else if (die==6){tknCnt1--;freq6++;}   //Token is given to the right or Player 3 
            }
        }else{ //for when the counter is 3 or more
            for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
                die = rand()%6+1; //Range: [1,6]
                cout << "Roll "<<(count+1)<< " = " << static_cast<int>(die)<<endl;
                if (die==4){tknCnt1--;freq4++;}        //Token is given to the left or Player 2
                else if (die==5) {tknCnt1--;freq5++;}  //Token is placed in the center and is lost for good
                else if (die==6){tknCnt1--;freq6++;}   //Token is given to the right or Player 3 
            }   
        }
        cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
    }
    cout << "For " << numLps << " loops: \n";
    cout << "Four appeared = "<<static_cast<int>(freq4)<< " times\n";
    cout << "Five appeared = "<<static_cast<int>(freq5)<< " times\n";
    cout << "Six appeared  = "<<static_cast<int>(freq6)<< " times\n";
    cout << "Percentage of 4 out of Number of Throws: "<<(static_cast<float>(freq4)/numLps)*100<<"%"<<endl;
    cout << "Percentage of 5 out of Number of Throws: "<<(static_cast<float>(freq5)/numLps)*100<<"%"<<endl;
    cout << "Percentage of 6 out of Number of Throws: "<<(static_cast<float>(freq6)/numLps)*100<<"%";
    //Exit the Program - Cleanup
    return 0;
}
