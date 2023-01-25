/* 
 * File:    main.cpp
 * Author:  Aamir Khan
 * Created: Nov. 23, 2022, 10:55 AM
 * Purpose: Version 16 - Adding recursion.
 * 
 * Note: Recursion is used to display our time as a fraction of minutes. 
 * It is also used to display our King pieces in descending order.
 * (I use a recursive quick-sort to display pieces in descending order.)
 */

//System Libraries:
#include <fstream>  //File library.

//User Libraries:
#include "Player.h" //Our player class.

//Global Constants.
//Math, Science, Universal, Conversions, High Dimensioned Arrays.

//Function Prototypes:
void showRules();         //To show our rules.
int gcd(int,int);         //A recursive GCD function.
int hashFnc(string);      //Hashes a string and returns a random value.
bool find(list<int>,int); //Searches a list for a value.

//Execution Begins Here:
int main(int argc, char** argv) {
    cout<<"CHECKERS GAME PROJECT:\n\n";
    
    //Set the random number seed.
    srand(static_cast<unsigned int>(time(0)));
    
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
    
    //Declaring 2 trees to hold the pieces each player has captured.
    Tree *tree1=new Tree(); //For player 1.
    Tree *tree2=new Tree(); //For player 2.
    
    //Declaring a map to keep count of how many pieces each player has captured.
    map<string,int> captPces;
    //The total number of pieces each player begins with.
    int allPces=12;
    
    //Declaring a hash table that will be used to check whether a randomly 
    //chosen piece was possibly captured at the end of our game or not.
    list<int> table[allPces]; //12 valid indices/lists.
    
    //We keep taking turns until either player has captured all opponent pieces.
    unsigned int begin=time(0);     //To keep track of time.
    //As long as neither player has captured all 12 opponent pieces, we loop.
    while(captPces[plyr1->getPiece()]!=allPces&&
          captPces[plyr2->getPiece()]!=allPces){
        //Making a move with our player.
        cout<<plyr1->getName()<<"'s Turn:\n";
        plyr1->makeMove(captPces,tree1);
        //After our turn, we store our count in the hash table.
        int indx=hashFnc(plyr1->getName())%allPces;
        table[indx].push_back(captPces[plyr1->getPiece()]);
        cout<<endl;

        //Making a move with our opponent.
        cout<<plyr2->getName()<<"'s Turn:\n";
        plyr2->makeMove(captPces,tree2);
        //After the opponent's turn, we store their count in the hash table.
        indx=hashFnc(plyr2->getName())%allPces;
        table[indx].push_back(captPces[plyr2->getPiece()]);
        cout<<endl;
        
    }
    unsigned int tot=time(0)-begin; //To keep track of time.
    //We'll use the GCD of our time and 60 to display the time in minutes.
    int dnmtr=gcd(tot,60); 
    
    cout<<"Closing Announcements:\n";
    cout<<"---------------------------------------------------------------------\n";
    //Storing the maximum and minimum number of pieces captured.
    int maxCapt=max(captPces[plyr1->getPiece()],captPces[plyr2->getPiece()]);
    int minCapt=min(captPces[plyr1->getPiece()],captPces[plyr2->getPiece()]);
    //Displaying the maximum and minimum number of pieces captured.
    cout<<"Time elapsed = "<<tot/dnmtr<<"/"<<60/dnmtr<<" minutes.\n"<<endl;
    cout<<"Maximum number of pieces captured = "<<maxCapt<<endl;
    cout<<"Minimum number of pieces captured = "<<minCapt<<endl;
    cout<<endl;
    //Displaying the pieces player 1 has captured.
    cout<<plyr1->getName()<<" has captured the following pieces:\n";
    //If player 1 has captured at least 1 piece, we display the pieces they've captured.
    if(!tree1->empty()) tree1->prntIn();
    //Otherwise, we display that they've captured none.
    else cout<<"NONE\n";
    //Displaying the pieces player 2 has captured.
    cout<<plyr2->getName()<<" has captured the following pieces:\n";
    //If player 2 has captured at least 1 piece, we display the pieces they've captured.
    if(!tree2->empty()) tree2->prntIn();
    //Otherwise, we display that they've captured none.
    else cout<<"NONE\n";
    
    //Checking to see if a random piece was possibly captured.
    cout<<"\nChecking to see if a random piece was possibly captured:\n";
    cout<<"---------------------------------------------------------------------\n";
    int randPce=rand()%allPces+1; //A random piece between 1-12.
    cout<<"Random piece to check = "<<randPce<<endl;
    //Getting player 1's hash value.
    int indx=hashFnc(plyr1->getName())%allPces;
    //Looking through our hashed list to see if we might've captured the piece.
    bool found=find(table[indx],randPce);
    found?cout<<plyr1->getName()<<" might've captured piece "<<randPce<<"."<<endl:
          cout<<plyr1->getName()<<" did not capture piece "<<randPce<<"."<<endl;
    //Getting player 2's hash value.
    indx=hashFnc(plyr2->getName())%allPces;
    //Looking through our hashed list to see if we might've captured the piece.
    found=find(table[indx],randPce);
    found?cout<<plyr2->getName()<<" might've captured piece "<<randPce<<"."<<endl:
          cout<<plyr2->getName()<<" did not capture piece "<<randPce<<"."<<endl;
    
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
    delete tree1; //Deleting player 1's tree.
    delete tree2; //Deleting player 2's tree.
    
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

//A recursive GCD function.
int gcd(int m,int n){
    //Base case:
    if(m%n==0) return n;
    //Recursion:
    return gcd(n,m%n);
}

//Hashes a string.
int hashFnc(string s){
    int hVal=0;    //Our hash value.
    short m=32767; //Size of a short.
    //Looping for as many characters we have...
    for(char c:s){
        //Updating our hash value to some random value.
        hVal=(hVal<<c)%m+(c*c)%m;
    }
    //Returning our hash value.
    return hVal;
}

//Searches a list for a value and returns whether it was found or not.
bool find(list<int> l,int target){
    //Looking through every element of the list.
    for(int val:l){
        //If we've found our value, we return true.
        if(val==target) return true;
    }
    //Not found...
    return false;
}