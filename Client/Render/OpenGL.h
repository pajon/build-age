//
//  OpenGL.h
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//


#ifndef __GAME__OpenGL__
#define __GAME__OpenGL__

#include <iostream>

#include "Client/Render/WSFML.h"

typedef struct
{
	GLfloat location[3];
	GLfloat tex[2];
	GLfloat normal[3];
	GLfloat colour[4];
	GLubyte padding[16]; // Pads the struct out to 64 bytes for performance increase
} Vert;

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

#define X_POS 0
#define Y_POS 1
#define Z_POS 2
// Texture Coordinates
#define U_POS 0
#define V_POS 1
// Colours
#define R_POS 0
#define G_POS 1
#define B_POS 2
#define A_POS 3

#define FOVY 60.0

class OpenGL {
public:
    int width, height;
    void initWindow(WSFML *window);
    void closeWindow();
    void DisplayCoords();
    void preRender();
    void setCamera(float ex, float ey, float ez, float px, float py, float pz, float u1, float u2, float u3);
    void Render();
private:
    WSFML *displayManager;
};

#endif /* defined(__GAME__OpenGL__) */
