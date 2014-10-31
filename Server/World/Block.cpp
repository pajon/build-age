//
//  Block.cpp
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 1.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Block.h"

Block::Block() {
    type = 0;
}

bool Block::Compare(Block *b) {
    return b->getX() == getX() && b->getY() == getY() && b->getZ() == getZ();
}

int Block::getType() {
    return type;
}

bool Block::isAir() {
    return type == 0;
}

int Block::getX() {
    return x;
}

int Block::getY() {
    return y;
}

int Block::getZ() {
    return z;
}