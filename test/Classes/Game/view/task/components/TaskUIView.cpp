#include "TaskUIView.h"
#include "TaskScrollView.h"
#include "utils/ScaleUtil.h"
#include "model/task/vo/TaskVo.h"
#include "TaskItem.h"
#include "../TaskMediator.h"
#include "control/AppFacade.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "model/player/RoleManage.h"
#include "TaskStrConcat.h"
#include "model/scene/NPCManager.h"
#include "LHLabelTTF.h"

TaskUIView::TaskUIView() : _curTaskId(0), _pMenuSpriteName(0)
{
	setIsHide(false);
}

TaskUIView::~TaskUIView()
{

}

bool TaskUIView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}


	this->setPosition(POS(ccp(848 - 28, 547 - 65-10), ScaleUtil::TOP_RIGHT));
	_pos = this->getPosition();

	loadItem();

	return true;
}

void TaskUIView::loadItem()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/map/res_map.plist");

	// bg circle
	{
		CCSprite * pBackCircle = new CCSprite();
		pBackCircle->initWithSpriteFrameName("mainui2/bigcircle.png");
		pBackCircle->setPosition(ccp(POSX(Size_ScrWidth)/2 , POSX(Size_ScrHight)/2 - POSX(5)));
		this->addChild(pBackCircle , ZOrder_back , Tag_back);
		pBackCircle->release();

		pBackCircle->setIsVisible(false);
	}
	
	// highlight
	{
		CCSprite * pBackLight = new CCSprite();
		pBackLight->initWithSpriteFrameName("backlight/light2.png");
		pBackLight->setPosition(ccp(POSX(Size_ScrWidth)/2 , POSX(Size_ScrHight)/2 - POSX(5)));
		pBackLight->setIsVisible(false);
		this->addChild(pBackLight , ZOrder_back +1 , Tag_HighLight);
		pBackLight->release();
	}
	

	TaskScrollView * pScrollView = 0;
	// scroll view
	{
		pScrollView = TaskScrollView::scrollViewWithRect(CCRectMake(0 , 0 , POSX(Size_ScrWidth) , POSX(Size_ScrHight)));
		this->addChild(pScrollView , ZOrder_item , Tag_ScrollView);
	}	

	// left director button
	{
		CCSprite * pLeftDir1 = new CCSprite();
		CCSprite * pLeftDir2 = new CCSprite();
		pLeftDir1->initWithSpriteFrameName(/*"mainui2/leftdir.png"*/"map/arrow.png");
		pLeftDir2->initWithSpriteFrameName(/*"mainui2/leftdir2.png"*/"map/arrow.png");
		CCMenuItemSprite * pDirMenuItemLeft = CCMenuItemSprite::itemFromNormalSprite(
			pLeftDir1,
			pLeftDir2,
			this,
			menu_selector(TaskUIView::onClick2Left));
		pLeftDir1->release();
		pLeftDir2->release();
		CCMenu * pDirMenuLeft = CCMenu::menuWithItem(pDirMenuItemLeft);
		pDirMenuLeft->setPosition(ccp(POSX(-4) , POSX(69)));
		pDirMenuLeft->setIsVisible(pScrollView->totalScreens > 1);
		pDirMenuLeft->setTag(Tag_LeftDir);
		this->addChild(pDirMenuLeft , ZOrder_item);
	}
	
	// right director button
	{
		CCSprite * pRightDir1 = new CCSprite();
		CCSprite * pRightDir2 = new CCSprite();
		pRightDir1->initWithSpriteFrameName(/*"mainui2/leftdir.png"*/"map/arrow.png");
		pRightDir2->initWithSpriteFrameName(/*"mainui2/leftdir2.png"*/"map/arrow.png");
		pRightDir1->setFlipX(true);
		pRightDir2->setFlipX(true);
		CCMenuItemSprite * pDirMenuItemRight = CCMenuItemSprite::itemFromNormalSprite(
			pRightDir1,
			pRightDir2,
			this,
			menu_selector(TaskUIView::onClick2Right));
		pRightDir1->release();
		pRightDir2->release();
		CCMenu * pDirMenuRight = CCMenu::menuWithItem(pDirMenuItemRight);
		pDirMenuRight->setPosition(ccp(POSX(Size_ScrWidth) + POSX(4) , POSX(69)));
		pDirMenuRight->setIsVisible(pScrollView->totalScreens > 1);
		pDirMenuRight->setTag(Tag_RightDir);
		this->addChild(pDirMenuRight , ZOrder_item);
	}
	
	// task button
	{
		CCSprite * pNameBtnSprite1 = CCSprite::spriteWithSpriteFrameName("ui/tab.png");
		CCSprite * pNameBtnSprite2 = CCSprite::spriteWithSpriteFrameName("ui/tab.png");
		pNameBtnSprite2->setColor(ccc3(12,233,25));
		_pMenuSpriteName = CCMenuItemSprite::itemFromNormalSprite(
			pNameBtnSprite1,
			pNameBtnSprite2,
			this,
			menu_selector(TaskUIView::onClickShowTask));
		_pMenuSpriteName->setScale(0.7);
		//pMenuSpriteName->setTag(taskVo->_id);
		CCSize mnsize = _pMenuSpriteName->getContentSize();
		LHLabelTTF * pNpcNameText = new LHLabelTTF();
		pNpcNameText ->initWithString("",CCSizeMake(POSX(160) , POSX(24)),CCTextAlignmentCenter , "Arial" , POSX(22) , POSX(0.5));
		pNpcNameText->setPosition(ccp(mnsize.width/2, mnsize.height/2));
		pNpcNameText->setColor(ccc3(255,215,0));
		_pMenuSpriteName->addChild(pNpcNameText , 0 , Tag_ButtonStr);
		pNpcNameText->release();
		_pMenuSpriteName->setPosition(ccp(POSX(Size_ScrWidth)/2, POSX(15)));
		CCMenu * pMenuName = CCMenu::menuWithItem(_pMenuSpriteName);
		pMenuName->setPosition(ccp(0,0));
		pMenuName->setTouchLayer(TLE::SceneUILayer -2);
		//pMenuName->setTag(Tag_NameBtn);
		this->addChild(pMenuName , 1);
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/map/res_map.plist");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/map/res_map.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/map/res_map.pvr.ccz");
	/*
	{
		CCSprite * pSpriteBtn1 = new CCSprite();
		CCSprite * pSpriteBtn2 = new CCSprite();
		pSpriteBtn1->initWithSpriteFrameName("mapbtn/showtask1.png");
		pSpriteBtn2->initWithSpriteFrameName("mapbtn/showtask2.png");
		pSpriteBtn1->setScale(0.8);
		pSpriteBtn2->setScale(0.8);
		CCMenuItemSprite * pMenuItem = CCMenuItemSprite::itemFromNormalSprite(
			pSpriteBtn1,
			pSpriteBtn2,
			this,
			menu_selector(TaskUIView::onClickShowTaskView));
		pSpriteBtn1->release();
		pSpriteBtn2->release();
		CCMenu * pTaskMenu = CCMenu::menuWithItem(pMenuItem);
		pTaskMenu->setTouchLayer(TLE::SceneUILayer);
		pTaskMenu->setPosition(ccp(POSX(Size_ScrWidth/2/0.8) , POSX(-20)));
		this->addChild(pTaskMenu , 1 ,Tag_TaskBtn);

		pTaskMenu->setIsVisible(false); // unused

	}
	*/
	
}

