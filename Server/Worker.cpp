//
//  Worker.cpp
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 3.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Worker.h"

pthread_t *Worker::getThread() {
    return &thread;
}

unsigned int Worker::getID() {
    return worker_id;
}

unsigned int Worker::getNum() {
    return num;
}

void *Worker::startThread(void *ptr) {
    Worker *w = (Worker *)ptr;
    
    
    printf("WORKER ID: %d\n",  w->getID());
    
    while(1) {
        if(Server::isShutdown()) {
            printf("SHUTDOWN WORKER: %d\n", w->getID());
            break;
        }
        
        // REMOVE DISCONNECT CLIENTS
        w->clientManager();
        
        w->runTasks();
        /*
        if(w->clients.size() > 0) {
            Client *c = w->clients.back();
            
            printf("RECV: %d", recv(c->getSock(), buffer, 255, NULL));
            printf("RECV: %s", buffer);
        }
         */
        usleep(1000000);
    }
    
    pthread_exit(NULL);
}

void Worker::addClient(Client *c) {
    pthread_mutex_lock(&mutex_clients);
    c->setWorker(this);
    
    clients.insert(std::make_pair(c->getSock(), c));
    num++;
    
    pthread_mutex_unlock(&mutex_clients);
}

void Worker::readBuffer(int socket, short flags, void *ptr) {
    printf("READ\n");
    
    char buffer[1024];
    Client *c = (Client *)ptr;
    
    memset(buffer, 0, 1024);
    
    try {
        int length = recv(c->getSock(), buffer, 1024, NULL);
        
        if(length == 0) {
            c->getWorker()->removeClient(c);
            c->closeConnect();
        }
        
        if(length < 0) {
            printf("ERROR: RECV < 0!!!!!!!!");
            return;
        }
        
        ClientBuffer *b = new ClientBuffer;
        b->data = new char[length];
        
        memcpy(b->data, buffer, length);
        b->length = length;
        
        //send(c->getSock(), buffer, length, NULL);
        printf("D: %d %s\n", length, buffer);
        
        c->insertBuffer(b);
    } catch (const char *m) {
        
    }
}

void Worker::removeClient(Client *c) {
    pthread_mutex_lock(&mutex_clients);
    removeClients.push(c);
    pthread_mutex_unlock(&mutex_clients);
}

void Worker::clientManager() {
    int size;
    
    Client *c;
    // REMOVE OLD CONNECTIONS
    pthread_mutex_lock(&mutex_clients);
    size = removeClients.size();
    if(size > 0) {
        for(int i=0; i < size; i++) {
            c = removeClients.front();
            clients.erase(c->getSock());
            num -= 1;
            
            // ODSTRANIT ZO ZOZNAMU A ZNIZIT POCET O 1
            removeClients.pop();
        }
    }
    pthread_mutex_unlock(&mutex_clients);
}

void Worker::runTasks() {
    std::tr1::unordered_map<int, Client *>::iterator it;
    for(it=clients.begin(); it != clients.end(); it++) {
        printf("LOOP\n");
        // WORK ONLY WITH DIRTY (NEW DATA)
        if(it->second->isDirty()) {
            printf("PARSE\n");
            it->second->preparePackets();
            it->second->setAsClean();
        }
        //it = (Client *)it->second;
        printf("CLIENT: %d %d\n", it->second->getSock(), it->second->isDirty());
    }
}
