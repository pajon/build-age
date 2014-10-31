//
//  VBO.h
//  Craft-Age
//
//  Created by Patrik Štrba on 20.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age__VBO__
#define __Craft_Age__VBO__

#include <iostream>

#include "Client/Render/Opengl.h"

enum VBOstatus {
    INIT,
    CREATE,
    LOAD
};

class VBO {
public:
    VBO() {
        vertex = NULL;
        index = NULL;
        
        status = INIT;
    }
    void create();
    void render();
    void clean();
    
    // READY TO RENDER
    bool isReady();
    
    void insertData(Vert *data, unsigned int num);
    void insertIndex(GLuint *index, unsigned int num);
private:
    unsigned int nvertex;
    Vert *vertex;
    
    unsigned int nindex;
    GLuint *index;
    
    GLuint vbo[2];
    
    VBOstatus status;
};

#endif /* defined(__Craft_Age__VBO__) */
