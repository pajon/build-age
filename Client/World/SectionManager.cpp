//
//  SectionManager.cpp
//  Build-Age
//
//  Created by Patrik Štrba on 4.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#include "SectionManager.h"
#include <cstdio>

SectionManager *SectionManager::inst = 0;

SectionManager *SectionManager::instance() {
    if(!inst)
        inst = new SectionManager();
    return inst;
}
SectionManager::SectionManager() {
    initialize();
}

void SectionManager::initialize() {
    offsetX = offsetZ = 0;
    offsetXact = offsetZact = 0;
    
    dirty = false;
    init = false;
    offsetSet = false;
    
    t = new Thread(&SectionManager::buildLoop, this);
    t->launch();
}

Section *SectionManager::getSection(int x, int z) {
    return sections[x-offsetXact][z-offsetZact];
}

bool SectionManager::isDirty() {
    return dirty;
}

void SectionManager::beginLoad(int offsetX, int offsetZ) {
    
    m.lock();
    this->offsetX = offsetX - SECTION_CACHE_X;
    this->offsetZ = offsetZ - SECTION_CACHE_Z;
    
    if(offsetSet == false) {
        offsetSet = true;
        m.unlock();
        
        while(1) {
            
            m.lock();
            if(init) {
                m.unlock();
                break;
            }
            m.unlock();
            
            sf::sleep(sf::milliseconds(1));
        }
        
        m.lock();
    }
}
void SectionManager::endLoad() {
    m.unlock();
}
    
