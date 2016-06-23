//
//  CCMD134.cpp
//  HLQS_IPAD
//
//  Created by hui long on 12-3-1.
//  Copyright (c) 2012 4399. All rights reserved.
//

#include "CCMD134.h"

bool CCMD134::Write()
{
	writeUint(a_battleId1);
	writeUint(b_battleId2);
    return true;
}