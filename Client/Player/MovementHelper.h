//
//  MovementHelper.h
//  Build-Age
//
//  Created by Patrik Štrba on 20.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Build_Age__MovementHelper__
#define __Build_Age__MovementHelper__

#include <iostream>
#include <cmath>

#include "Config.h"

class MovementHelper {
public:
    MovementHelper();
    
    void move(Vector3F *p, float viewX, float movementSpeed);
private:
    int prepareBound(float v);
    
    bool checkCollision(Vector3F obj1, float size1, Vector3F obj2, float size2);
};

#endif /* defined(__Build_Age__MovementHelper__) */
