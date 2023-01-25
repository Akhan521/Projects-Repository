/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 11, 2022, 10:20 AM
 * Purpose: Version 1 - Creating our checkers board.
 */

//System Libraries:
#include <iostream>  //I/O Library.
#include <list>      //Lists.
#include <iterator>  //Iterators.
using namespace std;

//User Libraries:

//Global Constants.
//Math, Science, Universal, Conversions, High Dimensioned Arrays.

//Function Prototypes:

//Execution Begins Here:
int main(int argc, char** argv) {
    //Initialize the Random Number Seed.
    
    //The dimensions of our board.
    const int DIM=8;
    //A 2-D list of strings as our board.
    list<list<string>> board(DIM,list<string>(DIM));
    //We declare an iterator to work with our 2-D list.
    list<list<string>>::iterator it;
    //To keep count of what row we're on.
    int row;
    //We iterate over our 2-D list and initialize it.
    for(it=board.begin();it!=board.end();it++){
        //We declare an iterator to work with each list in our board.
        list<string>::iterator itr;
        //Here, it points to each individual list.
        for(itr=it->begin();itr!=it->end();itr++){
            //Filling our list.
            *itr="   ";
        }
    }
    //We now display our board.
    cout<<"  +---+---+---+---+---+---+---+---+"<<endl;
    for(it=board.begin(),row=1;it!=board.end();it++,row++){
        cout<<row<<" |"; //Displaying the row we're on.
        //We declare an iterator to traverse each list in our board.
        list<string>::iterator itr;
        //Here, it points to each individual list.
        for(itr=it->begin();itr!=it->end();itr++){
            //Displaying our list.
            cout<<*itr<<"|";
        }
        cout<<endl<<"  +---+---+---+---+---+---+---+---+"<<endl;
    }
    //Displaying our columns.
    cout<<"    1   2   3   4   5   6   7   8"<<endl;
    
    //Exit the Program - Cleanup.
    return 0;
}