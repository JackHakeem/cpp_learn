#include "SCMD1A9.h"
#include "view/mail/MailMediator.h"
#include "control/AppFacade.h"

bool	SCMD1A9::Read()
{
	a_mailId = readUint();
	b_senderName = readString();
	c_mailTitle = readString();
	d_mailType = readUbyte();
	e_mailStatus = readUbyte();
	f_sendTime = readUint();
	g_attachStatus = readUbyte();

	return true;
}

int32 	SCMD1A9::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD1A9Handler::Execute(this) ;
}


uint32 SCMD1A9Handler::Execute(SCMD1A9* pPacket)
{
	if (!pPacket) return 1;

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->sockMailReceive(pPacket);
	}

	return 0;
}