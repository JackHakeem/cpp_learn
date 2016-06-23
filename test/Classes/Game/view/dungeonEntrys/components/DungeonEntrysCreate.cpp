#include "DungeonEntrysCreate.h"
#include "../DungeonEntrysMediator.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/ViewManager.h"
#include "manager/LevLimitConst.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/NewhandConst.h"

//DungeonEntrysCreate::DungeonEntrysCreate()
//{
//
//}

DungeonEntrysCreate::DungeonEntrysCreate(const CCRect& mRect):CCUIPartialScrollView(mRect)
{
	m_pri = TLE::WindowLayer_CopyMap+1;
	_btChallengeEnter = 0;
	_btStoryEnter = 0;
	btDragonTowerEnter = 0;
	btWorldBossEnter = 0;
	//CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, , true);
}

void DungeonEntrysCreate::addDungeonEntries()
{
	CCLayer * layer = this->getLayerByTag(0);
	if(!layer)
		return;
	const CCSize size = CCSizeMake(POSX(163.0f), POSX(481.0f));
	//distance between two item
	const float dist = POSX(18.0f);
	//5 item in every page, position i mean position of item i in every page
	const CCPoint pos[5] = {
		ccp(1 * dist + 0 * size.width + size.width / 2.0f, size.height / 2.0f),
		ccp(2 * dist + 1 * size.width + size.width / 2.0f, size.height / 2.0f),
		ccp(3 * dist + 2 * size.width + size.width / 2.0f, size.height / 2.0f),
		ccp(4 * dist + 3 * size.width + size.width / 2.0f, size.height / 2.0f),
		ccp(5 * dist + 4 * size.width + size.width / 2.0f, size.height / 2.0f)
	};

	int iLay = 0;
	CCSize btSize;
	CCSprite* spStoryEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
	if(spStoryEnter)
	{
		layer->addChild(spStoryEnter);
		spStoryEnter->setPosition(pos[iLay]);
	}
	CCSprite *pStoryNormalSprite = CCSprite::spriteWithSpriteFrameName("entrance/storyEntrance.png");
	CCSprite *pStoryPressedSprite = CCSprite::spriteWithSpriteFrameName("entrance/storyEntrance.png");
	//CCMenuItemSprite *btStoryEnter = CCMenuItemSprite::itemFromNormalSprite(
	_btStoryEnter = CCMenuItemSprite::itemFromNormalSprite(
		pStoryNormalSprite,
		pStoryPressedSprite,
		this, 
		menu_selector(DungeonEntrysCreate::onClickStoryEnterBtn));
	if(_btStoryEnter)
	{
		btSize = _btStoryEnter->getContentSize();
		CCMenu *bmStoryEnter = CCMenu::menuWithItems(_btStoryEnter, NULL);
		if(bmStoryEnter)
		{
			bmStoryEnter->setPosition(CCPointZero);
			_btStoryEnter->setPosition(pos[iLay]);
			bmStoryEnter->setTouchLayer(TLE::WindowLayer_CopyMap);
			layer->addChild(bmStoryEnter);
		}
	}

	CCLabelTTF* lableStory = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SCENAME001").c_str(), 
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter, 
		"Arial",
		POSX(20));
	if(lableStory)
	{
		lableStory->setPosition(ccp(pos[iLay].x, pos[iLay].y - btSize.height / 2));
		layer->addChild(lableStory);
	}

	///////////////////////////////////////////
	iLay++;
	CCSprite* spChallengeEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
	if(spChallengeEnter)
	{
		layer->addChild(spChallengeEnter);
		CCSize size = spChallengeEnter->getContentSize();
		spChallengeEnter->setPosition(pos[iLay]);
	}
	CCSprite *pChallengeNormalSprite = CCSprite::spriteWithSpriteFrameName("entrance/Challenge.png");
	CCSprite *pChallengePressedSprite = CCSprite::spriteWithSpriteFrameName("entrance/Challenge.png");
	//CCMenuItemSprite *btChallengeEnter = CCMenuItemSprite::itemFromNormalSprite(
	_btChallengeEnter = CCMenuItemSprite::itemFromNormalSprite(
		pChallengeNormalSprite,
		pChallengePressedSprite,
		this,
		menu_selector(DungeonEntrysCreate::onClickChallengeEnterBtn));

	if(_btChallengeEnter)
	{
		btSize = _btChallengeEnter->getContentSize();
		CCMenu *bmChallengeEnter = CCMenu::menuWithItems(_btChallengeEnter, NULL);
		if(bmChallengeEnter)
		{
			bmChallengeEnter->setPosition(CCPointZero);
			_btChallengeEnter->setPosition(pos[iLay]);
			bmChallengeEnter->setTouchLayer(TLE::WindowLayer_CopyMap);
			layer->addChild(bmChallengeEnter);
		}
	}

	CCLabelTTF* lableCHallenge = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SCENAME002").c_str(),
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	if(lableCHallenge)
	{
		lableCHallenge->setPosition(ccp(pos[iLay].x, pos[iLay].y - btSize.height / 2));
		layer->addChild(lableCHallenge);
	}
	////////////////////////////////////////////
	//iLay++;
	CCSprite* spLairEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
	if(spLairEnter)
	{
		layer->addChild(spLairEnter);
		spLairEnter->setIsVisible(false);
		CCSize size = spLairEnter->getContentSize();
		spLairEnter->setPosition(pos[iLay]);
	}
	CCSprite *pLairNormalSprite = CCSprite::spriteWithSpriteFrameName("entrance/chaoxue.png");
	CCSprite *pLairPressedSprite = CCSprite::spriteWithSpriteFrameName("entrance/chaoxue.png");
	CCMenuItemSprite *btLairEnter = CCMenuItemSprite::itemFromNormalSprite(
		pLairNormalSprite,
		pLairPressedSprite,
		this, 
		menu_selector(DungeonEntrysCreate::onClickLairEnterBtn));
	if(btLairEnter)
	{
		CCMenu *bmLairEnter = CCMenu::menuWithItems(btLairEnter, NULL);
		if(bmLairEnter)
		{
			bmLairEnter->setPosition(CCPointZero);
			btLairEnter->setPosition(pos[iLay]);
			bmLairEnter->setTouchLayer(TLE::WindowLayer_CopyMap);
			bmLairEnter->setIsVisible(false);
			layer->addChild(bmLairEnter);
		}
	}

	/////////////////////////////////////
	iLay++;
	CCSprite* spDragonTowerEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
	if(spDragonTowerEnter)
	{
		layer->addChild(spDragonTowerEnter);
		//spDragonTowerEnter->setIsVisible(false);
		CCSize size = spDragonTowerEnter->getContentSize();
		spDragonTowerEnter->setPosition(pos[iLay]);
	}
	CCSprite *pDragonTowerNormalSprite = CCSprite::spriteWithSpriteFrameName("entrance/huanlongTower.png");
	CCSprite *pDragonTowerPressedSprite = CCSprite::spriteWithSpriteFrameName("entrance/huanlongTower.png");
	btDragonTowerEnter = CCMenuItemSprite::itemFromNormalSprite(
		pDragonTowerNormalSprite,
		pDragonTowerPressedSprite,
		this, 
		menu_selector(DungeonEntrysCreate::onClickDragonTowerEnterBtn));
	if(btDragonTowerEnter)
	{
		btSize = btDragonTowerEnter->getContentSize();
		CCMenu *bmDragonTowerEnter = CCMenu::menuWithItems(btDragonTowerEnter, NULL);
		if(bmDragonTowerEnter)
		{
			bmDragonTowerEnter->setPosition(CCPointZero);
			btDragonTowerEnter->setPosition(pos[iLay]);
			bmDragonTowerEnter->setTouchLayer(TLE::WindowLayer_CopyMap);
			//bmDragonTowerEnter->setIsVisible(false);
			layer->addChild(bmDragonTowerEnter);
		}
	}
	CCLabelTTF* lableTower = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("SCENAME0010").c_str(),
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	if(lableTower)
	{
		lableTower->setPosition(ccp(pos[iLay].x,
			pos[iLay].y - btSize.height / 2));
		layer->addChild(lableTower);
	}
	lableTower = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("TOWR069").c_str(),
		CCSizeMake(POSX(160), POSX(90)),
		CCTextAlignmentLeft,
		"Arial",
		POSX(20));
	if(lableTower)
	{
		lableTower->setColor( ccc3(255,192,0) );
		lableTower->setPosition(ccp(pos[iLay].x,
			pos[iLay].y - btSize.height / 2 - POSX(70)));
		layer->addChild(lableTower);
	}
	//////////////////////////////////////////
	iLay++;
	CCSprite* spWorldBossEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
	if(spWorldBossEnter)
	{
		layer->addChild(spWorldBossEnter);
		spWorldBossEnter->setIsVisible(true);
		CCSize size = spWorldBossEnter->getContentSize();
		spWorldBossEnter->setPosition(pos[iLay]);
	}
	CCSprite *pWorldBossNormalSprite = CCSprite::spriteWithSpriteFrameName("entrance/worldBoss.png");
	CCSprite *pWorldBossPressedSprite = CCSprite::spriteWithSpriteFrameName("entrance/worldBoss.png");
	btWorldBossEnter = CCMenuItemSprite::itemFromNormalSprite(
		pWorldBossNormalSprite,
		pWorldBossPressedSprite,
		this, 
		menu_selector(DungeonEntrysCreate::onClickWorldBossEnterBtn));

	if(btWorldBossEnter)
	{
		btSize = btWorldBossEnter->getContentSize();
		CCMenu *bmWorldBossEnter = CCMenu::menuWithItems(btWorldBossEnter, NULL);
		if(bmWorldBossEnter)
		{
			bmWorldBossEnter->setPosition(CCPointZero);
			btWorldBossEnter->setPosition(pos[iLay]);
			bmWorldBossEnter->setTouchLayer(TLE::WindowLayer_CopyMap);
			bmWorldBossEnter->setIsVisible(true);
			layer->addChild(bmWorldBossEnter);
		}
	}

	CCLabelTTF* lableWorldBoss = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SCENAME003").c_str(),
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	if(lableWorldBoss)
	{
		lableWorldBoss->setPosition(ccp(pos[iLay].x, pos[iLay].y - btSize.height / 2));
		layer->addChild(lableWorldBoss);
	}

	CCLabelTTF* lableWorldBossTime = CCLabelTTF::labelWithString("",
		CCSizeMake(POSX(160), POSX(90)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	if(lableWorldBossTime)
	{
		lableWorldBossTime->setColor(ccc3(12,233,25));
		ViewManager::getInstance()->_WorldBossOpenTimeText = lableWorldBossTime;
		lableWorldBossTime->setPosition(ccp(pos[iLay].x, pos[iLay].y - btSize.height / 2 - POSX(60)));
		lableWorldBossTime->setTag(TAG_WorldBossTime);
		layer->addChild(lableWorldBossTime);
	}
	/////////////////////////////////
	iLay++;
	CCSprite* spSilverMineEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
	if(spSilverMineEnter)
	{
		layer->addChild(spSilverMineEnter);
		spSilverMineEnter->setIsVisible(true);
		CCSize size = spSilverMineEnter->getContentSize();
		spSilverMineEnter->setPosition(pos[iLay]);
	}
	CCSprite *pSilverMineNormalSprite = CCSprite::spriteWithSpriteFrameName("entrance/silverMine.png");
	CCSprite *pSilverMinePressedSprite = CCSprite::spriteWithSpriteFrameName("entrance/silverMine.png");
	CCMenuItemSprite *btSilverMineEnter = CCMenuItemSprite::itemFromNormalSprite(
		pSilverMineNormalSprite,
		pSilverMinePressedSprite,
		this, 
		menu_selector(DungeonEntrysCreate::onClickSilverMineEnterBtn));
	
	if(btSilverMineEnter)
	{
		btSize = btSilverMineEnter->getContentSize();
		CCMenu *bmSilverMineEnter = CCMenu::menuWithItems(btSilverMineEnter, NULL);
		if(bmSilverMineEnter)
		{
			bmSilverMineEnter->setPosition(CCPointZero);
			btSilverMineEnter->setPosition(pos[iLay]);
			bmSilverMineEnter->setTouchLayer(TLE::WindowLayer_CopyMap-100);
			bmSilverMineEnter->setIsVisible(true);
			layer->addChild(bmSilverMineEnter);
		}
	}

	CCLabelTTF* lableSilverMineEnter = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SCENAME004").c_str(),
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	if(lableSilverMineEnter)
	{
		lableSilverMineEnter->setPosition(ccp(pos[iLay].x, pos[iLay].y - btSize.height / 2));
		layer->addChild(lableSilverMineEnter);
		lableSilverMineEnter->setIsVisible(true);
	}

	CCLabelTTF* lableSilverMineEnterTime = CCLabelTTF::labelWithString("",
		CCSizeMake(POSX(160), POSX(90)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	if(lableSilverMineEnterTime)
	{
		ViewManager::getInstance()->_SilverMineEnterTimeText = lableSilverMineEnterTime;
		lableSilverMineEnterTime->setPosition(ccp(pos[iLay].x, pos[iLay].y - btSize.height / 2 - POSX(60)));
		lableSilverMineEnterTime->setTag(TAG_SilverMineTime);
		layer->addChild(lableSilverMineEnterTime);
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//the second page
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	layer = this->addLayerByTag(1); //add second page
	//Begin Kenfly 20121213 : add ranking entrance
	///////////////////////////////////////
	iLay = 0; //pos; 0 1 2 3 4
	CCSprite* spRankingEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
	if(spRankingEnter)
	{
		layer->addChild(spRankingEnter);
		spRankingEnter->setPosition(pos[iLay]);
	}
	CCSprite *spRankingNormal = CCSprite::spriteWithFile("assets/ui/entrance/ranking.png");
	CCSprite *spRankingPressed = CCSprite::spriteWithFile("assets/ui/entrance/ranking.png");
	CCMenuItemSprite *btRankingEnter = CCMenuItemSprite::itemFromNormalSprite(
		spRankingNormal,
		spRankingPressed,
		this, 
		menu_selector(DungeonEntrysCreate::onClickRankingEnterBtn));

	if(btRankingEnter)
	{
		btSize = btRankingEnter->getContentSize();
		CCMenu *bmRankingEnter = CCMenu::menuWithItems(btRankingEnter, NULL);
		if(bmRankingEnter)
		{
			bmRankingEnter->setPosition(CCPointZero);
			btRankingEnter->setPosition(pos[iLay]);
			bmRankingEnter->setTouchLayer(TLE::WindowLayer_CopyMap - 100);
			//bmDragonTowerEnter->setIsVisible(false);
			layer->addChild(bmRankingEnter);
		}
	}
	CCLabelTTF* lableRanking = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("SCENAME005").c_str(),
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	if(lableRanking)
	{
		lableRanking->setPosition(ccp(pos[iLay].x,
			pos[iLay].y - btSize.height / 2));
		layer->addChild(lableRanking);
	}

	//End Kenfly 20121213
<<<<<<< .mine
	///=>add by hwj campfight entrance
	iLay = 1;
	CCSprite* spCampFightEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
	if(spCampFightEnter)
	{
		layer->addChild(spCampFightEnter);
		//spDragonTowerEnter->setIsVisible(false);
		CCSize size = spCampFightEnter->getContentSize();
		spCampFightEnter->setPosition(ccp(size.width / 2 + size.width * iLay, size.height / 2));
	}
	CCSprite *spCampFightNormal = CCSprite::spriteWithFile("assets/ui/entrance/campFight.png");
	CCSprite *spCampFightPressed = CCSprite::spriteWithFile("assets/ui/entrance/campFight.png");
	CCMenuItemSprite *btCampFightEnter = CCMenuItemSprite::itemFromNormalSprite(
		spCampFightNormal,
		spCampFightPressed,
		this, 
		menu_selector(DungeonEntrysCreate::onClickCampFightEnterBtn));


	if(btCampFightEnter)
	{
		btSize = btCampFightEnter->getContentSize();
		CCMenu *bmCampFightEnter = CCMenu::menuWithItems(btCampFightEnter, NULL);
		if(bmCampFightEnter)
		{
			bmCampFightEnter->setPosition(CCPointZero);
			btCampFightEnter->setPosition(ccp(size.width / 2 + size.width * iLay, size.height / 2));
			bmCampFightEnter->setTouchLayer(TLE::WindowLayer_CopyMap - 100);
			//bmDragonTowerEnter->setIsVisible(false);
			layer->addChild(bmCampFightEnter);
		}
	}
	CCLabelTTF* lableCampFight = CCLabelTTF::labelWithString(
		ValuesUtil::Instance()->getString("SCENAME006").c_str(),
		CCSizeMake(POSX(200), POSX(20)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(20));
	if(lableCampFight)
	{
		lableCampFight->setPosition(ccp(size.width / 2 + size.width *iLay,
			size.height / 2 - btSize.height / 2));
		layer->addChild(lableCampFight);
	}
	///<=
=======
	///=>add by hwj campfight entrance
	{
		iLay = 1;
		CCSprite* spCampFightEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
		if(spCampFightEnter)
		{
			layer->addChild(spCampFightEnter);
			//spDragonTowerEnter->setIsVisible(false);
			CCSize size = spCampFightEnter->getContentSize();
			spCampFightEnter->setPosition(pos[iLay]);
		}
		CCSprite *spCampFightNormal = CCSprite::spriteWithFile("assets/ui/entrance/campFight.png");
		CCSprite *spCampFightPressed = CCSprite::spriteWithFile("assets/ui/entrance/campFight.png");
		CCMenuItemSprite *btCampFightEnter = CCMenuItemSprite::itemFromNormalSprite(
			spCampFightNormal,
			spCampFightPressed,
			this, 
			menu_selector(DungeonEntrysCreate::onClickCampFightEnterBtn));


		if(btCampFightEnter)
		{
			btSize = btCampFightEnter->getContentSize();
			CCMenu *bmCampFightEnter = CCMenu::menuWithItems(btCampFightEnter, NULL);
			if(bmCampFightEnter)
			{
				bmCampFightEnter->setPosition(CCPointZero);
				btCampFightEnter->setPosition(pos[iLay]);
				bmCampFightEnter->setTouchLayer(TLE::WindowLayer_CopyMap - 100);
				//bmDragonTowerEnter->setIsVisible(false);
				layer->addChild(bmCampFightEnter);
			}
		}
		CCLabelTTF* lableCampFight = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("SCENAME006").c_str(),
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentCenter,
			"Arial",
			POSX(20));
		if(lableCampFight)
		{
			lableCampFight->setPosition(ccp(pos[iLay].x,
				pos[iLay].y - btSize.height / 2));
			layer->addChild(lableCampFight);
		}
	}
	///<=
	{
		iLay = 2;
		CCSprite* spCampFightEnter = CCSprite::spriteWithSpriteFrameName("entrance/copy.png");
		if(spCampFightEnter)
		{
			layer->addChild(spCampFightEnter);
			//spDragonTowerEnter->setIsVisible(false);
			CCSize size = spCampFightEnter->getContentSize();
			spCampFightEnter->setPosition(pos[iLay]);
		}
		CCSprite *spCampFightNormal = CCSprite::spriteWithFile("assets/ui/entrance/gong.png");
		CCSprite *spCampFightPressed = CCSprite::spriteWithFile("assets/ui/entrance/gong.png");
		CCMenuItemSprite *btCampFightEnter = CCMenuItemSprite::itemFromNormalSprite(
			spCampFightNormal,
			spCampFightPressed,
			this, 
			menu_selector(DungeonEntrysCreate::onClickGongEnterBtn));


		if(btCampFightEnter)
		{
			btSize = btCampFightEnter->getContentSize();
			CCMenu *bmCampFightEnter = CCMenu::menuWithItems(btCampFightEnter, NULL);
			if(bmCampFightEnter)
			{
				bmCampFightEnter->setPosition(CCPointZero);
				btCampFightEnter->setPosition(pos[iLay]);
				bmCampFightEnter->setTouchLayer(TLE::WindowLayer_CopyMap - 100);
				//bmDragonTowerEnter->setIsVisible(false);
				layer->addChild(bmCampFightEnter);
			}
		}
		CCLabelTTF* lableCampFight = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("SCENAME007").c_str(),
			CCSizeMake(POSX(200), POSX(20)),
			CCTextAlignmentCenter,
			"Arial",
			POSX(20));
		if(lableCampFight)
		{
			lableCampFight->setPosition(ccp(pos[iLay].x,
				pos[iLay].y - btSize.height / 2));
			layer->addChild(lableCampFight);
		}

		CCLabelTTF* lableGongEnterTime = CCLabelTTF::labelWithString("",
			CCSizeMake(POSX(160), POSX(90)),
			CCTextAlignmentCenter,
			"Arial",
			POSX(20));
		if(lableGongEnterTime)
		{
			ViewManager::getInstance()->_GongEnterTimeText = lableGongEnterTime;
			lableGongEnterTime->setPosition(ccp(pos[iLay].x, pos[iLay].y - btSize.height / 2 - POSX(60)));
			lableGongEnterTime->setTag(TAG_GongTime);
			layer->addChild(lableGongEnterTime);
		}
	}
>>>>>>> .r5911
}

void DungeonEntrysCreate::onClickStoryEnterBtn(CCObject* pSender)
{
	int i = 1;
	//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if(m)
		m->onClickFunctionEnter(NULL, (void*)(&i));
}

void DungeonEntrysCreate::onClickChallengeEnterBtn(CCObject* pSender)
{
	// new hand
	NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_CHALLEGE_COPY_OVER);

	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_ChallegeCopy)
	{
		int i = 2;
		//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
		DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
		if(m)
			m->onClickFunctionEnter(NULL, (void*)(&i));
	}
	else
	{
		char path[256] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("TEM016").c_str() , LevLimitConst::Limit_ChallegeCopy);
		Message::Instance()->show(path , ccc3(233,12,25) , 1);
	}
	
}

