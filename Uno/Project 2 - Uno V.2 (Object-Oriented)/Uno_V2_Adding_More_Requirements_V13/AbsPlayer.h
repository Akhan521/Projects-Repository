/* 
 * File:   AbsPlayer.h
 * Author: Aamir Khan
 * Created on May 24, 2021, 9:15 AM
 * Purpose: AbsPlayer Class Specification
 */

#ifndef ABSPLAYER_H
#define ABSPLAYER_H

class AbsPlayer{
    public:
        //Pure Virtual Functions
        virtual void setDck(Deck *)=0;
        virtual void prntDck()=0;
        virtual string getName()=0;
        virtual int getnCards()=0;
};

#endif /* ABSPLAYER_H */
