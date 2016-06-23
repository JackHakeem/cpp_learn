/*
 * CCMD10F.cpp
 *
 *  Created on: 2012-10-26
 *      Author: doyang
 */
#include "CCMD10F.h"

bool CCMD10F::Write()
{
    writeByte(a_type);
	writeUint(b_accId);
    return true;
}


