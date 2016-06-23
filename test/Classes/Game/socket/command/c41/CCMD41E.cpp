#include "CCMD41E.h"

bool CCMD41E::Write(){

	writeByte(a_req);
	writeInt(b_delay);
	return true;
}