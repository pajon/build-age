//
//  PacketManager.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 4.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age_Server__PacketManager__
#define __Craft_Age_Server__PacketManager__

#include <iostream>

#include <tr1/unordered_map>

#include "Server/Packet/Packet.h"

#include "Server/Packet/PacketLogin.h"

#define PACKET_LOADER(type) \
     \
    switch(type) { \
        case 1: p = (PacketLogin *) new PacketLogin(); \
    } 


class PacketManager {
public:
    
    static PacketManager *instance();
protected:
    PacketManager() {
        packets.insert(std::make_pair(1, new PacketLogin()));
    }
private:
    static PacketManager *inst;
    
    std::tr1::unordered_map<unsigned short, Packet*> packets;
};

#endif /* defined(__Craft_Age_Server__PacketManager__) */
