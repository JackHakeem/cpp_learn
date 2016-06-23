#include "CCMD37D.h"

bool CCMD37D::Write(){

	writeByte(a_operationType);
	writeShort(b_mapId);
	writeInt(c_roomId);
	return true;
}