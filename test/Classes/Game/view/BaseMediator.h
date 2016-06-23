#ifndef HLCQ_BaseMediator_H_
#define HLCQ_BaseMediator_H_
#include "model/scene/SceneProxy.h"
#include "mvc/Mediator.h"
#include "control/AppFacade.h"
#include "model/task/TaskProxy.h"
#include "model/battle/FightProxy.h"
#include "events/GameDispatcher.h"
#include "model/scene/StoryProxy.h"
#include "socket/network/GameServerSocket.h"

using namespace cocos2d;

class BaseMediator: public Mediator
{
public:
	SceneProxy* _sceneProxy;
	TaskProxy *_taskProxy;
	GameServerSocket *_wSocket;
	FightProxy* _fightProxy;
	GameDispatcher *_dispatcher;
	StoryProxy * _storyProxy;
public:
	BaseMediator()
	{
		_sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
		_taskProxy = (TaskProxy *)g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
		_fightProxy = (FightProxy*)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
		_wSocket = GameServerSocket::getInstance();
		_dispatcher = GameDispatcher::getInstance();
		_storyProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
	}
};

#endif