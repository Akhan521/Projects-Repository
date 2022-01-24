/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on February 3, 2021, 10:00 PM
 * Purpose:  Working Token Counters For 3 Players-> LCR V.3 
 *    (From LCR V.4 -> The first version of my LCR game)
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
    unsigned char die,freq4,freq5,freq6;             //Dices rolled by 3 players + # of times 4,5,6 rolled
    unsigned short tknCnt1,tknCnt2,tknCnt3,tknLim;   //Token counter for 3 players
    //Initialize Variables
    tknCnt1 = tknCnt2 = tknCnt3 = tknLim = 3; //Start with 3 tokens each
    //Display Outputs
    //Player 1's Turn
    cout << "Player 1's Turn: Press Enter to start rolling...\n";
    cin.get();
    if(tknCnt1<tknLim){ //for when the counter goes below 3
        for (int count=0;count<tknCnt1;count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCnt1--;tknCnt2++;freq4++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCnt1--;freq5++;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCnt1--;tknCnt3++;freq6++;}  //Token is given to the right or Player 3 
        }
    }else{ //for when the counter is 3 or more
        for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCnt1--;tknCnt2++;freq4++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCnt1--;freq5++;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCnt1--;tknCnt3++;freq6++;}  //Token is given to the right or Player 3 
        }
    }
    cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
    cout << "Player 2 Current Token Count = " << tknCnt2<<endl;
    cout << "Player 3 Current Token Count = " << tknCnt3<<endl;
    //Player 2's Turn
    cout << "Player 2's Turn: Press Enter to start rolling...\n";
    cin.get();
    if(tknCnt2<tknLim){ //for when the counter goes below 3
        for (int count=0;count<tknCnt2;count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCnt2--;tknCnt3++;freq4++;}      //Token is given to the left or Player 3
            else if (die==5) {tknCnt2--;freq5++;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCnt2--;tknCnt1++;freq6++;} //Token is given to the right or Player 1
        }
    }else{ //for when the counter is 3 or more
        for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCnt2--;tknCnt3++;freq4++;}      //Token is given to the left or Player 3
            else if (die==5) {tknCnt2--;freq5++;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCnt2--;tknCnt1++;freq6++;} //Token is given to the right or Player 1
        }
    }
    cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
    cout << "Player 2 Current Token Count = " << tknCnt2<<endl;
    cout << "Player 3 Current Token Count = " << tknCnt3<<endl;
    //Player 3's Turn
    cout << "Player 3's Turn: Press Enter to start rolling...\n";
    cin.get();
    if(tknCnt3<tknLim){ //for when the counter goes below 3
        for (int count=0;count<tknCnt3;count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCnt3--;tknCnt1++;freq4++;}      //Token is given to the left or Player 1
            else if (die==5) {tknCnt3--;freq5++;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCnt3--;tknCnt2++;freq6++;} //Token is given to the right or Player 2 
        }
    }else{ //for when the counter is 3 or more
        for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<(count+1)<< " = " << static_cast<int>(die)<<endl;
            if (die==4){tknCnt3--;tknCnt1++;freq4++;}      //Token is given to the left or Player 1
            else if (die==5) {tknCnt3--;freq5++;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCnt3--;tknCnt2++;freq6++;} //Token is given to the right or Player 2 
        }
    }
    cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
    cout << "Player 2 Current Token Count = " << tknCnt2<<endl;
    cout << "Player 3 Current Token Count = " << tknCnt3<<endl;
    cout << "Four appeared = "<<static_cast<int>(freq4)<< " times\n";
    cout << "Five appeared = "<<static_cast<int>(freq5)<< " times\n";
    cout << "Six appeared  = "<<static_cast<int>(freq6)<< " times\n";
    //Exit the Program - Cleanup
    return 0;
}
