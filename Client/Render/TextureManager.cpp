//
//  TextureManager.cpp
//  Craft-Age
//
//  Created by Patrik Štrba on 18.3.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "TextureManager.h"


void TextureManager::add(char *name, sf::Texture *t) {
    list.insert(std::pair<char *, sf::Texture*>(name,t));
}