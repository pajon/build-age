//
//  Font.h
//  Craft-Age
//
//  Created by Patrik Štrba on 10.3.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age__Font__
#define __Craft_Age__Font__

#include <ft2build.h>
#include <iostream>
#include FT_FREETYPE_H


#include <SFML/Graphics/Image.hpp>

namespace GUI {

class Font {
    FT_Library lib;
    FT_Face face;
public:
    Font() {
        if(FT_Init_FreeType(&lib) != 0) {
            printf("ERROR: loading font\n");
            exit(-1);
        }
        
        loadFace();
        setSize();

        //for(int i=35;i<50;i++) {
        {
            int i = 64;
            sf::Image img;
            buildChar(i);
            
            char buffer[1024];
            
            unsigned char *buff;
            

            sprintf(buffer, "/Users/patrik/Dropbox/xcode/Build-Age/Build-Age/Data/%d.bmp", i);
            
            FT_Bitmap *b;
            
            b = &face->glyph->bitmap;
            
            buff = (unsigned char *) malloc(b->width * b->rows  * 4 * sizeof(unsigned char));
            
#define index(x,y) ((y) * b->rows + (x))
            
            for(int j=0; j < b->width; j++) {
                for(int k=0; k < b->rows; k++) {
                    buff[index(j,k) + 0] = b->buffer[index(j,k)+0];
                    //buff[index(j,k) + 1] = b->buffer[index(j,k)+0];
                    //buff[index(j,k) + 2] = b->buffer[index(j,k)+0];
                    //buff[index(j,k) + 3] = 1;
                }
            }
            
            
            img.create(b->width, b->rows, buff);
            //img.loadFromMemory(buff, b->width * b->rows * 4);
            
            img.saveToFile(buffer);
            
            //free(buff);
        }
        

    }
    
    void loadFace() {
        if(FT_New_Face(lib, "/Users/patrik/Dropbox/xcode/Build-Age/Build-Age/Data/Arial.ttf", 0, &face) != 0 ){
            printf("ERR0R: loading face\n");
            exit(-1);
        }
        
        printf("%d\n", face->num_charmaps);
        
    }
    
    void setSize() {
        FT_Set_Char_Size(face, 64 * 50, 64 * 50, 96, 96);
    }
    
    void buildChar(FT_ULong c) {
        if(FT_Load_Char(face, c, FT_LOAD_RENDER) != 0) {
            printf("ERROR: build char\n");
            exit(-1);
        }
    }
};
    
}

#endif /* defined(__Craft_Age__Font__) */
