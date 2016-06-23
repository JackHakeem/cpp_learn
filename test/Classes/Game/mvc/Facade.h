#ifndef _FACADE_H_
#define _FACADE_H_

#include "IFacade.h"
class SimpleCommand;
class Proxy;
class Mediator;

enum FACADEENUM
{
	Facade_Command = 0,
	Facade_Proxy,
	Facade_Mediator,
};


class Facade:public IFacade
{
public:


	Facade();
	~Facade();

	void init();

	virtual void registerCommand(int id, SimpleCommand* p);
	virtual void registerProxy(int id, Proxy* p);
	virtual void registerMediator(int id, Mediator* p);
	virtual void sendNotification(int type, int appfacade, char* body, int command);
	
	INotifier* retrieveMediator(int id)
	{
		if (id >= size) 
			return 0;
		return view[id];
	}

	INotifier* retrieveProxy(int id)
	{
		if (id >= size) 
			return 0;
		return model[id];
	}

	INotifier* retrieveController(int id)
	{
		if (id >= size) 
			return 0;
		return controller[id];
	}

public:
	INotifier** controller;
	INotifier** view;
	INotifier** model;
	int size;
};

extern Facade* g_pFacade;

#endif 