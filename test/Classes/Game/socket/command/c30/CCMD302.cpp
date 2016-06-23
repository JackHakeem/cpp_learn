#include "CCMD302.h"

bool CCMD302::Write(){
    
	writeShort(a_prototypeId);

	return true;
}

