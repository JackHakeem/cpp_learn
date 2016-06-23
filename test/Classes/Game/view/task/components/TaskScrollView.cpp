#include "TaskScrollView.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"
#include "TaskStrConcat.h"
#include "Message.h"
#include "TaskItem.h"
#include "model/newhand/NewhandManager.h"
#include "../TaskMediator.h"

TaskScrollView::TaskScrollView(CCRect rect):CCUIPartialScrollView(rect)
{
	setState(stat_0);
}

TaskScrollView::~TaskScrollView()
{

}

TaskScrollView *TaskScrollView::scrollViewWithRect(CCRect rect)
{
	TaskScrollView *pScrollView = new TaskScrollView(rect);
	pScrollView->m_pri = TLE::SceneUILayer -1;
	if(pScrollView && pScrollView->init())
	{
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
		return NULL;
}

void TaskScrollView::moveToPageImmediately(int page)
{
	CCUIPartialScrollView::moveToPageImmediately(page);

	CCLayer * pLayer = getLayerByTag(page - 1);
	if (pLayer)
	{
		TaskItem * pItem = (TaskItem *)pLayer->getChildByTag(0);
		if (pItem)
		{
			if (ViewManager::getInstance()->_taskUIView)
			{
				ViewManager::getInstance()->_taskUIView->updateTaskButtonInfo(pItem->_taskVo);
			}
			//pItem->ennableNameButtonTouch(true);
		}
	}
}

void TaskScrollView::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 0, true);
}

bool TaskScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	setState(stat_0);
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	_beginPos = touchPoint;
	CCPoint bottomPos = getScreenPos( this );
	if (CCRect::CCRectContainsPoint(CCRectMake(bottomPos.x , bottomPos.y , TaskUIView::Size_ScrWidth , TaskUIView::Size_ScrHight) , touchPoint))
	{
		if (ViewManager::getInstance()->_taskUIView)
		{
			ViewManager::getInstance()->_taskUIView->showHightLight(true);
		}

		return CCUIPartialScrollView::ccTouchBegan(pTouch, pEvent);
	}
	return false;
}

void TaskScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	_movePos = touchPoint;
	
	if (totalScreens <= 1)
	{
		
		setState(stat_0);
		return;
	}

	if (_movePos.x - _beginPos.x > POSX(5) || _movePos.x - _beginPos.x < POSX(-5))
	{
		setState(stat_1);
	}
	else
	{
		setState(stat_0);
		return;
	}
	

	/*
	if (ViewManager::getInstance()->_taskUIView)
	{
		ViewManager::getInstance()->_taskUIView->showHightLight(false);
	}
	*/

	return CCUIPartialScrollView::ccTouchMoved(pTouch , pEvent);
}

void TaskScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint;
	if (pTouch)
	{
		touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	}	

	if (ViewManager::getInstance()->_taskUIView)
	{
		ViewManager::getInstance()->_taskUIView->showHightLight(false);
	}

	if (getState() == stat_1)
	{
		setState(stat_0);
		if (pTouch)
		{
			// touch moving
			{
				TaskUIView * pUIView = ViewManager::getInstance()->_taskUIView;
				if (pUIView)
				{
					int page = currentScreen-1;
					if ( (touchPoint.x - startSwipe) < -scrollWidth / 3 && (currentScreen+1) <= totalScreens )
					{
						if (page < totalScreens-1)
						{
							++page;
						}						
					}
					else if ( (touchPoint.x - startSwipe) > scrollWidth / 3 && (currentScreen-1) > 0 )
					{
						if (page > 0)
						{
							--page;
						}
					}					
					CCLayer * pLayer = getLayerByTag(page);
					if (pLayer)
					{
						TaskItem * pItem = (TaskItem *)pLayer->getChildByTag(0);
						if (pItem && pItem->_taskVo)
						{
							pUIView->updateTaskButtonInfo(pItem->_taskVo);
						}
					}
				}
			}
			return CCUIPartialScrollView::ccTouchEnded(pTouch, pEvent);
		}
		else
		{
			return;
		}
	}
	else
	{
		TaskVo *pTaskVo = 0;
		TaskUIView * pUIView = ViewManager::getInstance()->_taskUIView;
		if (pUIView)
		{
			/*
			if (pUIView->_recTaskList.empty())
			{
				if (!pUIView->_canTaskList.empty())
				{
					if (currentScreen>=1)
					{
						pTaskVo = pUIView->_canTaskList[currentScreen-1];
					}				
				}
				else
				{
					//pTaskVo = TaskManager::Instance()->getTask(1);
					if (RoleManage::Instance()->roleLev()<2)
					{
						FindVo findVo;
						findVo._type = 1;
						findVo._sceneId = 1001;
						findVo._npcId = 1;
						GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);
						return;
					}
				}
			}
			else
			{
				if (currentScreen >= 1)
				{
					pTaskVo = pUIView->_recTaskList[currentScreen-1];
				}
			}
			*/
			if (pUIView->_allTaskList.empty())
			{
				if (RoleManage::Instance()->roleLev()<2)
				{
					FindVo findVo;
					findVo._type = 1;
					findVo._sceneId = 1001;
					findVo._npcId = 1;
					GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);
					return;
				}
			}
			else
			{
				if (currentScreen >= 1)
				{
					pTaskVo = pUIView->_allTaskList[currentScreen-1];
				}
			}

			if(pTaskVo)
			{
				int id = pTaskVo->_id;
				if (pTaskVo->_taskTip 
					&& (pTaskVo->_taskTip->_id == 1)
					&& (pTaskVo->_taskTip->_type == 8) )
				{
					if (!pTaskVo->_taskTip->_isFinish)
					{
						Message::Instance()-> show(pTaskVo->_description , ccc3(12 , 233 ,25) , 1);
					}
					else
					{
						TaskMediator *pTaskMediator = (TaskMediator *)g_pFacade->retrieveMediator(AppFacade_TASK_MEDIATOR);
						if(pTaskMediator) 
						{
							TaskView * pTaskView = pTaskMediator->_pTaskView;
							if (pTaskView )
							{
								if (pTaskView->getCanTakList().size()>0)
								{
									pTaskMediator->openTaskView();
									pTaskView->canTaskButtonClick(0);
									Message::Instance()-> show(ValuesUtil::Instance()->getString("task_tips1").c_str() , ccc3(12 , 233 ,25) , 2);
								}
								else
								{
									Message::Instance()-> show(ValuesUtil::Instance()->getString("task_tips2").c_str() , ccc3(12 , 233 ,25) , 2);
								}
							}	
						}
					}
				}
				//else
				{
					TaskStrConcat::findNPC(pTaskVo);
					pUIView->setCurTaskId(pTaskVo->_id);
				}
			}
			else if (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1001 
				&& RoleManage::Instance()->roleLev() <= 1
				&& NewhandManager::Instance()->_isNewAcount)
			{
				FindVo findVo;
				findVo._type = 1;
				findVo._sceneId = 1001;
				findVo._npcId = 1;
				GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);
			}
			
		}
		setState(stat_0);
		if (pTouch)
		{
			return CCUIPartialScrollView::ccTouchEnded(pTouch, pEvent);
		}
		else
		{
			return;
		}		
	}
}

void TaskScrollView::moveToNextPage()
{	
	CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.3f, ccp(-(((currentScreen+1)-1)*scrollWidth),0)));

	contentLayer->runAction(changePage);
	currentScreen = currentScreen+1;

	if (currentScreen < 1)
	{
		return;
	}	
	CCLayer * pLayer = getLayerByTag(currentScreen - 1);
	if (pLayer)
	{
		TaskItem * pItem = (TaskItem *)pLayer->getChildByTag(0);
		if (pItem)
		{
			if (ViewManager::getInstance()->_taskUIView)
			{
				ViewManager::getInstance()->_taskUIView->updateTaskButtonInfo(pItem->_taskVo);
			}
		}
	}
	
	
	/*
	for (int i = 0 ; i < totalScreens; i++)
	{
		CCLayer * pLayer = getLayerByTag(i);
		if (pLayer)
		{
				if ((i +1)== currentScreen)
				{
					//pItem->ennableNameButtonTouch(true);
				}
				else
				{
					//pItem->ennableNameButtonTouch(false);
				}				
			}
		}		
	}
	*/
}

void TaskScrollView::moveToPreviousPage()
{	
	CCEaseBounce* changePage =CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.3f, ccp(-(((currentScreen-1)-1)*scrollWidth),0)));
	contentLayer->runAction(changePage);
	currentScreen = currentScreen-1;

	if (currentScreen < 1)
	{
		return;
	}	
	CCLayer * pLayer = getLayerByTag(currentScreen - 1);
	if (pLayer)
	{
		TaskItem * pItem = (TaskItem *)pLayer->getChildByTag(0);
		if (pItem)
		{
			if (ViewManager::getInstance()->_taskUIView)
			{
				ViewManager::getInstance()->_taskUIView->updateTaskButtonInfo(pItem->_taskVo);
			}
		}
	}

	/*
	for (int i = 0 ; i < totalScreens; i++)
	{
		CCLayer * pLayer = getLayerByTag(i);
		if (pLayer)
		{
			TaskItem * pItem = (TaskItem *)pLayer->getChildByTag(0);
			if (pItem)
			{
				if ((i +1)== currentScreen)
				{
					//pItem->ennableNameButtonTouch(true);
				}
				else
				{
					//pItem->ennableNameButtonTouch(false);
				}				
			}
		}		
	}
	*/
}