#include "SCMD46D.h"
#include "manager/LangManager.h"
#include "control/AppFacade.h"
#include "socket/network/GameServerSocket.h"
#include "view/zx/ZXMediator.h"
#include "view/zx/components/ZXView.h"

bool SCMD46D::Read()
{
	a_XHScore = readUint();
	return true;
}

int32 SCMD46D::Execute()
{
	if(!Read())
	{
		return 1;
	}
	return SCMD46DHandler::Execute(this);
}

uint32 SCMD46DHandler::Execute( SCMD46D* pPacket )
{

	ZXMediator * pZXMediator = (ZXMediator *)g_pFacade->retrieveMediator(AppFacade_ZX);
	if (pZXMediator)
	{
		pZXMediator->updateScore(pPacket->a_XHScore);
	}	

	return 0;
}
