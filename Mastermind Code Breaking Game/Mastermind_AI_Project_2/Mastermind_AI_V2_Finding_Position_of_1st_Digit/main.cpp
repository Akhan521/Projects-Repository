/* 
 * File:   main.cpp
 * Author of template: Dr. Mark Lehr
 * Author of AI function: Aamir Khan
 * Created on May 16, 2022, 9:40 PM
 * Purpose:  Mastermind AI V.2 
 *
 * Finding the correct position of the 1st correct digit.
 * The # of guesses it takes to find the 1st position should be 12, but I just focus
 * on finding the 1st position in 14 guesses. That's because by the 10th guess, we'll have all of
 * our digits. It takes 3 more to find the 1st position (10+3=13), so by the 14th, we'll be done.
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
    
    //We need 9 guesses to find what digits are in our code.
    //By the 10th guess, we'll have all of our correct digits.
    //We need 3 more to find the position of the 1st correct digit.
    //By the 14th guess, we should have the 1st digit in the right place.
    for(int i=0;i<14;i++){
        nGuess++;
        guess=AI(rr,rw);
        eval(code,guess,rr,rw);
    }
    cout<<"\n# of guesses to find the correct position of the 1st digit = "<<nGuess<<endl;
    cout<<"Code  = "<<code<<endl;
    cout<<"Guess = "<<guess<<endl;
    cout<<"(Only the 1st correct digit will be in its correct position.)"<<endl;
    cout<<"(The rest of the digits will be digits that aren't in our code.)\n";
    //Exit the program
    return 0;
}

string AI(char rr,char rw){
    static int digit=-1;    //To hold which digit we're checking to see is in our code (0-8).
    static int nClrs=0;     //# of correct digits/colors we've found.
    static int index=0;     //Index variable for our correct colors array
    static int nWays=1;     //To hold the current way we're trying out a position.
    static char clrs[5];    //To hold our correct colors + null term.
    string sGuess="0000";   //To hold our guess string.
    clrs[4]='\0';           //Setting the null term.
    static char wrong;      //To hold a wrong digit. (We'll use this to find our positions.)
    //If we don't have all 4 digits/colors...
    if(nClrs!=4&&digit<=8){
        digit+=1; //0-8.
        //Store our guess as a string. All digits are the same (0000-8888):
        sGuess[0]=sGuess[1]=
        sGuess[2]=sGuess[3]=digit+'0'; //We need to add '0' because digit is an int.
        //If we have none correct, we save it as a wrong digit.
        if(rr==0&&rw==0)
            wrong=sGuess[0]-1;
        //If we have a correct digit/color, we save it into our colors array.
        //We know that a color is correct if rr is not 0 (in between 1 and 4 inclusive).
        if(rr>=1&&rr<=4){
            //Copy over the colors that are correct. We can have duplicates.
            for(int i=index;i<index+rr;i++){
                //Because the rr hint is based off of the previous guess,
                //we need to subtract sGuess[i] by 1 to store the previous #.
                clrs[i]=sGuess[0]-1; //All our #'s will be the same, so we just take sGuess[0].
                nClrs++;             //We've found a color/digit, so we increment.
            }
            index+=rr;               //We increment by rr to go to the next available index.
        }
        //If we reach 9999 but we don't have all of our digits, then that means 9 is our last digit.
        if(digit==9&&nClrs!=4){
            //Store the remaining 9's if we have any.
            for(int i=nClrs;i<4;i++){ //Whatever colors are remaining are our 9's.
                clrs[i]='9';
                nClrs++; //We've found a color/digit, so we increment.
            }
        } 
    }
    //If we've found our 4 digits, we can begin finding our positions.
    else{
        //If we're trying out the 1st way ( AWWW ), we reinitialize the index.
        if(nWays==1) index=0;
        //cout<<"rr = "<<static_cast<int>(rr)<<endl;
        //cout<<"rw = "<<static_cast<int>(rw)<<endl;
        //We set the correct digit in the 1st peg.
        sGuess[index]=clrs[0]; // A W W W
        for(int i=0;i<4;i++){ //Everything else becomes a wrong digit.
            if(i!=index)sGuess[i]=wrong;
        }
        //If we have a correct digit in the wrong place, we try out the other ways...
        //(W A W W), (W W A W), & (W W W A).
        if(rw==1){
            nWays++; //Trying out a different positioning or way.
            //We set the next peg as the correct color.
            sGuess[++index]=clrs[0];
            //Again, the rest become wrong digits.
            for(int i=0;i<4;i++){
                if(i!=index)sGuess[i]=wrong;
            }
        }
        
    }
    //cout<<"\nsGuess         = "<<sGuess<<endl;
    //cout<<"guess          = "<<guess<<endl;
    //cout<<"Correct Digits = "<<clrs<<endl;
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