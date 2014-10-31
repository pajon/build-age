 //
//  RenderManager.cpp
//  Build-Age
//
//  Created by Patrik Štrba on 6.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "RenderManager.h"
#include <cstdio>

RenderManager *RenderManager::inst = 0;

RenderManager *RenderManager::instance() {
    if(!inst)
        inst = new RenderManager();
    return inst;
}

RenderManager::RenderManager() {

}

void RenderManager::create(unsigned int num) {
    m.lock();
        for(int i=0;i<num;i++) {
            VBOs *v = new VBOs;
            glGenBuffers(2, v->vbo);
            v->clean = false;
            stackVBO.push(v);
        }
    m.unlock();
}

VBOs *RenderManager::get() {
    m.lock();
        VBOs *v = stackVBO.top();
        stackVBO.pop();
    m.unlock();
    return v;
}

void RenderManager::del(VBOs *v) {
    m.lock();
        stackVBO.push(v);
    m.unlock();
}

void RenderManager::clean() {
    m.lock();
    VBOs *v;
    while(!stackVBO.empty()) {
        v = stackVBO.top();
        if(v->clean) {
            glBindBuffer(GL_ARRAY_BUFFER, v->vbo[0]);
            glBufferData(GL_ARRAY_BUFFER, sizeof(Vert) * v->nvertex, NULL, GL_STATIC_DRAW);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, v->vbo[1]);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * v->nindex, NULL, GL_STATIC_DRAW);
            v->nindex = v->nvertex = 0;
            v->clean = false;
        }
        
        stackVBOtmp.push(v);
        stackVBO.pop();
    }
    while(!stackVBOtmp.empty()) {
        stackVBO.push(stackVBOtmp.top());
        stackVBOtmp.pop();
    }
    m.unlock();
}

void RenderManager::exit() {
    clean();
    
    while(!stackVBO.empty()) {
        VBOs *v = stackVBO.top();
        
        glDeleteBuffers(2, v->vbo);
        stackVBO.pop();
    }
}

void RenderManager::deleteVBO(GLuint buffer) {
    m.lock();
        stackDel.push(buffer);
    m.unlock();
}

void RenderManager::runDelete() {
    m.lock();
    while(!stackDel.empty()) {
        GLuint tmp = stackDel.top();
        
        glDeleteBuffers(1, &(tmp));
        stackDel.pop();
    }
    m.unlock();
}