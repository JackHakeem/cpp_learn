#include "MailProxyCommand.h"
#include "model/mail/MailProxy.h"
#include "socket/command/s1a/SCMD1AB.h"
#include "socket/command/s1a/SCMD1A1.h"
#include "socket/command/s1a/SCMD1A3.h"

MailProxyCommand::MailProxyCommand()
{

}

void MailProxyCommand::execute(int32 command, char* data)
{
	MailProxy  * pMailProxy = (MailProxy *)g_pFacade->retrieveProxy(AppFacade_Mail_Proxy);
	switch(command)
	{
	case INIT_MAIL_COUNT:
		pMailProxy->initMailCount((SCMD1AB *)data);
		break;
	case UPDATE_MAIL_LIST:
		pMailProxy->updateMailList((SCMD1A1 *)data);
		break;
	case UPDATE_MAIL_CONTENT:
		pMailProxy->updateMailContent((SCMD1A3 *)data);
		break;
	}
}