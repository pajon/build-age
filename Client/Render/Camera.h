//
//  Camera.h
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

//#include "OpenGL.h"
//#include "Block.h"
#include "../World/Section.h"

#ifndef __GAME__Camera__
#define __GAME__Camera__

#include <iostream>
#include <cmath>

class Camera {
public:
    static Camera *instance();
    void buildFrustum();
    bool inFrustrum(int x, int y, int z);
private:
    static Camera *inst;
    float frustum[6][4];
};

#endif /* defined(__GAME__Camera__) */
