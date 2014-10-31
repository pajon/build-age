  //
//  Section.cpp
//  GAME
//
//  Created by Patrik Štrba on 22.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Section.h"
#include "../Control/Control.h"
#include <cstdio>

Section::Section(int _x, int _z) {
    Section(_x, 0, _z);
}

Section::Section(int _x, int _y, int _z) {
    v = NULL;
    hidden = true; // OUTSIDE FRUSTRUM
    empty = true; // 0 BLOCKS
    
    index = NULL;
    vertex = NULL;
    
    nindex = nvertex = 0;
    
    this->x = _x;
    this->y = _y;
    this->z = _z;
    
    canClean = false;
    loadCache = false;
    
    LOG("SECTION INIT");
    loadBlocks();
}

Section::~Section() {
    if(v != NULL)
        RenderManager::instance()->del(v);
    
    if(vertex != NULL)
        free(vertex);
    
    if(index != NULL)
        free(index);
}

void Section::preLoad(Block *b) {
    int rx = this->x * SECTION_SIZE_X;
    int rz = this->z * SECTION_SIZE_Z;
    
    int tx,ty,tz;
    
    tx = b->getX() - rx;
    ty = b->getY() + 128;
    tz = b->getZ() - rz;
    
    if(tx != 0)
        blocks[tx-1][ty][tz].rside = true;
    if(ty != 0)
        blocks[tx][ty-1][tz].tside = true;
    if(tz != 0)
        blocks[tx][ty][tz-1].fside = true;
    
    if(tx != SECTION_SIZE_X-1)
        blocks[tx+1][ty][tz].lside = true;
    if(ty != SECTION_SIZE_Y-1)
        blocks[tx][ty+1][tz].bside = true;
    if(tz != SECTION_SIZE_Z-1)
        blocks[tx][ty][tz+1].uside = true;
    
    
    if(v != NULL)
        RenderManager::instance()->del(v);
    
    if(vertex != NULL) {
        free(vertex);
        vertex = NULL;
    }
    
    if(index != NULL) {
        free(index);
        index= NULL;
    }
    
    
    generateBuffers();
}

void Section::preBuild(Block *b) {
    int rx = this->x * SECTION_SIZE_X;
    int rz = this->z * SECTION_SIZE_Z;
    
    int tx,ty,tz;
    
    tx = b->getX() - rx;
    ty = b->getY() + 128;
    tz = b->getZ() - rz;
    
    
    blocks[tx][ty][tz].resetSide();
    blocks[tx][ty][tz].setType(1);
    
    if(tx != 0) {
        if(blocks[tx-1][ty][tz].isAir() == false) {
            blocks[tx-1][ty][tz].setRightSide(false);
            blocks[tx][ty][tz].setLeftSide(false);
        }
    }
    
    if(ty != 0) {
        if(blocks[tx][ty-1][tz].isAir() == false) {
            blocks[tx][ty-1][tz].setTopSide(false);
            blocks[tx][ty][tz].setBottomSide(false);
        }
    }

    if(tz != 0) {
        if(blocks[tx][ty][tz-1].isAir() == false) {
            blocks[tx][tz][tz-1].setFrontSide(false);
            blocks[tx][ty][tz].setBackSide(false);
        }
    }
    
    if(tx != SECTION_SIZE_X-1) {
        if(blocks[tx+1][ty][tz].isAir() == false) {
            blocks[tx+1][ty][tz].setLeftSide(false);
            blocks[tx][ty][tz].setRightSide(false);
        }
    }

    if(ty != SECTION_SIZE_Y-1) {
        if(blocks[tx][ty+1][tz].isAir() == false) {
            blocks[tx][ty+1][tz].setBottomSide(false);
            blocks[tx][ty][tz].setTopSide(false);
        }
    }
    if(tz != SECTION_SIZE_Z-1) {
        if(blocks[tx][ty][tz+1].isAir() == false) {
            blocks[tx][tz][tz+1].setBackSide(false);
            blocks[tx][ty][tz].setFrontSide(false);
        }
    }
    
    
    if(v != NULL)
        RenderManager::instance()->del(v);
    
    if(vertex != NULL) {
        free(vertex);
        vertex = NULL;
    }
    
    if(index != NULL) {
        free(index);
        index= NULL;
    }
    
    generateBuffers();
}

