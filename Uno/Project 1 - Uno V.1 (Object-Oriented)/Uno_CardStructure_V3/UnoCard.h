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
    string color;
    char descr[SIZE];
    unsigned char value;
};

#endif /* UNOCARD_H */