void SectionManager::buildLoop() {
    
    sf::Context context;
    
    WSFML *w = WSFML::instance();
    w->getWindow()->setActive(false);
    
    int n = 0, c = 0;
    
    int _offsetX, _offsetZ, _offsetXact, _offsetZact;
    _offsetX = _offsetXact = _offsetZ = _offsetZact = 0;
    
    while(w->getWindow()->isOpen()) {
        if(offsetSet == false) {
            sf::sleep(sf::milliseconds(1));
            continue;
        }
        
        if(c++ == 500) {
            c = 0;
            
            // FREE SECTION CACHE
            runFree();
        }
        
        m.lock();
            // INIT
            if(init == false) {
                offsetXact = offsetX;
                offsetZact = offsetZ;
                
                for(int x=0;x<SECTION_CACHE_SIZE_X;x++)
                    for(int z=0;z<SECTION_CACHE_SIZE_Z;z++)
                        sections[x][z] = new Section(offsetXact+x,0,offsetZact+z);
                /*
                for(int x=0;x<SECTION_CACHE_SIZE_X;x++) {
                    for(int z=0;z<SECTION_CACHE_SIZE_Z;z++)
                        printf("(%d %d) %ld", x,z, (long)sections[x][z]);
                    printf("\n");
                }*/
                
                init = true;
                
                _offsetX = offsetX;
                _offsetZ = offsetZ;

                m.unlock();
                continue;
            }
        
            // DONT CHANGE
            if(offsetX == _offsetX && offsetZ == _offsetZ) {
                m.unlock();
                sf::sleep(sf::milliseconds(1));
                continue;
            }
        
        //printf("REBUILD: %d %d %d %d\n", _offsetX,_offsetZ,offsetX,offsetZ);

            _offsetX = offsetX;
            _offsetXact = offsetXact;
            _offsetZ = offsetZ;
            _offsetZact = offsetZact;
        m.unlock();
        
        for(int x=0;x<SECTION_CACHE_SIZE_X;x++)
            for(int z=0;z<SECTION_CACHE_SIZE_Z;z++)
                sectionsTmp[x][z] = sections[x][z];
        
        for(int x=0;x<SECTION_CACHE_SIZE_X;x++)
            for(int z=0;z<SECTION_CACHE_SIZE_Z;z++) {
                if(x-(_offsetXact-_offsetX) < (SECTION_CACHE_SIZE_X) && x-(_offsetXact-_offsetX) >= 0 && z-(_offsetZact-_offsetZ) < (SECTION_CACHE_SIZE_Z) && z-(_offsetZact-_offsetZ) >= 0) {
                    sectionsData[x][z] = sectionsTmp[x-(_offsetXact-_offsetX)][z-(_offsetZact-_offsetZ)];
                    
                    sectionsTmp[x-(_offsetXact-_offsetX)][z-(_offsetZact-_offsetZ)] = NULL;
                } else {
                    sectionsData[x][z] = new Section(_offsetX+x,0,_offsetZ+z);
                    n++;
                }
            }
    
        /*
        for(int x=0;x<SECTION_CACHE_SIZE_X;x++) {
            for(int z=0;z<SECTION_CACHE_SIZE_Z;z++)
                printf("(%d %d) %ld ", x, z, (long)sectionsTmp[x-(_offsetXact-_offsetX)][z-(_offsetZact-_offsetZ)]);
            printf("\n");
        }
        */
        
        m.lock();
        for(int x=0;x<SECTION_CACHE_SIZE_X;x++)
            for(int z=0;z<SECTION_CACHE_SIZE_Z;z++)
                if(sectionsTmp[x][z] != NULL)
                    delete sectionsTmp[x][z];

        /*
        if(_offsetXact != _offsetX) {
            for(int z=0;z<SECTION_CACHE_SIZE_Z;z++) {
                printf("%d %d\n",(_offsetXact > _offsetX ? 0 : SECTION_CACHE_SIZE_X-1),z);
                printf("P*: %d\n", sectionsTmp[(_offsetXact < _offsetX ? 0 : SECTION_CACHE_SIZE_X-1)][z]);
                delete sectionsTmp[(_offsetXact < _offsetX ? 0 : SECTION_CACHE_SIZE_X-1)][z];
                n--;
            }
            
        } else if(_offsetZact != _offsetZ) {
            for(int x=0;x<SECTION_CACHE_SIZE_X;x++) {
                printf("%d %d\n",x,(_offsetZact > _offsetZ ? 0 : SECTION_CACHE_SIZE_Z-1));
                printf("P*: %d\n", sectionsTmp[x][(_offsetZact < _offsetZ ? 0 : SECTION_CACHE_SIZE_Z-1)]);
                delete sectionsTmp[x][(_offsetZact < _offsetZ ? 0 : SECTION_CACHE_SIZE_Z-1)];
                n--;
            }
            
        } else if(_offsetXact != _offsetX && _offsetZact != _offsetZ) {
            for(int z=0;z<SECTION_CACHE_SIZE_Z;z++) {
                delete sectionsTmp[(_offsetXact > _offsetX ? 0 : SECTION_CACHE_SIZE_X-1)][z];
                n--;
            }
            for(int x=0;x<SECTION_CACHE_SIZE_X-1;x++) {
                delete sectionsTmp[x][(_offsetZact > _offsetZ ? 0 : SECTION_CACHE_SIZE_Z-1)];
                n--;
            }
        }
        */
            for(int x=0;x<SECTION_CACHE_SIZE_X;x++)
                for(int z=0;z<SECTION_CACHE_SIZE_Z;z++)
                    sections[x][z] = sectionsData[x][z];
            
            offsetXact = _offsetX;
            offsetZact = _offsetZ;
        m.unlock();
    }
    for(int x=0;x<SECTION_CACHE_SIZE_X;x++)
        for(int z=0;z<SECTION_CACHE_SIZE_Z;z++)
            delete sections[x][z];
}

void SectionManager::freeMem(void *section) {
    SectionFree tmp;
    tmp.s = section;
    
    ms.lock();
    stackSec.push(tmp);
    ms.unlock();
}

void SectionManager::runFree() {
    ms.lock();
    while(!stackSec.empty()) {
        SectionFree tmp = stackSec.top();
        
        free(tmp.s); //->freeCache();
        //printf("DEL: %d %d\n", tmp.s->getX(),tmp.s->getZ());
        stackSec.pop();
    }
    ms.unlock();
}