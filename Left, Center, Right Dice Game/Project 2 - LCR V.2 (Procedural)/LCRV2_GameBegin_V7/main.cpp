/* 
 * File:   main.cpp
 * Author: Aamir
 * Created on February 6, 2021, 1:00 PM
 * Purpose: Searching, Sorting, and a 5 player function-> LCR V.7
 * Linear searching + 2 diff sort funcs + another function for 5 players + defaulted args and more
 */

//System Libraries
#include <iostream>  //I/O Library
#include <iomanip>   //Formatting Library
#include <string>
#include <cstdlib>   //Rand # Generator
#include <ctime>     //Time set to seed
#include <cmath>
#include <fstream>   //File Library
using namespace std;

//User Libraries

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
void threeTrn(int [],bool &, float &, int &); //3 player turn func
void fiveTrn (int [],bool &, int &, int &);   //5 player turn func
void bublSrt (int [],int = 3);                //Bubble Sort
void selcSrt (int [],int = 5);                //Selection Sort
void cpyLst  (int [],int [], int);            //Copies the contents of first list to second (used for sorting)
void rnking3 (int [],int [], int = 3);        //Displays rankings for 3 players
void rnking5 (int [],int [], int = 5);        //Displays rankings for 5 players
bool linSrch (int [],int, int);               //Linear Search
 int srchVal ();                              //Prompts for a value to search for
