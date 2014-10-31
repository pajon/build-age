 //
//  Control.cpp
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Control.h"
#include "../World/World.h"
#include <cstdio>

Control *Control::inst = 0;

Control *Control::instance() {
    if(!inst)
        inst = new Control();
    return inst;
}

Control::Control() {
    // START POSITION
    int _x=10;
    int _y=5;
    int _z=10;
    
    // SET START POSITION
    x = _x * BLOCK_SIZE + BLOCK_SIZE / 2.0;
    y = _y * BLOCK_SIZE;
    z = _z * BLOCK_SIZE + BLOCK_SIZE / 2.0;
    
    ax = 0;
    ay = 0;
    sx = sy = 0;
    cx = 1;
    
    k_up = false;
    k_down = false;
    k_left = false;
    k_right = false;
    k_jump = false;
    k_fall = false;
    k_pause = false;
    
    m_left = false;
    m_right = false;
    
    jumpTime = 0;
    jumpSize = 0;
    
    falling = true;
    
    mpx = mpy = 0;
}

bool Control::checkCollision(Vector3F obj1, float size1, Vector3F obj2, float size2) {
    if(absf(obj1.x - (obj2.x + (BLOCK_SIZE / 2.0))) > (size1 + size2)) return false;
    if(absf(obj1.z - (obj2.z + (BLOCK_SIZE / 2.0))) > (size1 + size2)) return false;
    return true;
}


float Control::getAX() {
    return ax;
}

Vector3F Control::getPosition() {
    return getPosition(0,0,0);
}

Vector3F Control::getPosition(int ox, int oy, int oz) {
    //x += (BLOCK_SIZE * ox);
    //y += (BLOCK_SIZE * oy);
    //z += (BLOCK_SIZE * oz);
    
    pos = World::instance()->getPlayer()->getPosition();
    pos.x += ox;
    pos.y += oy;
    pos.z += oz;
    
    /*
    pos.x = (int)( x ) - ( x < 0 && x != (int)x ? 1 : 0 );
    pos.y = (int)( y ) - ( y < 0 && y != (int)y ? 1 : 0 );
    pos.z = (int)( z ) - ( z < 0 && z != (int)z ? 1 : 0 );
    */
    //x -= (BLOCK_SIZE * ox);
    //y -= (BLOCK_SIZE * oy);
    //z -= (BLOCK_SIZE * oz);
    
    return pos;
}

Vector3F Control::getPositionBlock(Vector3F p) {
    pos.x = (int)( p.x ) - ( p.x < 0 && p.x != (int)p.x ? 1 : 0 );
    pos.y = (int)( p.y ) - ( p.y < 0 && p.y != (int)p.y ? 1 : 0 );
    pos.z = (int)( p.z ) - ( p.z < 0 && p.z != (int)p.z ? 1 : 0 );
    return pos;
}

Vector3F Control::getSection() {
    return getSection(getPosition());
}

Vector3F Control::getSection(Vector3F p) {
    
    if(p.x < 0 )
        sec.x = -1 + (int)((p.x + 1) / SECTION_SIZE_X);
    else
        sec.x = (int)(p.x / SECTION_SIZE_X);
    
    
    //sec.x = ((int)p.x / SECTION_SIZE_X) & 0xFFFFF;
    
    if(p.y < 0 )
        sec.y = -1 + (int)((p.y + 1) / SECTION_SIZE_Y);
    else
        sec.y = (int)(p.y / SECTION_SIZE_Y);
    
    //sec.z = ((int)p.z / SECTION_SIZE_Z) & 0xFFFFF;
    
    
    if(p.z < 0 )
        sec.z = -1 + (int)((p.z + 1) / SECTION_SIZE_Z);
    else
        sec.z = (int)(p.z / SECTION_SIZE_Z);
    
    return sec;
}


