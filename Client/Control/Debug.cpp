//
//  Debug.cpp
//  GAME
//
//  Created by Patrik Štrba on 25.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Debug.h"
#include <cstdio>

sf::Clock Debug::time = sf::Clock();

void Debug::log(std::string action, int thread) {
    //printf("DEBUG: %07lld %s\n", time.getElapsedTime().asMicroseconds(), action);
    std::cout << "DEBUG: " << time.getElapsedTime().asMicroseconds() << " " << action << std::endl;
    time.restart();
    
}