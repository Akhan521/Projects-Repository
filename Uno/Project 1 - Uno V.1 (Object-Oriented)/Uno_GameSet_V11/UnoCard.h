/* 
 * File: UnoCard.h
 * Author: Aamir Khan
 * Created on April 11, 2021, 8:55 PM
 * Purpose: Storing Data in a Card Structure
 */

const int SIZE=10;
#ifndef UNOCARD_H
#define UNOCARD_H

struct UnoCard{
    //Card Description
    char descr[SIZE];
    //Card Color
    char color[SIZE];
    //Card's Face Value
    unsigned char value;
};

#endif /* UNOCARD_H */

