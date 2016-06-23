#include "SCMD1AE.h"
#include "control/AppFacade.h"
#include "view/mail/MailMediator.h"

bool	SCMD1AE::Read()
{
	a_mailId = readUint();
	b_result = readUbyte();

	return true;
}

int32 	SCMD1AE::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD1AEHandler::Execute(this) ;
}


uint32 SCMD1AEHandler::Execute(SCMD1AE* pPacket)
{
	if (!pPacket) return 1;

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->sockAttachResult(pPacket);
	}

	return 0;
}