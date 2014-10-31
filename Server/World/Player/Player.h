//
//  Player.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 2.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age_Server__Player__
#define __Craft_Age_Server__Player__

#include <iostream>

class Player {
public:
    Player() {
        isLogin = false;
    }
    
    void login();
    void logout();
private:
    bool isLogin;
};

#endif /* defined(__Craft_Age_Server__Player__) */
