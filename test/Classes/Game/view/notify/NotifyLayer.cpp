#include "NotifyLayer.h"
#include "NotifyManager.h"
#include "NotifyGrid.h"
#include "utils/ScaleUtil.h"
#include "NotifyType.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"
#include "manager/PopEventName.h"
#include "manager/ViewManager.h"
#include "socket/network/GameServerSocket.h"
#include "manager/CDManage.h"
#include "../arena/ArenaMediator.h"
#include "socket/command/c2c/CCMD2C6.h"


NotifyLayer::NotifyLayer()
{
	_winSize = CCDirector::sharedDirector()->getWinSize();
	pViewMgrInstance = 0;
}

NotifyLayer::~NotifyLayer()
{

}

bool NotifyLayer::init()
{
	if (!CCLayerColor::init())
	{
		return false;
	}

	pViewMgrInstance = ViewManager::getInstance();

	this->setIsTouchEnabled(true);

	_winSize = CCDirector::sharedDirector()->getWinSize();

	this->setContentSize(_winSize);
	this->setColor(ccc3(255,0,0));

	void loadItem();

	return true;
}

void NotifyLayer::loadItem()
{

}

void NotifyLayer::resetNotices()
{
	int count = NotifyManager::Instance()->getListCount();
	std::map<int , NotifyGrid *> *list = NotifyManager::Instance()->getList();
	std::map<int , NotifyGrid *>::iterator iter = list->begin();
	int index = 0;

	for (int i = 0 ; i < NotifyManager::MAX_COUNT ; i ++)
	{
		this->removeChildByTag(1000+i , true);
	}

	for (iter ; iter != list->end() ; iter++)
	{
		if (!this->getChildByTag(1000+index))
		{
			NotifyGrid  *pItem = iter->second;
			if (pItem)
			{
				pItem->setPosition(ccp(_winSize.width/2 + POSX(70) *( (index%3) - 1), POSX(160) - POSX(70) *( index/3)));
				this->addChild(pItem , 0 , 1000+index);
			}			
		}
		++index;
	}
}

int NotifyLayer::getTypeByTouchPos(CCPoint pos)
{
	for (int i = 0 ; i< NotifyManager::MAX_COUNT ; i++)
	{
		 NotifyGrid * pItem = ( NotifyGrid * )this->getChildByTag(1000+i);
		 if (pItem)
		 {
			 CCPoint itemPos = pItem->getPosition();
			 if (CCRect::CCRectContainsPoint(CCRectMake(itemPos.x , itemPos.y , POSX(60) , POSX(60)) , pos))
			 {
				 return pItem->_type;
				 break;
			 }
		 }
	}
	return -1;
}

void NotifyLayer::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,TLE::TipsLayer - 6000,true);
}

void NotifyLayer::doFollowEvent(int type)
{
	if (type == -1)
	{
		return;
	}

	switch (type)
	{
	case NotifyType::NType_Mail:
		{
			GameDispatcher::getInstance()->dispatchEvent(PopEventName::SHOW_UI_EMAIL, 0);
		}
		break;
	case NotifyType::NType_Strength:
		{
			GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_STRENG, 0 );
		}
		break;
	case NotifyType::NType_WorldBoss:
		{
			if (ViewManager::getInstance()->_secNavigate)
			{
				ViewManager::getInstance()->_secNavigate->popUIHandler330(0);
			}
		}
		break;
	case NotifyType::NType_Sliver:
		{
			if (ViewManager::getInstance()->_secNavigate)
			{
				ViewManager::getInstance()->_secNavigate->popUIHandler330(0);
			}
		}
		break;
	case NotifyType::NType_Levy:
		{
			GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_LEVY, 0 );
		}
		break;
	case NotifyType::NType_Gift:
		{
			if (ViewManager::getInstance()->mainNavigate)
			{
				ViewManager::getInstance()->mainNavigate->popUIHandler2(0);
			}
		}
		break;
	case NotifyType::NType_Train:
		{
			if (ViewManager::getInstance()->mainNavigate)
			{
				ViewManager::getInstance()->mainNavigate->popUIHandler10(0);
			}
		}
		break;
	case NotifyType::NType_Appoint:
		{
			GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_APPOINT, 0 );
		}
		break;
	case NotifyType::NType_Arena:
		{
			GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_ARENA, 0 );
		}
		break;
	case NotifyType::NType_DailyTask:
		{
			GameDispatcher::getInstance()->dispatchEvent( PopEventName::SHOW_UI_DAILY_TASK_EX, 0 );
		}
		break;
	case NotifyType::NType_Trader:
		{
			struct StructTemp
			{
				int id;
				string name;
				int lv;
				int type;
			} param;
			param.id = 0;
			param.name="";
			param.lv = 0;
			param.type = 3;
			GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_ROB_INFO, &param );
		}
		break;
	default:
		break;
	}
}

bool NotifyLayer::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	int type =  getTypeByTouchPos(touchPoint);	
	if (type == -1)
	{
		return false;
	}

	return true;
}

void NotifyLayer::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
}

void NotifyLayer::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	int type =  getTypeByTouchPos(touchPoint);	
	//
	doFollowEvent(type);

	// erase
	std::map<int , NotifyGrid *> *list = NotifyManager::Instance()->getList();
	std::map<int , NotifyGrid *>::iterator iter = list->find(type);
	if (iter != list->end())
	{
		list->erase(iter);
	}

	// resort
	if (NotifyManager::Instance()->_notifyLayer)
	{
		NotifyManager::Instance()->_notifyLayer->resetNotices();
	}
}

void NotifyLayer::removeLayer( int type )
{
	// erase
	std::map<int , NotifyGrid *> *list = NotifyManager::Instance()->getList();
	std::map<int , NotifyGrid *>::iterator iter = list->find(type);
	if (iter != list->end())
	{
		list->erase(iter);
	}

	// resort
	if (NotifyManager::Instance()->_notifyLayer)
	{
		NotifyManager::Instance()->_notifyLayer->resetNotices();
	}
}