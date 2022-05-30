/* 
 * File:   main.cpp
 * Author of driver: Dr. Mark Lehr
 * Author of AI function: Aamir Khan
 * Created on May 18, 2022, 10:30 AM
 * Purpose:  Mastermind AI V.4 
 * 
 * Finding the correct position of the 3rd correct digit.
 * In this version, I won't be too worried about finding the 3rd position
 * by a certain # of guesses. I simply want to see if I'll be able to find it.
 */

//System Libraries
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <iomanip>
using namespace std;

//Function Prototypes
string AI(char,char);
bool eval(string,string,char &,char &);
string set();

int main(int argc, char** argv) {
    //Set the random number seed
    srand(static_cast<unsigned int>(time(0)));
    
    //Declare variables
    string code,guess;  //code to break, and current guess
    char rr,rw;         //right digit in right place vs. wrong place
    int nGuess;         //number of guesses
    
    //Initialize Values
    nGuess=0;
    code=set();
    rr=rw=0;
    
    //Loop until solved and count to find solution
    /*do{
       nGuess++;
       guess=AI(rr,rw);
    }while(eval(code,guess,rr,rw));
    */
    
    for(int i=0;i<18;i++){
        nGuess++;
        guess=AI(rr,rw);
        eval(code,guess,rr,rw);
        cout<<endl;
    }
    
    cout<<"# of guesses to find the correct position of the 3rd digit = "<<nGuess<<endl;
    cout<<"Code  = "<<code<<endl;
    cout<<"Guess = "<<guess<<endl;
    cout<<"(Only the 1st 3 correct digits will be in their correct positions.)"<<endl;
    cout<<"(The remaining digit will be a digit that isn't in our code.)\n";
    //Exit the program
    return 0;
}

