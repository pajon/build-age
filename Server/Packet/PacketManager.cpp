//
//  PacketManager.cpp
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 4.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "PacketManager.h"

PacketManager *PacketManager::inst = 0;

PacketManager *PacketManager::instance() {
    if(!inst)
        inst = new PacketManager();
    return inst;
}