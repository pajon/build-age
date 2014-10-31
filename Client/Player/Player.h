//
//  Human.h
//  Build-Age
//
//  Created by Patrik Štrba on 19.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Build_Age__Human__
#define __Build_Age__Human__

#include <iostream>

#include "Config.h"

#include "Client/Player/JumpHelper.h"
#include "Client/Player/FallHelper.h"
#include "Client/Player/MovementHelper.h"

enum PlayerStatus {
    PLAYER_JUMPING = 0,
    PLAYER_FALLING = 1,
    PLAYER_IDLE = 2
};

class Player {
public:
    Player();
    void setCamera();
    void setView(float angleX, float angleY);
    
    Vector3F getPosition();
    Vector3F getEye();
    Vector3F getView();
    void Control();
private:    
    float viewX;
    float viewY;
    
    PlayerStatus status;
    
    Vector3F pos;
    Vector3F viewD;
    
    JumpHelper jumpHelper;
    FallHelper fallHelper;
    MovementHelper moveHelper;
    
    void Jump();
    void Fall();
    
    void Movement(float movementSpeed);
    
    Vector3F UpdateAngle(float x, float y);
};

#endif /* defined(__Build_Age__Human__) */
