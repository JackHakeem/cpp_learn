#include "TaskFollowView.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "../TaskMediator.h"
#include "CCUIBaseClipLayer.h"
#include "utils/ScaleUtil.h"
#include "events/GameDispatcher.h"
#include "TaskStrConcat.h"
#include "TaskUtil.h"
#include "TaskAutoFindNpc.h"
#include "model/scene/NPCManager.h"
#include "model/scene/SceneManager.h"
#include "../TaskFollowMediator.h"
#include "utils/ValuesUtil.h"
#include "manager/GlobalManage.h"
#include "model/player/RoleManage.h"

#define CCSIZE_TASK_LAYER CCSizeMake(POSX(110), POSX(371))

#define CCPOINT_TASK_LAYER_VISIBLE ccp(0, 0)
#define CCPOINT_TASK_LAYER_INVISIBLE ccp(0, POSX(370))
#define CCPOINT_TASK_CAN_LABEL ccp(POSX(7), POSX(12))




TaskFollowView::TaskFollowView()
{
	_isTaskListViewShowing = false;
	_isDuringAction = false;
	_pTaskVo = 0;
	_nFlag = 0;
}

TaskFollowView::~TaskFollowView()
{

}

bool TaskFollowView::init()
{
	if(!CCLayer::init())
	{
		return false;
	}


	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/task/res_task.plist");

	this->setPosition(POS(ccp(790, 217), ScaleUtil::TOP_RIGHT));
	//this->setPosition(CCPointZero);

	//float floatScale = 1 / CCDirector::sharedDirector()->getContentScaleFactor();
	CCPoint CCPOINT_TASK_BTN = ccp(0, POSX(312));//ccp(POSX(815), POSX(548));
	CCPoint CCPOINT_TASK_CAN_BTN = ccp(POSX(9), POSX(18));

	CCPoint CCPOINT_TASK_CONTENT_LAYER = ccp(POSX(30), 0);//ccp(POSX(844), POSX(217));
	CCRect CCRECT_TASK_LIST = CCRectMake(POSX(16), POSX(68), POSX(70), POSX(270));
	CCRect CCRECT_TASK_LIST_CLIP = CCRectMake(CCPOINT_TASK_CONTENT_LAYER.x + CCRECT_TASK_LIST.origin.x ,\
		CCPOINT_TASK_CONTENT_LAYER.y + CCRECT_TASK_LIST.origin.y, \
		CCRECT_TASK_LIST.size.width, \
		CCRECT_TASK_LIST.size.height);

	//this->setIsTouchEnabled(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->setAnchorPoint(CCPointZero);

	// Open/close button
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_task_normal.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_task_pressed.png");
	CCMenuItemSprite *pTaskBtn = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this,
		menu_selector(TaskFollowView::controlButtonClick) );
	/*CCMenuItemImage *pTaskBtn = CCMenuItemImage::itemFromNormalImage(
	"assets/task/btn_task_normal.png",
	"assets/task/btn_task_pressed.png",
	this,
	menu_selector(TaskFollowView::controlButtonClick) );*/
	pTaskBtn->setPosition(CCPOINT_TASK_BTN);
	pTaskBtn->setAnchorPoint(CCPointZero);
	pTaskBtn->setScale(SCALE);
	CCMenu* pTaskMenu = CCMenu::menuWithItems(pTaskBtn, NULL);
	pTaskMenu->setPosition(CCPointZero);
	pTaskMenu->setAnchorPoint(CCPointZero);
	pTaskMenu->setTag(101);
	this->addChild(pTaskMenu , 1);
	
	//Task list
	CCUIBaseClipLayer *pTaskContentLayer = CCUIBaseClipLayer::initWithRect(CCRectMake(CCPOINT_TASK_CONTENT_LAYER.x,
		CCPOINT_TASK_CONTENT_LAYER.y,
		CCSIZE_TASK_LAYER.width,
		CCSIZE_TASK_LAYER.height));
	if(!pTaskContentLayer)
	{
		return false;
	}
	pTaskContentLayer->setClipLayerRect(CCRectMake(CCPOINT_TASK_CONTENT_LAYER.x + this->getPosition().x,
		CCPOINT_TASK_CONTENT_LAYER.y + this->getPosition().y,
		CCSIZE_TASK_LAYER.width,
		CCSIZE_TASK_LAYER.height));

	pTaskContentLayer->setAnchorPoint(CCPointZero);
	pTaskContentLayer->setIsRelativeAnchorPoint(true);

	/*_pTaskLayer = CCUIBaseClipLayer::initWithRect(CCRectMake(CCPOINT_TASK_LAYER_VISIBLE.x + pTaskContentLayer->getPositionInPixels().x,
		CCPOINT_TASK_LAYER_VISIBLE.y + pTaskContentLayer->getPositionInPixels().y,
		CCSIZE_TASK_LAYER.width,
		CCSIZE_TASK_LAYER.height));*/
	_pTaskLayer = new CCLayer();
	_pTaskLayer->init();
	_pTaskLayer->setContentSize(CCSIZE_TASK_LAYER);
	_pTaskLayer->setPosition(CCPOINT_TASK_LAYER_INVISIBLE);
	_pTaskLayer->setAnchorPoint(CCPointZero);
	pTaskContentLayer->addChild(_pTaskLayer);
	_pTaskLayer->release();

	// background
	//CCSprite *backgroundSprite = CCSprite::spriteWithFile("assets/task/TaskListBg.png");
	CCSprite *backgroundSprite = CCSprite::spriteWithSpriteFrameName("TaskListBg.png");
	backgroundSprite->setPosition(CCPointZero);
	backgroundSprite->setAnchorPoint(CCPointZero);
	backgroundSprite->setScale(SCALE);
	_pTaskLayer->addChild(backgroundSprite, 0);

	//　May meet mission button
	/*CCUIBaseClipLayer *pTaskCanBtntLayer = CCUIBaseClipLayer::initWithRect(CCRectMake(0,
		0,
		CCSIZE_TASK_LAYER.width,
		CCSIZE_TASK_LAYER.height));
	pTaskCanBtntLayer->setClipLayerRect(CCRectMake(_pTaskLayer->getPositionInPixels().x + pTaskCanBtntLayer->getPositionInPixels().x,
		_pTaskLayer->getPositionInPixels().y + pTaskCanBtntLayer->getPositionInPixels().y,
		CCSIZE_TASK_LAYER.width,
		CCSIZE_TASK_LAYER.height));
	pTaskCanBtntLayer->setAnchorPoint(CCPointZero);*/

	CCSprite *pTaskCanBtnNormalSprite = CCSprite::spriteWithSpriteFrameName("TaskCanBtnNormal.png");
	CCSprite *pTaskCanBtnPressedSprite = CCSprite::spriteWithSpriteFrameName("TaskCanBtnPressed.png");
	CCMenuItemSprite *pTaskCanBtn = CCMenuItemSprite::itemFromNormalSprite(
		pTaskCanBtnNormalSprite,
		pTaskCanBtnPressedSprite,
		this,
		menu_selector(TaskFollowView::canTaskButtonClick) );
	/*CCMenuItemImage *pTaskCanBtn = CCMenuItemImage::itemFromNormalImage(
	"assets/task/TaskCanBtnNormal.png",
	"assets/task/TaskCanBtnPressed.png",
	this,
	menu_selector(TaskFollowView::canTaskButtonClick) );*/
	pTaskCanBtn->setPosition(CCPOINT_TASK_CAN_BTN);
	pTaskCanBtn->setAnchorPoint(CCPointZero);
	pTaskCanBtn->setScale(SCALE);
	CCMenu* pTaskCanMenu = CCMenu::menuWithItems(pTaskCanBtn, NULL);
	pTaskCanMenu->setPosition(CCPointZero);

	// May meet the task of words
	CCLabelTTF *pCanTaskLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("task_look").c_str(),
		CCSizeMake(POSX(80), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	//pCanTaskLabel->setAnchorPoint(CCPointZero);
	//pCanTaskLabel->setPosition(ccpAdd(pTaskCanBtn->getPosition(), ccp(POSX(12), POSX(10))));
	pCanTaskLabel->setPosition(ccp(POSX(10), POSX(12)));
	pCanTaskLabel->setAnchorPoint(CCPointZero);
	pCanTaskLabel->setColor(ccc3(255, 255, 0));
	pTaskCanBtn->addChild(pCanTaskLabel, 1);

	//pTaskCanBtntLayer->addChild(pTaskCanMenu);
	_pTaskLayer->addChild(pTaskCanMenu);

	//　Has connected a task list
	_pListView = CCUIListView::listViewWithCCRect(CCRECT_TASK_LIST, false);
	//_pListView->setBackgroundWithFile("HelloWorld.png");
	_pListView->setAnchorPoint(CCPointZero);
	_pListView->setSpacingVertical(POSX(5));
	//_pListView->setAdapter(this);
	//_pListView->setClipLayerRect(CCRECT_TASK_LIST_CLIP);
	_pListView->setOnItemActionListener(this);
	_pListView->scrollToEnd(0);
	_pListView->setWorldSpaceLeftBottomPoint(ccp(
		this->getPosition().x + pTaskContentLayer->getPosition().x + 
		CCPOINT_TASK_LAYER_VISIBLE.x + CCRECT_TASK_LIST.origin.x,
		this->getPosition().y + pTaskContentLayer->getPosition().y + 
		CCPOINT_TASK_LAYER_VISIBLE.y + CCRECT_TASK_LIST.origin.y));
	_pTaskLayer->addChild(_pListView);
	_pListView->release();


	this->addChild(pTaskContentLayer);
	pTaskContentLayer->release();

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/task/res_task.plist");
	return true;
}
//
//void TaskFollowView::initData( EntrTaskVo *enTaskVo, MAP_INT_TASKVO recTaskList, MAP_INT_INT canTaskList )
//{
//	// Empty UI
//
//	// Copy
//	_enTaskVo = enTaskVo;
//	_recList = recTaskList;
//	_canList = canTaskList;
//}

