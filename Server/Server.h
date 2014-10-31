//
//  Server.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 31.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#pragma once

#ifndef __Craft_Age_Server__Server__
#define __Craft_Age_Server__Server__

#include <iostream>

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <event2/thread.h>
#include <errno.h>

#include <stack>

//#include <unordered_map>
#include <tr1/unordered_map>
#include <list>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>


#include "Server/Worker.h"
#include "Server/Client.h"

#define NUM_WORKERS 4

struct worklist {
    Worker *w;
    //unsigned int num;
    
};

class Server {
public:
    Server() {
        pthread_mutex_init(&mutex,NULL);
        
        port = 2000;
    }
    void startServer(int port);
    
    static void acceptCallback(evutil_socket_t fd, short ev, void *arg);
    
    static void acceptConn(evconnlistener *listener,evutil_socket_t fd, sockaddr *address, int socklen, void *ctx);
    
    static void accept_error_cb(struct evconnlistener *listener, void *ctx);
    
    event_base *getBase();
    
    static bool isShutdown();
private:
    int port;
    
    void addClient(Client *c);
    
    std::tr1::unordered_map<int, Client *> clients;
    std::list<worklist> workers;
    
    void startWorkers();
    
    pthread_mutex_t mutex;
    
    event_base *base;
    
    static bool shutdown;
};

#endif /* defined(__Craft_Age_Server__Server__) */
