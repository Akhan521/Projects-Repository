/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on January 26, 2021, 6:20 PM
 * Purpose:  Reworking + Adding onto V.5- LCR V.6
 * Using a bool to continue repetitions as needed + testing for a win + switch cases
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting Library
#include <fstream>   //File Library
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
    srand(static_cast<unsigned int>(time(0)));         //Set Random # Generator
    //Declare Variables
    fstream input;                                     //Input.open/close() functions
    unsigned char die;                                 //die Values rolled by each player
    unsigned short tknCnt1, tknCnt2, tknCnt3, tknLim;  //Token counters for players 1-3 and token limit
    unsigned short numPlyrs;                           //# of Players and games read from file
    string fn = "Num_Players.dat";
    string flnme = "Game_Rules.txt", lines;            //File name and variable that will store the text
    bool win = false;                                  //Initialize win with false for now
    //Open File
    input.open(flnme,ios::in);  //Open file for Rules
    while(getline(input,lines)){cout<<lines<<endl;}//while loop to read in and display the contents of the file
    input.close();
    while(input>>numPlyrs){};   //Empty while loop to read in the contents of the file
    (numPlyrs=numPlyrs==3?3:0); //Only allowing players to be 3 to play
    //Initialize Variables
    tknCnt1 = tknCnt2 = tknCnt3 = tknLim = 3; //Start with 3 tokens each
    //Map Inputs to Outputs -> Process
    if(numPlyrs==3){
    do{
        //Player 1's Turn
        cout << "Player 1's Turn: Press Enter to start rolling...\n";
        cin.get();
        if(tknCnt1<tknLim){ //for when the counter goes below 3
            for (int count=1;count<=tknCnt1;count++){ //Either 2 or 1 rolls based on the # of tokens you have
                die = rand()%6+1; //Range: [1,6]
                cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
                if (die==4){tknCnt1--;tknCnt2++;}      //Token is given to the left or Player 2
                else if (die==5) tknCnt1--;            //Token is placed in the center and is lost for good
                else if (die==6){tknCnt1--;tknCnt3++;} //Token is given to the right or Player 3 
            }
        }else{ //for when the counter is 3 or more
            for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
                die = rand()%6+1; //Range: [1,6]
                cout << "Roll "<<count<< " = " << static_cast<int>(die)<<endl;
                if (die==4){tknCnt1--;tknCnt2++;}      //Token is given to the left or Player 2
                else if (die==5) tknCnt1--;            //Token is placed in the center and is lost for good
                else if (die==6){tknCnt1--;tknCnt3++;} //Token is given to the right or Player 3 
            }
        }
        cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
        cout << "Player 2 Current Token Count = " << tknCnt2<<endl;
        cout << "Player 3 Current Token Count = " << tknCnt3<<endl;
        if(tknCnt1>0&&tknCnt2==0&&tknCnt3==0){win = true;}
        else if(tknCnt2>0&&tknCnt1==0&&tknCnt3==0){win = true;}
        else if(tknCnt3>0&&tknCnt1==0&&tknCnt2==0){win = true;}
        if(win==false){ //Independent if to see if win==false to continue turns
            //Player 2's Turn
            cout << "Player 2's Turn: Press Enter to start rolling...\n";
            cin.get();
            if(tknCnt2<tknLim){ //for when the counter goes below 3
                for (int count=1;count<=tknCnt2;count++){ //Either 2 or 1 rolls based on the # of tokens you have
                    die = rand()%6+1; //Range: [1,6]
                    cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
                    switch(die){
                        case 4:tknCnt2--;tknCnt3++;break;//Token is given to the left or Player 3
                        case 5:tknCnt2--;break;          //Token is placed in the center and is lost for good
                        case 6:tknCnt2--;tknCnt1++;break;//Token is given to the right or Player 1
                    }    
                }
            }else{ //for when the counter is 3 or more
                for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
                    die = rand()%6+1; //Range: [1,6]
                    cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
                    switch(die){
                        case 4:tknCnt2--;tknCnt3++;break;//Token is given to the left or Player 3
                        case 5:tknCnt2--;break;          //Token is placed in the center and is lost for good
                        case 6:tknCnt2--;tknCnt1++;break;//Token is given to the right or Player 1
                    }
                }
            }
            cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
            cout << "Player 2 Current Token Count = " << tknCnt2<<endl;
            cout << "Player 3 Current Token Count = " << tknCnt3<<endl;
            if(tknCnt1>0&&tknCnt2==0&&tknCnt3==0){win = true;}
            else if(tknCnt2>0&&tknCnt1==0&&tknCnt3==0){win = true;}
            else if(tknCnt3>0&&tknCnt1==0&&tknCnt2==0){win = true;}
        }
        if (win==false){
            //Player 3's Turn
            cout << "Player 3's Turn: Press Enter to start rolling...\n";
            cin.get();
            if(tknCnt3<tknLim){ //for when the counter goes below 3
                for (int count=1;count<=tknCnt3;count++){ //Either 2 or 1 rolls based on the # of tokens you have
                    die = rand()%6+1; //Range: [1,6]
                    cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
                    switch(die){
                        case 4:tknCnt3--;tknCnt1++;break;//Token is given to the left or Player 1
                        case 5:tknCnt3--;break;          //Token is placed in the center and is lost for good
                        case 6:tknCnt3--;tknCnt2++;break;//Token is given to the right or Player 2 
                    }
                }
            }else{ //for when the counter is 3 or more
                for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
                    die = rand()%6+1; //Range: [1,6]
                    cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
                    switch(die){
                        case 4:tknCnt3--;tknCnt1++;break;//Token is given to the left or Player 1
                        case 5:tknCnt3--;break;          //Token is placed in the center and is lost for good
                        case 6:tknCnt3--;tknCnt2++;break;//Token is given to the right or Player 2 
                    }
                }
            }
            cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
            cout << "Player 2 Current Token Count = " << tknCnt2<<endl;
            cout << "Player 3 Current Token Count = " << tknCnt3<<endl;
            if(tknCnt1>0&&tknCnt2==0&&tknCnt3==0){win = true;}
            else if(tknCnt2>0&&tknCnt1==0&&tknCnt3==0){win = true;}
            else if(tknCnt3>0&&tknCnt1==0&&tknCnt2==0){win = true;}
        }
    }while(win==false);
    }
    //Displaying Winner 
    (tknCnt1>tknCnt2&&tknCnt1>tknCnt3?cout<<"Player 1 won with "<<tknCnt1<< " tokens!":
     tknCnt2>tknCnt1&&tknCnt2>tknCnt3?cout<<"Player 2 won with "<<tknCnt2<< " tokens!":
     cout<<"Player 3 won with "<<tknCnt3<<" tokens!");
    //Exit the Program - Cleanup
    input.close();
    return 0;
}