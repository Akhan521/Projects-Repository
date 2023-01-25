/* 
 * File:   Node.h
 * Author:  Aamir Khan
 * Created: Nov. 22, 2022, 2:05 PM
 * Purpose: Version 15 - Adding hashing.
 */

#ifndef NODE_H
#define NODE_H

struct Node{
    //Our data.
    int data;
    //Our left child.
    Node *left;
    //Our right child.
    Node *right;
};

#endif /* NODE_H */

