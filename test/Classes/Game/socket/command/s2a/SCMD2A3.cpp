#include "SCMD2A3.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"

bool SCMD2A3::Read()
{
	a_gridNum = readUbyte();
	uint16 num1 = readUshort();
	for (int i = 0; i < num1 ; i++)
	{
		SCMD2A3Node1 node1;
		node1.a_mercId = readInt();
		node1.b_typeId = readUshort();
		
		uint16 num2 = readUshort();
		for (int j = 0; j < num2 ; j++)
		{
			SCMD2A3Node2 node2;
			node2.a_statsType = readUbyte();
			node2.b_statsLv = readUbyte();
			node1.c_statArr.push_back(node2);
		}
		b_MercArr.push_back(node1);
	}

	return true;
}

int32 SCMD2A3::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD2A3Handler::Execute(this);
}

uint32 SCMD2A3Handler::Execute( SCMD2A3* pPacket )
{
	if (!pPacket)
	{
		return 1;
	}
}
