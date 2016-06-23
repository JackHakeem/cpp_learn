#include "ChatBtnMenu.h"
#include "view/mainUI/components/MainNavigate.h"
#include "manager/LayerManager.h"
#include "view/chat/components/ChatView.h"

ChatBtnMenu::ChatBtnMenu()
{
	timer = 0.0f;
}

ChatBtnMenu::~ChatBtnMenu()
{}

ChatBtnMenu * ChatBtnMenu::menuWithItems(CCMenuItem* item, ...)
{
	va_list args;
	va_start(args,item);
	ChatBtnMenu *pRet = new ChatBtnMenu();
	if (pRet && pRet->initWithItems(item, args))
	{
		pRet->autorelease();
		va_end(args);
		return pRet;
	}
	va_end(args);
	CC_SAFE_DELETE(pRet)
	return NULL;
}

ChatBtnMenu* ChatBtnMenu::menuWithItem(CCMenuItem* item)
{
	return menuWithItems(item, NULL);
}


bool ChatBtnMenu::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CC_UNUSED_PARAM(event);
	//if (this->itemForTouch(touch))
	//	m_kState = 1;
	if (m_eState != kCCMenuStateWaiting || ! m_bIsVisible)
	{
		return false;
	}

	for (CCNode *c = this->m_pParent; c != NULL; c = c->getParent())
	{
		if (c->getIsVisible() == false)
		{
			return false;
		}
	}

	m_pSelectedItem = this->itemForTouch(touch);
	if (m_pSelectedItem)
	{
		m_eState = kCCMenuStateTrackingTouch;
		m_pSelectedItem->selected();
		return true;
	}
	return false;
}

bool ChatBtnMenu::initWithItems(CCMenuItem* item, va_list args)
{
    if (init())
    {
        int z=0;

		if (item)
		{
			this->addChild(item, z);
			CCMenuItem *i = va_arg(args, CCMenuItem*);
			while (i)
			{
				z++;
				this->addChild(i, z);
				i = va_arg(args, CCMenuItem*);
			}
		}

		return true;
    }
    return false;
}

void ChatBtnMenu::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
    CC_UNUSED_PARAM(touch);
    CC_UNUSED_PARAM(event);
	if (m_eState == kCCMenuStateWaiting)
	{
		return;
	}
	m_kState = 0;
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (m_pSelectedItem)
	{
		m_pSelectedItem->unselected();
		m_pSelectedItem->activate();
	}
	m_eState = kCCMenuStateWaiting;
}

void ChatBtnMenu::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	return;
    CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
	CCMenuItem *currentItem = this->itemForTouch(touch);
	if (currentItem != m_pSelectedItem) 
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
		}
		m_pSelectedItem = currentItem;
		if (m_pSelectedItem)
		{
			m_pSelectedItem->selected();
		}
	}
}

bool ChatBtnMenu::init()
{
    if (CCLayer::init())
    {
		setTouchLayer(99999);//kCCMenuTouchPriority

        this->m_bIsTouchEnabled = true;//KEVINCHANGE this->m_bIsTouchEnabled = true;

        // menu in the center of the screen
        CCSize s = CCDirector::sharedDirector()->getWinSize();

        this->m_bIsRelativeAnchorPoint = false;
        setAnchorPoint(ccp(0.5f, 0.5f));
        this->setContentSize(s);

        // XXX: in v0.7, winSize should return the visible size
        // XXX: so the bar calculation should be done there
        CCRect r;
        CCApplication::sharedApplication().statusBarFrame(&r);
        ccDeviceOrientation orientation = CCDirector::sharedDirector()->getDeviceOrientation();
        if (orientation == CCDeviceOrientationLandscapeLeft || orientation == CCDeviceOrientationLandscapeRight)
        {
            s.height -= r.size.width;
        }
        else
        {
            s.height -= r.size.height;
        }
        setPosition(ccp(s.width/2, s.height/2));
        //	[self alignItemsVertically];
        m_pSelectedItem = NULL;
        m_eState = kCCMenuStateWaiting;

		schedule (schedule_selector(ChatBtnMenu::step), 0.1f);
        return true;
    }
    return false;
}



void ChatBtnMenu::step(float dt)
{
	
	if (m_pSelectedItem && m_pSelectedItem->getIsSelected() == true)
	{
		timer+=dt;
		if (timer >= 0.6f)
		{
			timer = 0.0f;
			//按钮变回一态
			m_kState = 0;
			CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
			if (m_pSelectedItem)
			{
				m_pSelectedItem->unselected();
			//	m_pSelectedItem->activate();
				
				//使聊天泡泡打开或者关闭
				
				
				ChatView* chatview = (ChatView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_chatView);
				if (chatview)
				{
					if (chatview->_hide)
					{//需要上升
						chatview->_hide = false;
						chatview->stopAllActions();
						CCActionInterval *action1 = CCEaseOut::actionWithAction(CCMoveTo::actionWithDuration(0.3f, ccp(chatview->getPosition().x, 18)), 2);
						CCActionInterval *action2 = CCMoveTo::actionWithDuration(0.1, ccp(chatview->getPosition().x, 0));
						CCAction* dstAction = cocos2d::CCSequence::actions(action1, action2,0);
						chatview->runAction(dstAction);
						chatview->_pKKListView->setIsVisible(true);
					}
					else
					{//需要下降
						chatview->_hide = true;
						chatview->stopAllActions();
						CCActionInterval *action1 = CCEaseIn::actionWithAction(CCMoveTo::actionWithDuration(0.2f, ccp(chatview->getPosition().x, -400)), 2);
						//CCActionInterval *action2 = CCMoveTo::actionWithDuration(0.1, ccp(chatview->getPosition().x, 0));
						CCAction* dstAction = cocos2d::CCSequence::actions(action1, /*action2,*/0);
						chatview->runAction(dstAction);
						chatview->_pKKListView->setIsVisible(false);
					}
				}
				
			}
			m_eState = kCCMenuStateWaiting;
			
		}
	}
}