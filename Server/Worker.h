//
//  Worker.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 3.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//


#ifndef __Craft_Age_Server__Worker__
#define __Craft_Age_Server__Worker__

#include "Server/Client.h"
#include "Server/Server.h"

#include <iostream>
#include <queue>
#include <pthread.h>

#include <tr1/unordered_map>


#include <event2/event.h>

class Worker {
public:
    Worker() {
        perror("NULL WORKER");
    }
    Worker(unsigned int worker_id) {
        this->worker_id = worker_id;
        num = 0;
        
        pthread_mutex_init(&mutex_clients, NULL);
    }
    
    unsigned int getNum();
    unsigned int getID();
    pthread_t *getThread();
    
    static void *startThread(void *ptr);
    
    static void readBuffer(evutil_socket_t socket, short flags, void *ptr);
    
    void addClient(Client *c);
    void removeClient(Client *c);
    
    void runTasks();
    
private:
    unsigned int worker_id;
    unsigned int num;
    
    
    pthread_t thread;
    pthread_mutex_t mutex_clients;
    
    
    std::tr1::unordered_map<int, Client *> clients;
    
    
    std::queue<Client *> removeClients;
    
    void clientManager();
};

#endif /* defined(__Craft_Age_Server__Worker__) */
