//
//  GlobalFunctions.h
//  OOP_Project
//
//  Created by Aiman Khan on 03/11/2017.
//  Copyright © 2017 Aiman Khan. All rights reserved.
//

#ifndef GlobalFunctions_h
#define GlobalFunctions_h


#endif /* GlobalFunctions_h */
#pragma once

#include<time.h>
#include<stdlib.h>
//#include "LTexture.hpp"
//#include "Point.h"

struct GlobalFunctions
{
    static int GetSCREEN_WIDTH()
    {
		int SCREEN_WIDTH = 1270; //1024 //640 //1270
        return SCREEN_WIDTH;
    }

    static int GetSCREEN_HEIGHT()
    {
		int SCREEN_HEIGHT = 700; //768 //480 //700
        return SCREEN_HEIGHT;
    }
};