void dsply(fstream &, int [], int, float, int);//overloaded function for displaying info (mean is a float)
void dsply(fstream &, int [], int, int, int);  //overloaded function for displaying info (mean is an int)
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0))); //Set Random # Generator
    //Declare Variables
    fstream in;
    fstream out;
    char fn[] = "Num_Plyrs.dat";    //Character Array for filename Num_Plyrs
    string flnme = "Game_Stats.dat";//Will hold the winner and other stuff
    int numPlyrs;                   //Number of players
    //Validate File Input
    in.open(fn,ios::in);
    while(in>>numPlyrs){};                 //Empty while loop to read in the file content
    (numPlyrs==3||numPlyrs==5?numPlyrs:0); //Accepts 3 players or 5 and nothing else
    out.open(flnme,ios::out);
    //Display Outputs
    for(int game=1;game<=2;game++){ //Play 2 games
    if(numPlyrs==3){ //play if there are 3 players
        const int PLYRS = 3;
        int tknCntr[PLYRS]={3,3,3}; //Initialize all elements with 3 tokens
        int plcings[PLYRS]={};      //Sorted Placings after each round (Copy of the Prev. list)
        int numDice = 0;   //Number of dice rolled throughout game
        bool win = false;  //Create a condition for the do-while
        float mean = 0.0f, //Holds the mean as a float 
              val;         //Value to search for in the list of token counters after game ends
        int beg = time(0);
        do{
        threeTrn(tknCntr, win, mean,numDice);
        cpyLst(tknCntr,plcings,PLYRS);
        bublSrt(plcings,PLYRS);
        cout<<"Ranking after round:\n";
        rnking3(plcings,tknCntr,PLYRS);
        cout<<endl;
        }while(win==false);//Loop until a win occurs
        int end = time(0);
        cout<<"Number of possible combinations: "<<pow(6,3)<<endl;
        out<<"Number of possible combinations: "<<pow(6,3)<<endl;
        cout<<"Time Elapsed in Seconds: "<<end-beg<<endl;
        out<<"Time Elapsed in Seconds: "<<end-beg<<endl;
        dsply(out,tknCntr,PLYRS,mean,numDice);
        cin.ignore();
    }else if(numPlyrs==5){ //Play with 5 players
        const int PLYRS = 5;
        int tknCntr[PLYRS]={3,3,3,3,3}; //Initialize all elements with 3 tokens
        int plcings[PLYRS]={};          //Sorted Placings after each round (Copy of the Prev. list)
        int numDice = 0;   //Number of dice rolled throughout game
        bool win = false;  //Create a condition for the do-while
        int mean = 0,      //It has to be a whole number because you can't have half a dice or the like
            val;           //Value to search for in the list of token counters after game ends
        int beg = time(0);
        do{
        fiveTrn(tknCntr,win,mean,numDice);
        cpyLst(tknCntr,plcings,PLYRS);
        selcSrt(plcings,PLYRS);
        cout<<"Ranking after round:\n";
        rnking5(plcings,tknCntr,PLYRS);
        cout<<endl;
        }while(win==false);//Loop until a win occurs
        int end = time(0);
        cout<<"Number of possible combinations: "<<pow(6,3)<<endl;
        out<<"Number of possible combinations: "<<pow(6,3)<<endl;
        cout<<"Time Elapsed in Seconds: "<<end-beg<<endl;
        out<<"Time Elapsed in Seconds: "<<end-beg<<endl;
        dsply(out,tknCntr,PLYRS,mean,numDice);
        cin.ignore();
    }
    else cout<< "You need either 3 or 5 Players.\n";
    }
    //Exit the Program - Cleanup
    in.close();
    out.close();
    return 0;
}
void threeTrn(int tknCntr[], bool &win, float &mean, int &numDice){
    int tknLim=3; //Token limit is 3 for when we check if we are above/below limit
    char die; 
    if(tknCntr[0]!=0){
    //Player 1's Turn
    cout << "Player 1's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[0]<tknLim){ //for when the counter goes below 3
        for (int count=1;count<=tknCntr[0];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            mean+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            if (die==4){tknCntr[0]--;tknCntr[1]++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCntr[0]--;}          //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[0]--;tknCntr[2]++;}  //Token is given to the right or Player 3 
        }
    }else{ //for when the counter is 3 or more
        for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            mean+=die;
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
    }
    if(tknCntr[1]!=0){
    if(win==false){
    //Player 2's Turn
    cout << "Player 2's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[1]<tknLim){ //for when the counter goes below 3
        for (int count=1;count<=tknCntr[1];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            mean+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            switch(die){
                case 4:tknCntr[1]--;tknCntr[2]++;break; //Token is given to the left or Player 3
                case 5:tknCntr[1]--;break;              //Token is placed in the center and is lost for good
                case 6:tknCntr[1]--;tknCntr[0]++;break; //Token is given to the right or Player 1
            }
            }
    }else{ //for when the counter is 3 or more
        for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            mean+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            switch(die){
                case 4:tknCntr[1]--;tknCntr[2]++;break; //Token is given to the left or Player 3
                case 5:tknCntr[1]--;break;              //Token is placed in the center and is lost for good
                case 6:tknCntr[1]--;tknCntr[0]++;break; //Token is given to the right or Player 1
            }
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0){win = true;}
    }
    }
    if(tknCntr[2]!=0){
    if(win==false){
    //Player 3's Turn
    cout << "Player 3's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[2]<tknLim){ //for when the counter goes below 3
        for (int count=1;count<=tknCntr[2];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            mean+=die;
            numDice++;
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            switch(die){
                case 4:tknCntr[2]--;tknCntr[0]++;break; //Token is given to the left or Player 1
                case 5:tknCntr[2]--;break;              //Token is placed in the center and is lost for good
                case 6:tknCntr[2]--;tknCntr[1]++;break; //Token is given to the right or Player 2 
            }
        }
    }else{ //for when the counter is 3 or more
        for (int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            mean+=die;
            numDice++;
            cout << "Roll "<<count<< " = " << static_cast<int>(die)<<endl;
            switch(die){
                case 4:tknCntr[2]--;tknCntr[0]++;break;  //Token is given to the left or Player 1
                case 5:tknCntr[2]--;break;               //Token is placed in the center and is lost for good
                case 6:tknCntr[2]--;tknCntr[1]++;break;  //Token is given to the right or Player 2 
            }
        }
        }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0){win = true;}
    }
    }
}
void fiveTrn(int tknCntr[], bool &win, int &mean, int &numDice){
    int tknLim=3; //Token limit is 3 for when we check if we are above/below limit
    char die; 
    if(tknCntr[0]!=0){
    //Player 1's Turn
    cout << "Player 1's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[0]<tknLim){ //for when the counter goes below 3
        for(int count=1;count<=tknCntr[0];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            if (die==4){tknCntr[0]--;tknCntr[1]++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCntr[0]--;}             //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[0]--;tknCntr[4]++;} //Token is given to the right or Player 5 
        }
    }else{//for when the counter is 3 or more
        for(int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            if (die==4){tknCntr[0]--;tknCntr[1]++;}      //Token is given to the left or Player 2
            else if (die==5) {tknCntr[0]--;}             //Token is placed in the center and is lost for good
            else if (die==6){tknCntr[0]--;tknCntr[4]++;} //Token is given to the right or Player 5 
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl;
    cout << "Player 4 Current Token Count = " << tknCntr[3]<<endl;
    cout << "Player 5 Current Token Count = " << tknCntr[4]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[3]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[4]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0){win = true;}
    }
    if(win==false){
    if(tknCntr[1]!=0){
    //Player 2's Turn
    cout << "Player 2's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[1]<tknLim){ //for when the counter goes below 3
        for(int count=1;count<=tknCntr[1];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            switch(die){
                case 4:tknCntr[1]--;tknCntr[2]++;break; //Token is given to the left or Player 3
                case 5:tknCntr[1]--;break;              //Token is placed in the center and is lost for good
                case 6:tknCntr[1]--;tknCntr[0]++;break; //Token is given to the right or Player 1
            }
            }
    }else{//for when the counter is 3 or more
        for(int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            switch(die){
                case 4:tknCntr[1]--;tknCntr[2]++;break; //Token is given to the left or Player 3
                case 5:tknCntr[1]--;break;              //Token is placed in the center and is lost for good
                case 6:tknCntr[1]--;tknCntr[0]++;break; //Token is given to the right or Player 1
            }
        }
    }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl;
    cout << "Player 4 Current Token Count = " << tknCntr[3]<<endl;
    cout << "Player 5 Current Token Count = " << tknCntr[4]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[3]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[4]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0){win = true;}
    }
    }
    if(win==false){
    if(tknCntr[2]!=0){
    //Player 3's Turn
    cout << "Player 3's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[2]<tknLim){ //for when the counter goes below 3
        for(int count=1;count<=tknCntr[2];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            switch(die){
                case 4:tknCntr[2]--;tknCntr[3]++;break; //Token is given to the left or Player 4
                case 5:tknCntr[2]--;break;              //Token is placed in the center and is lost for good
                case 6:tknCntr[2]--;tknCntr[1]++;break; //Token is given to the right or Player 2 
            }
        }
    }else{//for when the counter is 3 or more
        for(int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " << static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            switch(die){
                case 4:tknCntr[2]--;tknCntr[3]++;break;  //Token is given to the left or Player 4
                case 5:tknCntr[2]--;break;               //Token is placed in the center and is lost for good
                case 6:tknCntr[2]--;tknCntr[1]++;break;  //Token is given to the right or Player 2 
            }
        }
        }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl;
    cout << "Player 4 Current Token Count = " << tknCntr[3]<<endl;
    cout << "Player 5 Current Token Count = " << tknCntr[4]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[3]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[4]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0){win = true;}
    }
    }
    if(win==false){
    if(tknCntr[3]!=0){
    //Player 4's Turn
    cout << "Player 4's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[3]<tknLim){ //for when the counter goes below 3
        for(int count=1;count<=tknCntr[3];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            switch(die){
                case 4:tknCntr[3]--;tknCntr[4]++;break; //Token is given to the left or Player 5
                case 5:tknCntr[3]--;break;              //Token is placed in the center and is lost for good
                case 6:tknCntr[3]--;tknCntr[2]++;break; //Token is given to the right or Player 3 
            }
        }
    }else{//for when the counter is 3 or more
        for(int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " << static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            switch(die){
                case 4:tknCntr[3]--;tknCntr[4]++;break;  //Token is given to the left or Player 5
                case 5:tknCntr[3]--;break;               //Token is placed in the center and is lost for good
                case 6:tknCntr[3]--;tknCntr[2]++;break;  //Token is given to the right or Player 3 
            }
        }
        }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl;
    cout << "Player 4 Current Token Count = " << tknCntr[3]<<endl;
    cout << "Player 5 Current Token Count = " << tknCntr[4]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[3]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[4]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0){win = true;}
    }
    }
    if(win==false){
    if(tknCntr[4]!=0){
    //Player 5's Turn
    cout << "Player 5's Turn: Press Enter to start rolling...";
    cin.get();
    if(tknCntr[4]<tknLim){ //for when the counter goes below 3
        for(int count=1;count<=tknCntr[4];count++){ //Either 2 or 1 rolls based on the # of tokens you have
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " <<static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            switch(die){
                case 4:tknCntr[4]--;tknCntr[0]++;break; //Token is given to the left or Player 1
                case 5:tknCntr[4]--;break;              //Token is placed in the center and is lost for good
                case 6:tknCntr[4]--;tknCntr[3]++;break; //Token is given to the right or Player 4 
            }
        }
    }else{//for when the counter is 3 or more
        for(int count=1;count<=tknLim;count++){ //3 rolls for having 3 or more tokens
            die = rand()%6+1; //Range: [1,6]
            cout << "Roll "<<count<< " = " << static_cast<int>(die)<<endl;
            mean+=die;
            numDice++;
            switch(die){
                case 4:tknCntr[4]--;tknCntr[0]++;break;  //Token is given to the left or Player 1
                case 5:tknCntr[4]--;break;               //Token is placed in the center and is lost for good
                case 6:tknCntr[4]--;tknCntr[3]++;break;  //Token is given to the right or Player 4 
            }
        }
        }
    cout << "Player 1 Current Token Count = " << tknCntr[0]<<endl;
    cout << "Player 2 Current Token Count = " << tknCntr[1]<<endl;
    cout << "Player 3 Current Token Count = " << tknCntr[2]<<endl;
    cout << "Player 4 Current Token Count = " << tknCntr[3]<<endl;
    cout << "Player 5 Current Token Count = " << tknCntr[4]<<endl<<endl;
    if(tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[3]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[3]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[4]==0){win = true;}
    else if(tknCntr[4]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0){win = true;}
    }
    }
}
void bublSrt(int a[],int n){
    bool swap;
    do{
        swap=false;
        for(int i=0;i<n-1;i++){    //Loop to swap with first in List
            if(a[i]<a[i+1]){       //Put the largest at top of List
                a[i]=a[i]^a[i+1];  //In place Swap
                a[i+1]=a[i]^a[i+1];//In place Swap
                a[i]=a[i]^a[i+1];  //In place Swap
                swap=true;
            }
        }
    }while(swap);
}
void selcSrt(int a[],int n){
    for(int i=0;i<n-1;i++){      //Loop for each position in List
        int mindex=i;
        for(int j=i+1;j<n;j++){  //Loop to swap with first in List
            if(a[mindex]<a[j]){  //Put the largest at top of List
                mindex=j;
            }
        }
        int temp=a[i];
        a[i]=a[mindex];
        a[mindex]=temp;
    }
}
void cpyLst(int a[], int b[], int n){
    for(int i=0;i<n;i++){
        b[i]=a[i];
    }
}
//For comparing the token cntrs and sorted plcings list and displaying appropriate players
void rnking3(int a[], int b[], int n){
    for(int i=0;i<n;i++){
        if(a[i]==b[0]&&a[i]==b[1]&&a[i]==b[2])cout<<"Player 1,2,& 3: ";
        else if(a[i]==b[1]&&a[i]==b[2])cout<<"Player 2 & 3: ";
        else if(a[i]==b[0]&&a[i]==b[2])cout<<"Player 1 & 3: ";
        else if(a[i]==b[0]&&a[i]==b[1])cout<<"Player 1 & 2: ";
        else if(a[i]==b[0])cout<<"Player 1: ";
        else if(a[i]==b[1])cout<<"Player 2: ";
        else cout<<"Player 3: ";
        cout<<a[i]<<" token/s" <<endl;
        }
}
//For comparing the token cntrs and sorted plcings list and displaying appropriate players
void rnking5(int a[], int b[], int n){
    for(int i=0;i<n;i++){
        if(a[i]==b[0]&&a[i]==b[1]&&a[i]==b[2]&&a[i]==b[3]&&a[i]==b[4])cout<<"Player 1,2,3,4,& 5: ";
        else if(a[i]==b[0]&&a[i]==b[2]&&a[i]==b[3]&&a[i]==b[4])cout<<"Player 1,3,4,& 5: ";
        else if(a[i]==b[1]&&a[i]==b[2]&&a[i]==b[3]&&a[i]==b[4])cout<<"Player 2,3,4,& 5: ";
        else if(a[i]==b[0]&&a[i]==b[1]&&a[i]==b[2]&&a[i]==b[3])cout<<"Player 1,2,3,& 4: ";
        else if(a[i]==b[0]&&a[i]==b[1]&&a[i]==b[2]&&a[i]==b[4])cout<<"Player 1,2,3,& 5: ";
        else if(a[i]==b[0]&&a[i]==b[1]&&a[i]==b[3]&&a[i]==b[4])cout<<"Player 1,2,4,& 5: ";
        else if(a[i]==b[1]&&a[i]==b[2]&&a[i]==b[3])cout<<"Player 2,3,& 4: ";
        else if(a[i]==b[1]&&a[i]==b[2]&&a[i]==b[4])cout<<"Player 2,3,& 5: ";
        else if(a[i]==b[1]&&a[i]==b[3]&&a[i]==b[4])cout<<"Player 2,4,& 5: ";
        else if(a[i]==b[0]&&a[i]==b[1]&&a[i]==b[2])cout<<"Player 1,2,& 3: ";
        else if(a[i]==b[0]&&a[i]==b[1]&&a[i]==b[3])cout<<"Player 1,2,& 4: ";
        else if(a[i]==b[0]&&a[i]==b[1]&&a[i]==b[4])cout<<"Player 1,2,& 5: ";
        else if(a[i]==b[0]&&a[i]==b[2]&&a[i]==b[3])cout<<"Player 1,3,& 4: ";
        else if(a[i]==b[0]&&a[i]==b[2]&&a[i]==b[4])cout<<"Player 1,3,& 5: ";
        else if(a[i]==b[0]&&a[i]==b[3]&&a[i]==b[4])cout<<"Player 1,4,& 5: ";
        else if(a[i]==b[2]&&a[i]==b[3]&&a[i]==b[4])cout<<"Player 3,4,& 5: ";
        else if(a[i]==b[1]&&a[i]==b[2])cout<<"Player 2 & 3: ";
        else if(a[i]==b[0]&&a[i]==b[2])cout<<"Player 1 & 3: ";
        else if(a[i]==b[0]&&a[i]==b[1])cout<<"Player 1 & 2: ";
        else if(a[i]==b[0]&&a[i]==b[3])cout<<"Player 1 & 4: ";
        else if(a[i]==b[0]&&a[i]==b[4])cout<<"Player 1 & 5: ";
        else if(a[i]==b[3]&&a[i]==b[4])cout<<"Player 4 & 5: ";
        else if(a[i]==b[1]&&a[i]==b[3])cout<<"Player 2 & 4: ";
        else if(a[i]==b[1]&&a[i]==b[4])cout<<"Player 2 & 5: ";
        else if(a[i]==b[2]&&a[i]==b[3])cout<<"Player 3 & 4: ";
        else if(a[i]==b[2]&&a[i]==b[4])cout<<"Player 3 & 5: ";
        else if(a[i]==b[0])cout<<"Player 1: ";
        else if(a[i]==b[1])cout<<"Player 2: ";
        else if(a[i]==b[2])cout<<"Player 3: ";
        else if(a[i]==b[3])cout<<"Player 4: ";
        else cout<<"Player 5: ";
        cout<<a[i]<<" token/s" <<endl;
        }
}
bool linSrch(int a[], int n, int val){
    for(int i=0;i<n;i++){
        if(a[i]==val)
            return true;
    }
    return false;
}
int srchVal(){
    int val;
    cout<< "Enter a token value greater than or equal to 0 to search for in the list: \n";
    cin >> val;
    if(val<0)
        exit(EXIT_FAILURE); //Example of exit function used to terminate program if val is less than 0
    return val;
}
void dsply(fstream &out, int tknCntr[], int PLYRS, float mean, int numDice){
    mean /= numDice;
    //Displaying & Sending mean to file
    cout<<fixed<<setprecision(2);
    cout<< "The mean value rolled was around = "<< mean<<endl;
    out<< "The mean value rolled was around = "<< mean<<endl;
    cout<<noshowpoint;
    //Sending Info to file
    (tknCntr[0]>tknCntr[1]&&tknCntr[0]>tknCntr[2]?out<<"Player 1 won with "<<tknCntr[0]<< " token/s!\n":
     tknCntr[1]>tknCntr[0]&&tknCntr[1]>tknCntr[2]?out<<"Player 2 won with "<<tknCntr[1]<< " token/s!\n":
     out<<"Player 3 won with "<<tknCntr[2]<<" token/s!\n");
    //Displaying Winner using Nested Ternary Operator
    (tknCntr[0]>tknCntr[1]&&tknCntr[0]>tknCntr[2]?cout<<"Player 1 won with "<<tknCntr[0]<< " token/s!\n":
     tknCntr[1]>tknCntr[0]&&tknCntr[1]>tknCntr[2]?cout<<"Player 2 won with "<<tknCntr[1]<< " token/s!\n":
     cout<<"Player 3 won with "<<tknCntr[2]<<" token/s!\n");
    //Perform Linear search for a specified value
    int val = srchVal();
    if(linSrch(tknCntr, PLYRS, val)){
        cout<< val<< " was found in the list of token counters.\n";
        out << val<< " was found in the list of token counters.\n";
    }else{ 
        cout<< val<<" was not found in the list.\n";
        out << val<<" was not found in the list.\n";
    }
}
void dsply(fstream &out, int tknCntr[], int PLYRS, int mean, int numDice){
    mean /= numDice;
    //Displaying & Sending info to file
    cout<< "The mean value rolled was around = "<< mean<<endl;
    out<< "The mean value rolled was around = "<< mean<<endl;
    //Sending Info to file
    (tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0?out<<"Player 1 won with "<<tknCntr[0]<< " token/s!\n":
     tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0?out<<"Player 2 won with "<<tknCntr[1]<< " token/s!\n":
     tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[3]==0&&tknCntr[4]==0?out<<"Player 3 won with "<<tknCntr[2]<< " token/s!\n":
     tknCntr[3]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[4]==0?out<<"Player 4 won with "<<tknCntr[3]<< " token/s!\n":
     out<<"Player 5 won with "<<tknCntr[4]<< " token/s!\n");
    //Displaying Winner using Nested Ternary Operator
    (tknCntr[0]>0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0?cout<<"Player 1 won with "<<tknCntr[0]<< " token/s!\n":
     tknCntr[1]>0&&tknCntr[0]==0&&tknCntr[2]==0&&tknCntr[3]==0&&tknCntr[4]==0?cout<<"Player 2 won with "<<tknCntr[1]<< " token/s!\n":
     tknCntr[2]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[3]==0&&tknCntr[4]==0?cout<<"Player 3 won with "<<tknCntr[2]<< " token/s!\n":
     tknCntr[3]>0&&tknCntr[0]==0&&tknCntr[1]==0&&tknCntr[2]==0&&tknCntr[4]==0?cout<<"Player 4 won with "<<tknCntr[3]<< " token/s!\n":
     cout<<"Player 5 won with "<<tknCntr[4]<< " token/s!\n");
    int val = srchVal();
    if(linSrch(tknCntr, PLYRS, val)){
        cout<< val<<" was found in the list of token counters.\n";
        out << val<<" was found in the list of token counters.\n";
    }else{ 
        cout<< val<<" was not found in the list.\n";
        out << val<<" was not found in the list.\n";
    }
}