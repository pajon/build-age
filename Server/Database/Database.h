//
//  Database.h
//  Craft-Age-Server
//
//  Created by Patrik Štrba on 2.2.2013.
//  Copyright (c) 2013 Patrik Štrba. All rights reserved.
//

#ifndef __Craft_Age_Server__Database__
#define __Craft_Age_Server__Database__

#include <iostream>

//
//#include "mongo/client/dbclient.h"

class Database {
public:
    Database() {
        Connect();
    }
    
    void Connect();
private:
   // mongo::DBClientConnection c;
    
};

#endif /* defined(__Craft_Age_Server__Database__) */
