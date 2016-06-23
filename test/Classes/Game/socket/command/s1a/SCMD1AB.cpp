#include "SCMD1AB.h"
#include "view/mail/MailMediator.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"

bool	SCMD1AB::Read()
{
	a_unreadNum = readUshort();
	b_totalNum = readUshort();
	c_playerMailNum = readUshort();
	d_systemMailNum = readUshort();

	return true;
}

int32 	SCMD1AB::Execute()
{
	if (!Read())
	{
		return 1;
	}
	return SCMD1ABHandler::Execute(this) ;
}


uint32 SCMD1ABHandler::Execute(SCMD1AB* pPacket)
{
	if (!pPacket) return 1;

	MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
	if (pMailMediator)
	{
		pMailMediator->sockMailCount(pPacket);
	}

	g_pGlobalManage->loadOneProgress( 2 );
	return 0;
}