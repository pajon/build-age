//
//  Geometry.h
//  Craft-Age
//
//  Created by Patrik Štrba on 15.3.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age__Geometry__
#define __Craft_Age__Geometry__

#include <iostream>

#include "Config.h"
#include <Client/Render/OpenGL.h>

enum FaceType {
    TOP = 0,
    BOTTOM = 1,
    FRONT = 2,
    BACK = 3,
    LEFT = 4,
    RIGHT = 5
};

class Geometry {
public:
    void addFace(FaceType type, Vert *vertex, Vector3f *block);
    void addIndex(unsigned int *index, int num);
private:
    void setNormal(FaceType type, Vector3f *n);
};

#endif /* defined(__Craft_Age__Geometry__) */
