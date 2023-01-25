/** \class 
 * File:    Tree.h
 * Author:  Aamir Khan
 * Created: Nov. 23, 2022, 10:55 AM
 * Purpose: Version 16 - Adding recursion.
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

/** \brief A tree class. */
class Tree{
    private:
        Node *root; /**< Our root node. */
        /** \brief Utility functions: */
        Node *newNode(int);        /**< Creates a new node. */
        void prntPre(Node *);      /**< Pre-Order traversal. */
        void prntIn(Node *);       /**< In-Order traversal. */
        void prntPost(Node *);     /**< Post-Order traversal. */
        void insert(Node *&,int);  /**< Inserts a node into our tree. */
        void destroy(Node *&);     /**< Destroys our tree. */
        int height(Node *);        /**< Determines the height of our tree. */
        void delNode(Node *&,int); /**< Deletes a node from our tree. */
        Node *findMin(Node *);     /**< Finds the node w/ the smallest value. */
        void lftRot(Node *&);      /**< Performs a left rotation about a root node. */
        void rghtRot(Node *&);     /**< Performs a right rotation about a root node. */
        void lftRghtRot(Node *&);  /**< Performs a left-right rotation about a root node. */
        void rghtLftRot(Node *&);  /**< Performs a right-left rotation about a root node. */
        void balance(Node *&);     /**< Balances our tree using tree rotations. */
    public:
        /** \brief Our constructor. 
         *
         *  Sets our root node to NULL.
         */
        Tree(){root=NULL;}
        /** \brief Overloaded constructor.
         * 
         *  Fills our tree w/ N randomly-filled nodes.
         */
        Tree(int n){fill(n);}
        /** \brief Our destructor.
         *  
         *  Destroys our tree.
         * 
         *  @param root Our root node.
         */
        ~Tree(){destroy(root);}
        /** \brief Pre-Order traversal.
         *  
         *  Traverses our tree using pre-order traversal.
         *  @param root Our root node.
         */
        void prntPre(){prntPre(root); cout<<endl;}      
        /** \brief In-Order traversal. 
         * 
         *  Traverses our tree using in-order traversal.
         *  @param root Our root node.
         */
        void prntIn(){prntIn(root); cout<<endl;} 
        /** \brief Post-Order traversal. 
         * 
         *  Traverses our tree using post-order traversal.
         *  @param root Our root node.
         */
        void prntPost(){prntPost(root); cout<<endl;}
        /** \brief Level-Order traversal. 
         * 
         *  Traverses our tree using level-order traversal.
         */
        void prntLvl(); 
        /** \brief Determines if our tree is empty. 
         * 
         *  If our root is NULL, we have an empty tree.
         *  Otherwise, we don't have an empty tree.
         *  @return bool Whether our tree is empty or not.
         */
        bool empty(){return root==NULL;}
        /** \brief Inserts a node into our tree.
         * 
         *  Inserts a node into our tree recursively.
         *  @param value The value to be inserted.
         *  @param root Our root node.
         */
        void insert(int value){insert(root,value);}  
        /** \brief Fills a tree with randomly-filled nodes. 
         * 
         *  @param N The number of nodes to fill our tree with.
         */
        void fill(int);  
        /** \brief Determines the height of our tree. 
         * 
         *  Determines the max depth of our tree.
         *  @param root Our root node.
         *  @return height The height of our tree.
         */
        int height(){return height(root);}
        /** \brief Deletes a node from our tree. 
         * 
         *  Deletes a node from our tree recursively.
         *  @param value The value to be deleted.
         *  @param root Our root node.
         */
        void delNode(int value){delNode(root,value);}
        /** \brief Finds the node w/ the smallest value. 
         * 
         *  Finds the node w/ the smallest value in our tree.
         *  @param root Our root node.
         *  @return node The node w/ the smallest value in our tree.
         */
        Node *findMin(){return findMin(root);}
};

#endif /* TREE_H */