void Control::drawCursor() {
    /*
    WSFML::instance()->getWindow()->pushGLStates();
    //sf::Text text("Hello");
    sf::Text text;
    text.setString("Hello");
    
    text.setPosition(100, 100);
    
    WSFML::instance()->getWindow()->draw(text);
    
    WSFML::instance()->getWindow()->popGLStates();
    */
    
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    
    glLoadIdentity();
    
    
    //gluOrtho2D(-100,100,-100,100);
    
    glOrtho(0.0, WSFML::instance()->getWidth(), WSFML::instance()->getHeight(), 0.0, -1.0, 10.0);
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    

    /*
    WSFML::instance()->getWindow()->pushGLStates();
    sf::Text text("Hello");
    WSFML::instance()->getWindow()->draw(text);
    WSFML::instance()->getWindow()->popGLStates();
    */
    glDisable(GL_FOG);
    
    
    
    //glDepthMask(GL_FALSE);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_LIGHTING);
    
    glColor3f(1, 1, 1);
    
    int size = 20;
        glBegin(GL_LINES);
            glVertex3f((WSFML::getWidth()/2) - size / 2, (WSFML::getHeight()/2), 0);
            glVertex3f((WSFML::getWidth()/2) + size / 2, (WSFML::getHeight()/2), 0);
    
            glVertex3f((WSFML::getWidth()/2), (WSFML::getHeight()/2) - size / 2, 0);
            glVertex3f((WSFML::getWidth()/2), (WSFML::getHeight()/2) + size / 2, 0);
        glEnd();
    
    
    /*
    sf::Font font;
    
    if(!font.loadFromFile("/Users/patrik/Dropbox/xcode/Build-Age/Arial.ttf")) {
        printf("ERROR FONT\n");
    }
    */
    
    
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    
}

void Control::getPick() {
    Block *b,*t;
    Vector3f eye, look, pos;
    float dx,dy,dz;
    
    Vector3F p = World::instance()->getPlayer()->getEye();
    
    pos.x = eye.x = p.x;
    pos.y = eye.y = p.y + HUMAN_HEIGHT;
    pos.z = eye.z = p.z;
    
    dx = World::instance()->getPlayer()->getView().x / 30.0;
    dy = World::instance()->getPlayer()->getView().y / 30.0;
    dz = World::instance()->getPlayer()->getView().z / 30.0;
    
    int maxDistance = 3;
    
    picked = NULL;
    
    while(1) {
        pos.x += dx;
        pos.y += dy;
        pos.z -= dz;
        
        // CHECK MAX DISTANCE
        if(
           abs(absf(pos.x) - absf(eye.x)) >= maxDistance ||
           abs(absf(pos.y) - absf(eye.y)) >= maxDistance ||
           abs(absf(pos.z) - absf(eye.z)) >= maxDistance
           )
            break;

        b = World::instance()->getBlock(pos.x,pos.y,pos.z);
        
        if(!b->isAir()) {
            t = World::instance()->getBlock(pos.x-dx,pos.y,pos.z);
            if(b->Compare(t) == false) {
                if(t->isAir() == false)
                    break;
                
                picketSide = dx > 0 ? 1 : 2; // 1 RIGHT, 2 LEFT
            }
            
            t = World::instance()->getBlock(pos.x,pos.y-dy,pos.z);
            if(b->Compare(t) == false) {
                if(t->isAir() == false)
                break;
                
                picketSide = dy > 0 ? 3 : 4; // 3 BOTTOM, 4 TOP
            }
            
            t = World::instance()->getBlock(pos.x,pos.y,pos.z+dz);
            if(b->Compare(t) == false) {
                if(t->isAir() == false)
                    break;
                
                picketSide = dz > 0 ? 5 : 6; // 5 FRONT, 6 BACK
            }
            
            //printf("%d\n", picketSide);
            
            picked = b;
            DrawPickBlock(b);
            break;
        }
    }
}

