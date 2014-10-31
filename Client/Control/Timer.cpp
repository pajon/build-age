//
//  Time.cpp
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Timer.h"
#include <cstdio>

sf::Time Timer::tick;
long Timer::fps_time = 0;
int Timer::fps = 0;

void Timer::startTime() {
    clock.restart();
}

void Timer::endTime() {
    tick = clock.getElapsedTime();
}

int Timer::getTick() {
    return (int)tick.asMicroseconds();
}

void Timer::getFPS() {
    fps_time += getTick();
    fps++;
    if(fps_time < 1000000)
        return;
    
    printf("FPS: %.1f\n", (float)((float)fps / ((float)(fps_time) / 1000000.0)));
    fps = 0;
    fps_time = 0;
}

void Timer::limitFPS(int fps) {
    int t = (1.0 / (float)fps) * 1000000;
    
    if(t < getTick())
        return;

    //sf::sleep((t - getTick()) / 1000);
    //SDL_Delay((t - getTick()) / 1000);
    endTime();
}