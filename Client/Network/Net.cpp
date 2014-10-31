//
//  Net.cpp
//  Build-Age
//
//  Created by Patrik Štrba on 7.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Net.h"

#define DEBUG_SOCKET(status) \
switch(status) { \
    case sf::TcpSocket::Done: printf("STATUS: DONE\n"); break; \
    case sf::TcpSocket::NotReady: printf("STATUS: NOTREADY\n"); break; \
    case sf::TcpSocket::Disconnected: printf("STATUS: DISCONNECT\n"); break; \
    case sf::TcpSocket::Error: printf("STATUS: ERROR\n"); break; \
}

void Net::startNet() {
    if(connect() == false) {
        return;
    }
    
    sf::Packet pack;
    
    while(1) {
        
        status = socket.receive(pack);
        DEBUG_SOCKET(status);
        
        //std::string  text = "hello";
        //socket.send(text.c_str(), text.length()+1);
        
        //printf("SEND: %s %lu\n", text.c_str(), text.length()+1);
        
        //usleep(10000000);
        
        sf::sleep(sf::seconds(10));
        
        //socket.disconnect();
        //break;
    }
}

bool Net::connect() {
    sf::IpAddress adr;
    
    status = socket.connect("localhost", 2000);
    
    if(status != sf::TcpSocket::Done) {
        connected = false;
        
        return false;
    }
    
    DEBUG_SOCKET(status);
    //return;
    
    if(socket.isBlocking()) {
        socket.setBlocking(false);
    }
    return true;
}