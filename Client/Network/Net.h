//
//  Net.h
//  Build-Age
//
//  Created by Patrik Štrba on 7.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Build_Age__Net__
#define __Build_Age__Net__

#include <iostream>

#include <list>

#include <SFML/System/Thread.hpp>
#include <SFML/Network/TcpSocket.hpp>
#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>
#include <SFML/Graphics.hpp>

#include "Server/Packet/Packet.h"

class Net {
public:
    Net() {
        connected = false;
    }
    
    void startNet();
private:
    
    bool connect();
    
    void sendPackets();
    
    void receivePackets();
    
    sf::TcpSocket socket;
    
    sf::TcpSocket::Status status;
    
    bool connected;
    
    std::list<CRAS::Packet *> input;
    std::list<CRAS::Packet *> output;
};

#endif /* defined(__Build_Age__Net__) */
