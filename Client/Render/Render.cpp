//
//  Render.cpp
//  Craft-Age
//
//  Created by Patrik Štrba on 18.3.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "Render.h"

Render *Render::inst = 0;

Render *Render::instance() {
    if(!inst)
        inst = new Render();
    return inst;
}

TextureManager *Render::getTextureManager() {
    return &tex;
}