#include "SCMD1A7.h"
#include "control/AppFacade.h"
#include "view/mail/MailMediator.h"

bool	SCMD1A7::Read()
{
	a_result = readUshort();

	return true;
}

int32 	SCMD1A7::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD1A7Handler::Execute(this) ;
}


uint32 SCMD1A7Handler::Execute(SCMD1A7* pPacket)
{
	if (!pPacket) return 1;

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->sockSendMailResult(pPacket);
	}

	return 0;
}