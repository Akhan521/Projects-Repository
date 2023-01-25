/* 
 * File:   main.cpp
 * Author of template: Dr. Mark Lehr
 * Author of AI function: Aamir Khan
 * Created on May 16, 2022, 12:40 PM
 * Purpose:  Mastermind AI V.1 
 * Finding all of the digits that are correct. (NOT SOLVING)
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
    
    //Output the solution
    for(int i=0;i<10;i++){
        nGuess++;
        guess=AI(rr,rw);
        eval(code,guess,rr,rw);
    }
    cout<<"\nNumber of guesses to find all digits in our code = "<<nGuess<<endl;
    cout<<"Code = "<<code<<endl;
    
    //Exit the program
    return 0;
}

string AI(char rr,char rw){
    static int digit=-1;    //To hold which digit we're checking to see is in our code (0-8).
    static int nClrs=0;     //# of correct digits/colors we've found.
    static int index=0;     //Index variable for our correct colors array
    static char clrs[5];    //To hold our correct colors + null term.
    string sGuess="0000";   //To hold our guess string.
    clrs[4]='\0';           //Setting the null term.
    //If we don't have all 4 digits/colors...
    if(nClrs!=4&&digit<=8){
        digit+=1; //0-8.
        //Store our guess as a string. All digits are the same (0000-8888):
        sGuess[0]=sGuess[1]=
        sGuess[2]=sGuess[3]=digit+'0'; //We need to add '0' because digit is an int.
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
            //cout<<"n colors = "<<nClrs<<endl;
            //Store the remaining 9's if we have any.
            for(int i=nClrs;i<4;i++){ //Whatever colors are remaining are our 9's.
                clrs[i]='9';
                nClrs++; //We've found a color/digit, so we increment.
            }
        } 
        cout<<"\nsGuess         = "<<sGuess<<endl;
        //cout<<"# of colors    = "<<nClrs<<endl;
        //cout<<"rr             = "<<static_cast<int>(rr)<<endl;
        //cout<<"index          = "<<index<<endl;
        cout<<"Correct Digits = "<<clrs<<endl;
    }
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