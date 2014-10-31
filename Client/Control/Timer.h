//
//  Time.h
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#ifndef __GAME__Time__
#define __GAME__Time__

#include <iostream>
#include <SFML/System/Clock.hpp>
//#include <SFML/System.hpp>
using namespace sf;

class Timer {
public:
    static int getTick();
    static void getFPS();
    void startTime();
    void endTime();
    void limitFPS(int fps);
protected:
    static sf::Time tick;
    static int fps;
    static long fps_time;

    sf::Clock clock;
    //static long tick;
    //static long time;
};

#endif /* defined(__GAME__Time__) */
