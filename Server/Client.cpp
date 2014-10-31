//
//  Client.cpp
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 31.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Client.h"

#include <cerrno>
#include <unistd.h>

void Client::closeConnect() {
    printf("DEBUG: close socket %d\n", sock);
    
    if(sock > 0) {
        close(sock);
    }
    
    if(e != NULL) {
        event_free(e);
    }
}

void Client::setSock(int sock) {
    this->sock = sock;
}

void Client::setEvent(event *event) {
    e = event;
}

void Client::setWorker(Worker *w) {
    this->w = w;
}

Worker *Client::getWorker() {
    return w;
}

int Client::getSock() {
    return sock;
}

void Client::insertBuffer(ClientBuffer *buffer) {
    pthread_mutex_lock(&mutex);
    
    buffers.push(buffer);
    
    // WORKER TO PARSE BUFFER
    dirtyBuffer = true;
    
    pthread_mutex_unlock(&mutex);
}

void Client::preparePackets() {
    int size = buffers.size();
    for(int i=0; i < size; i++) {
        ClientBuffer *cb = buffers.front();
        buffers.pop();
        
        printf("LENGTH: %d\n", cb->length);
        
        unsigned short packet;
        unsigned int length;
        
        
        memcpy(&packet, cb->data, 1);
        memcpy(&length, cb->data+1, 4);
        
        //Packet *p;
        //PACKET_LOADER(packet);
        
        //p->loadPacket(cb->data+5);
        //printf("SUM TU\n");
        
        printf("PACKET: %d %hu %d %s\n", length,packet, length, cb->data);
        
        delete cb->data;
        delete cb;
        
    }
}