void TaskUIView::onClickShowTaskView(CCObject * pSender)
{
	TaskMediator *pTaskMediator = (TaskMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
	if(pTaskMediator) 
	{
		pTaskMediator->openTaskView();
	}
}

void TaskUIView::onClick2Left(CCObject * pSender)
{
	return;

	TaskScrollView * pScrollView = (TaskScrollView *)this->getChildByTag(Tag_ScrollView);
	if (pScrollView)
	{
		if ( pScrollView->currentScreen > 1)
		{
			pScrollView->moveToPreviousPage();
		}		
	}	
}

void TaskUIView::onClick2Right(CCObject * pSender)
{
	return;

	TaskScrollView * pScrollView = (TaskScrollView *)this->getChildByTag(Tag_ScrollView);
	if (pScrollView)
	{
		if ( pScrollView->currentScreen < pScrollView->totalScreens)
		{
			pScrollView->moveToNextPage();
		}		
	}	
}

void TaskUIView::showHightLight(bool var)
{
	CCSprite * pLight = (CCSprite * )this->getChildByTag(Tag_HighLight);
	if (pLight)
	{
		pLight->setIsVisible(var);
	}
	
}

void TaskUIView::handleTaskListPriority()
{
	// handle task for id ->[240,250]
	/*
	{
		std::vector<TaskVo *>::iterator iter =  _canTaskList.begin();
		if (iter!= _canTaskList.end())
		{
			int taskid = (*iter)->_id;
			if (taskid >= 240 && taskid <= 250)
			{
				TaskVo *vo = *iter;
				_canTaskList.push_back(vo);
				_canTaskList.erase(_canTaskList.begin());
			}
		}
	}
	
	{
		std::vector<TaskVo *>::iterator iter =  _recTaskList.begin();
		if (iter!= _recTaskList.end())
		{
			int taskid = (*iter)->_id;
			if (taskid >= 240 && taskid <= 250)
			{
				TaskVo *vo = *iter;
				_recTaskList.push_back(vo);
				_recTaskList.erase(_recTaskList.begin());
			}
		}
	}
	*/

	std::vector<TaskVo *> * taskList = getAllTaskList();
	if (taskList)
	{
		std::vector<TaskVo *>::iterator iter =  taskList->begin();
		if (iter!= taskList->end())
		{
			int taskid = (*iter)->_id;
			if (taskid >= 240 && taskid <= 250)
			{
				TaskVo *vo = *iter;
				taskList->push_back(vo);
				taskList->erase(taskList->begin());
			}
		}
	}

	

}

void TaskUIView::resetScrollView()
{
	handleTaskListPriority();

	TaskScrollView * pScrollView = (TaskScrollView *)this->getChildByTag(Tag_ScrollView);
	if (!pScrollView)
	{
		return;
	}	

	int totalScreen = pScrollView->totalScreens;
	for (int i = 0 ; i < totalScreen ; i++)
	{
		if (pScrollView->getContentLayer() && pScrollView->getLayerByTag(i))
		{
			pScrollView->getContentLayer()->removeChildByTag(i , true);
		}
	}

	pScrollView->currentScreen = 0;
	pScrollView->totalScreens = 0;

	std::vector<TaskVo *> * mtaskList = &_allTaskList;

	std::vector<TaskVo *>::iterator iter = mtaskList->begin();

	if (mtaskList->empty())
	{
		if (RoleManage::Instance()->roleLev()<2)
		{
			TaskItem * pItem = new TaskItem(TaskManager::Instance()->getTask(1));
			CCLayer * pLayer = pScrollView->addLayerByTag(0);
			if (pLayer && pItem)
			{
				pLayer->addChild(pItem , 0 , 0);
				pItem->setPosition(ccp(POSX(Size_ScrWidth/2) - pItem->getContentSize().width/2 , POSX(15)));
				runMyAction( pItem , getMyAction(Action_Fade));
				pItem->release();
			}
		}
	}
	else
	{
		int page = 0;
		//bool hasMainTask = false;
		for (iter ; iter != mtaskList->end() ; iter++)
		{
			TaskItem * pItem = new TaskItem(*iter);
			CCLayer * pLayer = pScrollView->addLayerByTag(page);
			if (pLayer && pItem)
			{
				pLayer->addChild(pItem , 0 , 0);
				pItem->setPosition(ccp(POSX(Size_ScrWidth/2) - pItem->getContentSize().width/2 , POSX(15)));
				runMyAction( pItem , getMyAction(Action_Fade));
				pItem->release();
			}
			++page;
		}
	}

	/*
	bool isCanTaskList = false;
	std::vector<TaskVo *> mtaskList;
	if (_recTaskList.empty())
	{
		NPCManager::Instance()->setHasGetTask(false);
		mtaskList = _canTaskList;
		isCanTaskList = true;
	}
	else
	{
		NPCManager::Instance()->setHasGetTask(true);
		mtaskList = _recTaskList;
	}

	TaskScrollView * pScrollView = (TaskScrollView *)this->getChildByTag(Tag_ScrollView);
	if (!pScrollView)
	{
		return;
	}	

	int totalScreen = pScrollView->totalScreens;
	for (int i = 0 ; i < totalScreen ; i++)
	{
		if (pScrollView->getContentLayer() && pScrollView->getLayerByTag(i))
		{
			pScrollView->getContentLayer()->removeChildByTag(i , true);
		}
	}
	pScrollView->currentScreen = 0;
	pScrollView->totalScreens = 0;
	
	std::vector<TaskVo *>::iterator iter = mtaskList.begin();

	if (mtaskList.empty())
	{
		if (RoleManage::Instance()->roleLev()<2)
		{
			TaskItem * pItem = new TaskItem(TaskManager::Instance()->getTask(1));
			CCLayer * pLayer = pScrollView->addLayerByTag(0);
			if (pLayer && pItem)
			{
				pLayer->addChild(pItem , 0 , 0);
				pItem->setPosition(ccp(POSX(Size_ScrWidth/2) - pItem->getContentSize().width/2 , POSX(15)));
				runMyAction( pItem , getMyAction(Action_Fade));
				pItem->release();
			}
		}
	}
	else
	{
		int page = 0;
		//bool hasMainTask = false;
		for (iter ; iter != mtaskList.end() ; iter++)
		{
			if (isCanTaskList)
			{
				//if ((*iter)->_type == 1)
				{
					TaskItem * pItem = new TaskItem(*iter);

					CCLayer * pLayer = pScrollView->addLayerByTag(page);
					if (pLayer && pItem)
					{
						pLayer->addChild(pItem , 0 , 0);
						pItem->setPosition(ccp(POSX(Size_ScrWidth/2) - pItem->getContentSize().width/2 , POSX(15)));
						runMyAction( pItem , getMyAction(Action_Fade));
						pItem->release();
					}
					//hasMainTask = true;					

					break;
				}
			}
			else
			{
				TaskItem * pItem = new TaskItem(*iter);
				CCLayer * pLayer = pScrollView->addLayerByTag(page);
				if (pLayer && pItem)
				{
					pLayer->addChild(pItem , 0 , 0);
					pItem->setPosition(ccp(POSX(Size_ScrWidth/2) - pItem->getContentSize().width/2 , POSX(15)));
					runMyAction( pItem , getMyAction(Action_Fade));
					pItem->release();
				}
				++page;
			}				
		}

		
// 		if (isCanTaskList && (!hasMainTask))
// 		{
// 			TaskItem * pItem = new TaskItem(mtaskList[0]);
// 			CCLayer * pLayer = pScrollView->addLayerByTag(page);
// 			if (pLayer && pItem)
// 			{
// 				pLayer->addChild(pItem , 0 , 0);
// 				pItem->setPosition(ccp(POSX(Size_ScrWidth/2) - pItem->getContentSize().width/2 , POSX(15)));
// 				runMyAction( pItem , getMyAction(Action_Fade));
// 				pItem->release();
// 			}
// 		}
		
		
	}
	*/

	setCurTaskIcon();

	/*
	if (isCanTaskList)
	{
		showDirs(false);
	}
	else
	{
		showDirs(mtaskList.size() > 1);
	}
	*/
	showDirs(mtaskList->size() > 1);
}

std::vector<TaskVo *> * TaskUIView::getAllTaskList()
{
	_allTaskList.clear();
	std::vector<TaskVo *>::iterator iter = _recTaskList.begin();
	for (iter ; iter != _recTaskList.end() ; iter++)
	{
		_allTaskList.push_back(*iter);
	}

	iter = _canTaskList.begin();
	for (iter ; iter != _canTaskList.end() ; iter++)
	{
		_allTaskList.push_back(*iter);
	}
	return &_allTaskList;
}

CCNode * TaskUIView::getNewHandItem( int id )
{
	CCSprite * pBackCircle = (CCSprite *)this->getChildByTag(Tag_back);
	if (pBackCircle)
	{
		return pBackCircle;
	}
	return 0;
}

void TaskUIView::runMyAction(CCNode * pNode , CCAction * pAction)
{
	if (pNode && pAction)
	{
		pNode->runAction(pAction);
	}	
}

void TaskUIView::stopMyAction(CCNode * pNode )
{
	if (pNode)
	{
		pNode->stopAllActions();
		pNode->cleanup();
	}	
}

CCAction * TaskUIView::getMyAction(int type)
{
	switch (type)
	{
	case Action_Fade:
		{
			CCFiniteTimeAction * pFadeTo1 = CCFadeTo::actionWithDuration(0.5f , 128);
			CCFiniteTimeAction * pFadeTo2 = CCFadeTo::actionWithDuration (0.5f , 255);
			CCAction * pAction = CCSequence::actionOneTwo(pFadeTo1 , pFadeTo2);
			return pAction;
		}
		break;
	default :
		break;
	}
	return 0;
}

void TaskUIView::setCurTaskId(int id)
{
	_curTaskId = id;
}

void TaskUIView::setCurTaskIcon()
{
	TaskScrollView * pScrollView = (TaskScrollView *)this->getChildByTag(Tag_ScrollView);
	if (!pScrollView)
	{
		return;
	}
	if (pScrollView->totalScreens<1)
	{
		return;
	}
	
	pScrollView->moveToPageImmediately(1);

	int totalScreen = pScrollView->totalScreens;
	for (int i = 0 ; i < totalScreen ; i++)
	{
		CCLayer * pLayer = pScrollView->getLayerByTag(i);
		if (pLayer)
		{
			TaskItem * pItem = (TaskItem *)pLayer->getChildByTag(0);
			if (pItem && pItem->_taskVo)
			{
				if (_curTaskId == pItem->_taskVo->_id  /*||  _curTaskId == 0*/)
				{
					pScrollView->moveToPageImmediately(i+1);
					updateTaskButtonInfo(pItem->_taskVo);
					//pItem->setNameTouchPriority(TLE::SceneUILayer -1);
					break;
				}
				/*
				else
				{
					pItem->ennableNameButtonTouch(false);
				}
				*/
			}			
		}		
	}
}

void TaskUIView::onClickHideUI(CCObject * pSender)
{
	int plus = getIsHide() ? 0 : 1;
	this->setPosition(ccpAdd(_pos , ccp((plus) * (Size_ScrWidth + POSX(20)) , 0)));
	setIsHide(!getIsHide());
}

void TaskUIView::showUI(bool var)
{
	bool bhide = getIsHide();
	if(bhide ^ var)
	{
		return;
	}
	else
	{
		onClickHideUI(0);
	}
}

void TaskUIView::showDirs(bool var)
{
	CCNode * pNodeR = this->getChildByTag(Tag_RightDir);
	if (pNodeR)
	{
		pNodeR->setIsVisible(var);
	}

	CCNode * pNodeL = this->getChildByTag(Tag_LeftDir);
	if (pNodeL)
	{
		pNodeL->setIsVisible(var);
	}
	
}

void TaskUIView::updateTaskButtonInfo(TaskVo * taskVo)
{
	if (!taskVo)
	{
		return;
	}
	if (_pMenuSpriteName)
	{
		_pMenuSpriteName->setTag(taskVo->_id);
	}
	/*
	bool isFinish = TaskStrConcat::checkTaskFinish(taskVo->_taskTip);
	NPCVo *pNpcVo = NULL;
	if(isFinish)
	{
		pNpcVo = NPCManager::Instance()->getNPC(taskVo->getFinishTaskNpc());
	}
	else
	{
		pNpcVo = NPCManager::Instance()->getNPC(taskVo->getRecTaskNpc());
	}

	if(!pNpcVo || !NPCManager::Instance()->getHasGetTask())
	{
		pNpcVo = NPCManager::Instance()->getNPC(taskVo->getCanTaskNpc(taskVo->_id));
	}
	*/
	bool isFinish = TaskStrConcat::checkTaskFinish(taskVo->_taskTip);

	NPCVo *pNpcVo = NULL;
	if(isFinish)
	{
		pNpcVo = NPCManager::Instance()->getNPC(taskVo->getFinishTaskNpc());
	}
	else
	{
		if (taskVo->isRecived())
		{
			pNpcVo = NPCManager::Instance()->getNPC(taskVo->getFinishTaskNpc());
		}
		else
		{
			pNpcVo = NPCManager::Instance()->getNPC(taskVo->getCanTaskNpc(taskVo->_id));
		}		
	}

	if(!pNpcVo )
	{
		pNpcVo = NPCManager::Instance()->getNPC(taskVo->getRecTaskNpc());
	}

	if (!pNpcVo)
	{
		return;
	}
	char pName[64] = {0};
	if(taskVo->_type == 1)
	{
		sprintf(pName, "%s%s", ValuesUtil::Instance()->getString("task_lord2").c_str(), pNpcVo->name.c_str());
	}
	else
	{
		sprintf(pName, "%s%s", ValuesUtil::Instance()->getString("task_other2").c_str(), pNpcVo->name.c_str());
	}
	CCLabelTTF * pNpcNameText = (CCLabelTTF *)_pMenuSpriteName->getChildByTag(Tag_ButtonStr);
	if (pNpcNameText)
	{
		pNpcNameText->setString(pName);
	}	
}

void TaskUIView::onClickShowTask(CCObject * pSender)
{
	TaskMediator *pTaskMediator = (TaskMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
	if(pTaskMediator) 
	{
		pTaskMediator->openTaskView();
		if (pTaskMediator->_pTaskView)
		{
			pTaskMediator->_pTaskView->showTaskListItemByID(((CCNode *)pSender)->getTag());
		}		
	}
}