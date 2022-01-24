/* 
 * File: UnoCard.h
 * Author: Aamir Khan
 * Created on April 11, 2021, 8:55 PM
 * Purpose: Storing Data in a Card Structure
 */

#include <string>
const int SIZE=21;

#ifndef UNOCARD_H
#define UNOCARD_H

struct UnoCard{
    unsigned char value;
    string color;
    char descr[SIZE];
};

#endif /* UNOCARD_H */

