/* 
 * File:   main.cpp
 * Author of template: Dr. Mark Lehr
 * Author of AI function: Aamir Khan
 * Created on May 16, 2022, 10:30 PM
 * Purpose:  Mastermind AI V.3 
 * 
 * Finding the correct position of the 2nd correct digit.
 * By the 10th guess, we'll know all of our digits.
 * It takes 3 guesses (10+3=13) to find position 1, so we should have 
 * the 1st position by the 14th guess. It takes 2 more guesses (14+2=16)
 * to find the 2nd position. So, we'll have the 2nd position by 16 guesses. 
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
    
    for(int i=0;i<16;i++){
        nGuess++;
        //cout<<"Guess "<<nGuess<<":\n";
        guess=AI(rr,rw);
        eval(code,guess,rr,rw);
        cout<<endl;
    }
    
    cout<<"# of guesses to find the correct position of the 2nd digit = "<<nGuess<<endl;
    cout<<"Code  = "<<code<<endl;
    cout<<"Guess = "<<guess<<endl;
    cout<<"(Only the 1st 2 correct digits will be in their correct positions.)"<<endl;
    cout<<"(The rest of the digits will be digits that aren't in our code.)\n";
    //Exit the program
    return 0;
}

string AI(char rr,char rw){
    string sGuess="0000";   //To hold our guess string.
    static int digit=-1;    //To hold which digit we're checking to see is in our code (0-8).
    static int nGuesses=1;  //To hold how many guesses we've made. 
    static int nClrs=0;     //# of correct digits/colors we've found.
    static int index=0;     //Index variable for our correct colors array
    static int nWaysA=1;    //To hold the current way we're trying out the 1st digit.
    static int nWaysB=1;    //To hold which way we're trying out the 2nd digit or B.
    static char clrs[5];    //To hold our correct colors + null term.
    clrs[4]='\0';           //Setting the null term.
    static bool fndPos1,    //Whether we've found our first digit's position.
                fndPos2;    //Whether we've found our second digit's position.
    if(nWaysA==1&&!fndPos1) //If we're on our 1st way to place A, and we haven't already found pos1,
        fndPos1=false;      //then we set it to false. (Accounts for when our digit is in index 0).
    if(nWaysB==1)           //If we're on our 1st way to find B, then we set fndPos2 to false.
        fndPos2=false;      //Only on the 1st way, we set it to false.
    static int pos1=-1,     //Correct index of the 1st correct digit.
               pos2=-1;     //Correct index of the 2nd correct digit.
    static char wrong;      //To hold a wrong digit. (We'll use this to find our positions.)
    //If we don't have all 4 digits/colors...
    if(nClrs!=4||digit<=7){
        if(digit!=8)  //We want to stop by digit 8. (0000-8888).
            digit+=1; //0-8.
        //Store our guess as a string. All digits are the same (0000-8888):
        sGuess[0]=sGuess[1]=
        sGuess[2]=sGuess[3]=digit+'0'; //We need to add '0' because digit is an int.
        //If we have none correct, we save it as a wrong digit.
        if(rr==0&&rw==0)
            wrong=sGuess[0]-1;
        //If 8 is in our code, we'll know by guess 10. We store our 8's if we have any.
        if(nGuesses==10&&rr>=1&&rr<=4){
            int colors=nClrs+rr; //To hold how many colors we'll have after filling our 8's
            //Store the remaining 8's if we have any.
            for(int i=nClrs;i<colors;i++){ //Whatever colors are remaining are our 9's.
                clrs[i]='8';
                nClrs++; //We've found a color/digit, so we increment.
            }
        }
        cout<<"nClrs = "<<nClrs<<endl;
        //If we have a correct digit/color, we save it into our colors array.
        //We know that a color is correct if rr is in between 1 and 4 inclusive.
        if(rr>=1&&rr<=4&&nClrs!=4){
            //Copy over the colors that are correct. We can have duplicates.
            for(int i=index;i<index+rr;i++){
                //Because the rr hint is based off of the previous guess,
                //we need to subtract sGuess[i] by 1 to store the previous #.
                clrs[i]=sGuess[0]-1; //All our #'s will be the same, so we just take sGuess[0].
                nClrs++;             //We've found a color/digit, so we increment.
            }
            index+=rr;               //We increment by rr to go to the next available index.
        }
        //If by guess 10, we don't have all of our digits, we know that 9 is our last digit.
        if(nGuesses==10&&nClrs!=4){
            //Store the remaining 9's if we have any.
            for(int i=nClrs;i<4;i++){ //Whatever colors are remaining are our 9's.
                clrs[i]='9';
                nClrs++; //We've found a color/digit, so we increment.
            }
        } 
    }
    //If we've found our 4 digits, we can begin finding our positions.
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
            //Saving the correct digit in the correct position.
            //We ONLY want to set fndPos1 based on hints of guesses past 0000-8888.
            //On the 10th guess, we'll have a hint based on our 9th guess (8888).
            //We disregard this hint because this could falsely set fndPos1 to true
            //when we haven't actually found our 1st digit's position.
            if(rr==1&&nGuesses>10){
                //If we've found the position, we set fndPos1 to true.
                fndPos1=true;
                //Store the index of where the 1st digit is located.
                pos1=index;
                //cout<<"\nPos1 = "<<pos1<<endl;
                //cout<<"Digit = "<<answr[pos1]<<endl;
            }
        }
        //If we've already found pos 1, we now move on to fidning pos 2.
        else if(fndPos1&&!fndPos2){
            //cout<<"Found pos 1 = "<<pos1<<endl;
            //Finding the position of the 2nd digit:
            //If we haven't found
            if(nWaysB==1) //If we're on our first way to place B, we set index to 0.
                index=0;  //Resetting to 0.
            static int bIdx[3]; //To hold the indices that we can try B in.
            int temp=0;         //A temporary variable for indexing the bIdx array;
            if(nWaysB==1){ //On the 1st way, we save all the indices we can try B in.
                for(int i=0;i<4;i++){
                    if(i!=pos1){ //For any index besides position 1...
                        //Storing the indices we can try B in.
                        bIdx[temp]=i;
                        temp++;  //Increment our bIdx index variable.
                    }
                }
            }
            //cout<<"bIdx["<<index<<"] = "<<bIdx[index]<<endl;
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
                //cout<<"Way = "<<nWaysB<<endl;
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
        //If we've found both positions, we simply return our guess with those 2 correct digits.
        else{
            sGuess[pos1]=clrs[0]; //1st correct digit.
            sGuess[pos2]=clrs[1]; //2nd correct digit.
            //Setting the rest as wrong digits.
            for(int i=0;i<4;i++){
                if(i!=pos1&&i!=pos2)
                    sGuess[i]=wrong;
            }
        }
    }
    //cout<<"Found pos1?    = ";
    //fndPos1==true?cout<<"yes":cout<<"no"<<endl;
    //cout<<"\nFound pos2?    = ";
    //fndPos2==true?cout<<"yes":cout<<"no"<<endl;
    cout<<"\nsGuess         = "<<sGuess<<endl;
    cout<<"Correct Digits = "<<clrs<<endl;
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