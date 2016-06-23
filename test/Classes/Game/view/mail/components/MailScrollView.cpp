#include "MailScrollView.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "BaseType.h"
#include "MailItem.h"
#include "control/AppFacade.h"
#include "../MailMediator.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"
#include "MailView.h"

#define Item_width (POSX(300))
#define Item_Height (POSX(60))

#define Item_Num_perPage (6)

MailScrollView::~MailScrollView()
{

}

MailScrollView::MailScrollView(const CCRect & ccRect):CCUIPartialScrollView(ccRect)
{

}

MailScrollView * MailScrollView::scrollViewWithCCRect(const CCRect & ccRect)
{
	MailScrollView *pScrollView = new MailScrollView(ccRect);
	if(pScrollView && pScrollView->init())
	{
		pScrollView->setIsTouchEnabled(false);
		//pScrollView->autorelease();
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
	return NULL;
}

void MailScrollView::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,TLE::WindowLayer_MailView,true);
}

bool MailScrollView::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    //Doyang 20120924
    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    mTouchBeganPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	setTouchState(touch_state_0);
	setCurScreen(currentScreen);
	CCPoint TouchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	CCPoint pos = getScreenPos(this);
	CCRect rect = cocos2d::CCRect(pos.x,pos.y,scrollWidth,scrollHeight);
	if (CCRect::CCRectContainsPoint(rect,pos))
	{
		return CCUIPartialScrollView::ccTouchBegan(pTouch,pEvent);
	}
	return false;	
}

void MailScrollView::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //Doyang 20120924
    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(locationInView);
    if(abs(mTouchBeganPoint.x - movePoint.x) < 5)
    {
        return ;
    }
	setTouchState(touch_state_2);
	setCurScreen(currentScreen);
	CCPoint TouchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	CCUIPartialScrollView::ccTouchMoved(pTouch,pEvent);
}

void MailScrollView::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint TouchPoint = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
	if (getTouchState() == touch_state_2)
	{
		CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);

		// update page num
		// add code here

		MailView * pMailView = ViewManager::getInstance()->_mailView;
		if (pMailView && pMailView->getisPop())
		{
			pMailView->setCurPage(currentScreen);
			pMailView->setPageText(currentScreen,totalScreens);

			if (getCurScreen() != currentScreen)
			{
				setCurScreen(currentScreen);
				pMailView->showHightLight(false,CCPointZero);

				MailContentVo contentVo;
				pMailView->resetReadPanel(contentVo);
			}
		}

		return;
	}
	else if (getTouchState() == touch_state_0)
	{
		int nIndex;
		MailItem * pMailItem = (MailItem *)getTouchItemAndIndexByPos( TouchPoint, &nIndex );
		if (!pMailItem){return;	}
		int mailId = pMailItem->_headVo.mailId;
		MailMediator * pMailMediator = (MailMediator *)g_pFacade->retrieveMediator(AppFacade_Mail_Mediator);
		if (pMailMediator)
		{
			pMailMediator->onMailItemClick(mailId);
		}
		MailView * pMailView = ViewManager::getInstance()->_mailView;
		if (pMailView && pMailView->getisPop())
		{
			pMailView->setMailId(mailId);
			pMailView->setCurPage(currentScreen);
			pMailView->showReadLayer();
			pMailView->showHightLight(true,pMailItem->getPosition());
			pMailView->enableInput(false,false,false);
		}
	}
}

CCNode* MailScrollView::getTouchItemAndIndexByPos( CCPoint point, int* posIndex )
{
	CCSize size = CCSizeMake(Item_width,Item_Height);
	CCRect rect;

	int page = this->currentScreen-1;
	if (page < 0)	{return 0;	}

	CCNode * pNode = this->getLayerByTag(page);
	if (!pNode)	{	return 0;}

	for (int i = 0; i < Item_Num_perPage; i++)
	{
		CCNode * pNodeItem = pNode->getChildByTag( i);
		if (!pNodeItem)	{	break;}
		CCPoint pos = getScreenPos(pNodeItem);
		rect = CCRect(pos.x -size.width/2 ,pos.y - size.height/2,size.width,size.height);
		if (CCRect::CCRectContainsPoint(rect,point))
		{
			*posIndex =  page*Item_Num_perPage + i;
			return pNodeItem;
		}
	}
	return 0;
}
