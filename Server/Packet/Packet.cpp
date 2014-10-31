//
//  Packet.cpp
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 31.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Packet.h"

namespace CRAS { 

void Packet::addData(void *val, int length) {
    assert(type != RECEIVE);
        
    // COPY DATA
    memcpy(((char *)data) + packetOffset, val, length);
    
    // ADD OFFSET
    packetOffset += length;
}

void Packet::getData(void *val, int length) {
    assert(type != SEND);
    
    // COPY DATA
    memcpy(val, ((char *)data) + packetOffset, length);
    
    // ADD OFFSET
    packetOffset += length;
}

void Packet::loadPacket(void *val) {
    // CREATE BUFFER
    data = getBuffer();
    
    // COPY DATA
    memcpy(data, val, packetLength);
    
    // SET PACKET TYPE
    type = RECEIVE;
}

char *Packet::getBuffer() {
    char *tmp;
    if(status == NONE) {
        tmp = new char[packetLength];
        status = CREATED;
    } else
        tmp = data;
    
    return tmp;
}

}