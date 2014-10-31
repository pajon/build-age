//
//  JumpHelper.h
//  Build-Age
//
//  Created by Patrik Štrba on 20.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Build_Age__JumpHelper__
#define __Build_Age__JumpHelper__

#include <iostream>
#include <cmath>

#include "Config.h"


class JumpHelper {
public:
    JumpHelper();
    
    bool jump(Vector3F *v);
private:
    float jumpTime;
    
    bool checkCollision(Vector3F *v);
};

#endif /* defined(__Build_Age__JumpHelper__) */
