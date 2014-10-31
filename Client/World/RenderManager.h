//
//  RenderManager.h
//  Build-Age
//
//  Created by Patrik Štrba on 6.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Build_Age__RenderManager__
#define __Build_Age__RenderManager__

#include <iostream>
#include <stack>
#include <SFML/System/Mutex.hpp>
#include "Client/Render/WSFML.h"
#include "Client/Render/Opengl.h"


typedef struct {
    GLuint vbo[2];
    bool clean;
    int nvertex, nindex;
} VBOs;

class RenderManager {
public:
    static RenderManager *instance();
    
    void create(unsigned int num);
    VBOs *get();
    void del(VBOs *v);
    void clean();
    void exit();
    
    
    void deleteVBO(GLuint buffer);
    void runDelete();
    
private:
    RenderManager();
    static RenderManager *inst;
    
    sf::Mutex m;
    
    std::stack<GLuint> stackDel;
    
    std::stack<VBOs *> stackVBO;
    std::stack<VBOs *> stackVBOtmp;
};

#endif /* defined(__Build_Age__RenderManager__) */
