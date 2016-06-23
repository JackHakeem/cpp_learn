#include "TaskView.h"
#include "manager/OverPanelManage.h"
#include "CCUIBaseClipLayer.h"
#include "manager/PopEventName.h"
#include "UITaskPanelListView/CCUITaskPanelItem.h"
#include "BaseType.h"
#include "manager/LayerManager.h"
#include "manager/GlobalManage.h"
#include "../TaskListenerMediator.h"
#include "utils/ValuesUtil.h"
#include "model/scene/NPCManager.h"
#include "utils/ScaleUtil.h"
#include "events/TaskEvent.h"
#include "events/GameDispatcher.h"
#include "TaskStrConcat.h"
#include "TaskUtil.h"
#include "TaskAutoFindNpc.h"
#include "model/scene/SceneManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"


#define HEIGHT_LIST_ITEM_EXPANDED POSX(356)
#define HEIGHT_LIST_ITEM_COLLAPSED POSX(70)
#define WIDTH_LIST_ITEM POSX(886)

//#define CCPOINT_CLOSE_BTN ccp(SCALEW(756), SCALEH(520))
#define CCPOINT_BG ccp(0, 0)
#define CCPOINT_TASK_RECEIVE_BTN POS(ccp(156, 580), ScaleUtil::CENTER_TOP)
#define CCPOINT_TASK_CAN_BTN  POS(ccp(302, 580), ScaleUtil::CENTER_TOP)
#define CCPOINT_LIST_ITEM_TASK_BUTTON ccp(POSX(736), HEIGHT_LIST_ITEM_EXPANDED - POSX(12))

#define CCRECT_TASK_LIST_CLIP CCRectMake(POSX(30),\
	POSX(36), \
	CCSIZE_CONTENT_LAYER.width,\
	CCSIZE_CONTENT_LAYER.height)

#define CCPOINT_CONTENT_LAYER ccp(POSX(20), POSX(24))
#define CCSIZE_CONTENT_LAYER CCSizeMake(POSX(886), POSX(518))

USING_NS_CC;

TaskView * TaskView::initWithRect( const cocos2d::CCRect &rect )
{
	TaskView *pTaskView = new TaskView();
	if(pTaskView)
	{
		pTaskView->setContentSize(rect.size);
		pTaskView->setPosition(POS(rect.origin, ScaleUtil::CENTER));
		pTaskView->setIsRelativeAnchorPoint(true);
		pTaskView->setAnchorPoint(CCPointZero);
		pTaskView->init();
		return pTaskView;
	}
	CC_SAFE_DELETE(pTaskView);
	return NULL;
}

TaskView::TaskView()
{
	key = PopEventName::TASK;
}

TaskView::~TaskView()
{
	//this->release();
}


