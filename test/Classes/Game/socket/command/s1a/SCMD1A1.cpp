#include "SCMD1A1.h"
#include "view/mail/MailMediator.h"
#include "control/AppFacade.h"

bool	SCMD1A1::Read()
{
	a_mailType = readUbyte();
	b_mailCount = readUshort();
	c_startNum = readUshort();

	unsigned short SCMD1A1Node_len = readUshort();
	for (uint i = 0;i<(uint)SCMD1A1Node_len;i++)
	{
		SCMD1A1Node node;
		node.a_mailId = readUint();
		node.b_senderName = readString();
		node.c_mailTitle = readString();
		node.d_mailType = readUbyte();
		node.e_mailStatus = readUbyte();
		node.f_sendTime = readUint();
		node.g_attachStatus = readUbyte();
		d_mailList.push_back(node);
	}	
	return true;
}

int32 	SCMD1A1::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD1A1Handler::Execute(this) ;
}


uint32 SCMD1A1Handler::Execute(SCMD1A1* pPacket)
{
	if (!pPacket) return 1;

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->sockMailList(pPacket);
	}

	return 0;
}