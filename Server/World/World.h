//
//  World.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 1.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age_Server__World__
#define __Craft_Age_Server__World__

#include <iostream>
#include <stack>

#include "Server/World/Player/Player.h"

class World {
public:
    static World *instance();

protected:
    World();
    
private:
    static World *inst;
    
    std::stack<Player *> players;
};

#endif /* defined(__Craft_Age_Server__World__) */
