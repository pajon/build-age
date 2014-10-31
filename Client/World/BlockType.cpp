//
//  BlockType.cpp
//  GAME
//
//  Created by Patrik Štrba on 23.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "BlockType.h"

void BlockType::setData(std::string name, int tx, int ty) {
    this->name = name;
    this->tx = tx;
    this->ty = ty;
}
int BlockType::getTX() {
    return tx;
}

int BlockType::getTY() {
    return ty;
}