//
//  Render.h
//  Craft-Age
//
//  Created by Patrik Štrba on 18.3.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age__Render__
#define __Craft_Age__Render__

#include <iostream>
#include "Client/Render/TextureManager.h"
class Render {
public:
    static Render *instance();
    void start();
    
    void renderFrame();
    
    TextureManager *getTextureManager();
    
private:
    Render() {
        
    }
    TextureManager tex;
    
    static Render *inst;
};

#endif /* defined(__Craft_Age__Render__) */
