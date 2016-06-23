#include "CCMD30D.h"

bool CCMD30D::Write(){
    
	writeInt(a_merId);
	writeByte(b_skillRank);
	writeShort(c_skillId);

	return true;
}

