/* 
 * File:   main.cpp
 * Author: Aamir Khan
 * Created on March 22, 2022, 7:30 PM
 * Purpose: Mastermind V.8
 * In the previous version, the hints only worked properly when NO dups were used.
 * In this version, we get it to work with both cases (Dups Vs. No Dups).
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
char *genCde(const int,bool);                   //Generates a random 4-digit code to break.
char *setUpGss(const int);                      //Sets up our guess char array.
void dsplyBrd(char **,const int,const int);     //Displays our 2-D board.
void mkeGuess(char *,const int,int &,bool);     //Allows us to make a guess and store it.
                                                //Also keeps track of the # of tries used.
void streGss(char **,char *,const int, int);    //Stores our guess in our 2-D board.
void recvrMem(char **,char *,char *,const int); //Recovers all the memory that we allocated.
void shwHnts(char *,char *,const int);          //Shows hints for the guesses we make (Dup & No Dup).
//Execution Begins Here
int main(int argc, char** argv) {
    //Initialize the Random Number Seed
    srand(static_cast<unsigned int>(time(0)));
    //Declare Variables:
    const int PEGS=4;    //Number of pegs or our code length.
    const int ATMPTS=10; //Number of attempts that are allowed.
    int nTries=0;        //Number of tries we've used.
    char choice;         //To hold our choice for whether we want dups or not.
    bool useDup;         //To hold whether we're using duplicates or not.
    //Output the goal/objective:
    cout<<"A random 4 digit code to break will be generated. Try to guess the code in 10 tries."<<endl;
    cout<<"If you get it before all tries are used, you win. Otherwise, you lose.\n"<<endl;
    //Ask for whether we want to use duplicates or not.
    do{
        cout<<"Would you like to use duplicates? (y/n)"<<endl;
        cin>>choice;
    //We keep re-asking as long as the input is not either y or n.
    //Basically if it's not a y/Y and it's not an n/N, we re-ask:
    }while(choice!='y'&&choice!='n'&&choice!='Y'&&choice!='N');
    //Set useDup to true or false given our choice.
    useDup=(choice=='y'?true:choice=='Y'?true:false);
    //Create + setup our board:
    char **board=setUpBrd(ATMPTS,PEGS);
    //Generate a random cdeToBrk to find:
    char *cdeToBrk=genCde(PEGS,useDup);
    //Create and set up our guess array:
    char *guess=setUpGss(PEGS);
    //The cdeToBrk is visible for now because I haven't added hints yet...
    cout<<"\nCode to Break: "<<cdeToBrk<<" (The code isn't hidden in this program.)"<<endl;
    //Display the board:
    dsplyBrd(board,ATMPTS,PEGS);
    //Ask for a 4 digit guess from the user (Digits need to be between 0-7):
    mkeGuess(guess,PEGS,nTries,useDup);
    //Check to see if the guess matches the cdeToBrk. If it does, then we're done.
    //Otherwise, we need to ask the user again for another guess.
    if(strcmp(guess,cdeToBrk)==0){
        cout<<"\nCongrats! You've won Mastermind!\n";
        //Store the guess we made:
        streGss(board,guess,ATMPTS,nTries);
        //Display the hint for our guess. In this case, we should see 4 R's since we won.
        shwHnts(board[ATMPTS-nTries],cdeToBrk,PEGS);
    }
    else{
        //Store our first guess on the last row:
        streGss(board,guess,ATMPTS,nTries);
        //As long as we have tries left and we haven't gotten the correct cdeToBrk:
        while((strcmp(guess,cdeToBrk)!=0)&&nTries!=ATMPTS){
            //Display the board with each attempt:
            dsplyBrd(board,ATMPTS,PEGS);
            //Display the hint for the most recent guess:
            shwHnts(board[ATMPTS-nTries],cdeToBrk,PEGS);
            //Ask for a 4 digit guess from the user (Digits need to be between 0-7):
            mkeGuess(guess,PEGS,nTries,useDup);
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
    //Display the board at the end of our game, our hint, & the cdeToBrk:
    dsplyBrd(board,ATMPTS,PEGS);
    //The code to break that was generated at random.
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
        board[i]=new char[PEGS+1];   //4 elements per row (4 column) + Null Term.
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
char *genCde(const int PEGS, bool useDup){
    //The 4 digit cdeToBrk or solution will be stored here:
    char *cdeToBrk;  
    //Set up our cdeToBrk char array:
    cdeToBrk=new char[PEGS+1]; //For 4 pegs + null terminator.
    //Set the null term.
    cdeToBrk[PEGS]='\0';
    //Randomly create a code to find w/ digits between (0-7):
    //This just randomly generates a code that can have duplicates.
    //If we don't want to use dups, we'll go through and fix that.
    for(int i=0;i<PEGS;i++){
        cdeToBrk[i]=(rand()%8)+'0';
    }
    //If we are NOT using duplicates, we check to see if our code has dups.
    //If it does, we re-choose digits until they're all unique.
    if(!useDup){
        //If we have duplicates, we just choose different digits.
        for(int i=0;i<PEGS;i++){
            for(int j=0;j<PEGS;j++){
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
char *setUpGss(const int PEGS){
    //Our 4 digit guess will be stored here.
    char *guess;       
    //Set up our guess char array:
    guess=new char[PEGS+1]; //For 4 pegs + null terminator.
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
void mkeGuess(char *guess, const int PEGS, int &nTries, bool useDup){
    const int SIZE=10; //More than enough space for our input that needs to be validated.
    char temp[SIZE];   //A temp. var. used to store our guess that needs to be checked.
                       //If temp is a valid guess, we store it in our guess array.
                       //If it isn't, we keep taking guesses until we have a valid guess.
    //Ask for a 4 digit guess from the user (Digits need to be between 0-7):
    bool isVld;  //To determine whether we have a valid guess (Digits between 0-7).
    bool hasDup; //To determine if we have duplicate digits in our guess.
    //At the start, we have no dups. We'll check later on if we have dups.
    do{
        //Anytime we make a new guess, temp needs to be reset or emptied.
        //We also want to reinitialize isVld anytime we make a new guess.
        strcpy(temp,"");
        isVld=true;   //Our input begins as valid and we check to see if it's invalid later.
        hasDup=false; //At the start of each guess, we have no dups. We'll check to see if we do later on.
        cout<<"Enter a 4 digit number w/ digits between 0-7 ";
        cout<<(useDup==true?"(Duplicates Allowed):\n":"(Duplicates NOT Allowed):\n");
        cin>>temp;
        //Check to see if digits are between 0-7 in temp.
        for(int i=0;i<strlen(temp);i++){
            //If it isn't between 0-7, we have an invalid guess.
            if(temp[i]<'0'||temp[i]>'7'){
                isVld=false;
            }
        }
        //If we are NOT using duplicates, only then will we check to see if we have dups.
        if(!useDup){
            //Check for duplicates. If we have duplicate digits, the guess is invalid.
            for(int i=0;i<PEGS;i++){
                for(int j=0;j<PEGS;j++){
                    //We have to specify i!=j because values are always the same at the same index.
                    //We only check for duplicates at indices that are not the same.
                    if(temp[i]==temp[j]&&i!=j){
                        hasDup=true;
                    }
                }
            }
        }
    //Case 1: Loop again if the guess ISN'T the correct length. Or...
    //Case 2: Loop again if the guess IS the correct length, BUT we have an invalid guess. Or...
    //Case 3: Loop again if we aren't using dups but have duplicate digits in our guess.
    }while(strlen(temp)!=PEGS||(strlen(temp)==PEGS&&!isVld)||(!useDup&&hasDup));
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
    //Recover the memory we allocated for our board (4D array).
    for(int i=0;i<ATMPTS;i++){
        delete [] board[i];
    }
    delete [] board;
}
//Function to show hints for the guess we made:
void shwHnts(char *guess, char *cdeToBrk, const int PEGS){
    int rDrP=0; //To hold how many digits are correct and in the right place.
    int rDwP=0; //To hold how many digits are correct and in the wrong place.
    int wDwP=0; //To hold how many digits are incorrect and in the wrong place.
    //To keep track of what hints we have, I use a hint char array.
    char hint[PEGS+1];
    hint[PEGS]='\0'; //Set the null term.
    //We initialize the hint array with '_' to indicate that we have 0 hints to begin with.
    for(int i=0;i<PEGS;i++) hint[i]='_';
    //Figure out how many digits are right & in the right place:
    //Essentially, the digits need to match and be in the same places in both.
    for(int i=0;i<PEGS;i++){
        if(guess[i]==cdeToBrk[i]){
            rDrP++;
            //Set the 'R' hint for the given pair of digits.
            hint[i]='R';
        }
    }
    //Figure out how many digits are right but in the wrong place:
    for(int i=0;i<PEGS;i++){
        for(int j=0;j<PEGS;j++){
            //We check each digit of the code to break against all digits of our guess.
            //We need to specify that i!=j because we've already checked this in the loop for rDrP.
            //We also need to make sure that we don't already have a hint for a particular digit
            //in our code to break. If a digit in our code already has a hint, we skip it.
            if((cdeToBrk[i]==guess[j]&&i!=j)&&hint[i]=='_'){
                rDwP++;
                //Set the 'W' hint for the given pair of digits.
                hint[i]='W';
            }
        }
    }
    //Determine how many digits are wrong and in the wrong place.
    //This is simply what's left over after we determine rDrP & rDwP.
    wDwP=PEGS-(rDrP+rDwP);
    //Output the hint.
    //Just like in Mastermind, we want to output the hints w/ 'R' first, then 'W', then '_'.
    cout<<"HINT = ";
    //R (Red pin) -> Right digit in the right place.
    for(int i=0;i<rDrP;i++) cout<<"R ";
    //W (White pin) -> Right digit in the wrong place.
    for(int i=0;i<rDwP;i++) cout<<"W ";
    //_ (No pin) -> Wrong digit in the wrong place.
    for(int i=0;i<wDwP;i++) cout<<"_ ";
    //The reason why we don't simply output the hint array is because doing so would
    //give away the correct digits and/or correct positions.
    //For ex: _R_R would give away that the 2nd & 4th digits are correct and in the correct place.
    //This defeats the purpose of Mastermind because we are NOT supposed to know exactly which digits
    //are correct and in the correct place; we're ONLY supposed to know how many.
    cout<<endl;
}