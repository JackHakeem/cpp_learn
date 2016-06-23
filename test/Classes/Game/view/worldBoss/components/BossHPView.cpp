#include "BossHPView.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"

BossHPView::BossHPView()
{

}

BossHPView::~BossHPView()
{

}

bool BossHPView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	_winSize = CCDirector::sharedDirector()->getWinSize();
	this->setIsTouchEnabled(true);
	loadItems();

	return true;
}

void BossHPView::loadItems()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/worldboss/res_worldboss_boss.plist");
	// head picture
	CCSprite * pGrid = new CCSprite();
	if (pGrid)
	{
		bool bGrid = pGrid->initWithSpriteFrameName("peiyang/headbg.png");
		if (bGrid)
		{
			pGrid->setIsRelativeAnchorPoint(true);
			pGrid->setAnchorPoint(ccp(0.5,0.5));
			CCSprite * pHead = new CCSprite();
			bool bHead = pHead->initWithSpriteFrameName("worldboss/head.png");
			if (bHead)
			{
				CCSize size = pGrid->getContentSize();
				pHead->setAnchorPoint(ccp(0.5,0.5));
				pHead->setPosition(ccp(size.width/2 , size.height/2));
				pGrid->addChild(pHead , 0);
				pHead->release();
			}
			pGrid->setPosition(ccp(_winSize.width /2 + POSX(60), _winSize.height /2 + POSX(20)));
			this->addChild(pGrid , 5);
			pGrid->release();
		}
	}

	// name picture
	CCSprite * pName = new CCSprite();
	if (pName)
	{
		bool bName = pName->initWithSpriteFrameName("worldboss/bossname.png");
		if (bName)
		{
			pName->setPosition(ccp(_winSize.width /2 + POSX(180), _winSize.height /2 + POSX(40)));
			this->addChild(pName , 0);
			pName->release();
		}
	}

	CCPoint bloodPos = ccp(_winSize.width /2  + POSX(260), _winSize.height /2);

	// blood progress bar
	CCSprite * pBloodBack = new CCSprite();
	if (pBloodBack)
	{
		bool bBack = pBloodBack->initWithSpriteFrameName("figure/exp_bg.png");
		if (bBack)
		{
			pBloodBack->setScaleX(0.88);
			pBloodBack->setScaleY(1.8);
			pBloodBack->setPosition(bloodPos);
			this->addChild(pBloodBack , 0);
			pBloodBack->release();
		}
	}

	CCProgressTimer * pBloodBar = new CCProgressTimer();
	if (pBloodBar)
	{
		//CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("worldboss/blood.png");
		//if(!pFrame)
		//{
		//	return;
		//}
		bool bBar = pBloodBar->initWithFile("assets/ui/worldboss/blood.png");
		if (bBar)
		{
			pBloodBar->getSprite()->setColor(ccc3(255,0,0));
			pBloodBar->setScaleY(1.8);
			pBloodBar->setPosition(bloodPos);
			pBloodBar->setPercentage(0);
			pBloodBar->setType(CCProgressTimerType(2));
			pBloodBar->setTag(TAG_BloodBar);
			this->addChild(pBloodBar , 1);
			pBloodBar->release();
		}
	}

	//  blood text
	CCLabelTTF * pBloodBarText = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("WBS002").c_str(),
		CCSizeMake(POSX(480) , POSX(30)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(28));
	if (pBloodBarText)
	{
		pBloodBarText->setPosition(bloodPos);
		pBloodBarText->setTag(TAG_BloodText);
		this->addChild(pBloodBarText , 2);
	}
}

void BossHPView::updateHP(float dt , int curhp , int maxhp , float percent)
{
	// 前20分钟服务端传来的血量都是-1 之后才是真实血量
	if(( curhp != -1 ) && ( maxhp != -1 )) 
	{
		float per = (float)curhp / maxhp ;
		CCProgressTimer * pBloodBar = (CCProgressTimer *)this->getChildByTag(TAG_BloodBar);
		if (pBloodBar)
		{
			pBloodBar->setPercentage((1-per) * 100);
		}
		// update blood text
		char path[512] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WBS003").c_str() , curhp);
		CCLabelTTF * pBloodBarText = (CCLabelTTF *)this->getChildByTag(TAG_BloodText);
		if (pBloodBarText)
		{
			pBloodBarText->setString(path);
		}
	}
	else
	{
		CCProgressTimer * pBloodBar = (CCProgressTimer *)this->getChildByTag(TAG_BloodBar);
		if (pBloodBar)
		{
			pBloodBar->setPercentage((1-percent) * 100);
		}
	}
}