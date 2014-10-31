//
//  SFML.h
//  GAME
//
//  Created by Patrik Štrba on 28.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#ifndef __GAME__SFML__
#define __GAME__SFML__

#include <iostream>

#ifndef __APPLE__
	#include <GL/GLee.h>
	#include <GL/freeglut.h>

    #define glDeleteBuffersFIX(a,b)     glDeleteBuffersARB((a),(b))
    #define glGenBuffersFIX(a,b)        glGenBuffersARB((a),(b))
    #define glBindBufferFIX(a,b)        glBindBufferARB(a,b);
    #define glBufferDataFIX(a,b,c,d)    glBufferDataARB(a,b,c,d);
    #define glBufferSubDataFIX(a,b,c,d) glBufferSubDataARB(a,b,c,d);
#else
    #define glDeleteBuffersFIX(a,b)     glDeleteBuffers((a),(b))
    #define glGenBuffersFIX(a,b)        glGenBuffers((a),(b))
    #define glBindBufferFIX(a,b)        glBindBuffer(a,b);
    #define glBufferDataFIX(a,b,c,d)    glBufferData(a,b,c,d);
    #define glBufferSubDataFIX(a,b,c,d) glBufferSubData(a,b,c,d);
#endif

#include "Config.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/OpenGL.hpp>


using namespace sf;

class WSFML {
public:
    static WSFML *instance();
    void initGL();
    void close();
    void render();
    sf::RenderWindow *getWindow();
    
    static int getWidth();
    static int getHeight();
private:
    WSFML();
    sf::RenderWindow *window;
    static WSFML *inst;
    bool closed;
    sf::Mutex mutex;
};

#endif /* defined(__GAME__SFML__) */
