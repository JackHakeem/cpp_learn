#include "PassbyStory.h"
#include "model/battle/FightProxy.h"
#include "../../StoryProxy.h"
#include "control/AppFacade.h"
#include "manager/GlobalManage.h"
#include "manager/ViewManager.h"
#include "manager/PopManage.h"
#include "CCNode.h"
#include "model/player/RoleManage.h"
#include "util/TileUtil.h"
#include "manager/BattleManager.h"
#include "view/scene/SceneStoryMediator.h"
#include "../../StoryManager.h"

PassbyStory::PassbyStory(int storyId)
{
	_storyId = storyId;
	StoryProxy * pStoryProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
	StoryVo * pStory = StoryManager::Instance()->getStory(_storyId);
	pStoryProxy->_story = pStory;
	pStoryProxy->_storyId = storyId;
	pStoryProxy->setStoryId(storyId);

}

PassbyStory::~PassbyStory()
{
}

// 清除所有层
void PassbyStory::sweep()
{
	if(!g_pGlobalManage){return;}
	if(g_pGlobalManage->isInStory){return;}
	g_pGlobalManage->isInStory = true;

//	ViewManager::getInstance()->_scene->setIsTouchEnabled(false);

	// g_pPopManage->setAllWindowVisible(false); 待加入所有窗体隐藏功能

	// 取出新手引导层
// 	if( GlobalManage.getInstance().gameView.contains(LayerManager.newhandLayer))
// 	{
// 		GlobalManage.getInstance().gameView.removeChild(LayerManager.newhandLayer);
// 	}

// 	this.facade.sendNotification(SceneMediator.ROLE_STOP); // 角色停止移动
// 	this.facade.sendNotification(SmallMapMediator.LOCK_STATE, !RoleManage.getInstance().roleOpe());//锁小地图和世界按钮
// 	this.facade.sendNotification(SceneWorldMediator.REMOVE_WORLD_SCENE);//如果有世界地图，则移除


//	this.facade.sendNotification(SceneMediator.ROLE_STOP); // 角色停止移动

	StoryVo * pStory = StoryManager::Instance()->getStory(_storyId);
	CCPoint ePoint = CCPoint(pStory->x,pStory->y);
	CCPoint sPoint = CCPoint(RoleManage::Instance()->roleInfo()->playerBaseInfo.x, RoleManage::Instance()->roleInfo()->playerBaseInfo.y);
	CCPoint startPoint = TileUtil::Instance()->changeTileToPixs(sPoint);
	CCPoint endPoint = TileUtil::Instance()->changeTileToPixs(ePoint);

// 	FocusManage.getInstance().speed = 600;	
// 	FocusManage.getInstance().compFun = tweenComplete;
// 	FocusManage.getInstance().tween(endPoint, startPoint);
// 	StoryEffectManage.getInstance().show();

	tweenComplete();
}

void PassbyStory::tweenComplete()
{
// 	mg.addFrameScript(1,16);
// 	mg.play(endHandler);
	endHandler();

}

// into story
void PassbyStory::endHandler()
{
	StoryProxy * pStoryProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
	if (pStoryProxy)
	{
		pStoryProxy->sendNotification(Facade_Mediator,AppFacade_SCENESTORY_PROXY_CHANGE,(char *)_storyId,SceneStoryMediator::INTO_STORY);
	}
}

void PassbyStory::dispose()
{
	
}