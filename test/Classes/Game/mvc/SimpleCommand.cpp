#include "SimpleCommand.h"
#include "Facade.h"

void SimpleCommand::sendNotification(int type, int appfacade, char* body, int command)
{
	if (type == Facade_Command)
	{
		INotifier* p = g_pFacade->retrieveController(appfacade);
		if (p)
		{
			p->execute(command, body);
		}	
	}
	else if (type == Facade_Proxy)
	{
		/*
		INotifier* p = g_pFacade->retrieveProxy(appfacade);
		if (p)
		{
			p->execute(command, body);
		}	
		*/
	}
	else if (type == Facade_Mediator)
	{
		INotifier* p = g_pFacade->retrieveMediator(appfacade);
		if (p)
		{
			p->handleNotification(command, body);
		}		
	}

}