void Section::freeCache() {
    free(vertex);
    vertex = NULL;
    
    free(index);
    index = NULL;
    
    canClean = false;
}

bool Section::Compare(Section *s) {
    return getX() == s->getX() && getZ() == s->getZ();
}

int Section::getX() {
    return x;
}

int Section::getZ() {
    return z;
}

void Section::render() {
    if(empty)
        return;
    
    if(loadCache) {
        generateVBO();
        loadCache = false;
        canClean = true;
        
        // FREE CACHE DATA
        SectionManager::instance()->freeMem(vertex);
        //free(vertex);
        vertex = NULL;
        SectionManager::instance()->freeMem(index);
        //free(index);
        index = NULL;
    }
    
    renderVBO();
}

void Section::generateVBO() {
    LOG("CREATE VBO");    
    v = RenderManager::instance()->get();
    v->clean = true;
    v->nvertex = nvertex;
    v->nindex = nindex;
    
    
    glBindBuffer(GL_ARRAY_BUFFER, v->vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * nvertex, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vert) * nvertex, vertex);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v->vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nindex, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint) * nindex, index);
    LOG("CREATE VBO END");
}

void Section::renderVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, v->vbo[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v->vbo[1]);
    
    // SET OFFSET
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(12));
    glNormalPointer(GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(20));
    glColorPointer(4, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(32));
    glVertexPointer(3, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(0));

    glPushMatrix();
    
        glTranslatef(x*SECTION_SIZE_X+SECTION_SIZE_X, 0, z*SECTION_SIZE_Z+SECTION_SIZE_Z);
    
        glDrawElements(GL_TRIANGLES, nindex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
    glPopMatrix();
    
    glBindBuffer(GL_ARRAY_BUFFER, NULL);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
}

void Section::loadBlocks() {
    int rx = this->x * SECTION_SIZE_X;
    int rz = this->z * SECTION_SIZE_Z;
    
    double x0z0,x1z0,x0z1,x1z1;
    PerlinNoise p(0.69, 1, 30, 6, 75452334);
    x0z0 = p.GetData(rx, rz);
    x1z0 = p.GetData(rx+SECTION_SIZE_X, rz);
    x0z1 = p.GetData(rx, rz+SECTION_SIZE_Z);
    x1z1 = p.GetData(rx+SECTION_SIZE_X, rz+SECTION_SIZE_Z);

    for(int z=0;z<SECTION_SIZE_Z;z++)
        for(int x=0;x<SECTION_SIZE_X;x++) {
            float hdata = (float)p.biLinearInterpolation(x0z0,x1z0,x0z1,x1z1,x/(float)SECTION_SIZE_X,z/(float)SECTION_SIZE_Z);
            for(int y=0;y<SECTION_SIZE_Y;y++)
                blocks[x][y][z].init(rx+x,y-(SECTION_SIZE_Y >> 1),rz+z,y-(SECTION_SIZE_Y >> 1) < hdata ? 1 : 0);
        }

    generateBuffers();
    
}

void Section::generateBuffers() {
    stepInsert = 0;
    unsigned int count = prepareBlocks();
    
    if(count == 0)
        return;
    
    loadCache = true;
    empty = false;
    
    nvertex = count * 4;
    nindex = count * 6;
    
    if(vertex != NULL)
        free(vertex);
    
    vertex = (Vert *)malloc(sizeof(Vert) * nvertex);
    if(vertex == NULL)
        printf("MALLOC: VERTEX\n");
    
    if(index != NULL)
        free(index);
    
    index = (unsigned int *) malloc(sizeof(unsigned int) * nindex);
    if(index == NULL)
        printf("MALLOC: INDEX\n");
    
    memset(vertex, 0, sizeof(Vert) * nvertex);
    memset(index, 0, sizeof(unsigned int) * nindex);
    
    for(int z=0;z<SECTION_SIZE_Z;z++)
        for(int x=0;x<SECTION_SIZE_X;x++)
            for(int y=0;y<SECTION_SIZE_Y;y++)
                insertBlock(x,y,z);
    
    for (int n = 0; n < nvertex; n++)
	{
		vertex[n].colour[R_POS] = 1.0;
		vertex[n].colour[G_POS] = 1.0;
		vertex[n].colour[B_POS] = 1.0;
		vertex[n].colour[A_POS] = 1.0;
	}
}

