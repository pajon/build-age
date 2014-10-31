//
//  Control.h
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Timer.h"
#include "../World/Section.h"


#ifndef __GAME__Control__
#define __GAME__Control__

#include <iostream>
#include <cmath>

#define HUMAN_HEIGHT BLOCK_SIZE * 1.5 // Y offset
#define HUMAN_SIZE 0.2 // X,Z offset

#define absf(v1) ((v1) < 0 ? ((v1) * -1) : v1)

 /*
typedef struct {
    float x;
    float y;
    float z;
} Position;
*/
class Control {
public:
    static Control *instance();
    bool k_up;
    bool k_down;
    bool k_left;
    bool k_right;
    bool k_jump;
    bool k_fall;
    bool k_pause;
    
    bool m_left;
    bool m_right;
    float cx,sx,sy; // ANGLES COS/SIN X,Y
    
    float x,y,z; // CAMERA
    float getAX();
    Vector3F getPosition();
    Vector3F getPosition(int ox, int oy, int oz);
    Vector3F getPositionBlock(Vector3F p);
    Vector3F getSection();
    Vector3F getSection(Vector3F p);
    
    void drawCursor();
    
    void getPick();
    
    void destroyBlock();
    void buildBlock();
protected:
    Vector3F pos,sec; // POZICIA,SEKCIA
    float jumpTime;
    float jumpSize;
    bool falling;
    float ax,ay;
    int mpx,mpy;
private:
    static Control *inst;
    
    Control();
    bool checkCollision(Vector3F obj1, float size1, Vector3F obj2, float size2);
    float getDY();
    
    
    Block *picked;
    unsigned short picketSide;
    void DrawPickBlock(Block *b);
};

#endif /* defined(__GAME__Control__) */
