/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on March 23, 2022, 2:35 PM
 * Purpose: Mastermind V.10
 * Adding some finishing touches and tweaking some stuff.
 * (Even if we say not to use duplicates, the user should be able to type in any values,
 * so I make that change in the mkeGuess function. When we say no duplicates, it just ensures
 * that the code to break is unique. Regardless, we should be able to type in any values at all times.)
 */

//System Libraries
#include <iostream>  //I/O Library
#include <ctime>     //Time Library
#include <cstdlib>   //Rand() Function
#include <cstring>   //strcpy() + strcmp() Functions
using namespace std;

//User Libraries

//Global Constants
//Math, Science, Universal, Conversions, High Dimensioned Arrays

//Function Prototypes
void plyMstrMnd(int,bool);                                   //Play 1 game of Mastermind.
void shwRles();                                              //Description of MM + Rules
char **setUpBrd(const int,const int);                        //Creates + Sets up our board.
char *genCde(const int,bool);                                //Generates a random 4,6,or 8-digit code to break.
char *setUpGss(const int);                                   //Sets up our guess char array.
void dsplyBrd(char **,char **,const int,const int);          //Displays our 2-D board.
void mkeGuess(char *,const int,int &);                       //Allows us to make a guess and store it.
                                                             //Also keeps track of the # of tries used.
