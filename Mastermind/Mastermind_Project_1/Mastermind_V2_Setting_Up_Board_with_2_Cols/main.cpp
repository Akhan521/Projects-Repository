/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on March 21, 2022, 2:30 PM
 * Purpose: Mastermind V.2 
 * Using a Code Length of 2 (2 columns/pegs).
 * For this program, we continue with guesses of length 2.
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

//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Variables:
    const int PEGS=2;    //Number of pegs or code length.
    const int ATMPTS=10; //Number of attempts that are allowed.
    int nTries=0;        //Number of tries we've used.       
    char *cdeToBrk;      //The 2 digit cdeToBrk or solution will be stored here.
    char *guess;         //Our 2 digit guess will be stored here.
    char temp[ATMPTS];   //A temp. var. used for input validation of our guesses.
                         //temp is used to ensure our input is the correct length and
                         //that we only use digits between 0-7 for our guesses.
                         //Once we have a valid guess in temp, we copy the contents into guess.
    
    //Output the goal/objective:
    cout<<"A random 2 digit code to break will be generated. Try to guess the code in 10 tries."<<endl;
    cout<<"If you get it before all tries are used, you win. Otherwise, you lose.\n"<<endl;
    //Set up our cdeToBrk and guess char arrays:
    cdeToBrk=new char[PEGS+1];   //For 2 pegs + null terminator.
    cdeToBrk[PEGS]='\0';         //Set the null term.
    guess=new char[PEGS+1]; //For 2 pegs + null terminator.
    guess[PEGS]='\0';       //Set the null term.
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
    //Randomly create a cdeToBrk/solution to find w/ digits between (0-7):
    for(int i=0;i<PEGS;i++){
        cdeToBrk[i]=(rand()%8)+'0';
    }
    cout<<"Code to Break: "<<cdeToBrk<<" (The code isn't hidden in this program.)"<<endl;
    //Display the board:
    for(int i=0;i<ATMPTS;i++){
        for(int j=0;j<PEGS;j++){
            cout<<board[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
    //Ask for a 2 digit guess from the user (Digits need to be between 0-7):
    bool isVld;       //To determine whether we've used digits between 0-7.
    do{
        //Anytime we make a new guess, temp needs to be reset or emptied.
        //We also want to reset isVld anytime we make a new guess.
        strcpy(temp,"");
        isVld=true; //Our input begins as valid and we check to see if it's invalid later.
        cout<<"Enter a 2 digit number w/ digits between 0-7:\n";
        cin>>temp;
        //cout<<"Length = "<<strlen(temp)<<endl;
        //Check to see if digits are between 0-7 in temp.
        for(int i=0;i<strlen(temp);i++){
            //If it isn't between 0-7, we have an invalid guess.
            if(temp[i]<'0'||temp[i]>'7'){
                isVld=false;
            }
        }
        //cout<<"isVld = "<<isVld<<endl;
    //Case 1: Loop again if the guess isn't the correct length. Or...
    //Case 2: Loop again if the guess is the correct length, but doesn't have digits between 0-7.
    }while(strlen(temp)!=PEGS||(strlen(temp)==PEGS&&!isVld));
    //Now that we have a valid guess in temp, we copy the contents over into guess.
    for(int i=0;i<PEGS;i++){
        guess[i]=temp[i];
    }
    nTries++; //At this point, we've used 1 try to make 1 guess.
    //Check to see if the guess is equal to the cdeToBrk. If it is, then we're done.
    //Otherwise, we need to ask again for another guess.
    //If they match, strcmp() will return a 0. Otherwise, it won't.
    if(strcmp(guess,cdeToBrk)==0){
        cout<<"\nCongrats! You've won Mastermind!\n";
    }
    else{
        //Store our first attempt on the last row:
        //We want our attempts to be stored from bottom to top, so I use ATMPTS-nTries to do this.
        strcpy(board[ATMPTS-nTries],guess);
        //As long as we have tries left and we haven't gotten the correct cdeToBrk:
        //If guess and cdeToBrk don't match, strcmp() won't return a 0.
        while((strcmp(guess,cdeToBrk)!=0)&&nTries!=ATMPTS){
            //Display the board with each attempt:
            for(int i=0;i<ATMPTS;i++){
                for(int j=0;j<PEGS;j++){
                    cout<<board[i][j];
                }
                cout<<endl;
            }
            cout<<endl;
            //Ask for a 2 digit guess from the user (Digits need to be between 0-7):
            bool isVld;       //To determine whether we've used digits between 0-7.
            do{
                //Anytime we make a new guess, temp needs to be reset or emptied.
                //We also want to reset isVld anytime we make a new guess.
                strcpy(temp,"");
                isVld=true; //Our input begins as valid and we check to see if it's invalid later.
                cout<<"Enter a 2 digit number w/ digits between 0-7:\n";
                cin>>temp;
                //cout<<"Length = "<<strlen(temp)<<endl;
                //Check to see if digits are between 0-7 in temp.
                for(int i=0;i<strlen(temp);i++){
                    //If it isn't between 0-7, we have an invalid guess.
                    if(temp[i]<'0'||temp[i]>'7'){
                        isVld=false;
                    }
                }
                //cout<<"isVld = "<<isVld<<endl;
            //Case 1: Loop again if the guess isn't the correct length. Or...
            //Case 2: Loop again if the guess is the correct length, but doesn't have digits between 0-7.
            }while(strlen(temp)!=PEGS||(strlen(temp)==PEGS&&!isVld));
            //Now that we have a valid guess in temp, we copy the contents over into guess.
            for(int i=0;i<PEGS;i++){
                guess[i]=temp[i];
            }
            nTries++; //We've used another try to make another guess.
            //Store the current attempt.
            strcpy(board[ATMPTS-nTries],guess);
        }
        //Save the last attempt we made:
        strcpy(board[ATMPTS-nTries],guess);
        //If we get the correct guess within 10 tries, we win.
        cout<<((strcmp(guess,cdeToBrk)==0)?"\nCongrats! You've won Mastermind!\n"
                                          :"\nYou lose! Try again next time.\n");
    }
    //Output how many tries were used: (If all tries were used, say that all tries were used.)
    nTries==ATMPTS?cout<<"You used all "<<nTries<<" tries.\n"
                  :cout<<"You used "<<nTries<<" try/tries.\n";
    
    //Exit the Program - Cleanup:
    //Recover the memory that we allocated for our cdeToBrk and guess.
    delete [] cdeToBrk;
    delete [] guess;
    //Recover the memory allocated for our board.
    for(int i=0;i<ATMPTS;i++){
        delete [] board[i];
    }
    delete [] board;
    return 0;
}