//
//  FallHelper.h
//  Build-Age
//
//  Created by Patrik Štrba on 20.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Build_Age__FallHelper__
#define __Build_Age__FallHelper__

#include <iostream>
#include <cmath>

#include "Config.h"

class FallHelper {
public:
    FallHelper();
    
    bool fall(Vector3F *p);
private:
    float jumpTime;
    
    bool hasFallCollision(Vector3F *v);
    float getDY(Vector3F *p);
};

#endif /* defined(__Build_Age__FallHelper__) */
