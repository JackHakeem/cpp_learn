#include "SCMD191.h"
#include "view/chat/ChatMediator.h"
#include "control/AppFacade.h"

bool SCMD191::Read()
{
	a_id = readInt();;
	b_name = readString();
	c_content = readString();
	d_data = readString();
	d_line = readByte();
	e_accountType = readByte();

	return true;
}


int32 	SCMD191::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD191Handler::Execute(this) ;
}


uint32 SCMD191Handler::Execute(SCMD191* pPacket)
{
	if (!pPacket) return 1;

	ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
	if (pChatMediator)
	{
		pChatMediator->onWorldChat(pPacket);
	}

	return 0;
}