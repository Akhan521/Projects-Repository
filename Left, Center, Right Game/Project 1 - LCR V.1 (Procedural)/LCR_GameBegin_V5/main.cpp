/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on January 26, 2021, 3:00 PM
 * Purpose:  Reading Files-> LCR V.5
 * Reading a file, while loop/validating file content, and adding some repetition
 * Also adding text in between the lines
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting Library
#include <fstream>
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
    fstream input;
    unsigned char die;                               //Dices rolled by 3 players
    unsigned short tknCnt1,tknCnt2,tknCnt3,tknLim;   //Token counter for 3 players and loop control var.
    unsigned short numPlyrs;                         //# of Players read from file
    string fn = "Num_Players.dat";                   //File name for # of players
    string flnme = "Game_Rules.txt", lines;          //File name and variable that will store the text
    //Initialize Variables
    tknCnt1 = tknCnt2 = tknCnt3 = tknLim = 3; //Start with 3 tokens each
    input.open(flnme,ios::in);
    while(getline(input,lines)){cout<<lines<<endl;}//while loop to read in and display the contents of the file
    input.close();
    input.open(fn,ios::in);
    while(input>>numPlyrs){};   //Empty while loop to read in the contents of the file
    (numPlyrs=numPlyrs==3?3:0); //Only allowing players to be 3 to play
    if(numPlyrs==3){
        do{
            //Player 1's Turn
            cout << "Player 1's Turn: Press Enter to start rolling...\n";
            cin.get();
            if(tknCnt1<tknLim){ //for when the counter goes below 3
                for (int count=0;count<tknCnt1;count++){ //Either 2 or 1 rolls based on the # of tokens you have
                    die = rand()%6+1; //Range: [1,6]
                    cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
                    if (die==4){tknCnt1--;tknCnt2++;}      //Token is given to the left or Player 2
                    else if (die==5) tknCnt1--;            //Token is placed in the center and is lost for good
                    else if (die==6){tknCnt1--;tknCnt3++;} //Token is given to the right or Player 3 
                }
            }else{ //for when the counter is 3 or more
                for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
                    die = rand()%6+1; //Range: [1,6]
                    cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
                    if (die==4){tknCnt1--;tknCnt2++;}      //Token is given to the left or Player 2
                    else if (die==5) tknCnt1--;            //Token is placed in the center and is lost for good
                    else if (die==6){tknCnt1--;tknCnt3++;} //Token is given to the right or Player 3 
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
                    if (die==4){tknCnt2--;tknCnt3++;}      //Token is given to the left or Player 3
                    else if (die==5) tknCnt2--;            //Token is placed in the center and is lost for good
                    else if (die==6){tknCnt2--;tknCnt1++;} //Token is given to the right or Player 1
                }
            }else{ //for when the counter is 3 or more
                for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
                    die = rand()%6+1; //Range: [1,6]
                    cout << "Roll "<<(count+1)<< " = " <<static_cast<int>(die)<<endl;
                    if (die==4){tknCnt2--;tknCnt3++;}      //Token is given to the left or Player 3
                    else if (die==5) tknCnt2--;            //Token is placed in the center and is lost for good
                    else if (die==6){tknCnt2--;tknCnt1++;} //Token is given to the right or Player 1 
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
                    if (die==4){tknCnt3--;tknCnt1++;}      //Token is given to the left or Player 1
                    else if (die==5) tknCnt3--;            //Token is placed in the center and is lost for good
                    else if (die==6){tknCnt3--;tknCnt2++;} //Token is given to the right or Player 2 
                }
            }else{ //for when the counter is 3 or more
                for (int count=0;count<tknLim;count++){ //3 rolls for having 3 or more tokens
                    die = rand()%6+1; //Range: [1,6]
                    cout << "Roll "<<(count+1)<< " = " << static_cast<int>(die)<<endl;
                    if (die==4){tknCnt3--;tknCnt1++;}      //Token is given to the left or Player 1
                    else if (die==5) tknCnt3--;            //Token is placed in the center and is lost for good
                    else if (die==6){tknCnt3--;tknCnt2++;} //Token is given to the right or Player 2 
                }
            }
            cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
            cout << "Player 2 Current Token Count = " << tknCnt2<<endl;
            cout << "Player 3 Current Token Count = " << tknCnt3<<endl;
        }while(tknCnt1!=0); //Do while to add repetition, but I'll be adding a condition later
    }
    //Exit the Program - Cleanup
    input.close();
    return 0;
}