/**
*Initialized data
*e
*/
void TaskFollowView::initData( std::vector<TaskVo *> &recTaskList )
{
	this->_recList = recTaskList;
	setReceiveTaskList();
}

void TaskFollowView::initCanTaskData( std::vector<TaskVo *> &canTaskList )
{
	this->_canTaskList = canTaskList;
	setCanTaskList();
}

void TaskFollowView::registerWithTouchDispatcher()
{
	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

void TaskFollowView::controlButtonClick( CCObject* pSender )
{
	if(_isDuringAction)
		return;

	if(!_pTaskLayer)
	{
		return;
	}
	_pTaskLayer->stopAllActions();

	if(_isTaskListViewShowing)
	{
		this->dismissTaskFollowLayer();
	}
	else
	{
		this->showTaskFollowLayer();
	}

	if (_pListView)
	{
		if(_pListView->getChilds()->count() > 0)
		{
			int cnt = 0;
			bool hasMain = false;
			
			if (RoleManage::Instance()->roleLev() >= 15)
			{
				if (!_recList.empty())
				{
					std::vector<TaskVo *>::iterator iter = _recList.begin();
					for (iter ; iter != _recList.end() ; iter++)
					{
						if ((*iter)->_type == 1)
						{
							hasMain = true;
							break;
						}
						cnt++;
					}
				}
				else if (!_canTaskList.empty())
				{
					std::vector<TaskVo *>::iterator iter = _canTaskList.begin();
					for (iter ; iter != _canTaskList.end() ; iter++)
					{
						if ((*iter)->_type == 1)
						{
							hasMain = true;
							break;
						}
						cnt++;
					}
				}

				// run action
				if (hasMain )
				{
					CCNode * pNode = (CCNode *)_pListView->getChilds()->getObjectAtIndex(cnt);
					if (pNode && pNode->getChildByTag(0))
					{
						runLightAction(pNode->getChildByTag(0) , getLightAction());
					}					
				}
				/*
				CCFiniteTimeAction * pFadeOut = CCFadeOut::actionWithDuration(0.5f );
				CCFiniteTimeAction * pFadeOutR = pFadeOut->reverse();
				CCAction * pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeOut , pFadeOutR));
				if (pNode && pNode->getChildByTag(0))
				{
					pNode->getChildByTag(0)->runAction(pAction);
				}
				*/
			}
		}
	}
}

int TaskFollowView::getCount()
{
	//return 1;
	if (_nFlag == 0)
	{
		return _recList.size();
	}
	else if (_nFlag == 1)
	{
		if (!_canTaskList.empty())
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
	
	//return 10;
}

LayerNode * TaskFollowView::getView( int position )
{
	LayerNode *layer = new LayerNode();
	TaskVo *pTask = 0;
	if (_recList.empty())
	{
		NPCManager::Instance()->setHasGetTask(false);
		TaskProxy * pTaskProxy = (TaskProxy *)g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
		if (!pTaskProxy)		{return layer;		}
		std::vector<TaskVo *> pCanList = pTaskProxy->getCanTasks();
		if (pCanList.empty())		{return layer;		}
		std::vector<TaskVo *>::iterator iter = pCanList.begin();
		
		for (iter ; iter != pCanList.end() ; iter++)
		{
			if ((*iter)->_type == 1)
			{
				pTask = *iter;
				//_recList.push_back(pTask);
				break;
			}
		}
		if (!pTask)
		{
			pTask = *(pCanList.begin());
			//_recList.push_back(pTask);
		}
	}
	else
	{
		_pTaskVo = 0;
		NPCManager::Instance()->setHasGetTask(true);
	}
	_pTaskVo = pTask;

	if (_recList.empty())
	{
		if (!_canTaskList.empty())
		{
			pTask = _canTaskList[0];
		}		
	}
	else
	{
		pTask = _recList[position];
	}
	
	//Doyang 20120711
	//layer->autorelease();
	layer->init();
	layer->setContentSize(CCSizeMake(POSX(80), POSX(80 + 16)));

	ValuesUtil *pValueUtil = ValuesUtil::Instance();

	CCSprite *pNpcIconSprite = NULL;
	/*CCSprite *view = CCSprite::spriteWithFile("assets/task/TaskNPCIconTest.png");
	view->setAnchorPoint(CCPointZero);
	view->getTexture()->setAliasTexParameters();
	layer->setvisibleSize(CCSizeMake(POSX(80), POSX(80)));
	layer->addChild(view);
	return layer;*/
	
	if(!pTask)

	{
		// test
		pNpcIconSprite = new CCSprite();
		pNpcIconSprite->setAnchorPoint(CCPointZero);
		//pNpcIconSprite->getTexture()->setAliasTexParameters();
		layer->setvisibleSize(CCSizeMake(POSX(80), POSX(80)));
		layer->addChild(pNpcIconSprite);
		return layer;
	}

	bool isFinish = TaskStrConcat::checkTaskFinish(pTask->_taskTip);

	NPCVo *pNpcVo = NULL;
	if(isFinish)
	{
		pNpcVo = NPCManager::Instance()->getNPC(pTask->getFinishTaskNpc());
	}
	else
	{
		pNpcVo = NPCManager::Instance()->getNPC(pTask->getRecTaskNpc());
	}

	if(!pNpcVo || !NPCManager::Instance()->getHasGetTask())
	{
		pNpcVo = NPCManager::Instance()->getNPC(pTask->getCanTaskNpc());
	}

	if(!pNpcVo)
	{
		// test
		pNpcIconSprite = new CCSprite();
		pNpcIconSprite->initWithFile("assets/icon/head/unknown.png");
		pNpcIconSprite->setScale(0.815);
		pNpcIconSprite->setAnchorPoint(CCPointZero);
		//pNpcIconSprite->getTexture()->setAliasTexParameters();
		layer->setvisibleSize(CCSizeMake(POSX(80), POSX(80)));
		layer->addChild(pNpcIconSprite);
		pNpcIconSprite->release();
		return layer;
	}


	pNpcIconSprite = new CCSprite();
	char pNpcIconPath[30];
	sprintf(pNpcIconPath, "assets/res/%d/head.png", pNpcVo->_resId);
	bool var = pNpcIconSprite->initWithFile(pNpcIconPath);
	//pNpcIconSprite = CCSprite::spriteWithSpriteFrameName(pNpcIconPath);
	
	if(!var)
	{
		pNpcIconSprite->initWithFile("assets/icon/head/unknown.png");
		pNpcIconSprite->setScale(0.815);
		//var = pNpcIconSprite->initWithFile("assets/res/60/head.png");
	}
	
	pNpcIconSprite->setAnchorPoint(CCPointZero);
	pNpcIconSprite->setPosition(ccp(0, POSX(16)));
	//pNpcIconSprite->getTexture()->setAliasTexParameters();
	pNpcIconSprite->setTag(0);

	layer->setvisibleSize(CCSizeMake(POSX(80), POSX(80 + 16)));
	
	layer->addChild(pNpcIconSprite);
	pNpcIconSprite->release();

	/*CCLabelTTF *pNpcNameShadowLabel = CCLabelTTF::labelWithString(pNpcVo->name.c_str(),
	CCSizeMake(POSX(80), POSX(14)),
	CCTextAlignmentCenter,
	"Arial",
	POSX(14));
	if(pNpcNameShadowLabel)
	{
	pNpcNameShadowLabel->setColor(ccc3(0, 0, 0));
	pNpcNameShadowLabel->setAnchorPoint(CCPointZero);
	pNpcNameShadowLabel->setPosition(ccp(POSX(1), POSX(-1)));
	layer->addChild(pNpcNameShadowLabel);
	}*/
	char pName[128];
	if(pTask->_type == 1)
	{
		sprintf(pName, "%s%s", pValueUtil->getString("task_lord2").c_str(), pNpcVo->name.c_str());
	}
	else
	{
		sprintf(pName, "%s%s", pValueUtil->getString("task_other2").c_str(), pNpcVo->name.c_str());
	}

	CCLabelTTF *pNpcNameLabel = CCLabelTTF::labelWithString(pName,
		CCSizeMake(POSX(100), POSX(14)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(14));
	if(pNpcNameLabel)
	{
		pNpcNameLabel->setColor(ccc3(55, 21, 0));
		pNpcNameLabel->setPosition(ccp(POSX(40), POSX(7)));
		layer->addChild(pNpcNameLabel);
	}

	return layer;
}

void TaskFollowView::canTaskButtonClick( CCObject* pSender )
{
	TaskMediator *pTaskMediator = (TaskMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
	if(pTaskMediator) 
	{
		//g_pGlobalManage->showAllUI(false);

		pTaskMediator->openTaskView();
	}
}

void TaskFollowView::doAfterTaskListViewActions()
{
	//_isTaskListViewShowing = !_isTaskListViewShowing;
	if(_isTaskListViewShowing)
	{
		_pListView->scrollToTop(0);
		//GameDispatcher::getInstance()->dispatchEvent(TaskFollowMediator::ON_TASK_FOLLOW_LIST_SHOW, NULL);
	}
	else
	{
		//GameDispatcher::getInstance()->dispatchEvent(TaskFollowMediator::ON_TASK_FOLLOW_LIST_DISMISS, NULL);
	}
	_isDuringAction = false;
}

void TaskFollowView::setReceiveTaskList()
{
	_nFlag = 0;
	//Doyang 20120711
	CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin();
		it != listChilds->end();
		++ it)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		if ( pChildLayer->getParent() )
		{
			pChildLayer->removeFromParentAndCleanup(true);
		}
		
		pChildLayer->release();
	}
	_pListView->setAdapter(this);
	_pListView->scrollToEnd(0);
}

void TaskFollowView::setCanTaskList()
{
	if (!_recList.empty())
	{
		return;
	}	

	_nFlag = 1;

	CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin();
		it != listChilds->end();
		++ it)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		if ( pChildLayer->getParent() )
		{
			pChildLayer->removeFromParentAndCleanup(true);
		}

		pChildLayer->release();
	}
	_pListView->setAdapter(this);
	_pListView->scrollToEnd(0);
}

