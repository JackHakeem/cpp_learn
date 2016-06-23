#ifndef _IFACADE_H_
#define _IFACADE_H_
#include "INotifier.h"

class SimpleCommand;
class Proxy;
class Mediator;

class IFacade: public INotifier
{
public:
	virtual ~IFacade(){}

	virtual void registerCommand(int id, SimpleCommand* p){};
	virtual void registerProxy(int id, Proxy* p){};
	virtual void registerMediator(int id, Mediator* p){};
};

#endif