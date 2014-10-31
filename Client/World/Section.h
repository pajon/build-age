//
//  Section.h
//  GAME
//
//  Created by Patrik Štrba on 22.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Block.h"
#include "Client/World/SectionManager.h"
#include "Client/Render/OpenGL.h"

#ifndef __GAME__Section__
#define __GAME__Section__

#include <iostream>
#include "Client/World/Generate/PerlinNoise.h"
#include "Config.h"
#include "Client/World/RenderManager.h"
#include "Client/World/Block/Geometry.h"

class Section {
public:
    Section(int _x, int _y, int _z);
    Section(int _x, int _z);
    bool Compare(Section *s);
    void loadBlocks();
    void render();
    Block *getBlock(int x,int y,int z);
    int getX();
    int getZ();

    void freeCache();
    ~Section();
    
    GLuint vbo[2];
    VBOs *v;
    
    void preLoad(Block *b);
    void preBuild(Block *b);
    
    
    Vert *getData(int x, int y);
private:
    
    Geometry geometry;
    bool hidden;
    bool empty;
    int x,y,z;
    
    bool canClean;
    int stepInsert;
    
    unsigned int nvertex;
    Vert *vertex;
    
    unsigned int nindex;
    GLuint *index;
    
    bool loadCache;
    
    Block blocks[SECTION_SIZE_X][SECTION_SIZE_Y][SECTION_SIZE_Z];
    
    void generateBuffers();
    void generateVBO();
    void renderVBO();
    
    void insertBlock(int x, int y, int z);
    unsigned int prepareBlocks();
};

#endif /* defined(__GAME__Section__) */