void TaskFollowView::onItemClickListener( LayerNode *itemCell, int position )
{
	//TaskVo *pTask = _recList[position];

	TaskVo *pTask = 0;
	if (_recList.empty())
	{
		if (!_canTaskList.empty())
		{
			pTask = _canTaskList[position];
		}		
	}
	else
	{
		pTask = _recList[position];
	}

	if(!pTask)
		return;


	// 20120612
	// Doyang
	// fix find npc.
	TaskStrConcat::findNPC(pTask);

	/*GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TASK_AUTO_FIND_NPC,
		pTask);*/
	/*bool isFinish = TaskStrConcat::checkTaskFinish(pTask->_taskTip);

	NPCVo *pNpcVo = NPCManager::Instance()->getNPC(pTask->_pNpcs[1]);
	SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(pNpcVo->_mapId);
	
	if(!pNpcVo || !pSceneVo)
	{
		return;
	}

	FindVo findVo;
	findVo._type = 1;
	findVo._sceneId = pSceneVo->id;
	findVo._npcId = isFinish ? pTask->_pNpcs[1] : pTask->_pNpcs[0];

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);*/
}

void TaskFollowView::onItemTouchListener( LayerNode *itemCell, int position )
{
}

void TaskFollowView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{
}

void TaskFollowView::refresh()
{
	setReceiveTaskList();
}