void streGss(char **,char *,const int, int);                 //Stores our guess in our 2-D board.
void recvrMem(char **,char **,char *,char *,const int);      //Recovers all the memory that we allocated.
void streHnts(char **,char *,char *,const int,const int,int);//Stores hints for the guesses we make.
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare Variables:
    int cdeLnth=0;       //Our code length or the # of pegs we want to use.
    int input=0;         //To hold our input for the code length.
    char choice;         //To hold the choice we make for using dups or not
    bool useDup;         //To hold whether we're using duplicates or not.
    
    //Give an explanation of Mastermind and it's rules:
    shwRles();
    //Ask what our code length should be (Either 4, 6, or 8):
    do{
        cout<<"What should the code length be? (4, 6, or 8)"<<endl;
        cin>>input;
    //We keep re-asking as long as the input is not a 4, 6, or 8.
    }while(input!=4&&input!=6&&input!=8);
    //Set code length to our input.
    cdeLnth=input;
    
    //Ask for whether we want to use duplicates or not.
    do{
        cout<<"Would you like to use duplicates? (y/n)"<<endl;
        cin>>choice;
    //We keep re-asking as long as the input is not either y or n.
    //Basically if it's not a y/Y and it's not an n/N, we re-ask:
    }while(choice!='y'&&choice!='n'&&choice!='Y'&&choice!='N');
    //Set useDup to true or false given our choice.
    useDup=(choice=='y'?true:choice=='Y'?true:false);
    
    //Play a game of Mastermind:
    plyMstrMnd(cdeLnth,useDup);
    
    //Exit the Program.
    return 0;
}
//Function to provide a description of Mastermind and show rules:
void shwRles(){
    cout<<"Mastermind is a code-breaking game. A random code to break will be generated.\n";
    cout<<"It is the player's objective to guess that code within 10 tries.\n";
    cout<<"If the code can be guessed within 10 tries, you WIN. Otherwise, you LOSE.\n";
    cout<<"Hints will de displayed after each guess to assist the player.\n";
    cout<<"R - Indicates that a digit is correct and in the correct place.\n";
    cout<<"W - Indicates that a digit is correct but in the wrong place.\n";
    cout<<"_ - Indicates that a digit is wrong and in the wrong place.\n\n";
}
//Function to play 1 game of Mastermind: 
//The first input is how long our code length should be (# of pegs).
//The second input is whether we want to use duplicates or not.
void plyMstrMnd(int cdeLnth, bool useDup){
    const int ATMPTS=10; //Number of attempts that are allowed.
    int nTries=0;        //Number of tries we've used.
    //Output the goal/objective:
    cout<<endl;
    cout<<"A random "<<cdeLnth<<"-digit code to break will be generated. Try to guess the code in 10 tries."<<endl;
    cout<<"If you get it before all tries are used, you win. Otherwise, you lose.\n"<<endl;
    //Create + setup our board:
    char **board=setUpBrd(ATMPTS,cdeLnth);
    //Create + setup our hint board:
    char **hints=setUpBrd(ATMPTS,cdeLnth);
    //Generate a random cdeToBrk to find:
    char *cdeToBrk=genCde(cdeLnth,useDup);
    //Create and set up our guess array:
    char *guess=setUpGss(cdeLnth);
    //Show the code as a hidden number:
    cout<<"Code to Break: ";
    for(int i=0;i<cdeLnth;i++) cout<<"*";
    cout<<endl;
    //Display the board:
    dsplyBrd(board,hints,ATMPTS,cdeLnth);
    //Ask for a 4 digit guess from the user (Digits need to be between 0-7):
    mkeGuess(guess,cdeLnth,nTries);
    //Check to see if the guess matches the cdeToBrk. If it does, then we're done.
    //Otherwise, we need to ask the user again for another guess.
    if(strcmp(guess,cdeToBrk)==0){
        cout<<"\nCongrats! You've won Mastermind!\n";
        //Store the guess we made:
        streGss(board,guess,ATMPTS,nTries);
        //Store the hint for our guess. In this case, we should have 4 R's since we won.
        streHnts(hints,board[ATMPTS-nTries],cdeToBrk,ATMPTS,cdeLnth,nTries);
    }
    else{
        //Store our first guess on the last row:
        streGss(board,guess,ATMPTS,nTries);
        //Store the hint for the first guess we made:
        streHnts(hints,board[ATMPTS-nTries],cdeToBrk,ATMPTS,cdeLnth,nTries);
        //As long as we have tries left and we haven't gotten the correct cdeToBrk:
        while((strcmp(guess,cdeToBrk)!=0)&&nTries!=ATMPTS){
            //Display the board with each attempt:
            dsplyBrd(board,hints,ATMPTS,cdeLnth);
            //Ask for a guess from the user (Digits need to be between 0-7):
            mkeGuess(guess,cdeLnth,nTries);
            //Store the current guess.
            streGss(board,guess,ATMPTS,nTries);
            //Store the hint for the most recent guess:
            streHnts(hints,board[ATMPTS-nTries],cdeToBrk,ATMPTS,cdeLnth,nTries);
        }
        //Store the last guess we made:
        streGss(board,guess,ATMPTS,nTries);
        //Store the hint for our last guess.
        streHnts(hints,board[ATMPTS-nTries],cdeToBrk,ATMPTS,cdeLnth,nTries);
        //If we get the correct guess within 10 tries, we win.
        cout<<((strcmp(guess,cdeToBrk)==0)?"Congrats! You've won Mastermind!\n"
                                          :"You lose! Try again next time.\n");
    }
    //Output how many tries we used:
    nTries==ATMPTS?cout<<"You used all "<<ATMPTS<<" tries.\n"
                  :cout<<"You used "<<nTries<<" try/tries.\n";
    //Display the board at the end of our game, our hint, & the cdeToBrk:
    dsplyBrd(board,hints,ATMPTS,cdeLnth);
    //The code to break that was generated at random.
    cout<<"Code to Break = "<<cdeToBrk<<endl;
    //Exit the Program - Cleanup.
    recvrMem(board,hints,guess,cdeToBrk,ATMPTS);
}
//Function to create, setup, and return our board:
char **setUpBrd(const int ATMPTS, const int cdeLnth){
    //Create our board:
    char **board=new char *[ATMPTS];  //10 rows for 10 attempts.
    for(int i=0;i<ATMPTS;i++){
        board[i]=new char[cdeLnth+1]; //Code Length + Null Term.
    }
    //Set up our board:
    for(int i=0;i<ATMPTS;i++){
        for(int j=0;j<cdeLnth;j++){
            board[i][j]='_';
        }
        //Set the null terminator for each row.
        board[i][cdeLnth]='\0';
    }
    return board;
}
//Function to generate a random cdeToBrk to find:
char *genCde(const int cdeLnth, bool useDup){
    //The cdeToBrk or solution will be stored here:
    char *cdeToBrk;  
    //Set up our cdeToBrk char array:
    cdeToBrk=new char[cdeLnth+1]; //For cdeLnth + null terminator.
    //Set the null term.
    cdeToBrk[cdeLnth]='\0';
    //Randomly create a code to find w/ digits between (0-7):
    //This just randomly generates a code that can have duplicates.
    //If we don't want to use dups, we'll go through and fix that.
    for(int i=0;i<cdeLnth;i++){
        cdeToBrk[i]=(rand()%8)+'0';
    }
    //If we are NOT using duplicates, we check to see if our code has dups.
    //If it does, we re-choose digits until they're all unique.
    if(!useDup){
        //If we have duplicates, we just choose different digits.
        for(int i=0;i<cdeLnth;i++){
            for(int j=0;j<cdeLnth;j++){
                //We have to specify i!=j because values are always the same at the same index.
                //We only check for duplicates at indices that are not the same.
                if(cdeToBrk[i]==cdeToBrk[j]&&i!=j){
                    //As long as they're the same, we choose a different digit.
                    while(cdeToBrk[i]==cdeToBrk[j]){
                        cdeToBrk[j]=(rand()%8)+'0';
                    }
                }
            }
        }
    }
    return cdeToBrk;
}
//Function to create and set up our guess char array:
char *setUpGss(const int cdeLnth){
    //Our guess will be stored here.
    char *guess;       
    //Set up our guess char array:
    guess=new char[cdeLnth+1]; //For cdeLnth + null terminator.
    guess[cdeLnth]='\0';       //Set the null term.
    return guess;
}
//Function to display our board as well as our hints for the guesses we made:
void dsplyBrd(char **board, char **hints, const int ATMPTS, const int cdeLnth){
    //Display the board + hints:
    for(int i=0;i<ATMPTS;i++){
        for(int j=0;j<cdeLnth;j++){
            cout<<board[i][j];
        }
        cout<<"  "; //Some space between our guess and our hint.
        //Output the hints for each guess we've made.
        for(int j=0;j<cdeLnth;j++){
            cout<<hints[i][j];
        }
        cout<<endl;
    }
    cout<<endl;
}
//Function to make and store a guess. Also keeps track of the # of tries used:
//This function uses input validation on our guess to ensure that we have a valid guess.
void mkeGuess(char *guess, const int cdeLnth, int &nTries){
    const int SIZE=10; //More than enough space for our input that needs to be validated.
    char temp[SIZE];   //A temp. var. used to store our guess that needs to be checked.
                       //If temp is a valid guess, we store it in our guess array.
                       //If it isn't, we keep taking guesses until we have a valid guess.
    //Ask for a guess from the user (Digits need to be between 0-7):
    bool isVld;  //To determine whether we have a valid guess (Digits between 0-7).
    //At the start, we have no dups. We'll check later on if we have dups.
    do{
        //Anytime we make a new guess, temp needs to be reset or emptied.
        //We also want to reinitialize isVld anytime we make a new guess.
        strcpy(temp,"");
        isVld=true;   //Our input begins as valid and we check to see if it's invalid later.
        cout<<"Enter a "<<cdeLnth<<"-digit number w/ digits between 0-7:\n";
        cin>>temp;
        //Check to see if digits are between 0-7 in temp.
        for(int i=0;i<strlen(temp);i++){
            //If it isn't between 0-7, we have an invalid guess.
            if(temp[i]<'0'||temp[i]>'7'){
                isVld=false;
            }
        }
    //Case 1: Loop again if the guess ISN'T the correct length. Or...
    //Case 2: Loop again if the guess IS the correct length, BUT we have an invalid guess. Or...
    }while(strlen(temp)!=cdeLnth||(strlen(temp)==cdeLnth&&!isVld));
    //Now that we have a valid guess in temp, we copy the contents over into guess.
    for(int i=0;i<cdeLnth;i++){
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
void recvrMem(char **board, char **hints, char *guess, char *cdeToBrk, const int ATMPTS){
    //Recover the memory that we allocated for our cdeToBrk and guess arrays.
    delete [] cdeToBrk;
    delete [] guess;
    //Recover the memory we allocated for our board (2D array).
    for(int i=0;i<ATMPTS;i++){
        delete [] board[i];
    }
    delete [] board;
    //Recover the memory we allocated for our hint board (2D array).
    for(int i=0;i<ATMPTS;i++){
        delete [] hints[i];
    }
    delete [] hints;
}
//Function to store hints for the guess we made:
void streHnts(char **hints,char *guess, char *cdeToBrk, const int ATMPTS, const int cdeLnth, int nTries){
    int rDrP=0; //To hold how many digits are correct and in the right place.
    int rDwP=0; //To hold how many digits are correct and in the wrong place.
    int wDwP=0; //To hold how many digits are incorrect and in the wrong place.
    //To keep track of what hints we have, I use a hint char array.
    char hint[cdeLnth+1];
    hint[cdeLnth]='\0'; //Set the null term.
    //We initialize the hint array with '_' to indicate that we have 0 hints to begin with.
    for(int i=0;i<cdeLnth;i++) hint[i]='_';
    //Figure out how many digits are right & in the right place:
    //Essentially, the digits need to match and be in the same places in both.
    for(int i=0;i<cdeLnth;i++){
        if(guess[i]==cdeToBrk[i]){
            rDrP++;
            //Set the 'R' hint for the given digit.
            hint[i]='R';
        }
    }
    //Figure out how many digits are right but in the wrong place:
    for(int i=0;i<cdeLnth;i++){
        for(int j=0;j<cdeLnth;j++){
            //We check each digit of the code to break against all digits of our guess.
            //We need to specify that i!=j because we've already checked this in the loop for rDrP.
            //We also need to make sure that we don't already have a hint for a particular digit
            //in our code to break. If a digit in our code already has a hint, we skip it.
            if((cdeToBrk[i]==guess[j]&&i!=j)&&hint[i]=='_'){
                rDwP++;
                //Set the 'W' hint for the given digit.
                hint[i]='W';
            }
        }
    }
    //Determine how many digits are wrong and in the wrong place.
    //This is simply what's left over after we determine rDrP & rDwP.
    wDwP=cdeLnth-(rDrP+rDwP);
    //Create the final hint to be stored in our 2D hint board:
    //Just like in Mastermind, we want to output the hints w/ 'R' first, then 'W', then '_'.
    strcpy(hint,""); //We begin with an empty char array.
    int idx=0;       //Index variable for our hint array.
    //R (Red pin) -> Right digit in the right place.
    for(int i=0;i<rDrP;i++){
        hint[idx]='R';
        //Increment idx so that we can put the hints in their proper places.
        idx++;
    }
    //W (White pin) -> Right digit in the wrong place.
    for(int i=0;i<rDwP;i++){
        hint[idx]='W';
        //Increment idx so that we can put the hints in their proper places.
        idx++;
    }
    //_ (No pin) -> Wrong digit in the wrong place.
    for(int i=0;i<wDwP;i++){
        hint[idx]='_';
        //Increment idx so that we can put the hints in their proper places.
        idx++;
    }
    //Set the final hint in the correct row of our 2D hint board:
    strcpy(hints[ATMPTS-nTries],hint);
    //The reason why we don't simply store the hint array is because doing so would
    //give away the correct digits and/or correct positions.
    //For ex: _R_R would give away that the 2nd & 4th digits are correct and in the correct place.
    //This defeats the purpose of Mastermind because we are NOT supposed to know exactly which digits
    //are correct and in the correct place; we're ONLY supposed to know how many.
    cout<<endl;
}