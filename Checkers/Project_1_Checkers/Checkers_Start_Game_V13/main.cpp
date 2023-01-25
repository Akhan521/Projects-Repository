/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Oct. 16, 2022, 6:55 PM
 * Purpose: Version 13 - Starting my game. 
 * 
 *  Final version of my game. A complete game of checkers can be played.
 */

//System Libraries:
#include <fstream>  //File library.
#include <queue>    //Queues.

//User Libraries:
#include "Player.h" //Our player class.

//Global Constants.
//Math, Science, Universal, Conversions, High Dimensioned Arrays.

//Function Prototypes:
void showRules(); //To show our rules.

//Execution Begins Here:
int main(int argc, char** argv) {
    cout<<"CHECKERS GAME PROJECT:\n\n";
    //Displaying the rules:
    char choice; //To hold our choice.
    do{
        cout<<"Would you like to see the rules? (Y/N)\n";
        cin>>choice;
    }while(toupper(choice)!='Y'&&toupper(choice)!='N');
    //Displaying the rules if we chose to see them.
    if(toupper(choice)=='Y')
        showRules();
    cout<<endl;
    
    //Creating a board object.
    Board *board=new Board();
    
    //Creating 2 player objects.
    cin.ignore();
    string name1,name2;
    cout<<"What will player 1's name be?\n";
    getline(cin,name1);
    cout<<"\nWhat will player 2's name be?\n";
    getline(cin,name2);
    Player *plyr1=new Player(name1);
    Player *plyr2=new Player(name2);
    cout<<endl;
    
    //Setting pieces and the board for both players.
    plyr1->setPiece(" B ");  //Player 1 has black as their color.
    cout<<plyr1->getName()<<"'s pieces are: "<<(plyr1->getPiece()==" B "?"Black\n":"Red\n");
    plyr2->setPiece(" R ");  //Player 2 has red as their color.
    cout<<plyr2->getName()<<"'s pieces are: "<<(plyr2->getPiece()==" B "?"Black\n":"Red\n");
    plyr1->setBoard(board);  //Setting player 1's board.
    plyr2->setBoard(board);  //Setting player 2's board.
    cout<<endl;
    
    //Declaring a map to keep count of how many pieces each player has captured.
    map<string,int> captPces;
    //The total number of pieces each player begins with.
    int allPces=12;  
    
    //We keep taking turns until either player has captured all opponent pieces.
    unsigned int begin=time(0); //To keep track of time.
    //As long as neither player has captured all 12 opponent pieces, we loop.
    while(captPces[plyr1->getPiece()]!=allPces&&captPces[plyr2->getPiece()]!=allPces){
        //Making a move with our player.
        cout<<plyr1->getName()<<"'s Turn:\n";
        plyr1->makeMove(captPces);
        cout<<endl;

        //Making a move with our opponent.
        cout<<plyr2->getName()<<"'s Turn:\n";
        plyr2->makeMove(captPces);
        cout<<endl;
    }
    unsigned int end=time(0);   //To keep track of time.
    
    cout<<"Closing Announcements:\n";
    cout<<"---------------------------------------------------------------------\n";
    //Storing the maximum and minimum number of pieces captured.
    int maxCapt=max(captPces[plyr1->getPiece()],captPces[plyr2->getPiece()]);
    int minCapt=min(captPces[plyr1->getPiece()],captPces[plyr2->getPiece()]);
    //Displaying the maximum and minimum number of pieces captured.
    cout<<"Time elapsed = "<<end-begin<<" seconds."<<endl;
    cout<<"Maximum number of pieces captured = "<<maxCapt<<endl;
    cout<<"Minimum number of pieces captured = "<<minCapt<<endl;
    
    //Displaying the winner:
    cout<<"\nAnnouncing the winner:\n";
    cout<<"---------------------------------------------------------------------\n";
    cout<<"The game has finished! Good game to both players, but... ";
    captPces[plyr1->getPiece()]==allPces?cout<<plyr1->getName()<<" won!\n":
                                         cout<<plyr2->getName()<<" won!\n";
    //Exit the Program - Cleanup.
    delete board; //Deleting our board.
    delete plyr1; //Deleting player 1.
    delete plyr2; //Deleting player 2.
    
    return 0;
}

//To show the rules of the game.
void showRules(){
    //Declaring our input stream object and opening our file.
    ifstream in("Rules.txt");
    //To read in lines from our file.
    string line;
    //To store these lines in a queue.
    queue<string> rules;
    //As long as we can read in a line from our file...
    while(getline(in,line)){
        //We store it in our queue.
        rules.push(line);
    }
    cout<<endl;
    //Displaying the contents of our queue.
    while(!rules.empty()){
        //Storing the line at the front of our queue.
        string line=rules.front();
        //Displaying it.
        cout<<line<<endl;
        //Popping it off.
        rules.pop();
    }
    //Cleaning up.
    in.close();
}