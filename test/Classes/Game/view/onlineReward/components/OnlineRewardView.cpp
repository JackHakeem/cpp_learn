#include "OnlineRewardView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "UIListView/CCUIListView.h"
#include "model/onlineReward/OnlineRewardManager.h"
#include "RewardItem.h"
#include "RewardListView.h"
#include "utils/ValuesUtil.h"
#include "model/newhand/NewhandManager.h"
#include "events/GameDispatcher.h"
#include "model/scene/vo/FindVo.h"
#include "view/newhand/components/LeaderAlert.h"


OnlineRewardView::OnlineRewardView() : _pContainer(0)
{
	
}

void OnlineRewardView::close()
{
	PopContainer::close();

	if (NewhandManager::Instance()->_isNewAcount)
	{
		NewHandHandle();
	}	
}

void OnlineRewardView::clickCloseHandler(CCObject * pSender)
{
	PopContainer::clickCloseHandler(pSender);

	if (NewhandManager::Instance()->_isNewAcount)
	{
		NewHandHandle();
	}	
}

bool OnlineRewardView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	setNeedBg(NeedBg_YES);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist");

	this->key = PopEventName::UPSKILL;
	this->setIsTouchEnabled(true);
	this->setAnchorPoint(CCPointZero);
	this->setIsRelativeAnchorPoint(true);

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_viewSize = winSize;

	this->setContentSize(winSize);
	this->setPopContentSize(this->getContentSize());

	addStaic();

	addVListView();

	return true;
}

void OnlineRewardView::addStaic()
{
	if(!_pContainer)
	{
		_pContainer = new CCLayer();
		_pContainer->init();
		_pContainer->setAnchorPoint(CCPointZero);
		_pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER_TOP));
		this->addChild(_pContainer , 1);
		_pContainer->release();
	}

	// title
	{
		CCSprite * pGetedSprite = CCSprite::spriteWithSpriteFrameName("reward/logo.png");
		pGetedSprite->setPosition(ccp(POSX(480) , POSX(585)));
		_pContainer->addChild(pGetedSprite , 1);
	}

	// discribe
	{
		CCLabelTTF * pLabDis = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("RED003").c_str() , CCSizeMake(POSX(840) , POSX(38)) , CCTextAlignmentCenter , "Arial" , POSX(36));
		pLabDis->setColor(ccc3(12,233,25));
		pLabDis->setPosition(ccp(POSX(480) , POSX(530)));
		_pContainer->addChild(pLabDis , 1);
	}

	// back
	{
		CCUIBackground * pBack = new CCUIBackground();
		pBack->initWithSpriteFrame("ui2.png" , CCPointZero , CCPointZero ,CCSizeMake(CCRECT_REWARD_LISTVIEW.size.width + POSX(20) , CCRECT_REWARD_LISTVIEW.size.height + POSX(50)));
		pBack->setPosition(ccpAdd(CCRECT_REWARD_LISTVIEW.origin , ccp(POSX(-10) , POSX(-10))));
		_pContainer->addChild(pBack , 1);
		pBack->release();

		CCSize size = pBack->getContentSize();

		CCLabelTTF * pLabTitle1= CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("RED004").c_str() , CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentCenter , "Arial" , POSX(28));
		pLabTitle1->setColor(ccc3(233,133,25));
		pLabTitle1->setPosition(ccp(POSX(70) , size.height - POSX(20)));
		pBack->addChild(pLabTitle1 , 2);

		CCLabelTTF * pLabTitle2 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("RED005").c_str() , CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentCenter , "Arial" , POSX(28));
		pLabTitle2->setColor(ccc3(233,133,25));
		pLabTitle2->setPosition(ccp(POSX(350) , size.height - POSX(20)));
		pBack->addChild(pLabTitle2 , 2);

		CCLabelTTF * pLabTitle3 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("RED006").c_str() , CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentCenter , "Arial" , POSX(28));
		pLabTitle3->setColor(ccc3(233,133,25));
		pLabTitle3->setPosition(ccp(POSX(650) , size.height - POSX(20)));
		pBack->addChild(pLabTitle3 , 2);
	}	
}

void OnlineRewardView::addVListView()
{
	RewardListView * pListView = new RewardListView();
	if (pListView)
	{
		if (pListView->init())
		{
			pListView->setAnchorPoint(CCPointZero);
			pListView->setTag(Tag_ListView);
			_pContainer->addChild(pListView , 3);
			pListView->load();
			pListView->release();
		}
	}
}

void OnlineRewardView::refreshListView()
{
	if (_pContainer)
	{
		RewardListView * pListView = (RewardListView *)_pContainer->getChildByTag(OnlineRewardView::Tag_ListView);
		if (pListView)
		{
			pListView->refresh();
		}
	}		
}

void OnlineRewardView::NewHandHandle()
{
	NewhandManager::Instance()->_isNewAcount = false;
	
	//LeaderAlert::show("", 3, true, NULL, NULL, NULL); 
	
	// find NPC
	
	FindVo findVo;
	findVo._type = 1;
	findVo._sceneId = 1001;
	findVo._npcId = 1;
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::FIND_ELEMENT, &findVo);
	
}

OnlineRewardView::~OnlineRewardView()
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_icon.plist");
}
