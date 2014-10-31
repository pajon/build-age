//
//  World.h
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#ifndef __GAME__World__
#define __GAME__World__

#include <iostream>

#include "Config.h"
#include "Client/Control/Control.h"
#include "Client/Render/OpenGL.h"
#include "Client/Render/Camera.h"

#include "Client/Render/VBO.h"

#include "Client/World/Section.h"

#include "Client/World/SectionManager.h"
#include "Client/World/RenderManager.h"

#include "Client/Player/Player.h"


typedef struct {
    int x : 24;
    int y : 8;
    int z : 24;
    int type : 8;
} BLOCK;


const int numB = 4;// BLOCKS NUM

class World {
public:
    static World *instance();
    
    void prepareWorld();
    void drawWorld();
    
    void bindBlocksTexture();
    Block *getBlock(float x, float y, float z);
    Section *getCurrentSection();
    Section *getSection(Vector3F p);
    
    bool checkCollision(Vector3F p);
    bool checkCollision(Vector3F p, int dx, int dy, int dz);
    
    Player *getPlayer();
protected:
    World();
    
    void loadBlocksData();
    void loadBlocksTexture();
private:
    void prepareVBO();
    
    static World *inst;
    
    bool dirtyWorld;
    
    Control *c;
    Camera *cam;
    SectionManager *m;
    BlockType blockType[numB];
    GLuint gBlockTexture;

    bool initWorld;
    int offsetX,offsetY,offsetZ;
    Section *sections[VIEW_SIZE_X][VIEW_SIZE_Z];
    
    // PLAYER
    Player player;
    
    // 2 VBO
    VBO vbo[2];
    
    // ACTIVE RENDER INDEX VBO
    GLuint vboI;
};

#endif /* defined(__GAME__World__) */
