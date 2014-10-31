//
//  Event.h
//  Build-Age
//
//  Created by Patrik Štrba on 2.1.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Build_Age__Event__
#define __Build_Age__Event__

#include <iostream>
#include "Client/Control/Control.h"
#include "Client/Control/Debug.h"
#include "Client/Player/Player.h"

class Events {
public:
    void startListening(Player *p);
private:
    Control *c;
    void loop();
};

#endif /* defined(__Build_Age__Event__) */
