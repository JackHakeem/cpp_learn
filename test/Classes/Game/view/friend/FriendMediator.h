#ifndef _FRIENDMEDIATOR_H_
#define _FRIENDMEDIATOR_H_

#include "mvc/Mediator.h"

class FriendView;
class FriendProxy;
class GameDispatcher;

class FriendMediator:public Mediator
{

public:
	enum
	{
		FRI_POP,
		UPDATE_LIST,
		MY_BLESS_INFO,
		OPEN_REQ_PANEL,
	};

public:
	FriendMediator();
	~FriendMediator();
public:
	void handleNotification(int M2Vcmd, char* data);
	void pop(FriendView* view);
	void updateList(char* obj);

public:
	FriendView* _view;
	FriendProxy* _proxy;
	GameDispatcher* _dispatcher;
		
	bool viewON;
};

#endif