#include "SCMD2A5.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2A5::Read()
{
	a_mercId = readInt();
	b_mercModId = readUshort();
	uint16 num = readUshort();
	for (int i = 0; i < num ; i++)
	{
		SCMD2A5Node node;
		node.a_statsType = readUbyte();
		node.b_statsLv = readUbyte();
		c_statsArr.push_back(node);
	}

	return true;
}

int32 SCMD2A5::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD2A5Handler::Execute(this);
}

uint32 SCMD2A5Handler::Execute( SCMD2A5* pPacket )
{
	if (!pPacket)
	{
		return 1;
	}
}
