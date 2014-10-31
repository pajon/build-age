//
//  Human.cpp
//  Build-Age
//
//  Created by Patrik Štrba on 19.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Client/Player/Player.h"

#include "Client/Control/Control.h"
#include "Client/Control/Timer.h"

Player::Player() {
    pos.x = pos.y = pos.z = 0;
    pos.y = 100;
    viewD.x = 1;
    viewD.y = viewD.z = 0;
    
    viewX = viewY = 0;
    
    status = PLAYER_IDLE;
}

void Player::Control() {
    
    float movementSpeed = MOVEMENTSPEED; // block/s
    float dt = Timer::getTick() / 1000000.0; // TICK TIME
    
    // CALCULATE MOVEMENT SPEED
    movementSpeed *= dt;
    
    if(status == PLAYER_IDLE)
        if(Control::instance()->k_jump)
            status = PLAYER_JUMPING;
    
    
    if(status == PLAYER_JUMPING)
        Jump();
    
    if(status != PLAYER_JUMPING)
        Fall();
    
    if(status == PLAYER_FALLING)
        movementSpeed /= 1.5;
    
    Movement(movementSpeed);
}
/*
void Control::mouseControl(int x, int y) {
    if(x == WSFML::getWidth()/2 && y == WSFML::getHeight()/2)
        return;
    
    UpdateAngle((x - WSFML::getWidth()/2)*0.3, (y - WSFML::getHeight()/2)*0.3);
}
 
 void Control::UpdateAngle(float x, float y) {
 ax += 2*x;
 ay -= y; // / (50.0 / 1.5);
 
 if(ay < -90)
 ay = -90;
 else if(ay > 90)
 ay = 90;
 
 cx = cosf(ax * M_PI / 180.0) / 2;
 sx = sinf(ax * M_PI / 180.0) / 2;
 sy = sinf(ay * M_PI / 180.0) * 1.5;
 }
*/
void Player::setView(float angleX, float angleY) {
    angleX -= (WSFML::getWidth()  / 2.0);
    angleY -= (WSFML::getHeight() / 2.0);
    
    angleX *= 0.3f;
    angleY *= 0.3f;
    
    viewX += 1.5 * angleX;
    viewY -= angleY; // / (50.0 / 1.5);
    
    if(viewY < -90)
        viewY = -90;
    else if(viewY > 90)
        viewY = 90;
    
    viewX -= (int)(viewX / 360) * 360; 
    viewX = (viewX > 0 ? viewX : 360 + viewX);
    
    Vector3F tmp = UpdateAngle(viewX, viewY);
    viewD.x = tmp.x;
    viewD.y = tmp.y;
    viewD.z = tmp.z;
}

Vector3F Player::UpdateAngle(float x, float y) {
    Vector3F v;
    
    float tmp;
    
    tmp = (1 - absf(y / 90.1f));
    
    v.x = sinf(x * M_PI / 180.0) * tmp;
    v.y = sinf(y * M_PI / 180.0) * 2.0f;
    v.z = cosf(x * M_PI / 180.0) * tmp;
    
    return v;
}

void Player::setCamera() {
    gluLookAt(
              pos.x,
              pos.y + HUMAN_HEIGHT,
              pos.z,
              
              pos.x + viewD.x,
              pos.y + viewD.y + HUMAN_HEIGHT,
              pos.z - viewD.z,
              
              0,1,0
    );
}

void Player::Jump() {
    if(jumpHelper.jump(&pos) == false) {
        Control::instance()->k_jump = false;
            status = PLAYER_FALLING;
    }
}

void Player::Fall() {
    if(fallHelper.fall(&pos) == false)
        status = PLAYER_IDLE;
    else
        status = PLAYER_FALLING;
}

void Player::Movement(float movementSpeed) {
    moveHelper.move(&pos, viewX, movementSpeed);
}

Vector3F Player::getView() {
    return viewD;
}

Vector3F Player::getEye() {
    return pos;
}

Vector3F Player::getPosition() {
    Vector3F p;

    p.x = (int)pos.x - ( pos.x < 0 && pos.x != (int)pos.x ? 1 : 0 );
    p.y = (int)pos.y - ( pos.y < 0 && pos.y != (int)pos.y ? 1 : 0 );
    p.z = (int)pos.z - ( pos.z < 0 && pos.z != (int)pos.z ? 1 : 0 );
    return p;
}
