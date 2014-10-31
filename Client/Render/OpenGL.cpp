//
//  OpenGL.cpp
//  GAME
//
//  Created by Patrik Štrba on 20.12.2012.
//  Copyright (c) 2012 Patrik Štrba. All rights reserved.
//

#include "OpenGL.h"

void OpenGL::initWindow(WSFML *window) {
    displayManager = window;
    
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    
    
    //glEnable(GL_CULL_FACE);
    //glCullFace(GL_FRONT);
    
    
    GLfloat LightAmbient[]= { 0.3f, 0.3f, 0.3f, 0.0f };// Okolní světlo
    GLfloat LightDiffuse[]= { 1.0f, 1.0f, 1.0f, 1.0f };// Přímé světlo
    GLfloat LightPosition[]= { 50.0f, 50.0f, 50.0f, 1.0f };// Pozice světla
    
    glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);// Nastavení okolního světla
    glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);// Nastavení přímého světla
    glLightfv(GL_LIGHT1, GL_POSITION,LightPosition);// Nastavení pozice světla
    
    
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    
    //glEnable(GL_LIGHT1);
    //glEnable(GL_LIGHTING);
    //glEnable(GL_COLOR_MATERIAL);
    //int tmp;
    
    //glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &tmp);
    //printf("%s\n", glGetString(GL_EXTENSIONS));
    //printf("%d\n", tmp);
    
    
    //GLuint programID = LoadShaders();
    
    glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        //glScalef(0.6,0.6,0.6);
        gluPerspective(FOVY, ((float)WSFML::getWidth() / (float)WSFML::getHeight()), 0.05, 3000.0);
    glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
    
    //glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
    
    
    //glClearColor(0, 0, 0, 1);
    glClearDepth(1.0);
    glLineWidth(2);
}

void OpenGL::closeWindow() {
    displayManager->close();
}

void OpenGL::DisplayCoords() {
    glDisable(GL_TEXTURE_2D);
    
    glBegin(GL_LINES);
    
    glColor3f(1.0f,0.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(100.0f, 0.0f, 0.0f);
    
    glColor3f(0.0f,1.0f,0.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 100.0f, 0.0f);
    
    glColor3f(0.0f,0.0f,1.0f);
    glVertex3f(0.0f, 0.0f, 0.0f);
    glVertex3f(0.0f, 0.0f, 100.0f);
    glEnd();
}

void OpenGL::preRender() {
    glEnable(GL_DEPTH_TEST);
    glDepthFunc( GL_LEQUAL );
    
    glClearColor( 173.0 / 255.0, 216.0 / 230.0, 1.0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glLoadIdentity();
}

void OpenGL::setCamera(float ex, float ey, float ez, float px, float py, float pz, float u1, float u2, float u3) {
    gluLookAt(
              ex,ey,ez,
              px,py,pz,
              u1,u2,u3
              );
}

void OpenGL::Render() {
    displayManager->render();
}