//
//  World.cpp
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 1.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "World.h"

World *World::inst = 0;

World *World::instance() {
    if(!inst)
        inst = new World();
    return inst;
}

World::World() {

}