void DungeonEntrysCreate::onClickLairEnterBtn(CCObject* pSender)
{
	int i = 3;
	//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if(m)
		m->onClickFunctionEnter(NULL, (void*)(&i));
}

void DungeonEntrysCreate::onClickWorldBossEnterBtn(CCObject* pSender)
{
	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_WorldBoss)
	{
		int i = 4;
		//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
		DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
		if(m)
			m->onClickFunctionEnter(NULL, (void*)(&i));
	}
	else
	{
		char path[256] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WBS120").c_str() , LevLimitConst::Limit_WorldBoss);
		Message::Instance()->show(path , ccc3(233,12,25) , 1);
	}
}

void DungeonEntrysCreate::onClickSilverMineEnterBtn(CCObject* pSender)
{
	int i = 5;
	//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if(m)
		m->onClickFunctionEnter(NULL, (void*)(&i));
}

void DungeonEntrysCreate::onClickDragonTowerEnterBtn(CCObject* pSender)
{
	int i = 6;
	//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if(m)
		m->onClickFunctionEnter(NULL, (void*)(&i));
}

//Begin Kenfly 20121213
void DungeonEntrysCreate::onClickRankingEnterBtn(CCObject* pSender)
{
    int i = 7;
	//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
    DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
    if (m)
        m->onClickFunctionEnter(NULL, (void*)(&i));
}

