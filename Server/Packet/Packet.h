//
//  Packet.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 31.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age_Server__Packet__
#define __Craft_Age_Server__Packet__

#include <iostream>
#include <cassert>

namespace CRAS {

enum PacketProtocol {
    TCP = 0,
    UDP = 1
};

enum PacketType {
    RECEIVE = 0,
    SEND = 1
};

enum PacketStatus {
    NONE = 0,
    CREATED = 1,
    LOADED = 2
};

struct PacketHeader {
    short type;
    unsigned int length;
};

#define PACKET_SET_CHAR(val, var, length) \
    if(strlen(var) > (length)) { \
        printf("ERROR: set variable "); \
        printf("%s", var); \
        printf(" is too long\n"); \
        return; \
    } \
    memset(val, 0, length); \
    memcpy(val, var, std::min((int)strlen(var), (length)));

#define PACKET_GET_CHAR() \
    if(getStatus() != LOADED) { \
        if(getStatus() == CREATED) \
            extractData(); \
        else if(getStatus() == NONE) { \
            printf("ERROR: data must be loaded first!\n"); \
            exit(1); \
        } \
    }

#define PACKET_FUNCTION_CP(FUNC, var, length) \
    char *get##FUNC () { \
        PACKET_GET_CHAR(); \
        return var; \
    } \
    void set##FUNC (char *val) { \
        PACKET_SET_CHAR(var, val, length); \
    }

class Packet {
public:
    Packet() {
        packetOffset = 0;
        
        data = NULL;
        packetGenerate = false;
        
        status = NONE;
        protocol = TCP;
        type = SEND;
    }
    
    ~Packet() {
        // BUFFER IS CREATED
        if(status != NONE)
            delete data;
    }
    
    void loadPacket(void *val);
    virtual char *getBinary() = 0;// { printf("TMP\n"); }
protected:
    
    PacketStatus getStatus() { return status; }
    void setLoaded() { status = LOADED; }
    
    void addData(void *val, int length);
    void getData(void *val, int length);
    char *getBuffer();
    char *data;
    
    int packetNumber;
    int packetLength;
    
    bool packetGenerate;
    
    PacketStatus status;
    PacketType type;
    PacketProtocol protocol;
    
    virtual void extractData() = 0;
private:
    int packetOffset;
};
    
}

#endif /* defined(__Craft_Age_Server__Packet__) */