void TaskFollowView::showTaskFollowLayer()
{
	if(_isTaskListViewShowing || _isDuringAction)
		return;

	_isTaskListViewShowing = true;
	GameDispatcher::getInstance()->dispatchEvent(TaskFollowMediator::ON_TASK_FOLLOW_LIST_SHOW, NULL);

	_isDuringAction = true;

	float actionTime = 0.1;
	int lev = RoleManage::Instance()->roleLev();
	CCPoint pos = CCPOINT_TASK_LAYER_VISIBLE;
	
	if (!_recList.empty())
	{
		int len = _recList.size();
		CCPoint pos = ccp(0 , POSX(90) * len);
	}
	else if (!_canTaskList.empty())
	{
		int len = _canTaskList.size();
		CCPoint pos = ccp(0 , POSX(90) * len);
	}

	CCFiniteTimeAction *moveAction = CCMoveTo::actionWithDuration(actionTime, pos);
	CCFiniteTimeAction *fadeInAction = CCFadeIn::actionWithDuration(actionTime);
	CCFiniteTimeAction *easeInAction = CCEaseIn::actionWithDuration(actionTime);
	CCFiniteTimeAction *spawnAction = CCSpawn::actions(moveAction, fadeInAction, easeInAction, NULL);
	CCCallFunc *callBack = CCCallFunc::actionWithTarget(this, callfunc_selector(TaskFollowView::doAfterTaskListViewActions));
	CCAction *action = CCSequence::actions(spawnAction, callBack, NULL);
	_pTaskLayer->runAction(action);

	/*
	CCMenuItemSprite * pMenuSprite = (CCMenuItemSprite * )this->getChildByTag(101);
	if (pMenuSprite)
	{
		CCNode * pNode = (CCNode *)pMenuSprite->getSelectedImage();
		if (pNode)
		{
			pNode->stopAllActions();
			pNode->cleanup();
		}
	}
	*/
}

