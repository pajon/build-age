#include "World.h"
#include <cstdio>
#include <ft2build.h>


World *World::inst = 0;

World *World::instance() {
    if(!inst)
        inst = new World();
    return inst;
}

World::World() {
    
    initWorld = false;
    
    cam = Camera::instance();
    
    // CONTROL
    c = Control::instance();
    m = SectionManager::instance();
    
    // SET WORLD AS DIRTY
    dirtyWorld = true;
    
    loadBlocksTexture();
}

void World::prepareWorld() {
    Section *s;
    
    if(initWorld && ((s=getCurrentSection()) != NULL && s->Compare(sections[VIEW_SIZE_X >> 1][VIEW_SIZE_Z >> 1])))
        return;
    
    LOG("WORLD PREPARE");
    
    int offsetXNew = -(VIEW_SIZE_X >> 1) + c->getSection().x;
    int offsetZNew = -(VIEW_SIZE_Z >> 1) + c->getSection().z;
    
    m->beginLoad(offsetXNew, offsetZNew);
    
    for(int x=0;x<VIEW_SIZE_X;x++)
        for(int z=0;z<VIEW_SIZE_Z;z++)
            sections[x][z] = m->getSection(offsetXNew + x, offsetZNew + z);

    m->endLoad();
    
    offsetX = offsetXNew;
    offsetZ = offsetZNew;
    
    dirtyWorld = false;
    initWorld = true;
    
    LOG("WORLD PREPARE END");
}

void World::drawWorld() {    
    RenderManager::instance()->clean();
    prepareWorld();
    
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);    
    
    // NASTAVENIE TEXTURY
    bindBlocksTexture();

    // VYKRESLENIE SEKCII
    for(int x=0;x<VIEW_SIZE_X;x++)
            for(int z=0;z<VIEW_SIZE_Z;z++) {
                if(1 && !cam->inFrustrum(
                        sections[x][z]->getX()*SECTION_SIZE_X,
                        -128,
                        sections[x][z]->getZ()*SECTION_SIZE_Z
                                    )) {
                 continue;
                }
                
                
                sections[x][z]->render();
            }

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);
}


void World::loadBlocksData() {
    blockType[0].setData("GRASS1",0,0);
    blockType[0].setData("GRASS2",1,0);
    blockType[0].setData("GRASS3",0,1);
    blockType[0].setData("GRASS4",1,1);
}


void World::loadBlocksTexture() {
    FILE *f;
    unsigned char texdata[TEXTURE_WIDTH*TEXTURE_HEIGHT*TEXTURE_FORMAT];
    
    f = fopen(BLOCKTEXFILE, "r");
    if(f == NULL) {
        printf("ERROR: TEXFILE OPEN ERROR\n");
        exit(1);
    }
    
    fread(texdata, TEXTURE_WIDTH*TEXTURE_HEIGHT*TEXTURE_FORMAT, 1, f);
    fclose(f);
    
    
    

    
    
    
    glGenTextures(1, &gBlockTexture);// Generuje texturu
    glBindTexture(GL_TEXTURE_2D, gBlockTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, p->width,p->rows, 0,  GL_RGB,  GL_UNSIGNED_BYTE,p->buffer);
    
    
    glTexImage2D(GL_TEXTURE_2D, 0,
                 (TEXTURE_FORMAT == 3 ? GL_RGB : GL_RGBA), // INTERNY FORMAT
                 TEXTURE_WIDTH,
                 TEXTURE_HEIGHT,
                 0, // BORDER
                 (TEXTURE_FORMAT == 3 ? GL_RGB : GL_RGBA), // FORMAT TEXTURY
                 GL_UNSIGNED_BYTE,
                 texdata
                 );
     
}

void World::bindBlocksTexture() {    
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gBlockTexture);
}


Block *World::getBlock(float x, float y, float z) {
    Vector3F p,b;
    
    p.x = x;
    p.y = y;
    p.z = z;
    
    p = c->getPositionBlock(p);
    Section *s = getSection(p);

    b.x = (x - c->getSection(p).x * SECTION_SIZE_X);
    b.y = y;
    b.z = (z - c->getSection(p).z * SECTION_SIZE_Z);
    
    b = c->getPositionBlock(b);
    return s->getBlock(b.x,b.y,b.z);
}

Section *World::getCurrentSection() {
    return getSection(c->getPosition());
}

Section *World::getSection(Vector3F p) {
    /*
    // OCHRANA PRED PRETECENIM
    if(c->getSection(p).x-(offsetX) < 0 || c->getSection(p).x-(offsetX) >= VIEW_SIZE_X ||
       c->getSection(p).z-(offsetZ) < 0 || c->getSection(p).z-(offsetZ) >= VIEW_SIZE_Z
       ) {
        printf("XP:%f %f %f\n", c->getPosition().x, c->getPosition().y, c->getPosition().z);
        printf("XS:%f %f %f\n", c->getSection(p).x, c->getSection(p).y, c->getSection(p).z);
        printf("X+:%f %f %f\n",c->getSection(p).x-(offsetX),c->getSection(p).y-(offsetY),c->getSection(p).z-(offsetZ));
        exit(1);
    }  
     */

    return sections[(int)c->getSection(p).x-(offsetX)][(int)c->getSection(p).z-(offsetZ)];
}

bool World::checkCollision(Vector3F p) {
    Vector3F pd = c->getPositionBlock(p);
    if(World::instance()->getSection(pd)->getBlock(pd.x,pd.y,pd.z)->isAir() == false)
        return true;
    
    return false;
}

bool World::checkCollision(Vector3F p, int dx, int dy, int dz) {    
    Vector3F pd = c->getPositionBlock(p);
    
    pd.x += dx;
    pd.y += dy;
    pd.z += dz;
    
    if(World::instance()->getSection(pd)->getBlock(pd.x,pd.y,pd.z)->isAir() == false)
        return true;
    
    return false;
}

Player *World::getPlayer() {
    return &player;
}
