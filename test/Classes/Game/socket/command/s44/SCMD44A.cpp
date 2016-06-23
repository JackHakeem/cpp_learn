#include "SCMD44A.h"
#include "socket/network/GameServerSocket.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "manager/LangManager.h"
#include "view/gong/GongMediator.h"

bool	SCMD44A::Read()
{
	a_heroname = readString();
	
	b_accountid = readUint();
	c_score = readUint();
	d_beMBCount = readUint();

	short b_namesNum = readShort();
	for (int i = 0; i < b_namesNum; i++)
	{
		SCMD44ANode node;
		node.name = readString();
		node.mbtype = readByte();
		e_names.push_back(node);
	}

	return true;
}

int32 	SCMD44A::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD44AHandler::Execute(this) ;
}


uint32 SCMD44AHandler::Execute(SCMD44A* pPacket)
{
	if (!pPacket) return 1;

	GongMediator* p = (GongMediator*)g_pFacade->retrieveMediator(AppFacade_GONG);
	if (p)
		p->updateMBView(pPacket);
	
	return 0;
}