//
//  SectionManager.h
//  Build-Age
//
//  Created by Patrik Štrba on 4.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Build_Age__SectionManager__
#define __Build_Age__SectionManager__

#include <iostream>
#include "Config.h"
#include "Client/World/Section.h"
#include <SFML/System/Thread.hpp>

typedef struct {
    void *s;
} SectionFree;

#define SECTION_CACHE_X 1
#define SECTION_CACHE_Z 1
#define SECTION_CACHE_SIZE_X (VIEW_SIZE_X + (2 * SECTION_CACHE_X))
#define SECTION_CACHE_SIZE_Z (VIEW_SIZE_Z + (2 * SECTION_CACHE_Z))

class SectionManager {
public:
    static SectionManager *instance();
    Section *getSection(int x, int z);
    
    void beginLoad(int offsetX, int offsetZ);
    void endLoad();
    
    bool isDirty();
    
    //void freeSection(Section *section);
    void freeMem(void *section);
    void runFree();
private:
    SectionManager();
    void initialize();
    void buildLoop();
    static SectionManager *inst;
    
    int offsetX, offsetZ;
    int offsetXact, offsetZact;
    
    bool dirty;
    bool init;
    bool offsetSet;
    
    sf::Thread *t;
    sf::Mutex m;
    
    
    sf::Mutex ms;
    std::stack<SectionFree> stackSec;
    
    Section *sections[SECTION_CACHE_SIZE_X][SECTION_CACHE_SIZE_Z];
    Section *sectionsTmp[SECTION_CACHE_SIZE_X][SECTION_CACHE_SIZE_Z];
    Section *sectionsData[SECTION_CACHE_SIZE_X][SECTION_CACHE_SIZE_Z];
};

#endif /* defined(__Build_Age__SectionManager__) */
