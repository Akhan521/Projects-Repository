/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on March 21, 2022, 1:40 PM
 * Purpose: Mastermind V.1 
 * Creating a Board + Using a Code Length of 1 to start off with (1 column).
 * For this program, we start off with guesses of length 1.
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //Rand() Function
using namespace std;

//User Libraries

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Variables:
    const int PEGS=1;    //Number of pegs or code length.
    const int ATMPTS=10; //Number of attempts that are allowed.
    int nTries=0;        //Number of tries we've used.       
    char cdeToBrk;       //The 1 digit code to break or solution will be stored here.
    char guess;          //Our 1 digit guess will be stored here.
    
    //Create our board:
    char **board=new char *[ATMPTS]; //10 rows for 10 attempts.
    for(int i=0;i<ATMPTS;i++){
        board[i]=new char[PEGS+1];   //1 element per row (1 column) + Null Term.
    }
    //Set up our board:
    for(int i=0;i<ATMPTS;i++){
        for(int j=0;j<PEGS;j++){
            board[i][j]='_';
        }
        //Set the null terminator for each row.
        board[i][PEGS]='\0';
    }
    //Randomly create a guess to find (0-7):
    cdeToBrk=(rand()%8)+'0';
    //cout<<"Code to Break: "<<cdeToBrk<<endl;
    //Display the board:
    for(int i=0;i<ATMPTS;i++){
        for(int j=0;j<PEGS;j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    //Ask for a 1 digit guess from the user:
    do{
    cout<<"Enter a 1 digit number between 0-7:\n";
    cin>>guess;
    }while(guess<'0'||guess>'7');
    nTries++; //At this point, we've used 1 try to make 1 guess.
    //Check to see if the guess is equal to the cdeToBrk. If it is, then we're done.
    //Otherwise, we need to ask again for another guess.
    if(guess==cdeToBrk){
        cout<<"Congrats! You've won Mastermind!";
    }
    else{
        //Store our first attempt on the last row:
        //We want our attempts to be stored from bottom to top, so I use ATMPTS-nTries to do this.
        //We only have 1 column so j = PEGS-1 = 1-1 = 0 (Index for col. 1)
        //If we used just nTries, it would be stored from top to bottom.
        board[ATMPTS-nTries][PEGS-1]=guess;
        //As long as we have tries left and we haven't gotten the correct digit...
        while(guess!=cdeToBrk&&nTries!=ATMPTS){
            //Display the board with each attempt:
            for(int i=0;i<ATMPTS;i++){
                for(int j=0;j<PEGS;j++){
                    cout<<board[i][j];
                }
                cout<<endl;
            }
            cout<<endl;
            //Ask for another guess...
            do{
            cout<<"Enter a 1 digit number between 0-7:\n";
            cin>>guess;
            }while(guess<'0'||guess>'7');
            nTries++; //We've used another try to make another guess.
            //Store the current attempt.
            board[ATMPTS-nTries][PEGS-1]=guess;
        }
        //Save the last attempt we made:
        board[ATMPTS-nTries][PEGS-1]=guess;
        //If we get the correct guess within 10 tries, we win.
        cout<<(guess==cdeToBrk?"\nCongrats! You've won Mastermind!\n":"\nToo bad. Try again.\n");
    }
    //Output how many tries were used:
    cout<<"You used "<<nTries<<" tries.\n";
    //Exit the Program - Cleanup:
    //Recover the memory that we allocated.
    for(int i=0;i<ATMPTS;i++){
        delete [] board[i];
    }
    delete [] board;
    return 0;
}