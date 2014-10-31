//
//  Game.cpp
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Client/Client.h"
#include <cstdio>

void Client::init() {
    Debug::log("INIT");
    
    // INIT WINDOW
    WSFML *window = WSFML::instance();
    
    // CREATE CONTROL
    c = Control::instance();
    
    // CAMERA
    cam = Camera::instance();
    
    // TIME
    t = new Timer();
    
    hasStartEvent = false;

    window->getWindow()->setActive(false);
    
    sf::Thread thread_game(&Client::startGameLoop, this);
    thread_game.launch();
    
    Net *net = new Net();
    sf::Thread thread_net(&Net::startNet, net);
    thread_net.launch();
    
    while(hasStartEvent == false)
        sf::sleep(sf::milliseconds(1));
    
    printf("START\n");
    
    Events e;
    e.startListening(w->getPlayer());
}

void Client::startGameLoop() {
    WSFML::instance()->getWindow()->setActive(true);
    
    r = Render::instance();
    RenderManager::instance()->create(SECTION_CACHE_SIZE_X*SECTION_CACHE_SIZE_Z);
    
    // CREATE WORLD
    w = World::instance();
    w->prepareWorld();
    
    o = new OpenGL();
    o->initWindow(WSFML::instance());
    
    hasStartEvent = true;
    
    Player *p = w->getPlayer();
    
    while(WSFML::instance()->getWindow()->isOpen()) {
        // START TIME
        t->startTime();
        
        // MAIN LOOP
        p->Control();
        o->preRender();
        p->setCamera();
        
        // VYGENEROVANIE SURADNIC NA OREZAVANIE
        cam->buildFrustum();
        o->DisplayCoords();

      
        w->drawWorld();
  
        c->getPick();
        c->destroyBlock();
        c->buildBlock();

        Timer::getFPS();

        c->drawCursor();

        o->Render();
        // END TIME, PARSE TICK
        t->endTime();
    }
    RenderManager::instance()->exit();
}

void Client::shutdown() {
    o->closeWindow();
}