bool TaskView::init()
{
	/*if(!CCLayer::init())
	{
		return false;
	}*/

	this->setIsTouchEnabled(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	this->setContentSize(winSize);
	this->setPopContentSize(this->getContentSize());
	this->setPosition(CCPointZero);

	//Values manager
	ValuesUtil *pValuesUtil = ValuesUtil::Instance();
	ccColor3B textColor = ccc3(255, 255, 0);
	
	CCLayer *pInnerLayer = new CCLayer();
	if(!pInnerLayer || !pInnerLayer->init()) 
	{
		return false;
	}
	CCPoint innerLayerPosition = POS(ccp(16.0f, 12.0f), ScaleUtil::CENTER_TOP);
	pInnerLayer->setAnchorPoint(CCPointZero);
	//pInnerLayer->initWithColor(ccc4(255, 128, 128, 100));
	pInnerLayer->setPosition(innerLayerPosition);
	pInnerLayer->setIsRelativeAnchorPoint(true);
	pInnerLayer->setContentSize(CCDirector::sharedDirector()->getWinSize());

	// Close button
	/*CCMenuItemImage *pCloseBtn = CCMenuItemImage::itemFromNormalImage(
		"assets/task/TaskViewCloseBtnNormal.png",
		"assets/task/TaskViewCloseBtnPressed.png",
		this,
		menu_selector(TaskView::closeButtonClick));
	pCloseBtn->setPosition(CCPOINT_CLOSE_BTN);
	pCloseBtn->setAnchorPoint(CCPointZero);
	CCMenu* pCloseMenu = CCMenu::menuWithItems(pCloseBtn, NULL);
	pCloseMenu->setPosition(CCPointZero);
	this->addChild(pCloseMenu , 1);*/

	// background
	/*CCSprite *backgroundSprite = CCSprite::spriteWithFile("assets/task/TaskViewBg.png");
	backgroundSprite->setPosition(CCPOINT_BG);
	backgroundSprite->setAnchorPoint(CCPointZero);
	this->addChild(backgroundSprite);*/

	//��May meet mission button
	CCMenuItemSprite * pTaskCanBtn = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/button2_normal.png"),
		CCSprite::spriteWithSpriteFrameName("ui/button2_pressed.png"),
		this,
		menu_selector(TaskView::canTaskButtonClick) );
	pTaskCanBtn->setPosition(CCPOINT_TASK_CAN_BTN);
	pTaskCanBtn->setAnchorPoint(CCPointZero);
	_pTaskCanMenu = UICheckButton::menuWithItems(pTaskCanBtn, NULL);
	_pTaskCanMenu->setPosition(CCPointZero);
	_pTaskCanMenu->setTouchLayer(TLE::WindowLayer_TaskView);
	this->addChild(_pTaskCanMenu);
    
    CCLabelTTF* pEnTaskLabel = CCLabelTTF::labelWithString(pValuesUtil->getString("task_can").c_str(),
		CCSizeMake(POSX(96), POSX(24)),
		CCTextAlignmentLeft, 
		"Arial",
		POSX(24));
	pEnTaskLabel->setColor(textColor);
	pEnTaskLabel->setPosition( ccp(CCPOINT_TASK_CAN_BTN.x + POSX(30),
		CCPOINT_TASK_CAN_BTN.y + POSX(20)));
	pEnTaskLabel->setAnchorPoint( CCPointZero );
	pEnTaskLabel->setIsRelativeAnchorPoint(true);
	this->addChild(pEnTaskLabel);


	// Already quests button
	CCMenuItemSprite * pTaskReceiveBtn = CCMenuItemImage::itemFromNormalSprite(
		CCSprite::spriteWithSpriteFrameName("ui/button2_normal.png"),
		CCSprite::spriteWithSpriteFrameName("ui/button2_pressed.png"),
		this,
		menu_selector(TaskView::receiveTaskButtonClick));
	pTaskReceiveBtn->setPosition(CCPOINT_TASK_RECEIVE_BTN);
	pTaskReceiveBtn->setAnchorPoint(CCPointZero);
	_pTaskReceiveMenu = UICheckButton::menuWithItems(pTaskReceiveBtn, NULL);
	_pTaskReceiveMenu->setPosition(CCPointZero);
	_pTaskReceiveMenu->setIsCheck(true);
	_pTaskReceiveMenu->setIsTouchEnabled(false);
	_pTaskReceiveMenu->setTouchLayer(TLE::WindowLayer_TaskView);
	this->addChild(_pTaskReceiveMenu);

	CCLabelTTF* pRecTaskLabel = CCLabelTTF::labelWithString(pValuesUtil->getString("task_recd").c_str(), 
		CCSizeMake(POSX(96), POSX(24)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(24));
	pRecTaskLabel->setColor(textColor);
	pRecTaskLabel->setPosition( ccp(CCPOINT_TASK_RECEIVE_BTN.x + POSX(30),
		CCPOINT_TASK_RECEIVE_BTN.y + POSX(20)));
	pRecTaskLabel->setAnchorPoint( CCPointZero );
	pRecTaskLabel->setIsRelativeAnchorPoint(true);
	this->addChild(pRecTaskLabel);
    
	_pListView = CCUITaskPanelListView::listViewWithCCRect(CCRectMake(CCPOINT_CONTENT_LAYER.x,
		CCPOINT_CONTENT_LAYER.y,
		CCSIZE_CONTENT_LAYER.width,
		CCSIZE_CONTENT_LAYER.height), 
		false);
	if(!_pListView) 
		return false;
	_pListView->setAnchorPoint(CCPointZero);
	//_pListView->setBackgroundWithFile("HelloWorld.png");
	//_pListView->setClipLayerRect(CCRECT_TASK_LIST_CLIP);
	_pListView->setSpacingVertical(POSX(10));
	//_pListView->setAdapter(this);
	_pListView->setHeaderSize(POSX(20));
	_pListView->setFooterSize(POSX(20));
	_pListView->setOnItemActionListener(this);
	_pListView->setWorldSpaceLeftBottomPoint(ccp(pInnerLayer->getPosition().x + _pListView->getPosition().x,
		pInnerLayer->getPosition().y + _pListView->getPosition().y));
	_pListView->m_pri = TLE::WindowLayer_TaskView+1;
	pInnerLayer->addChild(_pListView);
	//_pListView->release(); // Kenfly 20130125 // disabled by LONGHUI

	// init task list type.
	setCurrentTaskTypeOnList(TASK_TYPE_REC);
	
	// reset view.
	_pListView->setAdapter(this);
	this->addChild(pInnerLayer);
	pInnerLayer->release();
	return true;
}

void TaskView::closeButtonClick( CCObject* pSender )
{
	setisPop(false);
	//g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());
}

//int32 TaskView::getSelfTag()
//{
//	return key;
//}

void TaskView::canTaskButtonClick( CCObject* pSender )
{
	if(getCurrentTaskTypeOnList() == TASK_TYPE_CAN) 
		return;

	_pTaskReceiveMenu->setIsCheck(false);
	_pTaskReceiveMenu->setIsTouchEnabled(true);
	_pTaskCanMenu->setIsCheck(true);
	_pTaskCanMenu->setIsTouchEnabled(false);

	setCurrentTaskTypeOnList(TASK_TYPE_CAN);

	//Doyang 20120711
	refresh();

}

void TaskView::receiveTaskButtonClick( CCObject* pSender )
{
	if(getCurrentTaskTypeOnList() == TASK_TYPE_REC) 
		return;

	_pTaskReceiveMenu->setIsCheck(true);
	_pTaskReceiveMenu->setIsTouchEnabled(false);
	_pTaskCanMenu->setIsCheck(false);
	_pTaskCanMenu->setIsTouchEnabled(true);

	setCurrentTaskTypeOnList(TASK_TYPE_REC);

	//Doyang 20120711
	refresh();
}

int TaskView::getCount()
{
	switch (getCurrentTaskTypeOnList())
	{
	case TASK_TYPE_CAN:
		return getCanTakList().size();
		break;
		 
	//case TASK_TYPE_REC:
	//	break;

	default:
		// TASK_TYPE_REC is default.
		return getRecTakList().size();
		break;
	}
}

LayerNode * TaskView::getView( int position )
{
	switch (getCurrentTaskTypeOnList())
	{
	case TASK_TYPE_CAN:
		return buildListItemCell(getCanTakList()[position], position);
		break;

		//case TASK_TYPE_REC:
		//	break;

	default:
		// TASK_TYPE_REC is default.
		return buildListItemCell(getRecTakList()[position], position);;
		break;
	}
}

void TaskView::initCanTree( std::vector<TaskVo *> &taskList )
{
	//Doyang 20120710
	//getCanTakList().clear();
	canTaskList.clear();
	canTaskList = taskList;
	//setCanTakList(taskList);
	//_pListView->setAdapter(this);
}

void TaskView::selectNode()
{

}

void TaskView::initReceivedTree( std::vector<TaskVo *> &taskList )
{
	//Doyang 21020710
	//getRecTakList().clear();
	recTaskList.clear();
	recTaskList = taskList;
	//setRecTakList(taskList);
}

void TaskView::onItemClickListener( LayerNode *itemCell, int position )
{
}

void TaskView::onItemTouchListener( LayerNode *itemCell, int position )
{
	((CCUITaskPanelItem *) itemCell )->setIsFocus(true);
}

void TaskView::onItemTouchCancelListener( LayerNode *itemCell, int position )
{
	((CCUITaskPanelItem *) itemCell )->setIsFocus(false);
}

void TaskView::listItemTaskMenuSelector( CCObject* pSender )
{
	CCMenu *pTaskMenu = (CCMenu *) pSender;
	int position = pTaskMenu->getTag();
	CCLog("----------------tag=%d", position);
	
	switch (getCurrentTaskTypeOnList())
	{
	case TASK_TYPE_CAN:
		{
			TaskVo *pTask = getCanTakList()[position];
			if(!pTask)
				return;
			/*
			FindVo findVo;
			findVo._type = 1;
			findVo._sceneId = 1001;
			findVo._npcId = pTask->_pNpcs[0];
			GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);*/
			//dispatchEvent(TaskUtil::FIND_ELEMENT, &TaskAutoFindNpc::Instance()->taskFollowStr(pTask));
			
			NPCVo *pStartNpc = NPCManager::Instance()->getNPC(pTask->getRecTaskNpc());
			SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(pStartNpc->_mapId);
			TaskTipVo *pTaskTipVo = new TaskTipVo();
			pTaskTipVo->_sceneName = pSceneVo->name;
			pTaskTipVo->_sceneId = pSceneVo->id;
			pTaskTipVo->_id = pStartNpc->id;
			pTaskTipVo->_name = pStartNpc->name;
			string condition = TaskStrConcat::getDialog(pTask, pTaskTipVo);

			//Doyang 20120712
			CC_SAFE_DELETE(pTaskTipVo);
			dispatchEvent(TaskUtil::FIND_ELEMENT, &condition);
		}
		break;

	default:
		{
			TaskVo *pTask = getRecTakList()[position];
			if(!pTask)
				return;
			/*bool isFinish = TaskStrConcat::checkTaskFinish(pTask->_taskTip);

			FindVo findVo;
			findVo._type = 1;
			findVo._sceneId = 1001;
			findVo._npcId = isFinish ? pTask->_pNpcs[1] : pTask->_pNpcs[0];
			GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);*/
            string str = TaskStrConcat::conditionHtmlString(pTask);
			dispatchEvent(TaskUtil::FIND_ELEMENT, &str);

			//LH20121114
			TaskUIView * pTaskView = ViewManager::getInstance()->_taskUIView;
			if (pTaskView)
			{
				pTaskView->setCurTaskId(pTask->_id);
				pTaskView->resetScrollView();
			}
			
		}
		// TASK_TYPE_REC is default.
		//TaskListenerMediator *taskListenerMediator = (TaskListenerMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_LISTENER_MEDIATOR);
		////taskListenerMediator->receiveHandler(1, 1);
		//TaskVo *pRecTask = getRecTakList()[position];
		//if(pRecTask != NULL)
		//{
		//	TaskEvent *pTaskEvent = new TaskEvent();
		//	pTaskEvent->id = pRecTask->_id;
		//	pTaskEvent->taskType = pRecTask->_type;
		//	GameDispatcher::getInstance()->dispatchEvent(TaskEvent::SUBMIT, pTaskEvent);
		//	//taskListenerMediator->submitHandler(pRecTask->_askType, pRecTask->_id);
		//}
		break;
	}

	this->close();
}

LayerNode * TaskView::buildListItemCell( TaskVo *taskVo, int position )
{
	if(!taskVo)
		return NULL;
	//Values manager
	ValuesUtil *pValuesUtil = ValuesUtil::Instance();
	ccColor3B textColor = ccc3(255, 255, 0);

	int leftSpacing = POSX(30);

	CCUITaskPanelItem *contentLayer = CCUITaskPanelItem::initWithWidthHeight(
		WIDTH_LIST_ITEM, 
		HEIGHT_LIST_ITEM_EXPANDED, 
		WIDTH_LIST_ITEM,
		HEIGHT_LIST_ITEM_COLLAPSED, 
		/*CCRECT_TASK_LIST_CLIP.origin.y*/_pListView->getWorldSpaceLeftBottomPoint().y, 
		/*CCRECT_TASK_LIST_CLIP.origin.y + CCSIZE_CONTENT_LAYER.height*/_pListView->getWorldSpaceLeftBottomPoint().y + _pListView->getContentSizeInPixels().height);
	//Doyang 20120720
	if(position == 0 && getCurrentTaskTypeOnList() == TASK_TYPE_REC)
	{
		contentLayer->setvisibleSize(CCSizeMake(WIDTH_LIST_ITEM, HEIGHT_LIST_ITEM_EXPANDED));
		contentLayer->endExpanded();
	}
	else
	{
		contentLayer->setvisibleSize(CCSizeMake(WIDTH_LIST_ITEM, HEIGHT_LIST_ITEM_COLLAPSED));
	}
	
	contentLayer->setParentWorldSpaceBottomLeftPoint(_pListView->getWorldSpaceLeftBottomPoint());

	

	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pTaskMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(TaskView::listItemTaskMenuSelector) );
			pTaskMenuItem->setAnchorPoint(ccp(0, 1));
			pTaskMenuItem->setTag(position);
			pTaskMenuItem->setPosition( CCPOINT_LIST_ITEM_TASK_BUTTON );
			CCMenu* pTaskMenu = CCMenu::menuWithItems(pTaskMenuItem, NULL);
			pTaskMenu->setPosition( CCPointZero );
			pTaskMenu->setTouchLayer(TLE::WindowLayer_TaskView);
			contentLayer->addChild(pTaskMenu);
		}
	}
	
	

	// Add menu text
	std::string menuStr;
	switch (getCurrentTaskTypeOnList())
	{
	case TASK_TYPE_CAN:
		menuStr = pValuesUtil->getString("task_rec").c_str();
		break;
	default:
		// TASK_TYPE_REC is default.
		menuStr = pValuesUtil->getString("task_fin").c_str();
		break;
	}
	CCLabelTTF *pMenuLabel = CCLabelTTF::labelWithString(menuStr.c_str(), 
		CCSizeMake(POSX(120), POSX(22)), 
		CCTextAlignmentLeft, 
		"Arial", 
		POSX(20));
	pMenuLabel->setColor(textColor);
	pMenuLabel->setAnchorPoint(ccp(0, 1));
	pMenuLabel->setPosition( ccp(CCPOINT_LIST_ITEM_TASK_BUTTON.x + POSX(20),
		CCPOINT_LIST_ITEM_TASK_BUTTON.y - POSX(15)));
	contentLayer->addChild(pMenuLabel);
	//	CCLog("---name=%s, desc=%s, find=%s", taskVo->_taskName.c_str(), taskVo->_description.c_str(), taskVo->_findStr.c_str());

	// Title.
	char pTitle[128];
	if(taskVo->_type == 1)
	{
		sprintf(pTitle, "%s%s", pValuesUtil->getString("task_lord").c_str(), taskVo->_taskName.c_str());
	}
	else
	{
		sprintf(pTitle, "%s%s", pValuesUtil->getString("task_other").c_str(), taskVo->_taskName.c_str());
	}
	CCLabelTTF* pTitleLabel = CCLabelTTF::labelWithString(pTitle,
		CCSizeMake(POSX(800), POSX(24)), 
		CCTextAlignmentLeft, 
		"Arial", 
		POSX(24));
	pTitleLabel->setColor(textColor);
	pTitleLabel->setAnchorPoint(ccp(0, 1));
	pTitleLabel->setIsRelativeAnchorPoint(true);
	pTitleLabel->setPosition( ccp(leftSpacing, HEIGHT_LIST_ITEM_EXPANDED - POSX(25)));
	contentLayer->addChild(pTitleLabel);

	CCLayerColor *divide = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255), 
		WIDTH_LIST_ITEM - POSX(20), 
		POSX(1));
	divide->setPosition(ccp (POSX(10), HEIGHT_LIST_ITEM_EXPANDED - POSX(78)));
	contentLayer->addChild(divide);

	// Description.
	char descriptionTipChars[50];
	sprintf(descriptionTipChars, "%s:%s", pValuesUtil->getString("task").c_str(), taskVo->_taskName.c_str());
	CCLabelTTF* pDescriptionTipLabel = CCLabelTTF::labelWithString(
		descriptionTipChars,
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentLeft, 
		"Arial", 
		POSX(20));
	pDescriptionTipLabel->setColor(textColor);
	pDescriptionTipLabel->setPosition( ccp(leftSpacing, HEIGHT_LIST_ITEM_EXPANDED - POSX(108)));
	pDescriptionTipLabel->setAnchorPoint(ccp(0, 1));
	pDescriptionTipLabel->setIsRelativeAnchorPoint(true);
	contentLayer->addChild(pDescriptionTipLabel);

	CCLabelTTF* pDescriptionLabel = CCLabelTTF::labelWithString(taskVo->_description.c_str(),
		CCSizeMake(POSX(800), POSX(40)), 
		CCTextAlignmentLeft, 
		"Arial", 
		POSX(20));
	pDescriptionLabel->setColor(textColor);
	pDescriptionLabel->setAnchorPoint(ccp(0, 1));
	pDescriptionLabel->setIsRelativeAnchorPoint(true);
	pDescriptionLabel->setPosition( ccp(POSX(262), HEIGHT_LIST_ITEM_EXPANDED - POSX(100)));
	contentLayer->addChild(pDescriptionLabel);

	CCLayerColor *divide1 = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255),
		WIDTH_LIST_ITEM - POSX(20), 
		POSX(1));
	divide1->setPosition(ccp (POSX(10), HEIGHT_LIST_ITEM_EXPANDED - POSX(166)));
	contentLayer->addChild(divide1);

	// Task need.
	CCLabelTTF* pTaskNeedTipLabel = CCLabelTTF::labelWithString(pValuesUtil->getString("task_need").c_str(),
		CCSizeMake(POSX(100), POSX(20)), 
		CCTextAlignmentLeft, 
		"Arial", 
		POSX(20));
	pTaskNeedTipLabel->setColor(textColor);
	pTaskNeedTipLabel->setAnchorPoint(ccp(0, 1));
	pTaskNeedTipLabel->setIsRelativeAnchorPoint(true);
	pTaskNeedTipLabel->setPosition( ccp(leftSpacing, HEIGHT_LIST_ITEM_EXPANDED - POSX(204)));
	contentLayer->addChild(pTaskNeedTipLabel);

	char taskNeedHeaderChars[100];
	NPCVo *pRecNpc = NPCManager::Instance()->getNPC(taskVo->getRecTaskNpc());
	NPCVo *pFinNpc = NPCManager::Instance()->getNPC(taskVo->getFinishTaskNpc());

	sprintf(taskNeedHeaderChars, "%sNPC:%s, %sNPC:%s\n%s:%s", 
		pValuesUtil->getString("task_pub").c_str(), 
		pRecNpc->name.c_str(), 
		pValuesUtil->getString("task_fin").c_str(), 
		pFinNpc->name.c_str(), 
		pValuesUtil->getString("task_go").c_str(),
		taskVo->_taskTip->_sceneName.c_str());
	char taskNeedChars[200];
	switch(taskVo->_taskTip->_type)
	{
	case 0:
		// monsters
		sprintf(taskNeedChars, "%s,%s %s (%d/%d)", 
			taskNeedHeaderChars, 
			pValuesUtil->getString("task_kill").c_str(), 
			taskVo->_taskTip->_name.c_str(), 
			taskVo->_taskTip->_nowCount, 
			taskVo->_taskTip->_count);
		break;
	case 1:
		// Collection.
		sprintf(taskNeedChars, "%s,%s %s(%d/%d)",
			taskNeedHeaderChars,
			pValuesUtil->getString("task_col").c_str(), 
			taskVo->_taskTip->_name.c_str(), 
			taskVo->_taskTip->_nowCount, 
			taskVo->_taskTip->_count);
		break;
	default:
		sprintf(taskNeedChars, "%s,%d", taskNeedHeaderChars, taskVo->_taskTip->_id);
		break;
	}
	CCLabelTTF* pTaskNeedLabel = CCLabelTTF::labelWithString(taskNeedChars, 
		CCSizeMake(POSX(500), POSX(40)), 
		CCTextAlignmentLeft, 
		"Arial", 
		POSX(20));
	pTaskNeedLabel->setColor(textColor);
	pTaskNeedLabel->setAnchorPoint(ccp(0, 1));
	pTaskNeedLabel->setIsRelativeAnchorPoint(true);
	pTaskNeedLabel->setPosition( ccp(POSX(262), HEIGHT_LIST_ITEM_EXPANDED - POSX(196)));
	contentLayer->addChild(pTaskNeedLabel);

	CCLayerColor *divide2 = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 255, 255, 255), 
		WIDTH_LIST_ITEM - POSX(20), 
		POSX(1));
	divide2->setPosition(ccp (POSX(10), HEIGHT_LIST_ITEM_EXPANDED - POSX(262)));
	contentLayer->addChild(divide2);

	// Description.
	CCLabelTTF* pRewardTipLabel = CCLabelTTF::labelWithString(pValuesUtil->getString("task_reward").c_str(), 
		CCSizeMake(POSX(200), POSX(20)), 
		CCTextAlignmentLeft, 
		"Arial",
		POSX(20));
	pRewardTipLabel->setColor(textColor);
	pRewardTipLabel->setPosition( ccp(leftSpacing, HEIGHT_LIST_ITEM_EXPANDED - POSX(300)));
	pRewardTipLabel->setAnchorPoint(ccp(0, 1));
	pRewardTipLabel->setIsRelativeAnchorPoint(true);
	contentLayer->addChild(pRewardTipLabel);

	char rewardChars[200];
	bool hasReward = false;

	char goldChars[10];
    char copperChars[10];
    char experienceChars[10];
    char lifeExperiences[10];
	if(taskVo->_gold > 0)
	{
		hasReward = true;
		sprintf(goldChars, "%s+%d", pValuesUtil->getString("gold").c_str(), taskVo->_gold);
	}
	else
	{
		sprintf(goldChars, "");
	}

	if(taskVo->_copper > 0)
	{
		hasReward = true;
		sprintf(copperChars, "%s+%d", pValuesUtil->getString("silver").c_str(), taskVo->_copper);
	}
	else
	{
        sprintf(copperChars, "");
	}

	if(taskVo->_experience > 0)
	{
		hasReward = true;
		sprintf(experienceChars, "%s+%d", pValuesUtil->getString("exp").c_str(), taskVo->_experience);
	}
	else
	{
        sprintf(experienceChars, "");
	}

	if(taskVo->_lifeExperiences > 0)
	{
		hasReward = true;
		sprintf(lifeExperiences, "%s+%d", pValuesUtil->getString("pat").c_str(), taskVo->_lifeExperiences);
	}
	else
	{
        sprintf(lifeExperiences, "");
	}

	if(!hasReward)
	{
		sprintf(rewardChars, "%s", pValuesUtil->getString("none").c_str());
	}
	else
	{
		sprintf(rewardChars, "%s %s %s %s", goldChars, copperChars, experienceChars, lifeExperiences);
	}
	CCLabelTTF* pRewardLabel = CCLabelTTF::labelWithString(rewardChars,
		CCSizeMake(POSX(500), POSX(20)),
		CCTextAlignmentLeft, 
		"Arial",
		POSX(20));
	pRewardLabel->setColor(textColor);
	pRewardLabel->setAnchorPoint(ccp(0, 1));
	pRewardLabel->setIsRelativeAnchorPoint(true);
	pRewardLabel->setPosition( ccp(POSX(262), HEIGHT_LIST_ITEM_EXPANDED - POSX(300)));
	contentLayer->addChild(pRewardLabel);

	return contentLayer;
}

