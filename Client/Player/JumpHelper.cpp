//
//  JumpHelper.cpp
//  Build-Age
//
//  Created by Patrik Štrba on 20.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Client/Player/JumpHelper.h"

#include "Client/World/World.h"
#include "Client/Control/Timer.h"

JumpHelper::JumpHelper() {
    jumpTime = 0;
}

bool JumpHelper::jump(Vector3F *v) {
    float t = 0.33;
    float dt = Timer::getTick() / 1000000.0;
    
    if(jumpTime > t) {
        jumpTime = 0;
        return false;
    }
    
    float jumpAct = (sinf(jumpTime * M_PI/(2/t)) - sinf((jumpTime+dt) * M_PI/(2/t))) * 10;
    jumpTime += dt;
    
    v->y -= jumpAct;
    
    if(checkCollision(v)) {
        v->y += jumpAct;
        jumpTime = 0;
        return false;
    }
    return true;
}

bool JumpHelper::checkCollision(Vector3F *v) {
    Vector3F p;
    p.x = v->x;
    p.y = v->y;
    p.z = v->z;
    
    p.y += HUMAN_HEIGHT + 0.1;
    
    if(World::instance()->checkCollision(p))
        return true;
    
    // +X CHECK
    p.x += HUMAN_SIZE;
    if(World::instance()->checkCollision(p))
        return true;
    p.x -= HUMAN_SIZE;
    // +X CHECK
    
    // -X CHECK
    p.x -= HUMAN_SIZE;
    if(World::instance()->checkCollision(p))
        return true;
    p.x += HUMAN_SIZE;
    // -X CHECK
    
    // +Z CHECK
    p.z += HUMAN_SIZE;
    if(World::instance()->checkCollision(p))
        return true;
    p.z -= HUMAN_SIZE;
    // +Z CHECK
    
    // -Z CHECK
    p.z -= HUMAN_SIZE;
    if(World::instance()->checkCollision(p))
        return true;
    p.z += HUMAN_SIZE;
    // -Z CHECK
    
    p.y -= HUMAN_HEIGHT + 0.1;
    return false;
}