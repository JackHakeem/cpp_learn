#include "SCMD1A5.h"
#include "view/mail/MailMediator.h"
#include "control/AppFacade.h"

bool	SCMD1A5::Read()
{
	a_result = readUshort();

	return true;
}

int32 	SCMD1A5::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD1A5Handler::Execute(this) ;
}


uint32 SCMD1A5Handler::Execute(SCMD1A5* pPacket)
{
	if (!pPacket) return 1;

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->sockMailDelete(pPacket);
	}
	return 0;
}