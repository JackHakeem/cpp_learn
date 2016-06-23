#include "NoticeBanner.h"
#include "utils/ScaleUtil.h"
#include "manager/LayerManager.h"
#include "utils/ValuesUtil.h"
#include "KKLabelTTF.h"
#include "manager/GlobalManage.h"
#include "control/AppFacade.h"
#include "view/scene/components/story/callback/StoryFollowNoticeAction.h"
#include "model/scene/StoryProxy.h"

NoticeBanner * g_pSysNotice = 0;

NoticeBanner::NoticeBanner()
{
	setIsRun(false);
	init();
}

NoticeBanner::~NoticeBanner()
{
	this->cleanup();
	this->removeAllChildrenWithCleanup(true);
	//this->removeFromParentAndCleanup(true);
}

bool NoticeBanner::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	this->setIsTouchEnabled(false);
	this->setAnchorPoint(ccp(0.5, 0.5));
	this->setContentSize(CCSizeMake(POSX(960), POSX(40)));
	this->setPosition(ccp(size.width / 2, size.height-POSX(150)));

	initView();
	
	return true;
}

void NoticeBanner::initView()
{
	CCSprite * pBackSprite = new CCSprite();
	if (pBackSprite)
	{
		if (pBackSprite->initWithFile("assets/ui/notice.png"))
		{
			pBackSprite->setTag(TAG_Background_Sprite);
			pBackSprite->setAnchorPoint(ccp(0.5,0.5));
            pBackSprite->setPosition(CCPointZero);
			pBackSprite->setScaleY(1.1);
			pBackSprite->setOpacity(255);
			this->addChild(pBackSprite);
		}
		pBackSprite->release();
	}
}

void NoticeBanner::reLoadNotice()
{
	if (!LayerManager::tipsLayer)
	{
		return;
	}
	
	this->setIsVisible(true);

	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_SysNotice))
	{
		//LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTag_Broadcast_Notice,true);
		return;
	}

	LayerManager::tipsLayer->addChild( this, TipsLayer::TipsLayerZ_SysNotice, TipsLayer::TipsLayerTAG_SysNotice);
	this->release();

}

void NoticeBanner::removeNotice()
{
	this->setIsVisible(false);

	if (this->getChildByTag(TAG_Content_Text))
	{
		this->removeChildByTag(TAG_Content_Text,true);
	}
}

void NoticeBanner::addNormalMessage(MAPSTRCOLOR msg, int time)
{
	if (time <= 0) { return;	}
	for (int i = 0;i < time ; i++)
	{
		_messageDic.push_back(msg);
	}

	checkAndRun();
}

void NoticeBanner::addPriorityMessage(MAPSTRCOLOR msg, int time)
{
	if (time <= 0) { return;	}
	for (int i = 0;i < time ; i++)
	{
		_messageDic.push_front(msg);
	}

	checkAndRun();
}

void NoticeBanner::checkAndRun()
{
	if (g_pGlobalManage->isInStory)
	{
		StoryProxy * pStoryProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
		if (pStoryProxy)
		{
			pStoryProxy->storyCallbackActionList.push_back((IAction *)new StoryFollowNoticeAction());
		}
		return;
	}

	if (!getIsRun())
	{
		run();
	}	
}

void NoticeBanner::showContent(MAPSTRCOLOR contentList)
{
	KKLabelTTF * pContentLabel = (KKLabelTTF *)this->getChildByTag(TAG_Content_Text);
	if (pContentLabel)
	{
		this->removeChildByTag(TAG_Content_Text,true);
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	pContentLabel = new KKLabelTTF();
	pContentLabel->init(30,30, CCSizeMake(4096, 40));
	pContentLabel->setAnchorPoint(ccp(0.5,0.5));

	MAPSTRCOLOR::iterator iter = contentList.begin();
	for (;iter!=contentList.end();iter++)
	{
		int len = iter->first.length();
		std::string str = iter->first.substr(2,len-1);
		pContentLabel->add(str,iter->second,false);
	}

	pContentLabel->setTag(TAG_Content_Text);

	if (pContentLabel->m_fCurTotleLabelPixelWidth <= winSize.width)
	{
		pContentLabel->setPosition(ccp( - pContentLabel->m_fCurMAXLabelPixelWidth / 2, - POSX(17)));
	}
	else
	{
		float deltaWidth = pContentLabel->m_fCurTotleLabelPixelWidth/2 - (winSize.width)/2 + winSize.width * 0.3f;
		CCPoint pos = ccp( - pContentLabel->m_fCurMAXLabelPixelWidth / 2 + deltaWidth , - POSX(17));
		pContentLabel->setPosition(pos);
		CCFiniteTimeAction * pAction = CCMoveTo::actionWithDuration(5.0f , ccp(pos.x - deltaWidth - winSize.width * 0.7 , - POSX(17)));
		pContentLabel->runAction(pAction);
	}
	pContentLabel->setAnchorPoint(ccp(0.5, 0.5));
	this->addChild(pContentLabel,1);
	pContentLabel->release();
}

CCFiniteTimeAction * NoticeBanner::getAction()
{
	CCActionInterval*  actionFadeIn = cocos2d::CCFadeTo::actionWithDuration(0.5f, 255);//µ­Èë
	CCActionInterval*  actionMove = CCMoveBy::actionWithDuration(4.0f, ccp(0,0));//Î»ÒÆ
	CCActionInterval*  actionFadeout = cocos2d::CCFadeOut::actionWithDuration(0.5f);//µ­³ö
	CCFiniteTimeAction * pAction = CCSequence::actions(actionFadeIn,actionMove,actionFadeout,0);
	return pAction;
}

void NoticeBanner::playAction()
{
	KKLabelTTF * pLabelText = (KKLabelTTF *)this->getChildByTag(TAG_Content_Text);
	if (pLabelText)
	{
		

		CCArray * objArr = pLabelText->getChildren();
		int count = pLabelText->getChildrenCount();
		for (int i = 0; i< count ; i++)
		{
			CCLabelTTF * pText = (CCLabelTTF * )objArr->objectAtIndex(i);
			if (pText)
			{
				CCFiniteTimeAction * pAction = getAction();
				pText->setOpacity(0);
				pText->runAction(pAction);
			}
		}
	}
}

void NoticeBanner::play(ccTime dt)
{
	if(!_messageDic.empty())
	{
		reLoadNotice();

		MAPSTRCOLOR strColorMap = _messageDic.front();
		showContent(strColorMap);

		playAction();

		_messageDic.pop_front();

	}
	else
	{
		removeNotice();

		setIsRun(false);

		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(NoticeBanner::play),this);
	}
}

void NoticeBanner::run()
{
	play(0);
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(NoticeBanner::play),this,5.0f,false);

	setIsRun(true);
}