DungeonEntrysCreate::~DungeonEntrysCreate()
{
	ViewManager::getInstance()->_WorldBossOpenTimeText = 0;
}


//End Kenfly 20121213
<<<<<<< .mine
void DungeonEntrysCreate::onClickCampFightEnterBtn(CCObject* pSender)
{
	int i = 8;
	//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if (m)
		m->onClickFunctionEnter(NULL, (void*)(&i));
}=======

void DungeonEntrysCreate::moveToPreviousPage()
{
	this->CCUIPartialScrollView::moveToPreviousPage();
	if (ViewManager::getInstance()->dungeonEntrysView)
	{
		ViewManager::getInstance()->dungeonEntrysView->updateDirText("");
	}
}

void DungeonEntrysCreate::moveToNextPage()
{
	this->CCUIPartialScrollView::moveToNextPage();
	if (ViewManager::getInstance()->dungeonEntrysView)
	{
		ViewManager::getInstance()->dungeonEntrysView->updateDirText("");
	}
}

//End Kenfly 20121213
void DungeonEntrysCreate::onClickCampFightEnterBtn(CCObject* pSender)
{
	int i = 8;
	//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if (m)
		m->onClickFunctionEnter(NULL, (void*)(&i));
}

void DungeonEntrysCreate::onClickGongEnterBtn(CCObject* pSender)
{
	int i = 9;
	//dispatchEvent(DungeonEntrysMediator::CLICK_FUNCTION_ENTER, (void*)(&i));
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if (m)
		m->onClickFunctionEnter(NULL, (void*)(&i));
}
>>>>>>> .r5911
