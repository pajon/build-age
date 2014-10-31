//
//  Config.h
//  Build-Age
//
//  Created by Patrik Štrba on 3.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//


#ifndef Build_Age_Config_h
#define Build_Age_Config_h

typedef struct {
    float x,y,z;
} Vector3F;

#define DEBUG_MODE 0

//#define DEBUG_FULLSCREEN_MODE

#if DEBUG_MODE
    #include "Control/Debug.h"
    #define LOG(x) Debug::log(x);
#else
    #define LOG(x) 
#endif


#define WORLD_DATA "/Users/Patrik/Desktop/Projekt 2/GAME/GAME/world.dat"

#define TEXTURE_FORMAT 3 // len RGB, pripadne 4 pre RGBA
#define TEXTURE_WIDTH 64
#define TEXTURE_HEIGHT 64
#ifndef __APPLE__
#define BLOCKTEXFILE "Data/tex2.rgb"
#else
#define BLOCKTEXFILE "/Users/patrik/Dropbox/xcode/Build-Age/Build-Age/Data/tex2.rgb_povodna"
//#define BLOCKTEXFILE "/Users/patrik/Dropbox/xcode/Build-Age/Documentation/Texture/Game/Data/tex2.rgb"
#endif

#define BLOCK_SIZE 1.0

#define WORLD_SIZE_X 64
#define WORLD_SIZE_Y 128
#define WORLD_SIZE_Z 64

// MUSI BYT NEPARNE !!!!
#define VIEW_SIZE_X 9
#define VIEW_SIZE_Z 9


// OSU Y NEBUDEME CACHOVAT
#define CACHE_SIZE_X 8
#define CACHE_SIZE_Z 8

#define SECTION_SIZE_X 16
#define SECTION_SIZE_Y 256
#define SECTION_SIZE_Z 16

#define MOVEMENTSPEED 4.0

#endif
