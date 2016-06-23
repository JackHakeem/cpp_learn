#include "SCMD199.h"
#include "view/chat/ChatMediator.h"
#include "control/AppFacade.h"

bool SCMD199::Read()
{
	a_err = readByte();

	return true;
}


int32 	SCMD199::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD199Handler::Execute(this) ;
}


uint32 SCMD199Handler::Execute(SCMD199* pPacket)
{
	if (!pPacket) return 1;

	ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
	if (pChatMediator)
	{
		pChatMediator->onChatError(pPacket);
	}

	return 0;
}