void TaskFollowView::dismissTaskFollowLayer()
{
	// newhand By LH 20121016
// 	if (RoleManage::Instance()->roleLev() < 0)
// 	{
// 		return;
// 	}
	/*
	if (RoleManage::Instance()->roleLev() < 15)
	{
		if (_recList.empty())
		{
			CCMenuItemSprite * pMenuSprite = (CCMenuItemSprite * )this->getChildByTag(101);
			if (pMenuSprite)
			{
				CCNode * pNode = (CCNode *)pMenuSprite->getSelectedImage();
				if (pNode)
				{
					runLightAction(pNode , getLightAction());
				}
			}
		}
	}
	*/
	


	if(!_isTaskListViewShowing || _isDuringAction)
		return;
	_isTaskListViewShowing = false;
	GameDispatcher::getInstance()->dispatchEvent(TaskFollowMediator::ON_TASK_FOLLOW_LIST_SHOW, NULL);

	_isDuringAction = true;

	_pListView->scrollToEnd(0);
	float actionTime = 0.1;
	CCFiniteTimeAction *moveAction = CCMoveTo::actionWithDuration(actionTime, CCPOINT_TASK_LAYER_INVISIBLE);
	CCFiniteTimeAction *fadeOutAction = CCFadeOut::actionWithDuration(actionTime);
	CCFiniteTimeAction *easeOutAction = CCEaseOut::actionWithDuration(actionTime);
	CCFiniteTimeAction *spawnAction = CCSpawn::actions(moveAction, fadeOutAction, easeOutAction, NULL);
	CCCallFunc *callBack = CCCallFunc::actionWithTarget(this, callfunc_selector(TaskFollowView::doAfterTaskListViewActions));
	CCAction *action = CCSequence::actions(spawnAction, callBack, NULL);
	_pTaskLayer->runAction(action);

}

