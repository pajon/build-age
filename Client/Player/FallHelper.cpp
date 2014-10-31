//
//  FallHelper.cpp
//  Build-Age
//
//  Created by Patrik Štrba on 20.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Client/Player/FallHelper.h"

#include "Client/Control/Timer.h"
#include "Client/World/World.h"

FallHelper::FallHelper() {
    jumpTime = 0;
}

bool FallHelper::fall(Vector3F *p) {
    float t = 0.37;
    float dt = Timer::getTick() / 1000000.0;
    
    float d = ((sinf((jumpTime-dt) * M_PI/(2/t)) - sinf(jumpTime * M_PI/(2/t))) * 20.0f);
    float dy;
    
    if(!hasFallCollision(p)) {
        p->y += d;
        return true;
    } else if((dy = getDY(p)) > 0) {
        if(dy + d < 0)
            d = -dy;
        p->y += d;
        
        return true;
    }
    
    jumpTime = 0;
    return false;
}

bool FallHelper::hasFallCollision(Vector3F *v) {
    Vector3F p;
    p.x = v->x;
    p.y = v->y;
    p.z = v->z;
    
    if(World::instance()->checkCollision(p, 0, -1, 0))
        return true;
    
    // +X CHECK
    p.x += HUMAN_SIZE;
    if(World::instance()->checkCollision(p, 0, -1, 0) && World::instance()->checkCollision(p) == false)
        return true;
    p.x -= HUMAN_SIZE;
    // +X CHECK
    
    // -X CHECK
    p.x -= HUMAN_SIZE;
    if(World::instance()->checkCollision(p, 0, -1, 0) && World::instance()->checkCollision(p) == false)
        return true;
    p.x += HUMAN_SIZE;
    // -X CHECK
    
    // +Z CHECK
    p.z += HUMAN_SIZE;
    if(World::instance()->checkCollision(p, 0, -1, 0) && World::instance()->checkCollision(p) == false)
        return true;
    p.z -= HUMAN_SIZE;
    // +Z CHECK
    
    // -Z CHECK
    p.z -= HUMAN_SIZE;
    if(World::instance()->checkCollision(p, 0, -1, 0) && World::instance()->checkCollision(p) == false)
        return true;
    p.z += HUMAN_SIZE;
    // -Z CHECK
    
    return false;
}

float FallHelper::getDY(Vector3F *p) {
    return p->y - ( (int)p->y - ( p->y < 0 && p->y != (int)p->y ? 1 : 0 )); // FIX
}