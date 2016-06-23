#include "SCMD24F.h"
#include "control/vip/VipCommand.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "view/mainUI/MainUIMediator.h"


bool SCMD24F::Read()
{
	int cnt = readUshort();
	for (int i=0; i<cnt; i++)
	{
		SCMD24FNode node;
		node.a_type = readShort();
		node.b_num = readByte();
		a_tokens.push_back(node);
	}

	return true;
}

int32 SCMD24F::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD24FHandler::Execute(this);
}

uint32 SCMD24FHandler::Execute( SCMD24F* pPacket )
{
	if (!pPacket) return 1;

	MainUIMediator * mUImediator = (MainUIMediator *)g_pFacade->retrieveMediator( AppFacade_MainUIMediator );
	mUImediator->updateTokenInfo(pPacket);

	return 0;
}
