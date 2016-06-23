//
//  CCMD138.cpp
//  HLQS_IPAD
//
//  Created by hui long on 12-3-1.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "CCMD138.h"

bool CCMD138::Write()
{
//    writeInt(1/*a_stopType*/);
	writeByte(_type);
    return true;
}