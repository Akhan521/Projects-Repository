/* 
 * File:    Tree.cpp
 * Author:  Aamir Khan
 * Created: Nov. 23, 2022, 10:55 AM
 * Purpose: Version 16 - Adding recursion.
 */

//Including our tree class header file:
#include "Tree.h"

/** Creates a new node and initializes it. */
Node *Tree::newNode(int value){
    //Allocating memory for our new node.
    Node *node=new Node;
    //Setting its data.
    node->data=value;
    //Setting its pointers.
    node->left=NULL;
    node->right=NULL;
    //Returning our new node.
    return node;
}
/** Pre-Order traversal. */
void Tree::prntPre(Node *root){
    //Base case:
    if(root==NULL) return;
    //Root->Left->Right:
    cout<<root->data<<" ";
    prntPre(root->left);
    prntPre(root->right);
}
/** In-Order traversal. */
void Tree::prntIn(Node *root){
    //Base case:
    if(root==NULL) return;
    //Left->Root->Right:
    prntIn(root->left);
    cout<<root->data<<" ";
    prntIn(root->right);
}
/** Post-Order traversal. */
void Tree::prntPost(Node *root){
    //Base case:
    if(root==NULL) return;
    //Left->Right->Root:
    prntPost(root->left);
    prntPost(root->right);
    cout<<root->data<<" ";
}
/** Level-Order traversal. */
void Tree::prntLvl(){
    //Creating an empty queue.
    queue<Node *> q;
    //Storing the root in a temp. variable.
    Node *temp=root;
    //Looping while we have a valid node:
    while(temp){
        //1. Outputting the current node's data.
        cout<<temp->data<<" ";
        //2. Enqueueing its children.
        if(temp->left)  q.push(temp->left);
        if(temp->right) q.push(temp->right);
        //3. Dequeueing a node and assigning it to temp.
        if(!q.empty()){
            //Assigning the node at the front to temp.
            temp=q.front();
            //Popping the assigned node off of our queue.
            q.pop();
        }
        //If the queue is empty, we have no nodes to display.
        else temp=NULL;
    }
    cout<<endl;
}
/** Inserts a node recursively. */
void Tree::insert(Node *&root,int value){
    //Base case: If we have an invalid node, we
    //create a new node and assign it to root.
    //(This is the insertion taking place.)
    if(root==NULL) root=newNode(value);
    //Otherwise, if we have a valid node...
    else{
        //If the value we're trying to insert is less than the 
        //current node's data, we'll be inserting into the left subtree.
        if(value<root->data){
            insert(root->left,value);
        }
        //Otherwise, we'll be inserting into the right subtree.
        else insert(root->right,value);
    }
    //Balancing our tree after the insertion.
    balance(root);
}
/** Destroys our tree using post-order traversal. */
void Tree::destroy(Node *&root){
    //Base case:
    if(root==NULL) return;
    //Left->Right->Root;
    destroy(root->left);
    destroy(root->right);
    delete root; //Deallocating the node's memory.
    root=NULL;   //Setting it to NULL.
}
/** Fills a tree w/ random data and a specified number of nodes. */
void Tree::fill(int n){
    //Initializing our root node.
    root=NULL;
    //Inserting N nodes:
    for(int i=1;i<=n;i++){
        //Inserting a node w/ a random value between 10-99.
        insert(root,rand()%90+10);
    }
}
/** Determines the height of our tree recursively. */
int Tree::height(Node *root){
    //Base case:
    if(root==NULL) return 0;
    //Recursively finding the heights of the subtrees.
    int lHeight=height(root->left);  //Height of the left subtree.
    int rHeight=height(root->right); //Height of the right subtree.
    //Returning the correct height.
    //(We add 1 to account for the root node.)
    if(lHeight>rHeight) return lHeight+1;
    else return rHeight+1;
}
/** Deletes a node from our tree recursively. */
void Tree::delNode(Node *&root,int target){
    //Base case:
    if(root==NULL) return;
    //If the data we want to remove is less than the current node's data...
    else if(target<root->data){
        //The node that will be deleted lies in our left subtree, so we
        //recursively delete the node from our left subtree.
        delNode(root->left,target);
    }
    //If the data we want to remove is greater than the current node's data...
    else if(target>root->data){
        //The node that will be deleted lies in our right subtree, so we
        //recursively delete the node from our right subtree.
        delNode(root->right,target);
    }
    //If we've found the node that will be deleted...
    else{
        //Case 1: If the node we need to delete has no children...
        if(root->left==NULL&&root->right==NULL){
            //We delete the node w/ our target value.
            delete root;
            //We set it to NULL to remove it from our tree.
            root=NULL;
        }
        //Case 2: If the node we need to delete has 1 child.
        else if(root->left==NULL){ //1 right child.
            //We store the right child in a temp. variable.
            Node *child=root->right;
            //We delete the node w/ our target value.
            delete root;
            //We set it equal to its right child.
            root=child;
        }
        else if(root->right==NULL){ //1 left child.
            //We store the left child in a temp. variable.
            Node *child=root->left;
            //We delete the node w/ our target value.
            delete root;
            //We set it equal to its left child.
            root=child;
        }
        //Case 3: If the node we need to delete has 2 children...
        else{
            //1. Find the node w/ the smallest value in the right subtree.
            Node *min=findMin(root->right);
            //2. Set the current node's data to the minimum value we found.
            root->data=min->data;
            //3. Recursively delete the duplicate in our right subtree.
            delNode(root->right,min->data);
        }
    }
    //Balancing our tree after the deletion.
    balance(root);
}
/** Finds the node w/ the smallest value. */
Node *Tree::findMin(Node *root){
    //Going to the left-most node. Since nodes in a BST are placed such that
    //if they are on the left, they have smaller data, we use this property 
    //to find the node w/ the smallest value. The node w/ the smallest value
    //is the left-most node of our tree.
    while(root->left){
        root=root->left;
    }
    //Returning the node w/ the smallest value.
    return root;
}
/** Performs a left rotation about a root node. */
void Tree::lftRot(Node *&root){
    //Storing the root node in a temp. variable.
    Node *temp=root;
    //The right child becomes the new root node.
    root=root->right;
    //The new root node's left child becomes the previous 
    //root node's right child.
    temp->right=root->left;
    //The new root node takes the previous root node as its left child.
    root->left=temp;
    /* For Example:  
     *        a
     *         \                       b
     *          b         ----->      / \
     *           \                   a   c
     *            c
     */    
}
/** Performs a right rotation about a root node. */
void Tree::rghtRot(Node *&root){
    //Storing the root node in a temp. variable.
    Node *temp=root;
    //The left child becomes the new root node.
    root=root->left;
    //The new root node's right child becomes the previous 
    //root node's left child.
    temp->left=root->right;
    //The new root node takes the previous root node as its right child.
    root->right=temp;
    /* For Example:  
     *            c
     *           /                     b
     *          b         ----->      / \
     *         /                     a   c
     *        a
     */   
}
/** Performs a left-right rotation about a root node. */
void Tree::lftRghtRot(Node *&root){
    //First, we do a right rotation on the right subtree.
    rghtRot(root->right);
    //Then, we do a left rotation on the root node.
    lftRot(root);
}
/** Performs a right-left rotation about a root node. */
void Tree::rghtLftRot(Node *&root){
    //First, we do a left rotation on the left subtree.
    lftRot(root->left);
    //Then, we do a right rotation on the root node.
    rghtRot(root);
}
/** Balances our tree using tree rotations. */
void Tree::balance(Node *&root){
    //If we have an invalid node, we simply exit.
    if(root==NULL) return;
    //Storing the heights of the left and right subtrees.
    int lh=height(root->left);
    int rh=height(root->right);
    //If the tree is right heavy...
    if(rh-lh>1){
        //Storing the heights of the right subtree's left and right subtrees.
        lh=height(root->right->left);  //Right subtree's left subtree height.
        rh=height(root->right->right); //Right subtree's right subtree height.
        //If the right subtree is left heavy...
        if(rh-lh<0) lftRghtRot(root);  //Perform a left-right rotation.
        //Otherwise...
        else lftRot(root);             //Perform a single left rotation.
    }
    //If the tree is left heavy...
    else if(rh-lh<-1){
        //Storing the heights of the left subtree's left and right subtrees.
        lh=height(root->left->left);   //Left subtree's left subtree height.
        rh=height(root->left->right);  //Left subtree's right subtree height.
        //If the left subtree is right heavy...
        if(rh-lh>0) rghtLftRot(root);  //Perform a right-left rotation.
        //Otherwise...
        else rghtRot(root);            //Perform a single right rotation.
    }
    //NOTE: If the difference between the heights of the subtrees is
    //greater than 1, then the tree is unbalanced. In this case, we check to
    //see which rotation is needed to bring the tree back to a balanced state.
}
