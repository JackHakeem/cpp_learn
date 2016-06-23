#include "SmallMapMediator.h"
#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/SceneManager.h"
#include "components/SmallMapUI.h"
#include "manager/LayerManager.h"
#include "manager/ViewManager.h"
#include "../newhand/NewhandMediator.h"

SmallMapMediator::SmallMapMediator()
{
	_dispatcher = 0;
	_smallMapUI = 0;
	_sceneVo = 0;

}

SmallMapMediator::~SmallMapMediator()
{}

void SmallMapMediator::handleNotification(int M2Vcmd, char* data)
{
	switch(M2Vcmd)
	{
	case STARTUP_SMALLMAP_UI:
		{
			startupSmallmapUI();
		}
		break;
	default:
		break;
	}
}

void SmallMapMediator::startupSmallmapUI()
{
	PlayerInfoVo* playInfo = RoleManage::Instance()->roleInfo();
	if (!playInfo)
		return;
	int32 mapId = playInfo->playerBaseInfo._mapId;
	mapId = mapId<=0?1:mapId;
	_sceneVo = SceneManager::Instance()->getSceneDic(mapId);
	CCPoint rolePos = ccp(playInfo->playerBaseInfo.x, playInfo->playerBaseInfo.y);
	_smallMapUI = new SmallMapUI();
	_smallMapUI->initWithParam(_sceneVo->name, rolePos);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_smallMapUI->setPosition(ccp(winSize.width-255, 10));
	LayerManager::sceneUILayer->addChild(_smallMapUI, 0, SceneUILayer::SceneUILayerTAG_SmallMapMediator);
	startListener();
	ViewManager::getInstance()->smallMapUI = _smallMapUI;
	/*
	if(_mailProxy.getUnreadMailNum() > 0){
				_smallMapUI.receiveNewMail();
			}
			*/
	sendNotification(Facade_Mediator, AppFacade_NEWHAND_MEDIATOR, 0, NewhandMediator::INIT_BUTTONS);
}

void SmallMapMediator::startListener()
{}

