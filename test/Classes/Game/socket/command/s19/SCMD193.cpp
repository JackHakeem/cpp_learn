#include "SCMD193.h"
#include "view/chat/ChatMediator.h"
#include "control/AppFacade.h"

bool SCMD193::Read()
{
	a_id = readInt();;
	b_name = readString();
	c_content = readString();
	d_data = readString();
	d_line = readByte();
	e_accountType = readByte();

	return true;
}


int32 	SCMD193::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD193Handler::Execute(this) ;
}


uint32 SCMD193Handler::Execute(SCMD193* pPacket)
{
	if (!pPacket) return 1;

	ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
	if (pChatMediator)
	{
		pChatMediator->onGuildChat(pPacket);
	}

	return 0;
}