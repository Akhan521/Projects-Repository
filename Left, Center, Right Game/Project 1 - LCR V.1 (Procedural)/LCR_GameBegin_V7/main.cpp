/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on January 26, 2021, 6:20 PM
 * Purpose:  Adding onto V.6- LCR V.7
 * Using a bool to continue repetitions as needed + testing for a win + switch cases
 * Replacing NumPlyrs with NumGmes -> Take the # of games as input, not players anymore
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting Library
#include <string>    //String Library
#include <fstream>   //File Library
#include <cstdlib>   //Rand # Generator
#include <ctime>     //Time set to seed
#include <cmath>     //Math Library
using namespace std;

//User Libraries

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays
const short PRCNT = 100;
//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));         //Set Random # Generator
    //Declare Variables
    fstream input;                                     //Input.open/close() functions
    fstream output;                                    //Output.open/close() functions
    unsigned char die;                                 //die Values rolled by each player
    unsigned short tknCnt1, tknCnt2, tknCnt3, tknLim;  //Token counters for players 1-3 and token limit
    unsigned short numGmes, p1Wins,p2Wins,p3Wins;      //# of games read from file and wins counter
    string fn = "Num_Games.dat";
    string flnme = "Game_Rules.txt", lines;            //File name and variable that will store the text
    char outName[] = "Game_Stats.dat";                 //Character Array for game stats
   
    //Open File
    input.open(flnme,ios::in);  //Open file for Rules
    while(getline(input,lines)){cout<<lines<<endl;}//while loop to read in and display the contents of the file
    input.close();
    input.open(fn,ios::in);
    while(input>>numGmes){};             //Empty while loop to read in the contents of the file
    (numGmes=numGmes<=4?numGmes:4);      //Only allowing games to be reach 4
    output.open(outName,ios::out);       //For when we do stats at the end
    //Initialize Variables
    p1Wins = p2Wins = p3Wins = 0;
    int beg = time(0);
    for(int game=1;game<=numGmes;game++){
        tknCnt1 = tknCnt2 = tknCnt3 = tknLim = 3; //Start with 3 tokens each
        bool win = false;                         //Initialize win with false for now
        int sum = 0;
        float mean = 0.0f, numDice = 0;
        //Map Inputs to Outputs -> Process
        do{
            //Player 1's Turn
            cout << "Player 1's Turn: Press Enter to start rolling...\n";
            cin.get();
            if(tknCnt1<tknLim){ //for when the counter goes below 3
                for (int count=1;count<=tknCnt1;count++){ //Either 2 or 1 rolls based on the # of tokens you have
                    die = rand()%6+1; //Range: [1,6]
                    sum+=die;
                    numDice++;
                    cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
                    if (die==4){tknCnt1--;tknCnt2++;}      //Token is given to the left or Player 2
                    else if (die==5) tknCnt1--;            //Token is placed in the center and is lost for good
                    else if (die==6){tknCnt1--;tknCnt3++;} //Token is given to the right or Player 3 
                }
            }else{ //for when the counter is 3 or more
                for (int count=1;count<=tknLim;count++){   //3 rolls for having 3 or more tokens
                    die = rand()%6+1; //Range: [1,6]
                    sum+=die;
                    numDice++;
                    cout << "Roll "<<count<< " = " << static_cast<int>(die)<<endl;
                    if (die==4){tknCnt1--;tknCnt2++;}      //Token is given to the left or Player 2
                    else if (die==5) tknCnt1--;            //Token is placed in the center and is lost for good
                    else if (die==6){tknCnt1--;tknCnt3++;} //Token is given to the right or Player 3 
                }
            }
            cout << "Player 1 Current Token Count = " << tknCnt1<<endl;
            cout << "Player 2 Current Token Count = " << tknCnt2<<endl;
            cout << "Player 3 Current Token Count = " << tknCnt3<<endl;
            if(tknCnt1>0&&tknCnt2==0&&tknCnt3==0){win = true;p1Wins++;}
            else if(tknCnt2>0&&tknCnt1==0&&tknCnt3==0){win = true;p2Wins++;}
            else if(tknCnt3>0&&tknCnt1==0&&tknCnt2==0){win = true;p3Wins++;}
            if(win==false){ //Independent if to see if win==false to continue turns
            //Player 2's Turn
            cout << "Player 2's Turn: Press Enter to start rolling...\n";
            cin.get();
            if(tknCnt2<tknLim){ //for when the counter goes below 3
                for (int count=1;count<=tknCnt2;count++){ //Either 2 or 1 rolls based on the # of tokens you have
                    die = rand()%6+1; //Range: [1,6]
                    sum+=die;
                    numDice++;
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
                    sum+=die;
                    numDice++;
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
            if(tknCnt1>0&&tknCnt2==0&&tknCnt3==0){win = true;p1Wins++;}
            else if(tknCnt2>0&&tknCnt1==0&&tknCnt3==0){win = true;p2Wins++;}
            else if(tknCnt3>0&&tknCnt1==0&&tknCnt2==0){win = true;p3Wins++;}
        }
        if (win==false){
            //Player 3's Turn
            cout << "Player 3's Turn: Press Enter to start rolling...\n";
            cin.get();
            if(tknCnt3<tknLim){ //for when the counter goes below 3
                for (int count=1;count<=tknCnt3;count++){ //Either 2 or 1 rolls based on the # of tokens you have
                    die = rand()%6+1; //Range: [1,6]
                    sum+=die;
                    numDice++;
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
                    sum+=die;
                    numDice++;
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
            if(tknCnt1>0&&tknCnt2==0&&tknCnt3==0){win = true;p1Wins++;}
            else if(tknCnt2>0&&tknCnt1==0&&tknCnt3==0){win = true;p2Wins++;}
            else if(tknCnt3>0&&tknCnt1==0&&tknCnt2==0){win = true;p3Wins++;}
        }
        }while(win==false);
        mean = sum / numDice;
        //Displaying Winner and some stats
        (tknCnt1>0&&tknCnt2==0&&tknCnt3==0?cout<<"Player 1 won with "<<tknCnt1<< " tokens!\n":
         tknCnt2>0&&tknCnt1==0&&tknCnt3==0?cout<<"Player 2 won with "<<tknCnt2<< " tokens!\n":
         tknCnt3>0&&tknCnt1==0&&tknCnt2==0?cout<<"Player 3 won with "<<tknCnt3<<" tokens!\n":
         cout<<"Error\n");
        cout<<setprecision(2)<<fixed;
        cout<<"Mean = "<<mean<<endl;
        //Send winners to the file
        (tknCnt1>0&&tknCnt2==0&&tknCnt3==0?output<<"Player 1 won with "<<tknCnt1<< " tokens!\n":
         tknCnt2>0&&tknCnt1==0&&tknCnt3==0?output<<"Player 2 won with "<<tknCnt2<< " tokens!\n":
         tknCnt3>0&&tknCnt1==0&&tknCnt2==0?output<<"Player 3 won with "<<tknCnt3<<" tokens!\n":
         output<<"Error\n");
        output<<"Mean = "<<mean<<endl;
    }
    int end = time(0);
    //Displaying some stats
    cout<<fixed<<setprecision(2)<<showpoint;
    cout<< "Time Elapsed for all games played: "<<end-beg<< " seconds"<<endl;
    cout<<"Number of Games Played: "<<numGmes<<endl;
    cout<<"Player 1 Percentage of Wins: "<<static_cast<float>(p1Wins)/numGmes*PRCNT<<"%"<<endl;
    cout<<"Player 2 Percentage of Wins: "<<static_cast<float>(p2Wins)/numGmes*PRCNT<<"%"<<endl;
    cout<<"Player 3 Percentage of Wins: "<<static_cast<float>(p3Wins)/numGmes*PRCNT<<"%"<<endl;
    cout<<"Number of Possible Combinations using 3 six-sided die: "<<pow(6,3);
    //Sending some stats to a file
    output<< "Time Elapsed for all games played: "<<end-beg<<" seconds"<< endl;
    output<<"Number of Games Played: "<<numGmes<<endl;
    output<<"Player 1 Percentage of Wins: "<<static_cast<float>(p1Wins)/numGmes*PRCNT<<"%"<<endl;
    output<<"Player 2 Percentage of Wins: "<<static_cast<float>(p2Wins)/numGmes*PRCNT<<"%"<<endl;
    output<<"Player 3 Percentage of Wins: "<<static_cast<float>(p3Wins)/numGmes*PRCNT<<"%"<<endl;
    output<<"Number of Possible Combinations using 3 six-sided die: "<<pow(6,3);
    //Exit the Program - Cleanup
    input.close();
    output.close();
    return 0;
}