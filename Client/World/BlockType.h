//
//  BlockType.h
//  GAME
//
//  Created by Patrik Štrba on 23.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#ifndef __GAME__BlockType__
#define __GAME__BlockType__

#include <iostream>

class BlockType {
public:
    BlockType() {
        
    }
    void setData(std::string name, int tx, int ty);
    int getTX();
    int getTY();
protected:
    std::string name;
    int tx,ty;
};

#endif /* defined(__GAME__BlockType__) */
