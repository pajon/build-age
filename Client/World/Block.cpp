  //
//  Block.cpp
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Block.h"

#include "Generate/PerlinNoise.h"

Block::Block(int x, int y, int z) {
    this->x = x;
    this->y = y;
    this->z = z;

    type = 0;    
    resetSide();
}

Block::Block() {
    type = 0;
    resetSide();
}

void Block::resetSide() {
    tside = bside = lside = rside = fside = uside = 1;
}

void Block::init(int bx, int by, int bz, unsigned short btype) {
    x = bx;
    y = by;
    z = bz;
    
    type = btype;
}

void Block::setType(unsigned short type) {
    this->type = type;
}

void Block::setLeftSide(bool state) {
    if(isAir())
        return;
    
    lside = state ? 1 : 0;
}

void Block::setRightSide(bool state) {
    if(isAir())
        return;
    
    rside = state ? 1 : 0;
}

void Block::setTopSide(bool state) {
    if(isAir())
        return;
    
    tside = state ? 1 : 0;
}

void Block::setBottomSide(bool state) {
    if(isAir())
        return;
    
    bside = state ? 1 : 0;
}

void Block::setFrontSide(bool state) {
    if(isAir())
        return;
    
    fside = state ? 1 : 0;
}

void Block::setBackSide(bool state) {
    if(isAir())
        return;
    
    uside = state ? 1 : 0;
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