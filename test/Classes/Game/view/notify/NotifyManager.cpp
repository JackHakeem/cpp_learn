#include "NotifyManager.h"
#include "NotifyType.h"
#include "NotifyLayer.h"
#include "manager/LayerManager.h"
#include "NotifyGrid.h"
#include "utils/ScaleUtil.h"
#include "model/battle/FightProxy.h"
#include "manager/GlobalManage.h"
#include "control/AppFacade.h"
#include "../fight/callback/ShowNotificationAction.h"
#include "../scene/components/story/callback/StoryFollowNotifyAction.h"
#include "model/scene/StoryProxy.h"

NotifyManager::NotifyManager() : _notifyLayer(0)
{
	_notifyLayer = 0;
	init();
}

NotifyManager::~NotifyManager()
{
	std::map<int , NotifyGrid *>::iterator iter = _noticeList.begin();
	for (iter ; iter != _noticeList.end() ; iter++)
	{
		if (iter->second)
		{
			((NotifyGrid *)iter->second)->release();
		}
	}
	_noticeList.clear();
}

bool NotifyManager::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	addNoticeLayer();

	return true;
}

void NotifyManager::addNoticeLayer()
{
	if (!_notifyLayer)
	{
		_notifyLayer = new NotifyLayer();
		_notifyLayer->init();
		if (LayerManager::tipsLayer)
		{
			LayerManager::tipsLayer->addChild(_notifyLayer , 6001, 6001);
		}
		
		_notifyLayer->release();
	}
}

void NotifyManager::addNotification(int type)
{
	if ( (type != NotifyType::NType_Mail) && (type != NotifyType::NType_Trader) )
	{
		return;
	}

	if ((type < 0) || (type > MAX_COUNT-1)
		||_noticeList.find(type) != _noticeList.end())
	{
		return;
	}
	// fight callback
	if (g_pGlobalManage->getisInFight())
	{
		FightProxy * pFightProxy = (FightProxy *)g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
		if (pFightProxy)
		{
			pFightProxy->_bData._callbacks.push_back(new ShowNotificationAction(type));
		}
		return;
	}
	// story callback
	if (g_pGlobalManage->isInStory)
	{
		StoryProxy * pStoryProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
		if (pStoryProxy)
		{
			pStoryProxy->storyCallbackActionList.push_back((IAction *)new StoryFollowNotifyAction(type));
		}
		return;
	}

	NotifyGrid * pItem = new NotifyGrid(type);
	_noticeList.insert(make_pair(type , pItem));

	CCSprite * pFlyItem = new CCSprite();
	pFlyItem->initWithSpriteFrameName("popuibg/bg1.png");
	playFlyAction(pFlyItem);
}

int NotifyManager::getListCount()
{
	return _noticeList.size();
}

std::map<int , NotifyGrid *> * NotifyManager::getList()
{
	return &_noticeList;
}

void NotifyManager::playFlyAction(CCSprite * pItem)
{
	if (!LayerManager::tipsLayer)
	{
		return;
		LayerManager::tipsLayer->addChild(_notifyLayer , 6001, 6001);
	}
	_notifyLayer = (NotifyLayer *)LayerManager::tipsLayer->getChildByTag(6001);
	if (!_notifyLayer || !pItem)
	{
		return;
	}

	if (_notifyLayer->getChildByTag(3001))
	{
		_notifyLayer->removeChildByTag(3001 , true);
	}
	
	_notifyLayer->addChild(pItem, 10, 3001);
	pItem->release();
	CCPoint pos = getStartPos(_notifyLayer->_winSize);
	pItem->setPosition(pos);
	CCPoint posto = ccp(_notifyLayer->_winSize.width/2 ,  POSX(200));
	CCFiniteTimeAction * pFadeIn = CCFadeIn::actionWithDuration(0.5f);
	CCFiniteTimeAction * pMoveTo = CCMoveTo::actionWithDuration(1.0f , posto);
	CCFiniteTimeAction * pFadeOut = CCFadeOut::actionWithDuration(0.5f);
	CCCallFuncND * pCallBack = CCCallFuncND::actionWithTarget(this , callfuncND_selector(NotifyManager::refresh) , (void *)0);
	pItem->setOpacity(0);
	pItem->runAction(CCSequence::actions(pFadeIn , pMoveTo , pFadeOut , pCallBack , 0));
}

void NotifyManager::refresh(CCNode * pNode , void * data)
{
	_notifyLayer->removeChildByTag(3001 , true);	

	if (_notifyLayer)
	{
		_notifyLayer->resetNotices();
	}
}

CCPoint & NotifyManager::getStartPos(CCSize &size)
{
	srand(Timer::millisecondNow());
	int posX = rand()%((int)(size.width+1));
	srand(Timer::millisecondNow());
	int posY = rand()%((int)(size.height+1));

    CCPoint point = ccp(posX , posY);
	return point;
}

void NotifyManager::removeLayerByType( int type )
{
	if (_notifyLayer)
	{
		_notifyLayer->removeLayer(type);
	}	
}
