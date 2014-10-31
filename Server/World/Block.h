//
//  Block.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 1.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age_Server__Block__
#define __Craft_Age_Server__Block__

#include <iostream>

class Block {
public:
    Block();
    int getType();
    int getX();
    int getY();
    int getZ();
    bool isAir();
    
    bool Compare(Block *b);
protected:
    int x : 24;
    int y : 8; // -128 / + 127
    int z : 24;
    unsigned short type : 8; // 0 - 255
};

#endif /* defined(__Craft_Age_Server__Block__) */
