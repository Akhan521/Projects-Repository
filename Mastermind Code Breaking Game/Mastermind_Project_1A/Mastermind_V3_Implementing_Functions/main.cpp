/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on March 21, 2022, 7:30 PM
 * Purpose: Mastermind V.3
 * Creating functions to simplify our code and main.
 * We create functions for our setup, cleanup, etc.
 */

//System Libraries
#include <iostream>  //I/O Library
#include <cstdlib>   //Rand() Function
#include <cstring>   //strcpy() + strcmp() Functions
using namespace std;

//User Libraries

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
char **setUpBrd(const int,const int);           //Creates + Sets up our board.
char *genCde(const int);                        //Generates a random 2-digit cdeToBrk.
char *setUpGss(const int);                      //Sets up our guess char array.
void dsplyBrd(char **,const int,const int);     //Displays our 2-D board.
void mkeGuess(char *,const int,int &);          //Allows us to make a guess and store it.
                                                //Also keeps track of the # of tries used.
void streGss(char **,char *,const int, int);    //Stores our guess in our 2-D board.
void recvrMem(char **,char *,char *,const int); //Recovers all the memory that we allocated.
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Variables:
    const int PEGS=2;    //Number of pegs or our code length.
    const int ATMPTS=10; //Number of attempts that are allowed.
    int nTries=0;        //Number of tries we've used.       
    
    //Output the goal/objective:
    cout<<"A random 2 digit code to break will be generated. Try to guess the code in 10 tries."<<endl;
    cout<<"If you get it before all tries are used, you win. Otherwise, you lose.\n"<<endl;
    
    //Create + setup our board:
    char **board=setUpBrd(ATMPTS,PEGS);
    //Generate a random cdeToBrk to find:
    char *cdeToBrk=genCde(PEGS);
    //Create and set up our guess array:
    char *guess=setUpGss(PEGS);
    
    cout<<"Code to Break: "<<cdeToBrk<<" (The code isn't hidden in this program.)"<<endl;
    //Display the board:
    dsplyBrd(board,ATMPTS,PEGS);
    
    //Ask for a 2 digit guess from the user (Digits need to be between 0-7):
    mkeGuess(guess,PEGS,nTries);
    
    //Check to see if the guess matches the cdeToBrk. If it does, then we're done.
    //Otherwise, we need to ask the user again for another guess.
    //If they match, strcmp() will return a 0. Otherwise, it won't.
    if(strcmp(guess,cdeToBrk)==0){
        cout<<"\nCongrats! You've won Mastermind!\n";
        //Store the guess we made:
        streGss(board,guess,ATMPTS,nTries);
    }
    else{
        //Store our first guess on the last row:
        streGss(board,guess,ATMPTS,nTries);
        //As long as we have tries left and we haven't gotten the correct cdeToBrk:
        while((strcmp(guess,cdeToBrk)!=0)&&nTries!=ATMPTS){
            //Display the board with each attempt:
            dsplyBrd(board,ATMPTS,PEGS);
            //Ask for a 2 digit guess from the user (Digits need to be between 0-7):
            mkeGuess(guess,PEGS,nTries);
            //Store the current guess.
            streGss(board,guess,ATMPTS,nTries);
        }
        //Store the last guess we made:
        streGss(board,guess,ATMPTS,nTries);
        //If we get the correct guess within 10 tries, we win.
        cout<<((strcmp(guess,cdeToBrk)==0)?"\nCongrats! You've won Mastermind!\n"
                                          :"\nYou lose! Try again next time.\n");
    }
    //Output how many tries we used:
    nTries==ATMPTS?cout<<"You used all "<<ATMPTS<<" tries.\n"
                  :cout<<"You used "<<nTries<<" try/tries.\n";
    //Display the board at the end of our game along with the cdeToBrk:
    dsplyBrd(board,ATMPTS,PEGS);
    cout<<"Code to Break = "<<cdeToBrk<<endl;
    //Exit the Program - Cleanup.
    recvrMem(board,guess,cdeToBrk,ATMPTS);
    return 0;
}
//Function to create, setup, and return our board:
char **setUpBrd(const int ATMPTS, const int PEGS){
    //Create our board:
    char **board=new char *[ATMPTS]; //10 rows for 10 attempts.
    for(int i=0;i<ATMPTS;i++){
        board[i]=new char[PEGS+1];   //2 elements per row (2 column) + Null Term.
    }
    //Set up our board:
    for(int i=0;i<ATMPTS;i++){
        for(int j=0;j<PEGS;j++){
            board[i][j]='_';
        }
        //Set the null terminator for each row.
        board[i][PEGS]='\0';
    }
    return board;
}
//Function to generate a random cdeToBrk to find:
char *genCde(const int PEGS){
    //The 2 digit cdeToBrk or solution will be stored here:
    char *cdeToBrk;  
    //Set up our cdeToBrk char array:
    cdeToBrk=new char[PEGS+1]; //For 2 pegs + null terminator.
    //Set the null term.
    cdeToBrk[PEGS]='\0';
    //Randomly create a cdeToBrk/solution to find w/ digits between (0-7):
    for(int i=0;i<PEGS;i++){
        cdeToBrk[i]=(rand()%8)+'0';
    }
    return cdeToBrk;
}
//Function to create and set up our guess char array:
char *setUpGss(const int PEGS){
    //Our 2 digit guess will be stored here.
    char *guess;       
    //Set up our guess char array:
    guess=new char[PEGS+1]; //For 2 pegs + null terminator.
    guess[PEGS]='\0';       //Set the null term.
    return guess;
}
//Function to display our board:
void dsplyBrd(char **board,const int ATMPTS, const int PEGS){
    //Display the board:
    for(int i=0;i<ATMPTS;i++){
        for(int j=0;j<PEGS;j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
//Function to make and store a guess. Also keeps track of the # of tries used:
//This function uses input validation on our guess to ensure that we have a valid guess.
void mkeGuess(char *guess, const int PEGS, int &nTries){
    const int SIZE=10; //More than enough space for our input that needs to be validated.
    char temp[SIZE];   //A temp. var. used to store our guess that needs to be checked.
                       //If temp is a valid guess, we store it in our guess array.
                       //If it isn't, we keep taking guesses until we have a valid guess.
    //Ask for a 2 digit guess from the user (Digits need to be between 0-7):
    bool isVld;        //To determine whether we have a valid guess or not (Digits between 0-7).
    do{
        //Anytime we make a new guess, temp needs to be reset or emptied.
        //We also want to reinitialize isVld anytime we make a new guess.
        strcpy(temp,"");
        isVld=true; //Our input begins as valid and we check to see if it's invalid later.
        cout<<"Enter a 2 digit number w/ digits between 0-7:\n";
        cin>>temp;
        //Check to see if digits are between 0-7 in temp.
        for(int i=0;i<strlen(temp);i++){
            //If it isn't between 0-7, we have an invalid guess.
            if(temp[i]<'0'||temp[i]>'7'){
                isVld=false;
            }
        }
    //Case 1: Loop again if the guess ISN'T the correct length. Or...
    //Case 2: Loop again if the guess IS the correct length, BUT we have an invalid guess.
    }while(strlen(temp)!=PEGS||(strlen(temp)==PEGS&&!isVld));
    //Now that we have a valid guess in temp, we copy the contents over into guess.
    for(int i=0;i<PEGS;i++){
        guess[i]=temp[i];
    }
    nTries++; //At this point, we've used 1 try to make 1 guess.
}
//Function to store our guess in our 2-D board:
void streGss(char **board, char *guess , const int ATMPTS, int nTries){
    //We want our attempts to be stored from bottom to top, so I use ATMPTS-nTries to do this.
    //Our guesses are stored in our 2-D board using strcpy().
    //ATMPTS-nTries returns the correct index for the row we're on from the bottom.
    strcpy(board[ATMPTS-nTries],guess);
}
//Function to recover all of the memory that we allocated for all objects:
void recvrMem(char **board, char *guess, char *cdeToBrk, const int ATMPTS){
    //Recover the memory that we allocated for our cdeToBrk and guess arrays.
    delete [] cdeToBrk;
    delete [] guess;
    //Recover the memory we allocated for our board (2D array).
    for(int i=0;i<ATMPTS;i++){
        delete [] board[i];
    }
    delete [] board;
}