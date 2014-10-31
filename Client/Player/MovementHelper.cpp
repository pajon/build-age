//
//  MovementHelper.cpp
//  Build-Age
//
//  Created by Patrik Štrba on 20.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Client/Player/MovementHelper.h"

#include "Client/Control/Control.h"
#include "Client/World/World.h"

MovementHelper::MovementHelper() {
    
}

void MovementHelper::move(Vector3F *p, float viewX, float movementSpeed) {
    float dc, ds;

    
    
    dc = cosf(viewX * M_PI / 180.0);
    ds = sinf(viewX * M_PI / 180.0);
    
    int numLoop = 32;
    float dpx = (float)(movementSpeed * ds) / (float)numLoop;
    float dpz = (float)(movementSpeed * dc) / (float)numLoop;
    
    int type = 0;
    float halfBlock = (float) (BLOCK_SIZE / 2.0);
    float halfHuman = (float) (HUMAN_SIZE);
    
    Vector3F tp;
    
    Control *c = Control::instance();
    
    if(c->k_up) {
        
        for(int i=0; i<numLoop; i++) {
            p->x += dpx;
            tp.x = p->x;
            tp.z = p->z;
            
            type = prepareBound(p->z);
            
            if(type == 0) {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(ds > 0 ? 1 : -1, 0,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds > 0 ? 1 : -1, 1,0), halfBlock)
                   )
                    p->x -= dpx;
            } else {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(ds > 0 ? 1 : -1, 0,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds > 0 ? 1 : -1, 1,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds > 0 ? 1 : -1, 0,1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds > 0 ? 1 : -1, 1,1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds > 0 ? 1 : -1, 0,-1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds > 0 ? 1 : -1, 1,-1), halfBlock)
                   )
                    p->x -= dpx;
            }
            
            p->z -= dpz;
            
            tp.x = p->x;
            tp.z = p->z;
            
            
            type = prepareBound(p->x);
            
            if(type == 0) {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(0,0,dc < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(0,1,dc < 0 ? 1 : -1), halfBlock)
                   )
                    p->z += dpz;
            } else {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(0,0,dc < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(0,1,dc < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(1,0,dc < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(1,1,dc < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(-1,0,dc < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(-1,1,dc < 0 ? 1 : -1), halfBlock)
                   )
                    p->z += dpz;
            }
        }
    } else if(c->k_down) {
        for(int i=0; i<numLoop; i++) {
            
            p->x -= dpx;
            tp.x = p->x;
            tp.z = p->z;
            
            type = prepareBound(p->z);
            
            if(type == 0) {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(ds < 0 ? 1 : -1, 0,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds < 0 ? 1 : -1, 1,0), halfBlock)
                   )
                    p->x += dpx;
            } else {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(ds < 0 ? 1 : -1, 0,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds < 0 ? 1 : -1, 1,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds < 0 ? 1 : -1, 0,1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds < 0 ? 1 : -1, 1,1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds < 0 ? 1 : -1, 0,-1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(ds < 0 ? 1 : -1, 1,-1), halfBlock)
                   )
                    p->x += dpx;
            }
            
            p->z += dpz;
            tp.x = p->x;
            tp.z = p->z;
            
            type = prepareBound(p->x);
            
            if(type == 0) {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(0,0,dc > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(0,1,dc > 0 ? 1 : -1), halfBlock)
                   )
                    p->z -= dpz;
            } else {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(0,0,dc > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(0,1,dc > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(1,0,dc > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(1,1,dc > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(-1,0,dc > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(-1,1,dc > 0 ? 1 : -1), halfBlock)
                   )
                    p->z -= dpz;
            }
        }
    }
    
    if(c->k_left) {
        float tmp = dpx;
        dpx = dpz;
        dpz = tmp;
        
        for(int i=0; i<numLoop; i++) {
            p->x -= dpx;
            tp.x = p->x;
            tp.z = p->z;
            
            type = prepareBound(p->z);
            
            if(type == 0) {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(dc < 0 ? 1 : -1, 0,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc < 0 ? 1 : -1, 1,0), halfBlock)
                   )
                    p->x += dpx;
            } else {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(dc < 0 ? 1 : -1, 0,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc < 0 ? 1 : -1, 1,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc < 0 ? 1 : -1, 0,1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc < 0 ? 1 : -1, 1,1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc < 0 ? 1 : -1, 0,-1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc < 0 ? 1 : -1, 1,-1), halfBlock)
                   )
                    p->x += dpx;
            }
            
            
            type = prepareBound(p->x);
            
            p->z -= dpz;
            tp.x = p->x;
            tp.z = p->z;
            
            if(type == 0) {
                // LEN STRED
                if(
                   checkCollision(tp, halfHuman, c->getPosition(0,0, ds < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(0,1, ds < 0 ? 1 : -1), halfBlock)
                   )
                    p->z += dpz;
            } else {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(0,0, ds < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(0,1, ds < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(1,0, ds < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(1,1, ds < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(-1,0, ds < 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(-1,1, ds <  0 ? 1 : -1), halfBlock)
                   )
                    p->z += dpz;
            }
        }
        
        tmp = dpx;
        dpx = dpz;
        dpz = tmp;
    } else if(c->k_right) {
        float tmp = dpx;
        dpx = dpz;
        dpz = tmp;
        
        for(int i=0; i<numLoop; i++) {
            p->x += dpx;
            tp.x = p->x;
            tp.z = p->z;
            
            type = prepareBound(p->z);
            
            if(type == 0) {
                // LEN STRED
                // ds > 0 ? 1 : -1
                if(
                   checkCollision(tp, halfHuman, c->getPosition(dc > 0 ? 1 : -1, 0,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc > 0 ? 1 : -1, 1,0), halfBlock)
                   )
                    p->x -= dpx;
            } else {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(dc > 0 ? 1 : -1, 0,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc > 0 ? 1 : -1, 1,0), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc > 0 ? 1 : -1, 0,1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc > 0 ? 1 : -1, 1,1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc > 0 ? 1 : -1, 0,-1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(dc > 0 ? 1 : -1, 1,-1), halfBlock)
                   )
                    p->x -= dpx;
            }
            
            
            type = prepareBound(p->x);
            p->z += dpz;
            
            tp.x = p->x;
            tp.z = p->z;
            
            if(type == 0) {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(0,0,ds > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(0,1,ds > 0 ? 1 : -1), halfBlock)
                   )
                    p->z -= dpz;
            } else {
                if(
                   checkCollision(tp, halfHuman, c->getPosition(0,0,ds > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(0,1,ds > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(1,0,ds > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(1,1,ds > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(-1,0,ds > 0 ? 1 : -1), halfBlock) ||
                   checkCollision(tp, halfHuman, c->getPosition(-1,1,ds > 0 ? 1 : -1), halfBlock)
                   )
                    p->z -= dpz;
            }
        }
        tmp = dpx;
        dpx = dpz;
        dpz = tmp;
    }
}

int MovementHelper::prepareBound(float v) {
    #define fixBound(v) ((v) <= 0 && (v) >= -BLOCK_SIZE ? BLOCK_SIZE : 0)
    #define fixBoundI(v) ((v) <= 0 && (v) >= -BLOCK_SIZE ? 1 : 0)
    
    float p;
    p = (absf(v) + fixBound(v) - HUMAN_SIZE - abs((int)(((int)v/BLOCK_SIZE)+fixBoundI(v))));
    if(p > BLOCK_SIZE || p < 0)
        return 1;
    p = (absf(v) + fixBound(v) + HUMAN_SIZE - abs((int)(((int)v/BLOCK_SIZE)+fixBoundI(v))));
    if(p > BLOCK_SIZE || p < 0)
        return -1;
    return 0;
}

bool MovementHelper::checkCollision(Vector3F obj1, float size1, Vector3F obj2, float size2) {
    if(World::instance()->getSection(obj2)->getBlock(obj2.x,obj2.y,obj2.z)->isAir())
        return false;
    
    if(absf(obj1.x - (obj2.x + (BLOCK_SIZE / 2.0))) > (size1 + size2)) return false;
    if(absf(obj1.z - (obj2.z + (BLOCK_SIZE / 2.0))) > (size1 + size2)) return false;
    return true;
}