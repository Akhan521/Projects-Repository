/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on February 3, 2021, 10:00 PM
 * Purpose:  Using Files and Adding repetition-> LCR V.5 
 * File Input/Output + while loop reading + do-while structuring 
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting Library
#include <cstdlib>   //Rand # Generator
#include <ctime>     //Time set to seed
#include <fstream>   //File Library
using namespace std;

//User Libraries

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
void threeTrn(int [], bool &, float &);
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0))); //Set Random # Generator
    //Declare Variables
    fstream in;
    fstream out;
    char fn[] = "Num_Plyrs.dat";    //Character Array for filename Num_Plyrs
    string flnme = "Game_Stats.dat";//Will hold the winner and other stuff
    int numPlyrs;               //Number of players
    const int PLYRS = 3;
    int tknCntr[PLYRS]={3,3,3}; //Initialize all elements with 3 tokens
    //Validate File Input
    in.open(fn,ios::in);
    while(in>>numPlyrs){};      //Empty while loop to read in the file content
    (numPlyrs=numPlyrs==3?3:0); //For now, returns either 3 or 0 for # of players
    out.open(flnme,ios::out);
    //Display Outputs
    if(numPlyrs==3){ //Only play if there are 3 players
        bool win = false;  //Create a condition for the do-while
        float mean=0.0f;
        do{
        threeTrn(tknCntr, win, mean);
        }while(win==false);//Loop until a win occurs
        cout<< "The mean value rolled = "<< mean<<endl;
        //Displaying Winner using Nested Ternary Operator
        (tknCntr[0]>tknCntr[1]&&tknCntr[0]>tknCntr[2]?cout<<"Player 1 won with "<<tknCntr[0]<< " token/s!":
         tknCntr[1]>tknCntr[0]&&tknCntr[1]>tknCntr[2]?cout<<"Player 2 won with "<<tknCntr[1]<< " token/s!":
         cout<<"Player 3 won with "<<tknCntr[2]<<" token/s!");
        //Sending Info to file
        out<< "The mean value rolled = "<< mean<<endl;
        (tknCntr[0]>tknCntr[1]&&tknCntr[0]>tknCntr[2]?out<<"Player 1 won with "<<tknCntr[0]<< " token/s!":
         tknCntr[1]>tknCntr[0]&&tknCntr[1]>tknCntr[2]?out<<"Player 2 won with "<<tknCntr[1]<< " token/s!":
         out<<"Player 3 won with "<<tknCntr[2]<<" token/s!");
    }else cout<< "You need 3 Players.";
    //Exit the Program - Cleanup
    in.close();
    out.close();
    return 0;
}
void threeTrn(int tknCntr[], bool &win, float &mean){
    int tknLim = 3; //Token limit is 3 for when we check if we are above/below limit
    char die;
    int sum = 0; 
    float numDice = 0;
    mean = 0.0f;
    //Player 1's Turn
    cout << "Player 1's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[0]<tknLim){ //for when the counter goes below 3
        for (int count=1;count<=tknCntr[0];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            sum+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[0]--;tknCntr[1]++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCntr[0]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[0]--;tknCntr[2]++;}  //Token is given to the right or Player 3 
        }
    }else{ //for when the counter is 3 or more
        for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            sum+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[0]--;tknCntr[1]++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCntr[0]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[0]--;tknCntr[2]++;}  //Token is given to the right or Player 3 
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0){win = true;}
    if(win==false){
    //Player 2's Turn
    cout << "Player 2's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[1]<tknLim){ //for when the counter goes below 3
        for (int count=1;count<=tknCntr[1];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            sum+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[1]--;tknCntr[2]++;}      //Token is given to the left or Player 3
            else if (die==5) {tknCntr[1]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[1]--;tknCntr[0]++;} //Token is given to the right or Player 1
        }
    }else{ //for when the counter is 3 or more
        for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            sum+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[1]--;tknCntr[2]++;}      //Token is given to the left or Player 3
            else if (die==5) {tknCntr[1]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[1]--;tknCntr[0]++;} //Token is given to the right or Player 1
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0){win = true;}
    }
    if(win==false){
    //Player 3's Turn
    cout << "Player 3's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[2]<tknLim){ //for when the counter goes below 3
        for (int count=1;count<=tknCntr[2];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            sum+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[2]--;tknCntr[0]++;}      //Token is given to the left or Player 1
            else if (die==5) {tknCntr[2]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[2]--;tknCntr[1]++;} //Token is given to the right or Player 2 
        }
    }else{ //for when the counter is 3 or more
        for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            sum+=die;
            numDice++;
            cout << "Roll "<<count<< " = " << static_cast<int>(die)<<endl;
            if (die==4){tknCntr[2]--;tknCntr[0]++;}      //Token is given to the left or Player 1
            else if (die==5) {tknCntr[2]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[2]--;tknCntr[1]++;} //Token is given to the right or Player 2 
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0){win = true;}
    }
    mean = sum / numDice;
}