CCNode * TaskFollowView::getNewHandItem( int taskId )
{
	////如果隐藏了，返回展开按钮
	//if(!bg.visible){
	//	return btnTaskFollow;
	//}

	TaskVo *pTaskVo = NULL;
	std::vector<TaskVo *>::iterator it;
	for(it = _recList.begin(); it != _recList.end(); ++it)
	{
		TaskVo *pTask = *it;
		if(!pTask)
		{
			continue;
		}

		if(pTask->_id == taskId)
		{
			pTaskVo = pTask;
			break;
		}
	}

	if(pTaskVo && _pListView){
		if(_pListView->getChilds()->count() > 0)
		{
			CCNode * pNode = (CCNode *)_pListView->getChilds()->getObjectAtIndex(0);
			if (RoleManage::Instance()->roleLev() >= 15)
			{
				// run action
				if (pNode && pNode->getChildByTag(0))
				{
					runLightAction(pNode->getChildByTag(0) , getLightAction());
				}
				/*
				CCFiniteTimeAction * pFadeOut = CCFadeOut::actionWithDuration(0.5f );
				CCFiniteTimeAction * pFadeOutR = pFadeOut->reverse();
				CCAction * pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeOut , pFadeOutR));
				if (pNode && pNode->getChildByTag(0))
				{
					pNode->getChildByTag(0)->runAction(pAction);
				}
				*/
				return 0;
			}
			return pNode;
		}
	}
	return NULL;				
}

CCAction * TaskFollowView::getLightAction()
{
	CCFiniteTimeAction * pFadeOut = CCFadeOut::actionWithDuration(0.5f );
	CCFiniteTimeAction * pFadeOutR = pFadeOut->reverse();
	CCAction * pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeOut , pFadeOutR));
	return pAction;
}

void TaskFollowView::runLightAction(CCNode * pNode , CCAction * pAction)
{
	if (pNode && pAction)
	{
		pNode->runAction(pAction);
	}	
}
