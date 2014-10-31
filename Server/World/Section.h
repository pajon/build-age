//
//  Section.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 1.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age_Server__Section__
#define __Craft_Age_Server__Section__

#include <iostream>

#include "Server/World/Block.h"

#define SECTION_SIZE_X 16
#define SECTION_SIZE_Y 256
#define SECTION_SIZE_Z 16

class Section {
private:
    int x, y, z;
    
    Block blocks[SECTION_SIZE_X][SECTION_SIZE_Y][SECTION_SIZE_Z];
};

#endif /* defined(__Craft_Age_Server__Section__) */
