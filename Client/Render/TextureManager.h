//
//  TextureManager.h
//  Craft-Age
//
//  Created by Patrik Štrba on 18.3.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age__TextureManager__
#define __Craft_Age__TextureManager__

#include <iostream>
#include "Client/Render/Texture.h"

#include <map>

class TextureManager {
public:
    void add(char *name, sf::Texture *t);
private:
    std::map<char *,sf::Texture*> list;
    
};

#endif /* defined(__Craft_Age__TextureManager__) */
