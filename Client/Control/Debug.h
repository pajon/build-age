//
//  Debug.h
//  GAME
//
//  Created by Patrik Štrba on 25.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#ifndef __GAME__Debug__
#define __GAME__Debug__

#include <iostream>
#include <SFML/System/Clock.hpp>

using namespace std;

class Debug {
public:
    static void log(std::string action, int thread = 0);
    static sf::Clock time;
};

#endif /* defined(__GAME__Debug__) */
