//
//  SFML.cpp
//  GAME
//
//  Created by Patrik Štrba on 28.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Client/Render/WSFML.h"

WSFML *WSFML::inst = 0;

WSFML *WSFML::instance() {
    if(!inst)
        inst = new WSFML();
    return inst;
}

WSFML::WSFML() {
    closed = false;
    
    initGL();
}

sf::RenderWindow *WSFML::getWindow() {
    return window;
}

void WSFML::initGL() {
    
    sf::ContextSettings settings;
    settings.depthBits = 32;
    settings.stencilBits = 8;
    settings.antialiasingLevel = 0;
    settings.majorVersion = 3;
    settings.minorVersion = 0;
    // sf::Style::Default
    window = new RenderWindow(
                              sf::VideoMode(getWidth(), getHeight()),
                              "SFML window",
#ifdef DEBUG_FULLSCREEN_MODE
                              sf::Style::Fullscreen,
#else
                              sf::Style::Default,
#endif
                              settings
            );
    window->setVerticalSyncEnabled(false);
    
    window->setFramerateLimit(60);
    
    //window->setFramerateLimit(5);
    
    window->setMouseCursorVisible(false);
    
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_DONT_CARE);
    
    //printf("%d %d\n", getWidth(),getHeight());
}

int WSFML::getWidth() {
#ifdef DEBUG_FULLSCREEN_MODE
    return sf::VideoMode::getDesktopMode().width;
#else
    return 640;
#endif
}

int WSFML::getHeight() {
#ifdef DEBUG_FULLSCREEN_MODE
    return sf::VideoMode::getDesktopMode().height;
#else
    return 480;
#endif
}

void WSFML::close() {
    mutex.lock();
    closed = true;
    window->setActive(false);
    window->close();
    mutex.unlock();
}

void WSFML::render() {
    mutex.lock();
    if(closed)
        return;
    
    window->display();
    window->clear();
    mutex.unlock();
}