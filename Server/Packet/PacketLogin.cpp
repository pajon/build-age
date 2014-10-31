//
//  PacketLogin.cpp
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 31.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "PacketLogin.h"

char *PacketLogin::getBinary() {
    if(packetGenerate)
        return data;
    
    data = getBuffer();
    
    // GENERATE DATA
    addData(login, PACKET_LOGIN_LOGIN);
    addData(password, PACKET_LOGIN_PASSWORD);
    
    packetGenerate = true;
    
    return data;
}