void TaskView::refresh()
{
	if(_pListView)
	{

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

			pChildLayer->removeFromParentAndCleanup(true);
			pChildLayer->release();
		}
		_pListView->setAdapter(this);
	}
}

std::string TaskView::conditionHtmlString( TaskVo *pTaskVo )
{
	//string condition:String = "";
	//var taskTipVo:TaskTipVo = new TaskTipVo;  
	//var sceneVo:SceneVo;

	//var npc:NPCVo;
	//var startNpc:NPCVo = NPCManager.getInstance().getNPC(taskVO.npcs[0]);
	//var endNpc:NPCVo = NPCManager.getInstance().getNPC(taskVO.npcs[1]);

	//condition += LangManager.getText("TSK068") + "<font color='#ffcc00'>" + startNpc.name +"</font>��";
	//condition += LangManager.getText("TSK069") + "<font color='#ffcc00'>" + endNpc.name + "</font>\n";

	//if(taskVO.taskTips.length == 0){
	//	npc = (curTabIndex == TAB_CAN_TASK) ? startNpc : endNpc;
	//	sceneVo = SceneManager.getInstance().getSceneDic(npc.mapId);
	//	taskTipVo.sceneName = sceneVo.name;
	//	taskTipVo.sceneId = sceneVo.id;
	//	taskTipVo.id = npc.id;
	//	taskTipVo.name = npc.name;  
	//	condition += TaskStrConcat.getDialog(taskVO, taskTipVo, "#ffcc00", "#ffffff");
	//}
	//else{
	//	var isFinish:Boolean = TaskStrConcat.checkTaskFinish(taskVO.taskTips);
	//	if(curTabIndex==TAB_CAN_TASK){ // �ɽ�״̬
	//		npc = startNpc;
	//		sceneVo = SceneManager.getInstance().getSceneDic(npc.mapId);
	//		taskTipVo.sceneName = sceneVo.name;
	//		taskTipVo.sceneId = sceneVo.id;
	//		taskTipVo.id = npc.id;
	//		taskTipVo.name = npc.name;
	//		condition += TaskStrConcat.getDialog(taskVO, taskTipVo, "#ffcc00", "#ffffff");

	//	}
	//	else if(curTabIndex==TAB_REC_TASK){
	//		if(isFinish){  // ���ύ״̬
	//			npc = endNpc;
	//			sceneVo = SceneManager.getInstance().getSceneDic(npc.mapId);
	//			taskTipVo.sceneName = sceneVo.name;
	//			taskTipVo.sceneId = sceneVo.id;
	//			taskTipVo.id = npc.id;
	//			taskTipVo.name = npc.name;
	//			condition += TaskStrConcat.getDialog(taskVO, taskTipVo, "#ffcc00", "#ffffff");
	//		}
	//		else{  // δ���״�?	//			condition += TaskStrConcat.getTaskTip(taskVO, "#ffffff");
	//		}
	//	}
	//}


	string condition;
	bool isFinish = TaskStrConcat::checkTaskFinish(pTaskVo->_taskTip);
	if(isFinish)
	{
		NPCVo *pEndNpc = NPCManager::Instance()->getNPC(pTaskVo->getFinishTaskNpc());
		SceneVo *pSceneVo = SceneManager::Instance()->getSceneDic(pEndNpc->_mapId);
		TaskTipVo *pTaskTipVo = new TaskTipVo();
		pTaskTipVo->_sceneName = pSceneVo->name;
		pTaskTipVo->_sceneId = pSceneVo->id;
		pTaskTipVo->_id = pEndNpc->id;
		pTaskTipVo->_name = pEndNpc->name;
		condition = TaskStrConcat::getDialog(pTaskVo, pTaskTipVo);
		//Doyang 20120712
		CC_SAFE_DELETE(pTaskTipVo);
	}
	else
	{
		condition = TaskStrConcat::getTaskTip(pTaskVo);
	}
	return condition;
}

