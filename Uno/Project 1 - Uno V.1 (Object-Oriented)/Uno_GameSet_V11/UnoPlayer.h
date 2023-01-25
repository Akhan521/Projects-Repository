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
    //The # of cards a player has.
    int numCrds; 
    //An entire deck of cards
    UnoCard *deck; 
};

#endif /* UNOPLAYER_H */

