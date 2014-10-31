//
//  Client.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 31.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//



#ifndef __Craft_Age_Server__Client__
#define __Craft_Age_Server__Client__

#include <iostream>

#include <stack>
#include <queue>
#include <pthread.h>

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <event2/event.h>

#include "Server/Packet/Packet.h"
#include "Server/Packet/PacketManager.h"
#include "Server/World/Player/Player.h"

class Worker;

struct ClientBuffer {
    char *data;
    unsigned int length;
};

class Client {
public:
    Client() {
        sock = -1;
        e = NULL;
        
        pthread_mutex_init(&mutex, NULL);
        dirtyBuffer = false;
    }
    void shutdown();
    void closeConnect();
    
    void setSock(int sock);
    int getSock();
    
    void setWorker(Worker *w);
    Worker *getWorker();
    
    void setEvent(event* event);
    
    bool isDirty() { return dirtyBuffer; }
    void setAsClean() { dirtyBuffer = false; }
    
    void insertBuffer(ClientBuffer *buffer);
    
    void preparePackets();
    
private:
    
    std::queue<ClientBuffer *> buffers;
    bool dirtyBuffer;
    
    char buffer[256];
    
    PacketHeader head;
    
    Player player;
    
    Worker *w;
    
    int sock;
    event *e;
    
    pthread_mutex_t mutex;
};


#endif /* defined(__Craft_Age_Server__Client__) */