void TaskView::close()
{
	this->setisPop(false);
}

void TaskView::showTaskListItemByID(int id)
{
	int count = 0;
	bool isExist = false;
	receiveTaskButtonClick(0);
	std::vector<TaskVo *> list = getRecTakList();
	std::vector<TaskVo *>::iterator iter = list.begin();
	for (iter ; iter != list.end() ; iter++)
	{
		if ((*iter) && ((*iter)->_id == id))
		{
			isExist = true;
			break;
		}
		++count;
	}
	
	if (!isExist)
	{
		canTaskButtonClick(0);
		count = 0;
		std::vector<TaskVo *> list = getCanTakList();
		std::vector<TaskVo *>::iterator iter = list.begin();
		for (iter ; iter != list.end() ; iter++)
		{
			if ((*iter) && ((*iter)->_id == id))
			{
				isExist = true;
				break;
			}
			++count;
		}
	}
	
	if (isExist && _pListView)
	{
		//_pListView->scrollToItemByIndex(count , 0.2);
		if (_pListView->getChilds())
		{
			CCUITaskPanelItem * pLayer = (CCUITaskPanelItem *)_pListView->getChilds()->getObjectAtIndex(count);
			if (pLayer && _pListView->getContentLayer())
			{
				float deltaY = count * pLayer->getMinHeight();
				CCPoint orgPos = _pListView->getContentLayer()->getPosition();
				//_pListView->moveContentLayerToPosition(ccpAdd(orgPos , ccp(0 , count * deltaY)));
				onItemTouchListener(_pListView->getChilds()->getObjectAtIndex(count) , count);
			}
		}
	}
	
}