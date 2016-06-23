#include "Facade.h"
#include "SimpleCommand.h"
#include "Mediator.h"
#include "Proxy.h"

Facade* g_pFacade = 0;

Facade::Facade():controller(0),view(0),model(0)
{
	size = 0;
	init();
}

Facade::~Facade()
{
	if (size)
	{
		for (int i = 0; i < size; i++)
		{
			CC_SAFE_DELETE( controller[i] );
			CC_SAFE_DELETE( view[i] );
			CC_SAFE_DELETE( model[i] );
		}	
	}
	CC_SAFE_DELETE_ARRAY( controller );
	CC_SAFE_DELETE_ARRAY( view );
	CC_SAFE_DELETE_ARRAY( model );
}

void Facade::init()
{
	size = AppFacade_APPFACADEENUM_MAX;
	if (!size) return;
	
	controller = new INotifier*[size];
	for (int i = 0; i < size; i++)
		controller[i] = 0;
	view = new INotifier*[size];
	for (int i = 0; i < size; i++)
		view[i] = 0;
	model = new INotifier*[size];
	for (int i = 0; i < size; i++)
		model[i] = 0;
}

void Facade::registerCommand(int id, SimpleCommand* p)
{
	if (!p || controller[id]) 
	{//serious
		return;
	}

	controller[id] = p;
}

void Facade::registerProxy(int id, Proxy* p)
{
	if (!p || model[id]) 
	{//serious
		return;
	}

	model[id] = p;
}

void Facade::registerMediator(int id, Mediator* p)
{
	if (!p || view[id])
	{//serious
		return;
	}

	view[id] = p;
}

void Facade::sendNotification(int type, int appfacade, char* body, int command)
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
