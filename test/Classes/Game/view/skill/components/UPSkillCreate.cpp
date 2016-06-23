#include "UPSkillCreate.h"
#include "UpSkillView.h"
#include "manager/ViewManager.h"
#include "manager/TouchLayerEnum.h"

UPSkillCreate * g_pPassiveSkillScrollView = 0;
UPSkillCreate * g_pFormationScrollView = 0;
UPSkillCreate * g_pTalentScrollView = 0;

UPSkillCreate::UPSkillCreate(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	_curLightIndex = 0;
	setTouchStat(STATE_TOUCH_0);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/upskill/res_upskill.plist");
	spriteLight = CCSprite::spriteWithSpriteFrameName("upskill/select.png");
	//spriteLight->setAnchorPoint(CCPointZero);
	if (spriteLight)
	{
		spriteLight->setIsVisible(false);
		this->addChild(spriteLight);
	}

	_curLightPos = ccp(POSX(54) , POSX(390));
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/upskill/res_upskill.plist");
}

UPSkillCreate* UPSkillCreate::UPSkillScrollViewWithCCRect(const CCRect& mRect)
{
	UPSkillCreate *pScrollView = new UPSkillCreate(mRect);
	if(pScrollView && pScrollView->init()){
		pScrollView->setIsTouchEnabled(false);//That may not be the touch
		return pScrollView;
	}
	CC_SAFE_DELETE(pScrollView)
		return NULL;
}

void UPSkillCreate::registerWithTouchDispatcher()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_UpskillView, true);
}

 bool UPSkillCreate::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
 {
     //Doyang 20120924
     CCPoint locationInView = pTouch->locationInView(pTouch->view());
     mTouchBeganPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

 	return CCUIPartialScrollView::ccTouchBegan(pTouch, pEvent);
 }

void UPSkillCreate::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    //Doyang 20120924
    CCPoint locationInView = pTouch->locationInView(pTouch->view());
    CCPoint movePoint = CCDirector::sharedDirector()->convertToGL(locationInView);
    if(abs(mTouchBeganPoint.x - movePoint.x) < 5)
    {
        return ;
    }

	if (spriteLight)
	{
		spriteLight->setIsVisible(false);
	}
	this->CCUIPartialScrollView::ccTouchMoved(pTouch,pEvent);
	setTouchStat(STATE_TOUCH_1);
}

void UPSkillCreate::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	CCPoint touchPoint = pTouch->locationInView(pTouch->view());
	touchPoint = CCDirector::sharedDirector()->convertToGL(touchPoint);

	//
	UpSkillView * pSkillView = ViewManager::getInstance()->_upSkillView;
	if (!pSkillView)
	{
		setTouchStat(STATE_TOUCH_0);
		this->CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);
		return;
	}

	//	
	if (!currentScreen)
	{
		this->CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);
		setTouchStat(STATE_TOUCH_0);
		return;
	}

	//
	if (getTouchStat() == STATE_TOUCH_1)
	{
		this->CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);

		pSkillView->updateDirections(pSkillView->_curSelectTab); // refresh page show

		setTouchStat(STATE_TOUCH_0);
		return;
	}	

	//
	int page = currentScreen-1;
	CCLayer * pScrollLayer = getLayerByTag(page);
	for (int i = 0;i<UPSKILL_NUM_PER_PAGE;i++)
	{
		if (!pScrollLayer)
		{
			this->CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);
			setTouchStat(STATE_TOUCH_0);
			return;
		}
		_curLightIndex = i+page*UPSKILL_NUM_PER_PAGE;
		UPSkillItem * pSkillItem = (UPSkillItem *)pScrollLayer->getChildByTag(_curLightIndex);
		if (!pSkillItem)
		{
			this->CCUIPartialScrollView::ccTouchEnded(pTouch,pEvent);
			setTouchStat(STATE_TOUCH_0);
			return;
		}
		_curLightPos = pSkillItem->getPosition();
		CCPoint p = getScreenPos(pSkillItem);
		float w = POSX(98); //pSkillItem->getContentSize().width;
		float h = POSX(98); //pSkillItem->getContentSize().height;
		if (CCRect::CCRectContainsPoint(CCRectMake(p.x-w/2,p.y-h/2,w,h),touchPoint))
		{
			if (spriteLight)
			{
				spriteLight->setIsVisible(true);
				spriteLight->setPosition(_curLightPos);
			}
			pSkillView->_curSelectedItemTag = i+page*UPSKILL_NUM_PER_PAGE;

			if (pSkillItem->_info)
			{
				if ( pSkillView->_curSelectTab == UpSkillView::TAB_PASSIVE )
				{
					if ( ( pSkillItem->_info->lev >= UpSkillView::MAX_SKILL_LEVEL ) )
					{
						pSkillView->enableButton(UpSkillView::TAG_BTN_UPGRADE,false);
					}
					else{pSkillView->enableButton(UpSkillView::TAG_BTN_UPGRADE,true);}
				}
				else if ( pSkillView->_curSelectTab == UpSkillView::TAG_FORMATION )
				{
					if ( ( pSkillItem->_info->lev >= UpSkillView::MAX_FORMATION_LEVEL ) )
					{
						pSkillView->enableButton(UpSkillView::TAG_BTN_UPGRADE,false);
					}
					else{pSkillView->enableButton(UpSkillView::TAG_BTN_UPGRADE,true);}
				}

				pSkillView->loadUPSkillTips(pSkillItem->_info);
			}

			break;
		}
	}
	setTouchStat(STATE_TOUCH_0);
}

void UPSkillCreate::setHightLight(bool bVar)
{
	if (spriteLight)
	{
		spriteLight->setIsVisible(bVar);
		spriteLight->setPosition(_curLightPos);
	}
}