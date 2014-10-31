//
//  VBO.cpp
//  Craft-Age
//
//  Created by Patrik Štrba on 20.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "VBO.h"


void VBO::create() {
    if(status != INIT)
        return perror("try to create VBO without INIT status");
    
    glGenBuffers(2, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * nvertex, vertex, GL_STATIC_DRAW);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vert) * nvertex, vertex);
    
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * nindex, NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(GLuint) * nindex, index);
    //LOG("CREATE VBO END");
}

void VBO::clean() {
    if(status != LOAD)
        return perror("try to clean VBO without LOAD status");
    
    free(vertex);
    vertex = NULL;
    
    free(index);
    index = NULL;
    
    glDeleteBuffers(2, vbo);
    
    status = INIT;
}

void VBO::render() {
    if(status != LOAD)
        return perror("try to render VBO without LOAD status");
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    
    // SET OFFSET
    glTexCoordPointer(2, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(12));
    glNormalPointer(GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(20));
    glColorPointer(4, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(32));
    glVertexPointer(3, GL_FLOAT, sizeof(Vert), BUFFER_OFFSET(0));
    
    glDrawElements(GL_LINES, nindex, GL_UNSIGNED_INT, BUFFER_OFFSET(0));
}

bool VBO::isReady() {
    return status == LOAD;
}