void Section::insertBlock(int x, int y, int z) {
    
    // AK KOCKA NEEXISTUJE NEBUDEME PRIDAVAT ZIADNE VERTEXY
    if(blocks[x][y][z].isAir())
        return;
    
    int i,j;
    
    Vector3f b;
    
    b.x = x;
    b.y = y;
    b.z = z;
 
    i = stepInsert * 4;
    j = stepInsert * 6;
    
    for(int type = 0; type < 6; type++) {
        if(blocks[x][y][z].hasVisible((FaceType)type)) {
            i = stepInsert * 4;
            j = stepInsert * 6;
            
            geometry.addFace((FaceType)type, vertex+(stepInsert*4), &b);
            geometry.addIndex(index+j, i);

            stepInsert++;
        }
    }
}

Block *Section::getBlock(int x,int y,int z) {
    int fx,fy,fz;
    
    if(x < 0) {
        if(x % SECTION_SIZE_X == 0)
                fx = 0;
            else
                fx = SECTION_SIZE_X - ((x*-1) % SECTION_SIZE_X);
    } else
        fx = x % SECTION_SIZE_X;
    
    fy = y + 128;
    
    if(z < 0) {
        if(z % SECTION_SIZE_Z == 0)
            fz = 0;
        else
            fz = SECTION_SIZE_Z - ((z*-1) % SECTION_SIZE_Z);
    } else
        fz = z % SECTION_SIZE_Z;
    
    return &blocks[fx][fy][fz];
}

unsigned int Section::prepareBlocks() {
    unsigned int num = 0;
    for(int x=0;x<SECTION_SIZE_X;x++) {
        for(int y=0;y<SECTION_SIZE_Y;y++) {
            for(int z=0;z<SECTION_SIZE_Z;z++) {
                if(blocks[x][y][z].isAir())
                    continue;
                
                // TOP
                if(y != (SECTION_SIZE_Y-1) && blocks[x][y+1][z].isAir() == false)
                    blocks[x][y][z].tside = 0;
                else
                    num++;
                
                // BOT
                if(y != 0 && blocks[x][y-1][z].isAir() == false)
                    blocks[x][y][z].bside = 0;
                else
                    num++;
                
                // FRONT
                if(z != (SECTION_SIZE_Z-1) && blocks[x][y][z+1].isAir() == false)
                    blocks[x][y][z].fside = 0;
                else
                    num++;
                
                // BACK
                if(z != 0 && blocks[x][y][z-1].isAir() == false)
                    blocks[x][y][z].uside = 0;
                else
                    num++;
                
                // LEFT
                if(x != (SECTION_SIZE_X-1) && blocks[x+1][y][z].isAir() == false)
                    blocks[x][y][z].rside = 0;
                else
                    num++;
                
                // RIGHT
                if(x != 0 && blocks[x-1][y][z].isAir() == false)
                    blocks[x][y][z].lside = 0;
                else
                    num++;
            }
        }
    }
    return num;
}

/*


Vert *Section::getData(int x, int y) {
    unsigned int count = prepareBlocks();
    
    if(count == 0)
        return NULL;
    
    nvertex = count * 4;
    nindex = count * 6;
    
    if(vertex != NULL)
        free(vertex);
    
    vertex = (Vert *)malloc(sizeof(Vert) * nvertex);
    if(vertex == NULL)
        printf("MALLOC: VERTEX\n");
    
    if(index != NULL)
        free(index);
    
    index = (unsigned int *) malloc(sizeof(unsigned int) * nindex);
    if(index == NULL)
        printf("MALLOC: INDEX\n");
    
    for(int z=0;z<SECTION_SIZE_Z;z++)
        for(int x=0;x<SECTION_SIZE_X;x++)
            for(int y=0;y<SECTION_SIZE_Y;y++)
                insertBlock(x,y,z);
    
    for (int n = 0; n < count*4; n++)
	{
		vertex[n].colour[R_POS] = 1.0;
		vertex[n].colour[G_POS] = 1.0;
		vertex[n].colour[B_POS] = 1.0;
		vertex[n].colour[A_POS] = 1.0;
	}

}
 */

