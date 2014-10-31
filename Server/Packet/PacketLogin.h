//
//  PacketLogin.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 31.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age_Server__PacketLogin__
#define __Craft_Age_Server__PacketLogin__

#include <iostream>

#include "Server/Packet/Packet.h"

#define PACKET_LOGIN_LOGIN 16
#define PACKET_LOGIN_PASSWORD 32

using namespace CRAS;

class PacketLogin: public Packet {
public:
    PacketLogin() {
        packetNumber = 1;
        packetLength = PACKET_LOGIN_LOGIN+PACKET_LOGIN_PASSWORD;
    }

    PACKET_FUNCTION_CP(Login, login, PACKET_LOGIN_LOGIN);
    PACKET_FUNCTION_CP(Password, password, PACKET_LOGIN_PASSWORD);
    
    char *getBinary();
protected:
    
    char login[PACKET_LOGIN_LOGIN];
    char password[PACKET_LOGIN_PASSWORD]; // MD5 PASSWORD
    
    void extractData() {
        getData(login, PACKET_LOGIN_LOGIN);
        getData(password, PACKET_LOGIN_PASSWORD);
        setLoaded();
    }
    
};

#endif /* defined(__Craft_Age_Server__PacketLogin__) */
