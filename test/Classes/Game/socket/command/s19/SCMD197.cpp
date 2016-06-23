#include "SCMD197.h"
#include "view/chat/ChatMediator.h"
#include "control/AppFacade.h"

bool SCMD197::Read()
{
	a_fromId = readInt();
	b_fromName = readString();
	c_content = readString();
	d_data = readString();
	d_line = readByte();
	e_toId = readInt();
	f_toName = readString();
	g_accountType = readByte();

	return true;
}


int32 	SCMD197::Execute()
{
	if (!Read())
	{
		return 1;
	}

	return SCMD197Handler::Execute(this) ;
}


uint32 SCMD197Handler::Execute(SCMD197* pPacket)
{
	if (!pPacket) return 1;

	ChatMediator * pChatMediator = (ChatMediator *)g_pFacade->retrieveMediator(AppFacade_CHAT_CHANGE);
	if (pChatMediator)
	{
		pChatMediator->onPrivateChat(pPacket);
	}

	return 0;
}