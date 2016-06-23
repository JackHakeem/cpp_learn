#include "CCMD15D.h"

bool CCMD15D::Write()
{
	writeByte(_type);
	writeByte(_prop);
	return true;
}
