/** \struct 
 * File:    Node.h
 * Author:  Aamir Khan
 * Created: Nov. 23, 2022, 10:55 AM
 * Purpose: Version 16 - Adding recursion. 
 */

#ifndef NODE_H
#define NODE_H

/** \brief A node struct. to represent nodes in a tree.*/
struct Node{
    int data;    /**< Our data. */
    Node *left;  /**< Our left child. */
    Node *right; /**< Our right child. */
};

#endif /* NODE_H */

