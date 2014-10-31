//
//  Game.h
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "Client/Render/OpenGL.h"
#include "Client/Render/Render.h"
#include "Client/Control/Control.h"
#include "Client/World/World.h"
#include "Client/Render/Camera.h"
#include "Client/Control/Timer.h"

#ifndef __GAME__Game__
#define __GAME__Game__

#include <iostream>
#include "Client/Control/Debug.h"
#include "Client/Control/Events.h"
#include "Client/Player/Player.h"
#include "Client/Network/Net.h"


#include <SFML/System/Thread.hpp>


class Client {
public:
    void init();
private:
    
    bool hasStartEvent;
    
    OpenGL *o;
    Control *c;
    World *w;
    Camera *cam;
    Timer *t;
    
    Render *r;
    void startGameLoop();
    void shutdown();
};

#endif /* defined(__GAME__Game__) */
