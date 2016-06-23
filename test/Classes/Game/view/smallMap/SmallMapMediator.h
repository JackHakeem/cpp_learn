#ifndef _SMALLMAPMEDIATOR_H_
#define _SMALLMAPMEDIATOR_H_

#include "mvc/Mediator.h"

class MainNavigate;
class GameDispatcher;
class SmallMapUI;
class SceneVo;

class SmallMapMediator:public Mediator
{
public:
	enum
	{
		STARTUP_SMALLMAP_UI = 0,
		LOCK_STATE,
	};

	SmallMapMediator();
	~SmallMapMediator();

public:
	virtual void handleNotification(int M2Vcmd, char* data);
	void startListener();
	void startupSmallmapUI();

public:
	GameDispatcher* _dispatcher;
	SmallMapUI* _smallMapUI;
	SceneVo* _sceneVo;
};

#endif


