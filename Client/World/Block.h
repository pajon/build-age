//
//  Block.h
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "BlockType.h"

#ifndef __GAME__Block__
#define __GAME__Block__

#include <iostream>
#include "Client/World/Block/Geometry.h"

class Block {
public:
    Block();
    Block(int x,int y, int z);
    int getType();
    int getX();
    int getY();
    int getZ();
    bool isAir();
    
    void setType(unsigned short type);
    
    void init(int bx, int by, int bz, unsigned short btype);
    void resetSide();
    
    void setLeftSide(bool state);
    void setRightSide(bool state);
    void setTopSide(bool state);
    void setBottomSide(bool state);
    void setFrontSide(bool state);
    void setBackSide(bool state);
    
    bool hasVisible(FaceType type) {
        switch(type) {
            case TOP:
                return tside == 1;
            case BOTTOM:
                return bside == 1;
            case FRONT:
                return fside == 1;
            case BACK:
                return uside == 1;
            case LEFT:
                return lside == 1;
            case RIGHT:
                return rside == 1;
        }
        return false;
    }
    bool hasVisibleTop() { return tside == 1; }
    bool hasVisibleBottom() { return bside == 1; }
    bool hasVisibleLeft() { return lside == 1; }
    bool hasVisibleRight() { return rside == 1; }
    bool hasVisibleFront() { return fside == 1; }
    bool hasVisibleBack() { return uside == 1; }
    
    unsigned short lside : 1; // LEFT
    unsigned short rside : 1; // RIGHT
    
    unsigned short tside : 1; // TOP
    unsigned short bside : 1; // BOTTOM
    
    unsigned short fside : 1; // FRONT
    unsigned short uside : 1; // BACK
    
    bool Compare(Block *b);
protected:
    int x : 24;
    int y : 8; // -128 / + 127
    int z : 24;
    unsigned short type : 8; // 0 - 255
};

#endif /* defined(__GAME__Block__) */