string AI(char rr,char rw){
    string sGuess="0000";   //To hold our guess string.
    static int digit=-1;    //To hold which digit we're checking to see is in our code (0-8).
    static int nGuesses=1;  //To hold how many guesses we've made. 
    static int nClrs=0;     //# of correct digits/colors we've found (Should total to 4).
    static int index=0;     //Index variable for our arrays.
    static int nWaysA=1;    //To hold the current way we're trying out the 1st digit.
    static int nWaysB=1;    //To hold which way we're trying out the 2nd digit or B.
    static int nWaysC=1;    //To hold which way we're trying out the 3rd digit or C.
    static char clrs[5];    //To hold our correct colors + null term.
    clrs[4]='\0';           //Setting the null term.
    static bool fndPos1,    //Whether we've found our first digit's position.
                fndPos2,    //Whether we've found our second digit's position.
                fndPos3;    //Whether we've found our third digit's position.
    if(nWaysA==1&&!fndPos1) //If we're on our 1st way to place A, and we haven't already found pos1,
        fndPos1=false;      //then we set it to false. (Accounts for when our digit is in index 0).
    if(nWaysB==1&&!fndPos2) //If we're on our 1st way to place B, and we haven't already found pos2,
        fndPos2=false;      //then we set it to false. (Accounts for when our digit is in index 0).
    if(nWaysC==1)           //If we're on our 1st way to find C, then we set fndPos3 to false.
        fndPos3=false;      //Only on the 1st way, we set it to false.
    static int pos1=-1,     //Correct index of the 1st correct digit.
               pos2=-1,     //Correct index of the 2nd correct digit.
               pos3=-1;     //Correct index of the 3rd correct digit.
    static char wrong;      //To hold a wrong digit. (We'll use this to find our positions.)
    static bool isVldHnt;   //To hold whether we have a valid hint or not.
                            //When we make the guesses 0000-8888, if one of those digits happens
                            //to be in our code, rr would = 1 on the next guess, and this could 
                            //falsely set fndPos1 to true. We want to set fndPos1 only when we've
                            //found all of our digits and the hint is not for guesses 0000-8888.
    
    //cout<<"Guess # "<<nGuesses<<endl;
    //If we don't have all 4 digits or we're still testing for digits in our code (0-8).
    if(nClrs!=4||digit<=7){ 
        if(digit!=8){   //If we haven't tried digits 0-8...
            digit+=1;   //0,1,2,...,8. -> Which digits are in our code?
        }
        //Store our guess as a string All digits are the same (0000-8888):
        sGuess[0]=sGuess[1]=
        sGuess[2]=sGuess[3]=digit+'0'; //We need to add '0' because digit is an int.
        //If we have none correct, we save the digit as a wrong digit.
        //Moreover, nGuesses is < 10 because we choose our wrong digit by the 9th guess.
        if(rr==0&&rw==0&&nGuesses<10)
            wrong=sGuess[0]-1;
        //If 8 is in our code, we'll know by guess 10. We store our 8's if we have any.
        if(nGuesses==10&&rr>=1&&rr<=4){
            int colors=nClrs+rr; //To hold how many colors we'll have after filling our 8's
            //Store the remaining 8's if we have any.
            for(int i=nClrs;i<colors;i++){ //Whatever colors are remaining are our 9's.
                clrs[i]='8';
                nClrs++; //We've found a color/digit, so we increment.
                //cout<<"nClrs = "<<nClrs<<endl;
            }
        }
        //If we have a correct digit, we save it into our colors array.
        //We know that a color is correct if rr is >=1 & <= 4.
        //We also can't already have 4 digits by this point.
        else if(rr>=1&&rr<=4&&nClrs!=4){
            //Copy over the colors that are correct. We can have duplicates.
            for(int i=index;i<index+rr;i++){
                //Because the rr hint is based off of the previous guess,
                //we need to subtract sGuess[i] by 1 to store the previous #.
                clrs[i]=sGuess[0]-1; //All our #'s will be the same, so we just take sGuess[0].
                nClrs++;             //We've found a color/digit, so we increment.
            }
            index+=rr;               //We increment by rr to go to the next available index.
        }
        //If by the 9th guess (8888) we don't have all of our digits, then
        //that means 9 is our last digit and we'll save it on the 10th guess.
        if(nGuesses==10&&nClrs!=4){
            //Store the remaining 9's if we have any.
            for(int i=nClrs;i<4;i++){ //Whatever colors are remaining are our 9's.
                clrs[i]='9';
                nClrs++; //We've found a color/digit, so we increment.
                //cout<<"nClrs = "<<nClrs<<endl;
            }
        }
    }
    //Determining whether we have a valid hint for testing position 1.
    //The reason I specify <=10 instead of <10 is because on the 10th guess,
    //we're still processing the hint for 8888 (9th guess), so we want to set isVldHnt on the next guess.
    //For ex. if 8 was in our code, then 8888 would make rr = 1 on the next guess, and this would
    //falsely set fndPos1 to true, when we want to start finding positions based on hints for guesses
    //that aren't all the same digits. (We disregard hints for the guesses 0000-8888).
    if(nGuesses<=10&&nClrs==4&&rr>=1&&rr<=4){
        isVldHnt=false;  //We're processing a guess w/ 4 of the same digits, so we can't use this hint.
    }
    else{//Once we have all 4 digits, this is set to true, meaning we're now dealing w/ hints we can use.
        isVldHnt=true; //We're now processing guesses w/ different digits.
                       //This means that the hints are based on guesses w/ different digits.
    }
    //If we've found our 4 digits, we can begin finding our positions.
    //We start checking for positions from the 10th guess and onwards.
    if(nClrs==4){
        //Finding the position of our 1st digit.
        if(!fndPos1){ //If we haven't found the position of our 1st digit...
            //If we're trying out the 1st way ( AWWW ), we reinitialize the index.
            if(nWaysA==1){
                index=0;
                //On our 1st variation to place A, we set pos1 to 0.
                pos1=0;
            }
            //We set the correct digit in the 1st peg.
            sGuess[index]=clrs[0]; // A W W W
            for(int i=0;i<4;i++){ //Everything else becomes a wrong digit.
                if(i!=index)sGuess[i]=wrong;
            }
            //If we have a correct digit in the wrong place, we try out the other ways...
            //(W A W W), (W W A W), & (W W W A).
            if(rw==1){
                nWaysA++; //Trying out a different positioning or way.
                //We set the next peg as the correct color.
                sGuess[++index]=clrs[0];
                //Again, the rest become wrong digits.
                for(int i=0;i<4;i++){
                    if(i!=index)sGuess[i]=wrong;
                }
            }
            //Saving the 1st correct digit in the correct position.
            //If we have rr=1 and we have a valid hint for testing a position.
            if(rr==1&isVldHnt){
                //If we've found the position, we set fndPos1 to true.
                fndPos1=true;
                //Store the index of where the 1st digit is located.
                pos1=index;
            }
        }
        //If we've already found pos 1, we now move on to finding pos 2.
        if(fndPos1&&!fndPos2){
            //Finding the position of the 2nd digit:
            if(nWaysB==1) //If we're on our first way to place B, we set index to 0.
                index=0;  //Resetting to 0.
            static int bIdx[3]; //To hold the indices that we can try B in.
            int temp=0;         //A temporary variable for indexing the bIdx array;
            if(nWaysB==1){ //On the 1st way, we save all the indices we can try B in.
                for(int i=0;i<4;i++){
                    if(i!=pos1){ //For any index besides position 1...
                        //Storing the indices we can try B in.
                        bIdx[temp]=i;
                        //cout<<bIdx[temp]<<" ";
                        temp++;  //Increment our bIdx index variable.
                    }
                }
            }
            //Trying out the 1st way to have the 2nd digit. (For Ex. ABWW)
            sGuess[bIdx[index]]=clrs[1]; //Index begins with 0.
            //Storing the 1st correct digit in our guess.
            sGuess[pos1]=clrs[0];
            //Marking the rest as wrong.
            for(int i=0;i<4;i++){
                if(i!=bIdx[index]&&i!=pos1)
                    sGuess[i]=wrong;
            }
            if(rw==1){
                nWaysB++; //Trying out a different way to place B.
                sGuess[bIdx[++index]]=clrs[1];
                //Marking the rest as wrong.
                for(int i=0;i<4;i++){
                    if(i!=bIdx[index]&&i!=pos1)
                        sGuess[i]=wrong;
                }
            }
            //Saving the correct digit in the correct position.
            if(rr==2){ //If A and B are both correct...
                fndPos2=true;
                pos2=bIdx[index];
                //cout<<"\nFound pos 2 = "<<pos2<<endl;
            }
        }
        //If we've found the positions of the 1st 2 digits & haven't found the 3rd...
        if(fndPos1&&fndPos2&&!fndPos3){
            if(nWaysC==1) //If we're on our first way to place C, we set index to 0.
                index=0;
            static int cIdx[2]; //To hold the indices that we can try C in.
            int temp=0;         //A temporary variable for indexing the cIdx array;
            if(nWaysC==1){ //On the 1st way, we save all the indices we can try C in.
                for(int i=0;i<4;i++){
                    if(i!=pos1&&i!=pos2){ //For any index besides position 1 and 2...
                        //Storing the indices we can try C in.
                        cIdx[temp]=i;
                        //cout<<cIdx[temp]<<" "; //Indices that C can be in.
                        temp++;  //Increment our bIdx index variable.
                    }
                }
            }
            //Trying out the 1st way to have the 3rd digit. (For Ex. ABCW)
            sGuess[cIdx[index]]=clrs[2]; //Index begins with 0.
            //Storing the 1st correct digit in our guess.
            sGuess[pos1]=clrs[0];
            //Storing the 2nd correct digit in our guess.
            sGuess[pos2]=clrs[1];
            //Marking the rest as wrong.
            for(int i=0;i<4;i++){
                if(i!=cIdx[index]&&i!=pos1&&i!=pos2)
                    sGuess[i]=wrong;
            }
            //If our C needs to be in a different position, we try a different variation.
            if(rw==1){
                nWaysC++; //Trying out a different way to place C.
                //cout<<"Way = "<<nWaysC<<endl;
                sGuess[cIdx[++index]]=clrs[2];
                //Marking the rest as wrong.
                for(int i=0;i<4;i++){
                    if(i!=cIdx[index]&&i!=pos1&&i!=pos2)
                        sGuess[i]=wrong;
                }
            }
            //Saving the correct digit in the correct position.
            if(rr==3){ //If A, B, and C are all correct...
                fndPos3=true;
                pos3=cIdx[index];
                //cout<<"\nFound pos 3 = "<<pos3<<endl;
            }
        }
        //If we've found our 3 positions, we simply return our guess with those 3 correct digits.
        if(fndPos1&&fndPos2&&fndPos3){
            sGuess[pos1]=clrs[0]; //1st correct digit.
            sGuess[pos2]=clrs[1]; //2nd correct digit.
            sGuess[pos3]=clrs[2]; //3rd correct digit.
            //Setting the rest as wrong digits.
            for(int i=0;i<4;i++){
                if(i!=pos1&&i!=pos2&&i!=pos3)
                    sGuess[i]=wrong;
            }
        }
    }
    //Outputting our guess.
    //cout<<"\nGuess        = "<<sGuess<<endl; //The guess we're returning.
    //cout<<"Code Digits  = "<<clrs<<endl;     //The digits in our code.
    //Outputting whether we've found our positions.
    //We start checking positions from guess 10.
    /*if(nGuesses>=10){
        cout<<"\nFound pos1?  = ";
        fndPos1==true?cout<<"Yes":cout<<"No";
        cout<<"\nFound pos2?  = ";
        fndPos2==true?cout<<"Yes":cout<<"No";
        cout<<"\nFound pos3?  = ";
        fndPos3==true?cout<<"Yes":cout<<"No";
        cout<<endl;
    }
    */ 
    nGuesses++; //Increment our # of guesses.
    return sGuess;
}

bool eval(string code,string guess,char &rr,char &rw){
    string check="    ";
    rr=0,rw=0;
    //Check how many are right place
    for(int i=0;i<code.length();i++){
        if(code[i]==guess[i]){
            rr++;
            check[i]='x';
            guess[i]='x';
        }
    }
    //Check how many are wrong place
    for(int j=0;j<code.length();j++){
        for(int i=0;i<code.length();i++){
            if((i!=j)&&(code[i]==guess[j])&&(check[i]==' ')){
                rw++;
                check[i]='x';
                break;
            }
        }
    }
    
    //Found or not
    if(rr==4)return false;
    return true;
}

string set(){
    string code="0000";
    for(int i=0;i<code.length();i++){
        code[i]=rand()%10+'0';
    }
    return code;
}