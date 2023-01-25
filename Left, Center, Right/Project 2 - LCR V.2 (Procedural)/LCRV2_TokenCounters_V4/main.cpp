/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on February 3, 2021, 10:00 PM
 * Purpose:  Working Token Counters For 3 Players-> LCR V.4 
 * Putting the prev. vers. into a function and using an array for counters
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
void threeTrn(int []);
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0))); //Set Random # Generator
    //Declare Variables
    const int PLYRS = 3;
    int tknCntr[PLYRS]={3,3,3}; //Initialize all elements with 3 tokens
    //Initialize Variables
    
    //Display Outputs
    threeTrn(tknCntr);
    //Exit the Program - Cleanup
    return 0;
}
void threeTrn(int tknCntr[]){
    int tknLim = 3; //Token limit is 3 for when we check if we are above/below limit
    char die;
    //Player 1's Turn
    cout << "Player 1's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[0]<tknLim){ //for when the counter goes below 3
        for (int count=0;count<tknCntr[0];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[0]--;tknCntr[1]++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCntr[0]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[0]--;tknCntr[2]++;}  //Token is given to the right or Player 3 
        }
    }else{ //for when the counter is 3 or more
        for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[0]--;tknCntr[1]++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCntr[0]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[0]--;tknCntr[2]++;}  //Token is given to the right or Player 3 
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl<<endl;
    //Player 2's Turn
    cout << "Player 2's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[1]<tknLim){ //for when the counter goes below 3
        for (int count=0;count<tknCntr[1];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[1]--;tknCntr[2]++;}      //Token is given to the left or Player 3
            else if (die==5) {tknCntr[1]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[1]--;tknCntr[0]++;} //Token is given to the right or Player 1
        }
    }else{ //for when the counter is 3 or more
        for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[1]--;tknCntr[2]++;}      //Token is given to the left or Player 3
            else if (die==5) {tknCntr[1]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[1]--;tknCntr[0]++;} //Token is given to the right or Player 1
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl<<endl;
    //Player 3's Turn
    cout << "Player 3's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[2]<tknLim){ //for when the counter goes below 3
        for (int count=0;count<tknCntr[2];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[2]--;tknCntr[0]++;}      //Token is given to the left or Player 1
            else if (die==5) {tknCntr[2]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[2]--;tknCntr[1]++;} //Token is given to the right or Player 2 
        }
    }else{ //for when the counter is 3 or more
        for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " << static_cast<int>(die)<<endl;
            if (die==4){tknCntr[2]--;tknCntr[0]++;}      //Token is given to the left or Player 1
            else if (die==5) {tknCntr[2]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[2]--;tknCntr[1]++;} //Token is given to the right or Player 2 
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl<<endl;
}