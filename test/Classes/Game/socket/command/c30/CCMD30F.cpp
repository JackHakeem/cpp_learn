#include "CCMD30F.h"

bool CCMD30F::Write(){
    
	writeShort(a_formationId);
	writeUint(b_mercId);
	writeByte(c_oldPos);
	writeByte(d_newPos);

	return true;
}

