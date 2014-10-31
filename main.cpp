//
//  main.cpp
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include <iostream>
#include "Client/Client.h"

#include <SFML/Graphics/Font.hpp>

#include "Client/GUI/Font.h"


int main(int argc, const char * argv[])
{
    
    /*
    sf::Font f;
    
    f.loadFromFile("/Users/patrik/Dropbox/xcode/Build-Age/Build-Age/Data/Arial.ttf");
    
    for(int i = 'A'; i <= 'Z'; i++) {
        f.getGlyph(i, 15, false);
    }
    f.getTexture(15).copyToImage().saveToFile("/Users/patrik/Dropbox/xcode/Build-Age/Build-Age/Data/test.jpg");
    //GUI::Font *f = NULL;
    */
    //f = new GUI::Font();
    
    //return 0;
    
    
    Client c;
    c.init();
    return 0;
}