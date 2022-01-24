/* 
 * File:   UnoPlayer.h
 * Author: Aamir 
 * Created on April 17, 2021, 9:30 AM
 * Purpose: UnoPlayer structure (Nested Structure)
 */

/* 
 * File:   UnoPlayer.h
 * Author: Aamir Khan
 *
 * Created on April 17, 2021, 7:00 PM
 */

#include "UnoCard.h"
#ifndef UNOPLAYER_H
#define UNOPLAYER_H

struct UnoPlayer{
    int numCrds;   //The # of cards a player has.
    UnoCard *deck; //An entire deck of cards (Structure Array)
};

#endif /* UNOPLAYER_H */