void Control::DrawPickBlock(Block *b) {
    int bx,by,bz;
    
    bx = b->getX() * BLOCK_SIZE;
    by = b->getY() * BLOCK_SIZE;
    bz = b->getZ() * BLOCK_SIZE;
    
    glBegin(GL_LINES);
        glVertex3f(bx, by, bz);                             glVertex3f(bx + BLOCK_SIZE, by, bz);
        glVertex3f(bx, by, bz);                             glVertex3f(bx, by + BLOCK_SIZE, bz);
        glVertex3f(bx+ BLOCK_SIZE, by, bz);                 glVertex3f(bx + BLOCK_SIZE, by + BLOCK_SIZE, bz);
        glVertex3f(bx, by+ BLOCK_SIZE, bz);                 glVertex3f(bx + BLOCK_SIZE, by + BLOCK_SIZE, bz);
        
        glVertex3f(bx, by, bz + BLOCK_SIZE);                glVertex3f(bx + BLOCK_SIZE, by, bz + BLOCK_SIZE);
        glVertex3f(bx, by, bz + BLOCK_SIZE);                glVertex3f(bx, by + BLOCK_SIZE, bz + BLOCK_SIZE);
        glVertex3f(bx+ BLOCK_SIZE, by, bz + BLOCK_SIZE);    glVertex3f(bx + BLOCK_SIZE, by + BLOCK_SIZE, bz + BLOCK_SIZE);
        glVertex3f(bx, by+ BLOCK_SIZE, bz + BLOCK_SIZE);    glVertex3f(bx + BLOCK_SIZE, by + BLOCK_SIZE, bz + BLOCK_SIZE);
        
        glVertex3f(bx, by, bz);                             glVertex3f(bx, by, bz + BLOCK_SIZE);
        glVertex3f(bx, by +BLOCK_SIZE, bz);                 glVertex3f(bx, by + BLOCK_SIZE, bz + BLOCK_SIZE);
        glVertex3f(bx +BLOCK_SIZE, by, bz);                 glVertex3f(bx + BLOCK_SIZE, by, bz + BLOCK_SIZE);
        glVertex3f(bx + BLOCK_SIZE, by + BLOCK_SIZE, bz);   glVertex3f(bx + BLOCK_SIZE, by + BLOCK_SIZE, bz + BLOCK_SIZE);
    glEnd();
}

void Control::destroyBlock() {
    if(!m_left || picked == NULL)
        return;
    
    // DEACTIVATE MOUSE LEFT CLICK
    m_left = false;
    
    // BOTTOM BLOCK IS INDESTRUCTIBLE
    if(picked->getY() == -128)
        return;
    
    // DELETE PICKED BLOCK
    picked->setType(0);
    
    Vector3F p;
    p.x = picked->getX();
    p.y = picked->getY();
    p.z = picked->getZ();
    World::instance()->getSection(p)->preLoad(picked);
    
    picked = NULL;
}

void Control::buildBlock() {
    if(!m_right || picked == NULL)
        return;
    
    m_right = false;
    
    Vector3F p, human, human2;
    p.x = picked->getX();
    p.y = picked->getY();
    p.z = picked->getZ();
    
    // 1 RIGHT, 2 LEFT
    // 3 BOTTOM, 4 TOP
    // 5 FRONT, 6 BACK
    switch(picketSide) {
        case 1:
            p.x--;
            break;
        case 2:
            p.x++;
            break;
        case 3:
            p.y--;
            break;
        case 4:
            p.y++;
            break;
        case 5:
            p.z++;
            break;
        case 6:
            p.z--;
            break;
    }
    
    float halfBlock = BLOCK_SIZE / 2.0;
    
    human2 = human = World::instance()->getPlayer()->getEye();
    /*
    human2.x = human.x = x;
    human2.y = human.y = y;
    human2.z = human.z = z;
    */
     human2.y++;

    // COLLISION
    if(checkCollision(human, halfBlock,p, HUMAN_SIZE) || checkCollision(human, halfBlock,p, HUMAN_SIZE))
        return;
    
    Block *b = World::instance()->getBlock(p.x,p.y,p.z);
    World::instance()->getSection(p)->preBuild(b);
}