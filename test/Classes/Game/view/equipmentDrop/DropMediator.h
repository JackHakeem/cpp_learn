#ifndef _DROPMEDIATOR_H_
#define _DROPMEDIATOR_H_

#include "mvc/Mediator.h"


class GameDispatcher;
class DropCheckView;
class DropMediator:public Mediator
{
public:
	enum 
	{

	};
public:
	DropMediator();
public:

	void openDropCheckView();
public:
	DropCheckView* _dropCheckView;
	GameDispatcher* _dispatcher;
};

#endif