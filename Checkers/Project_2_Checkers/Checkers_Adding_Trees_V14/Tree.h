/* 
 * File:    Tree.h
 * Author:  Aamir Khan
 * Created: Nov. 22, 2022, 11:25 AM
 * Purpose: Version 14 - Adding trees.
 */

#ifndef TREE_H
#define TREE_H

//Our System + User Libraries:
#include <iostream>  //I/O Library.
#include <ctime>     //Rand() + Srand().
#include <queue>     //Queues - Level-Order Traversal.
#include <cstdlib>   //CSTD Library.
#include "Node.h"    //Our Node struct.
using namespace std;

class Tree{
    private:
        //Our root node.
        Node *root;
        //Utility functions:
        Node *newNode(int);        //Creates a new node.
        void prntPre(Node *);      //Pre-Order traversal.
        void prntIn(Node *);       //In-Order traversal.
        void prntPost(Node *);     //Post-Order traversal.
        void insert(Node *&,int);  //Inserts a node into our tree.
        void destroy(Node *&);     //Destroys our tree.
        int height(Node *);        //Determines the height of our tree.
        void delNode(Node *&,int); //Deletes a node from our tree.
        Node *findMin(Node *);     //Finds the node w/ the smallest value.
        void lftRot(Node *&);      //Performs a left rotation about a root node.
        void rghtRot(Node *&);     //Performs a right rotation about a root node.
        void lftRghtRot(Node *&);  //Performs a left-right rotation about a root node.
        void rghtLftRot(Node *&);  //Performs a right-left rotation about a root node.
        void balance(Node *&);     //Balances our tree using tree rotations.
    public:
        //Our constructor.
        Tree(){root=NULL;}
        //Overloaded constructor.
        Tree(int n){fill(n);}
        //Our destructor.
        ~Tree(){destroy(root);}
        //Pre-Order traversal.
        void prntPre(){prntPre(root); cout<<endl;}      
        //In-Order traversal.
        void prntIn(){prntIn(root); cout<<endl;} 
        //Post-Order traversal.
        void prntPost(){prntPost(root); cout<<endl;}
        //Level-Order traversal.
        void prntLvl(); 
        //Determines if our tree is empty.
        bool empty(){return root==NULL;}
        //Inserts a node into our tree.
        void insert(int value){insert(root,value);}  
        //Fills a tree with randomly-filled nodes.
        void fill(int);  
        //Determines the height of our tree.
        int height(){return height(root);}
        //Deletes a node from our tree.
        void delNode(int value){delNode(root,value);}
        //Finds the node w/ the smallest value.
        Node *findMin(){return findMin(root);}
};

#endif /* TREE_H */

