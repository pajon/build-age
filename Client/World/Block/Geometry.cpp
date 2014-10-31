//
//  Geometry.cpp
//  Craft-Age
//
//  Created by Patrik Štrba on 15.3.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Geometry.h"

void Geometry::addFace(FaceType type, Vert *vertex, Vector3f *block) {
    int x,y,z;
    
    x = block->x;
    y = block->y;
    z = block->z;
    
    Vector3f v[4];
    Vector3f n;
    
    // CLEAR
    for(int i=0;i<4;i++)
        v[i].x = v[i].y = v[i].z = 0;
    
    setNormal(type, &n);
    
    switch(type) {
        case TOP:
            v[0].y = v[1].y = v[2].y = v[3].y = BLOCK_SIZE;
        case BOTTOM:
            v[1].x = v[2].x = v[2].z = v[3].z = BLOCK_SIZE;
            break;
            
        case RIGHT:
            v[0].x = v[1].x = v[2].x = v[3].x = BLOCK_SIZE;
        case LEFT:
            v[1].z = v[2].z = v[2].y = v[3].y = BLOCK_SIZE;
            break;
            
        case FRONT:
            v[0].z = v[1].z = v[2].z = v[3].z = BLOCK_SIZE;
        case BACK:
            v[1].x = v[2].x = v[2].y = v[3].y = BLOCK_SIZE;
            break;
    }
    
    vertex[0].location[X_POS]	= x - SECTION_SIZE_X + v[0].x;
    vertex[0].location[Y_POS]	= y - 128 + v[0].y;
    vertex[0].location[Z_POS]	= z - SECTION_SIZE_Z + v[0].z;

    vertex[1].location[X_POS]	= x - SECTION_SIZE_X + v[1].x;
    vertex[1].location[Y_POS]	= y - 128 + v[1].y;
    vertex[1].location[Z_POS]	= z - SECTION_SIZE_Z + v[1].z;
    
    vertex[2].location[X_POS]	= x - SECTION_SIZE_X + v[2].x;
    vertex[2].location[Y_POS]	= y - 128 + v[2].y;
    vertex[2].location[Z_POS]	= z - SECTION_SIZE_Z + v[2].z;
    
    vertex[3].location[X_POS]	= x - SECTION_SIZE_X + v[3].x;
    vertex[3].location[Y_POS]	= y - 128 + v[3].y;
    vertex[3].location[Z_POS]	= z - SECTION_SIZE_Z + v[3].z;

    vertex[0].tex[U_POS]	= 0;	vertex[0].tex[V_POS]	= 0.0;
    vertex[1].tex[U_POS]	= 0;	vertex[1].tex[V_POS]	= 0.5;
    vertex[2].tex[U_POS]	= 0.5;	vertex[2].tex[V_POS]    = 0.5;
    vertex[3].tex[U_POS]	= 0.5;	vertex[3].tex[V_POS]	= 0.0;

    vertex[0].normal[X_POS]	= n.x;	vertex[0].normal[Y_POS]	= n.y;	vertex[0].normal[Z_POS]	= n.z;
    vertex[1].normal[X_POS]	= n.x;	vertex[1].normal[Y_POS]	= n.y;	vertex[1].normal[Z_POS]	= n.z;
    vertex[2].normal[X_POS]	= n.x;	vertex[2].normal[Y_POS]	= n.y;	vertex[2].normal[Z_POS]	= n.z;
    vertex[3].normal[X_POS]	= n.x;	vertex[3].normal[Y_POS]	= n.y;	vertex[3].normal[Z_POS]	= n.z;
}

void Geometry::addIndex(unsigned int *index, int num) {
    index[0] = num+0;
    index[1] = num+1;
    index[2] = num+2;
    
    index[3] = num+2;
    index[4] = num+3;
    index[5] = num+0;
}

void Geometry::setNormal(FaceType type, Vector3f *n) {
    n->x = n->y = n->z = 0;
    switch(type) {
        case TOP:
            n->y = 1;
            break;
        case BOTTOM:
            n->y = -1;
            break;
            
        case RIGHT:
            n->x = -1;
            break;
        case LEFT:
            n->x = 1;
            break;
            
        case FRONT:
            n->z = 1;
            break;
        case BACK:
            n->z = -1;
            break;
    }
}