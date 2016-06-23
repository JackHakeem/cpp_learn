#include "UpSkillView.h"
#include "manager/PopEventName.h"
#include "CCObject.h"
#include "manager/LayerManager.h"
#include "manager/GlobalManage.h"
#include "utils/ValuesUtil.h"
#include "BaseType.h"
#include "CCLabelTTF.h"
#include "UPSkillCreate.h"
#include "model/skill/SkillManager.h"
#include "model/skill/vo/SkillType.h"
#include "Message.h"
#include "view/figure/components/SkillView.h"
#include "../UpSkillMediator.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"
#include "model/crystal/vo/CrystalType.h"
#include "manager/LevLimitConst.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/ButtonIDConst.h"

UpSkillView::UpSkillView()
{
	_pCryProxy = (CrystalProxy *)g_pFacade->retrieveProxy(AppFacade_CRYSTAL_PROXY_CHANGE);
	memset(_nLen,0,sizeof(_nLen));
	memset(PassiveSkillID,0,sizeof(PassiveSkillID));
	memset(FormationSkillID,0,sizeof(FormationSkillID));
	_curSelectedItemTag = 0;
	_curSelectTab = TAB_FORMATION;
	_tipsLayer = 0;
	_skillMenu = 0;
	_formationMenu = 0;
	_talentMenu = 0;
	_pContainer = 0;
}

bool UpSkillView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/upskill/res_upskill.plist");

	this->key = PopEventName::UPSKILL;
	this->setIsTouchEnabled(true);
	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(CCPointZero);
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	_viewSize = CCSizeMake(960, 640);
	//_viewSize = BG_SIZE_960_640;
	//setPopContentSize(_viewSize);
	//this->setPosition(ccp(POSX(winSize.width / 2.0f-_viewSize.width/2), POSX(winSize.height / 2.0f-_viewSize.height/2)));

	this->setContentSize(winSize);
	this->setPopContentSize(this->getContentSize());

	if(!_pContainer)
	{
		_pContainer = new CCLayer();
		_pContainer->setAnchorPoint(CCPointZero);
		_pContainer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
	}

	addBackGround();

	addButtons();

	addScrollViews();

	this->addChild(_pContainer);

	return true;
}

void UpSkillView::addBackGround()
{
	CCUIBackground * _skillBackGround1 = new CCUIBackground();
	_skillBackGround1->initWithSpriteFrame("ui2.png",ccp(POSX(_viewSize.width/35),POSX(45)),CCPointZero,CCSizeMake(POSX(_viewSize.width*3/5),POSX(_viewSize.height*9/12)));
	_pContainer->addChild(_skillBackGround1,Z_BG,TAG_BG);
	//Doyang 20120712
	_skillBackGround1->release();

	CCUIBackground * _skillBackGround2 = new CCUIBackground();
	_skillBackGround2->initWithSpriteFrame("ui2.png",ccp(POSX(_viewSize.width*3/5+_viewSize.width/35),POSX(45)),CCPointZero,CCSizeMake(POSX(_viewSize.width*2/5-_viewSize.width*3/35),POSX(_viewSize.height*9/12)));
	_pContainer->addChild(_skillBackGround2,Z_BG,TAG_BG+1);
	//Doyang 20120712
	_skillBackGround2->release();

	// logo
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/upskill/res_upskill.plist");
	SpriteNode * pSpriteLogo = new SpriteNode;
	pSpriteLogo->initWithSpriteFrameName("upskill/logo.png");
	CCPoint pos = ccp(this->getContentSize().width/2,this->getContentSize().height-POSX(100));
	pSpriteLogo->setPosition(pos);
	this->addChild(pSpriteLogo,1);
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/upskill/res_upskill.plist");
}

void UpSkillView::loadDirections(int tabID)
{
	//return;
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/upskill/res_upskill.plist");
	UPSkillCreate * pSkillCreate = getCurrentCreate();
	if (!pSkillCreate){return;}	

	int nCurPage = pSkillCreate->currentScreen;
	int totalPage = pSkillCreate->totalScreens;

	// left
	CCMenuItemImage * pLeftDirImage = CCMenuItemImage::itemFromNormalImage(
		"assets/ui/common/direct.png",
		"assets/ui/common/direct_pressed.png",
		"assets/ui/common/direct.png",
		this,
		menu_selector(UpSkillView::onPrePage));
	CCMenu * pLeftDirMenu = CCMenu::menuWithItem(pLeftDirImage);
	pLeftDirMenu->setTouchLayer(TLE::WindowLayer_UpskillView);
	pLeftDirMenu->setPosition(ccp(POSX(20),POSX(375)));
	pLeftDirMenu->setScale(0.6);
	pLeftDirMenu->setTag(TAG_DIR_LEFT);
	if (_pContainer->getChildByTag(TAG_DIR_LEFT))
	{
		_pContainer->removeChildByTag(TAG_DIR_LEFT,true);
	}
	_pContainer->addChild(pLeftDirMenu,2);

	//right
	CCMenuItemImage * pRightDirImage = CCMenuItemImage::itemFromNormalImage(
		"assets/ui/common/direct0.png",
		"assets/ui/common/direct_pressed0.png",
		"assets/ui/common/direct0.png",
		this,
		menu_selector(UpSkillView::onNextPage));
	CCMenu * pRightDirMenu = CCMenu::menuWithItem(pRightDirImage);
	pRightDirMenu->setTouchLayer(TLE::WindowLayer_UpskillView);
	pRightDirMenu->setPosition(ccp(POSX(120),POSX(375)));
	pRightDirMenu->setScale(0.6);
	pRightDirMenu->setTag(TAG_DIR_RIGHT);
	if (_pContainer->getChildByTag(TAG_DIR_RIGHT))
	{
		_pContainer->removeChildByTag(TAG_DIR_RIGHT,true);
	}
	_pContainer->addChild(pRightDirMenu,2);
	
	char path[8];
	sprintf(path,ValuesUtil::Instance()->getString("US18").c_str(),nCurPage,totalPage);
	CCLabelTTF * pPageTxt = CCLabelTTF::labelWithString(
		path, 
		CCSizeMake(POSX(120) , POSX(30)) , 
		CCTextAlignmentCenter ,
		g_sSimHeiFont, POSX(24));
	pPageTxt->setPosition(ccp(POSX(270),POSX(504)));
	pPageTxt->setTag(TAG_DIR_TXT);
	if (_pContainer->getChildByTag(TAG_DIR_TXT))
	{
		_pContainer->removeChildByTag(TAG_DIR_TXT,true);
	}
	_pContainer->addChild(pPageTxt);

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/upskill/res_upskill.plist");
}

UPSkillCreate * UpSkillView::getCurrentCreate()
{
	UpSkillView * pSkillView = ViewManager::getInstance()->_upSkillView;
	if (!pSkillView)
	{
		return 0;
	}
	UPSkillCreate * pSkillCreate = 0;
	switch(pSkillView->_curSelectTab)
	{
	case UpSkillView::TAB_PASSIVE:
		pSkillCreate = g_pPassiveSkillScrollView;
		break;
	case UpSkillView::TAB_FORMATION:
		pSkillCreate = g_pFormationScrollView;
		break;
	case UpSkillView::TAB_TALENT:
		pSkillCreate = g_pTalentScrollView;
		break;
	default:
		pSkillCreate = g_pPassiveSkillScrollView;
		break;
	}

	return pSkillCreate;
}

void UpSkillView::updateDirections(int tabID)
{
	if (!_pContainer)	{return;	}

	UPSkillCreate * pSkillCreate = getCurrentCreate();
	if (!pSkillCreate){return;}	

	int nCurPage = pSkillCreate->currentScreen;
	int totalPage = pSkillCreate->totalScreens;

	char path[8];
	sprintf(path,ValuesUtil::Instance()->getString("US18").c_str(),nCurPage,totalPage);
	CCLabelTTF * pPageTxt = (CCLabelTTF *)_pContainer->getChildByTag(TAG_DIR_TXT);
	if (pPageTxt)
	{
		pPageTxt->setString(path);
	}
}

void UpSkillView::addScrollViews() 
{	
	if (!g_pPassiveSkillScrollView) // passive
	{
		g_pPassiveSkillScrollView = new UPSkillCreate(CCRectMake(POSX(40),POSX(45),POSX(550),POSX(447)));
		_pContainer->addChild(g_pPassiveSkillScrollView,Z_SCROLL,TAG_PASSIVE);
		g_pPassiveSkillScrollView->release(); // LH20120108
	}

	if (!g_pFormationScrollView) // Formation
	{
		g_pFormationScrollView = new UPSkillCreate(CCRectMake(POSX(40),POSX(45),POSX(550),POSX(447)));
		_pContainer->addChild(g_pFormationScrollView,Z_SCROLL,TAG_FORMATION);
		g_pFormationScrollView->release(); // LH20120108
	}

	if (!g_pTalentScrollView) // talent
	{
		g_pTalentScrollView = new UPSkillCreate(CCRectMake(POSX(40),POSX(45),POSX(550),POSX(447)));
		_pContainer->addChild(g_pTalentScrollView,Z_SCROLL,TAG_TALENT);
		g_pTalentScrollView->release(); // LH20120108
	}

	loadSkillItems();
	loadFormationItems();
	loadTalentItems();
	setDefaultPanel();
}

void UpSkillView::setDefaultPanel()
{
	if (_pContainer)
	{
		if (_pContainer->getChildByTag(TAG_BTN_FORMATION))
		{
			clickFormationHandler(0);
		}
		else if (_pContainer->getChildByTag(TAG_BTN_PASSIVE))
		{
			clickSkillHandler(0);
		}
		else if (_pContainer->getChildByTag(TAG_BTN_TALENT))
		{
			clickTalentHandler(0);
		}
		else
		{

		}
	}
}

void UpSkillView::addButtons()
{
	if (!_pContainer)
	{
		return;
	}	

	// button skill
	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Passive 
		&& !_pContainer->getChildByTag(TAG_BTN_PASSIVE))
	{
		CCMenuItemSprite *_btnSkill = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this, 
			menu_selector(UpSkillView::clickSkillHandler));
		_btnSkill->setTag(TAG_BTN_IMG);
		_skillMenu = CCMenu::menuWithItems(_btnSkill, NULL);
		_btnSkill->setPosition(CCPointZero);
		_skillMenu->setTag(TAG_BTN_PASSIVE);
		_skillMenu->setTouchLayer(TLE::WindowLayer_UpskillView);
		_skillMenu->setPosition(ccp(POSX(_viewSize.width*53/100), POSX(_viewSize.height-40)));
		_pContainer->addChild(_skillMenu, Z_BTN);
		CCLabelTTF * c1 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("US1").c_str(),
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(22));
		c1->setColor(ccc3(240,240,28));
		c1->setPosition(ccp(POSX(_viewSize.width*53/100), POSX(_viewSize.height-40)));
		_pContainer->addChild(c1,Z_BTN+1);

		//clickSkillHandler(0);
	}
	
	//c1->setPosition(CCPointZero);

	// button formation
	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_UpFormation
		&& !_pContainer->getChildByTag(TAG_BTN_FORMATION))
	{
		CCMenuItemSprite *_btnFormation = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this, 
			menu_selector(UpSkillView::clickFormationHandler));
		_btnFormation->setTag(TAG_BTN_IMG);
		_formationMenu = CCMenu::menuWithItems(_btnFormation, NULL);
		_formationMenu->setTouchLayer(TLE::WindowLayer_UpskillView);
		_btnFormation->setPosition(CCPointZero);
		_formationMenu->setTag(TAG_BTN_FORMATION);
		_formationMenu->setPosition(ccp(POSX(_viewSize.width*33/100), POSX(_viewSize.height-40)));
		_pContainer->addChild(_formationMenu, Z_BTN);
		CCLabelTTF * c2 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("US2").c_str(),
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(22));
		c2->setColor(ccc3(240,240,28));
		c2->setPosition(ccp(POSX(_viewSize.width*33/100), POSX(_viewSize.height-40)));
		_pContainer->addChild(c2,Z_BTN+1);

		//clickFormationHandler(0);
	}
	

	// button talent
	if (RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_Tallent
		&& !_pContainer->getChildByTag(TAG_BTN_TALENT))
	{
		CCMenuItemSprite *_btnTalent = CCMenuItemImage::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("ui/tab.png"), 
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			CCSprite::spriteWithSpriteFrameName("ui/tabOn.png"),
			this, 
			menu_selector(UpSkillView::clickTalentHandler));
		_btnTalent->setTag(TAG_BTN_IMG);
		_talentMenu = CCMenu::menuWithItems(_btnTalent, NULL);
		_talentMenu->setTouchLayer(TLE::WindowLayer_UpskillView);
		_btnTalent->setPosition(CCPointZero);
		_talentMenu->setTag(TAG_BTN_TALENT);
		_talentMenu->setPosition(ccp(POSX(_viewSize.width*73/100), POSX(_viewSize.height-40)));
		_pContainer->addChild(_talentMenu, Z_BTN);
		CCLabelTTF * c3 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("US3").c_str(),
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(22));
		c3->setColor(ccc3(240,240,28));
		c3->setPosition(ccp(POSX(_viewSize.width*73/100), POSX(_viewSize.height-40)));
		_pContainer->addChild(c3,Z_BTN+1);

		//clickTalentHandler(0);
	}
	

	// button upgrade
	

	{
		_btnUpgrade = CCMenuItemSprite::itemFromNormalSprite(
			CCSprite::spriteWithSpriteFrameName("button.png"),
			CCSprite::spriteWithSpriteFrameName("button1.png"),
			CCSprite::spriteWithSpriteFrameName("button2.png"),
			this, 
			menu_selector(UpSkillView::clickUpgradeHandler));
		CCMenu *upgradeMenu = CCMenu::menuWithItems(_btnUpgrade, NULL);
		_btnUpgrade->setPosition(CCPointZero);
		_btnUpgrade->setTag(TAG_BTN_IMG);
		upgradeMenu->setTouchLayer(TLE::WindowLayer_UpskillView);
		upgradeMenu->setPosition(ccp(POSX(_viewSize.width-200), POSX(_viewSize.height/9+20)));
		upgradeMenu->setTag(TAG_BTN_UPGRADE);
		_pContainer->addChild(upgradeMenu, Z_BTN);
		CCLabelTTF * c4 = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("US0").c_str(),
			CCSizeMake(POSX(100), POSX(20)),
			CCTextAlignmentCenter,
			g_sSimHeiFont,
			POSX(22));
		c4->setColor(ccc3(240,240,28));
		c4->setPosition(ccp(POSX(_viewSize.width-200), POSX(_viewSize.height/9+20)));
		_pContainer->addChild(c4,Z_BTN+1);
	}
	
	setDefaultPanel();
}

void UpSkillView::loadSkillItems()
{
	std::map<int, std::map<int, SkillNode> > * rankDic = &SkillManager::Instance()->_learnedSkillRankDic;
	std::map<int, std::map<int, SkillNode> >::iterator iter = rankDic->find(SkillType::PASSVIE);
	if(iter != rankDic->end())
	{
		int sitNum = 0;
		UpGradeInfo info;
		std::map<int, SkillNode> * skillNode = &iter->second;
		std::map<int, SkillNode>::iterator it = skillNode->begin();
		CCLayer * c = 0;
		int page = 0;
		if (!g_pPassiveSkillScrollView)
		{
			return;
		}
		_nLen[TAB_PASSIVE] = 0;

		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/upskill/res_upskill.plist");

		for (;it != skillNode->end();it++)
		{
			info.id = it->second.skillInfo.id;
			info.lev = it->second.skillInfo.lev;
			info.active = it->second.skillInfo.active;
// 			if (!info.active)
// 			{
// 				continue;
// 			}
			if (sitNum < MAX_SKILL_NUM)
			{
				PassiveSkillID[sitNum] = info.id;
				++_nLen[TAB_PASSIVE];
			}
			if (sitNum%UPSKILL_NUM_PER_PAGE == 0)
			{
				page = (int)sitNum/UPSKILL_NUM_PER_PAGE;
				if (!g_pPassiveSkillScrollView->getLayerByTag(page))
				{
					g_pPassiveSkillScrollView->addLayerByTag(page);
				}
				c = g_pPassiveSkillScrollView->getLayerByTag(page);
			}
			if (c->getChildByTag(sitNum))
			{
				c->removeChildByTag(sitNum,true);
			}
			UPSkillItem * si = new UPSkillItem(sitNum,page,&info);
			// position
			//CCLog("UPSkill:bg size(%f,%f)",_viewSize.width,_viewSize.height);
			si->setPosition(POSX(54+(sitNum%COL_UPSKILL)*109),POSX(390 - ((sitNum%UPSKILL_NUM_PER_PAGE)/COL_UPSKILL)*111));
			c->addChild(si,0,sitNum);
			si->release(); // LH07012
			++sitNum;
		}
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_skill_icon.plist");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/upskill/res_upskill.plist");
	}

	if (g_pPassiveSkillScrollView)
	{
		g_pPassiveSkillScrollView->setHightLight(true);
	}
	
}

void UpSkillView::loadFormationItems()
{
	std::map<int, std::map<int, SkillNode> > * rankDic = &SkillManager::Instance()->_learnedSkillRankDic;
	std::map<int, std::map<int, SkillNode> >::iterator iter = rankDic->find(SkillType::FORMATION);
	if(iter != rankDic->end())
	{
		int sitNum = 0;
		UpGradeInfo info;
		std::map<int, SkillNode> * skillNode = &iter->second;
		std::map<int, SkillNode>::iterator it = skillNode->begin();
		CCLayer * c = 0;
		int page = 0;
		if (!g_pFormationScrollView)
		{
			return;
		}
		_nLen[TAB_FORMATION] = 0;

		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/upskill/res_upskill.plist");

		for (;it != skillNode->end();it++)
		{
			info.id = it->second.formationInfo->getId();
			info.lev = it->second.formationInfo->lev;
			info.active = it->second.formationInfo->active;
// 			if (!info.active)
// 			{
// 				continue;
// 			}
			if (info.id>16)
			{
				return;
			}
			
			if (sitNum < MAX_SKILL_NUM)
			{
				FormationSkillID[sitNum] = info.id;
				++_nLen[TAB_FORMATION];
			}
			if (sitNum%UPSKILL_NUM_PER_PAGE == 0)
			{
				page = (int)sitNum/UPSKILL_NUM_PER_PAGE;
				if (!g_pFormationScrollView->getLayerByTag(page))
				{
					g_pFormationScrollView->addLayerByTag(page);
				}
				c = g_pFormationScrollView->getLayerByTag(page);
			}
			if (c->getChildByTag(sitNum))
			{
				c->removeChildByTag(sitNum,true);
			}
			UPSkillItem * si = new UPSkillItem(sitNum,page,&info);
			// position
			//CCLog("UPSkill:bg size(%f,%f)",_viewSize.width,_viewSize.height);
			si->setPosition(POSX(54+(sitNum%COL_UPSKILL)*109),POSX(390-((sitNum%UPSKILL_NUM_PER_PAGE)/COL_UPSKILL)*111));
			c->addChild(si,0,sitNum);
			si->release(); // LH07012
			++sitNum;
		}
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_skill_icon.plist");
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/upskill/res_upskill.plist");
	}

	if (g_pFormationScrollView)
	{
		g_pFormationScrollView->setHightLight(true);
	}
}

void UpSkillView::loadTalentItems()
{
	// this function has not be opened
}

void UpSkillView::clickSkillHandler(CCObject * pSender)
{
	bool a[3] = {false,true,true};
	setBtnState(a);

	_curSelectTab = TAB_PASSIVE;
	if (g_pPassiveSkillScrollView)
	{
		g_pPassiveSkillScrollView->setIsVisible(true);
		g_pPassiveSkillScrollView->setIsTouchEnabled(true);
	}
	if (g_pFormationScrollView)
	{
		g_pFormationScrollView->setIsVisible(false);
		g_pFormationScrollView->setIsTouchEnabled(false);
	}
	if (g_pTalentScrollView)
	{
		g_pTalentScrollView->setIsVisible(false);
		g_pTalentScrollView->setIsTouchEnabled(false);
	}

	if (g_pFormationScrollView && g_pFormationScrollView->spriteLight)
	{
		g_pFormationScrollView->spriteLight->setIsVisible(false);
	}
	if (g_pTalentScrollView && g_pTalentScrollView->spriteLight)
	{
		g_pTalentScrollView->spriteLight->setIsVisible(false);
	}
	
	loadDirections(TAB_PASSIVE);

	showDefaultTips(TAB_PASSIVE);
}

void UpSkillView::clickFormationHandler(CCObject * pSender)
{
	bool a[3] = {true,false,true};
	setBtnState(a);

	_curSelectTab = TAB_FORMATION;
	if (g_pPassiveSkillScrollView)
	{
		g_pPassiveSkillScrollView->setIsVisible(false);
		g_pPassiveSkillScrollView->setIsTouchEnabled(false);
	}
	if (g_pFormationScrollView)
	{
		g_pFormationScrollView->setIsVisible(true);
		g_pFormationScrollView->setIsTouchEnabled(true);
	}
	if (g_pTalentScrollView)
	{
		g_pTalentScrollView->setIsVisible(false);
		g_pTalentScrollView->setIsTouchEnabled(false);
	}
	

	if (g_pPassiveSkillScrollView && g_pPassiveSkillScrollView->spriteLight)
	{
		g_pPassiveSkillScrollView->spriteLight->setIsVisible(false);
	}
	if (g_pTalentScrollView && g_pTalentScrollView->spriteLight)
	{
		g_pTalentScrollView->spriteLight->setIsVisible(false);
	}
	
	loadDirections(TAB_FORMATION);

	showDefaultTips(TAB_FORMATION);
}

void UpSkillView::clickTalentHandler(CCObject * pSender)
{
	bool a[3] = {true,true,false};
	setBtnState(a);

	_curSelectTab = TAB_TALENT;

	Message::Instance()->show(ValuesUtil::Instance()->getString("US4"),ccc3(250,33,33),1);
	return;

	g_pPassiveSkillScrollView->setIsVisible(false);
	g_pPassiveSkillScrollView->setIsTouchEnabled(false);
	g_pFormationScrollView->setIsVisible(false);
	g_pFormationScrollView->setIsTouchEnabled(false);
	g_pTalentScrollView->setIsVisible(true);
	g_pTalentScrollView->setIsTouchEnabled(true);

	if (g_pPassiveSkillScrollView->spriteLight)
	{
		g_pPassiveSkillScrollView->spriteLight->setIsVisible(false);
	}
	if (g_pFormationScrollView->spriteLight)
	{
		g_pFormationScrollView->spriteLight->setIsVisible(false);
	}

	loadDirections(TAB_TALENT);

	showDefaultTips(TAB_TALENT);
}

void UpSkillView::clickUpgradeHandler(CCObject * pSender)
{
	//new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_UpFormation) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_UpFormation , NewhandManager::Flag_Done);
		NewhandManager::Instance()->touchNextEvent(807);
	}


	if (_btnUpgrade)
	{
		_btnUpgrade->setIsEnabled(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(UpSkillView::lockBtn),
			this,0.2f,false);
	}

	UpSkillMediator * pSkillMediator = (UpSkillMediator *)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
	if (!pSkillMediator)
	{
		return;
	}

	UPSkillCreate * pSkillCreate = 0;

	switch(_curSelectTab)
	{
	case TAB_PASSIVE:
		pSkillCreate = g_pPassiveSkillScrollView;
		if (pSkillCreate)
		{
			int page = pSkillCreate->currentScreen-1;
			if (page < 0)
			{
				return;
			}
			
			CCLayer * pScrollLayer = pSkillCreate->getLayerByTag(page);
			if (pScrollLayer)
			{
				UPSkillItem * pSkillItem = (UPSkillItem *)pScrollLayer->getChildByTag(_curSelectedItemTag);
				if (pSkillItem && pSkillItem->_info)
				{
					if (!isCanUpgradeOK(pSkillItem->_info))
					{
						return;
					}

					if (pSkillItem->_info->lev >= MAX_SKILL_LEVEL)
					{
						enableButton(TAG_BTN_UPGRADE,false);
						Message::Instance()->show(ValuesUtil::Instance()->getString("US16"),ccc3(233,55,11),1);
						return;
					}
					else{enableButton(TAG_BTN_UPGRADE,true);}
					pSkillMediator->sendUpgradePassiveSkillRequest(pSkillItem->_info->id);
				}
			}
		}
		break;
	case TAB_FORMATION:
		pSkillCreate = g_pFormationScrollView;
		if (pSkillCreate)
		{
			int page = pSkillCreate->currentScreen-1;
			if (page < 0)
			{
				return;
			}

			CCLayer * pScrollLayer = pSkillCreate->getLayerByTag(page);
			if (pScrollLayer)
			{
				UPSkillItem * pSkillItem = (UPSkillItem *)pScrollLayer->getChildByTag(_curSelectedItemTag);
				if (pSkillItem && pSkillItem->_info)
				{
					if (!isCanUpgradeOK(pSkillItem->_info))
					{
						return;
					}

					if (pSkillItem->_info->lev >= MAX_SKILL_LEVEL)
					{
						enableButton(TAG_BTN_UPGRADE,false);
						Message::Instance()->show(ValuesUtil::Instance()->getString("US16"),ccc3(233,55,11),1);
						return;
					}
					else{enableButton(TAG_BTN_UPGRADE,true);}
					pSkillMediator->sendUpgradeFormationRequest(pSkillItem->_info->id);
				}
			}
		}
		break;
	case TAB_TALENT:
		break;
	default:
		break;
	}
		
}

void UpSkillView::lockBtn(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(UpSkillView::lockBtn), this);
	if (_btnUpgrade)
	{
		_btnUpgrade->setIsEnabled(true);
	}
}

void UpSkillView::clickCloseHandler(CCObject * pSender)
{
	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_UpFormation) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->touchNextScript("addBtn" , ButtonIDConst::ButtonID_Upskill);
	}
	else if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_UpFormation) == NewhandManager::Flag_Done)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_UpFormation , NewhandManager::Flag_Close);
		NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_UPFORMATION_OVER);
		NewhandManager::Instance()->doTaskFollow();
	}

	this->setisPop(false);
	
	g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());

}

void UpSkillView::addNewPassiveSkill(UpGradeInfo *info)
{
	Message::Instance()->show(ValuesUtil::Instance()->getString("US5"),ccc3(24,233,44),1);

	if (!g_pPassiveSkillScrollView) // passive
	{
		return;
	}	
	int totalPage = g_pPassiveSkillScrollView->totalScreens;
	if (totalPage <= 0)
	{
		return;
	}
	CCLayer * pScrollLayer = 0;
	if (totalPage <= 0)
	{
		if (!g_pPassiveSkillScrollView->getLayerByTag(0))
		{
			g_pPassiveSkillScrollView->addLayerByTag(0);
		}
        //Doyang 20120718
		//	pScrollLayer = g_pPassiveSkillScrollView->getLayerByTag(0);
	}	
	pScrollLayer = g_pPassiveSkillScrollView->getLayerByTag(totalPage-1);
	if (!pScrollLayer)
	{
		
		return;
	}
	int sitNum = 0;
	for (sitNum =0;sitNum<UPSKILL_NUM_PER_PAGE;sitNum++)
	{
		if (!pScrollLayer->getChildByTag(sitNum))
		{
			UPSkillItem * pSkillItem = new UPSkillItem(sitNum,totalPage-1,info);
			pSkillItem->setPosition(POSX(54+(sitNum%COL_UPSKILL)*109),POSX(390 - ((sitNum%UPSKILL_NUM_PER_PAGE)/COL_UPSKILL)*111));
			pScrollLayer->addChild(pSkillItem,0,sitNum);
			pSkillItem->release(); // LH0712LEAK
			break;
		}
	}
	if (sitNum == UPSKILL_NUM_PER_PAGE)
	{
		sitNum = 0;
		int page = totalPage;
		if (!g_pPassiveSkillScrollView->getLayerByTag(page))
		{
			g_pPassiveSkillScrollView->addLayerByTag(page);
		}
		UPSkillItem * pSkillItem = new UPSkillItem(sitNum,totalPage,info);
		pScrollLayer = g_pPassiveSkillScrollView->getLayerByTag(page);
		pSkillItem->setPosition(POSX(54+(sitNum%COL_UPSKILL)*109),POSX(390 - ((sitNum%UPSKILL_NUM_PER_PAGE)/COL_UPSKILL)*111));
		pScrollLayer->addChild(pSkillItem,0,sitNum);
		pSkillItem->release(); // LH0712LEAK
	}	
}

void UpSkillView::addNewFormation(UpGradeInfo *info)
{
	Message::Instance()->show(ValuesUtil::Instance()->getString("US15"),ccc3(24,233,44),1);


	if (!g_pFormationScrollView) // formtion
	{
		return;
	}	
	int totalPage = g_pFormationScrollView->totalScreens;
	if (totalPage <= 0)
	{
		return;
	}
	
	CCLayer * pScrollLayer;
	if (totalPage <= 0)
	{
		if (!g_pFormationScrollView->getLayerByTag(0))
		{
			g_pFormationScrollView->addLayerByTag(0);
		}
        //Doyang 20120718
		//pScrollLayer = g_pFormationScrollView->getLayerByTag(0);
	}	
	pScrollLayer = g_pFormationScrollView->getLayerByTag(totalPage-1);
	if (!pScrollLayer)
	{
		return;
	}
	int sitNum = 0;
	for (sitNum =0;sitNum<UPSKILL_NUM_PER_PAGE;sitNum++)
	{
		if (!pScrollLayer->getChildByTag(sitNum))
		{
			UPSkillItem * pSkillItem = new UPSkillItem(sitNum,totalPage-1,info);
			pSkillItem->setPosition(POSX(54+(sitNum%COL_UPSKILL)*109),POSX(390 - ((sitNum%UPSKILL_NUM_PER_PAGE)/COL_UPSKILL)*111));
			pScrollLayer->addChild(pSkillItem,0,sitNum);
			pSkillItem->release(); // LH0712LEAK
			break;
		}
	}
	if (sitNum == UPSKILL_NUM_PER_PAGE)
	{
		sitNum = 0;
		int page = totalPage;
		if (!g_pFormationScrollView->getLayerByTag(page))
		{
			g_pFormationScrollView->addLayerByTag(page);
		}
		UPSkillItem * pSkillItem = new UPSkillItem(sitNum,totalPage,info);
		pScrollLayer = g_pFormationScrollView->getLayerByTag(page);
		pSkillItem->setPosition(POSX(54+(sitNum%COL_UPSKILL)*109),POSX(390 - ((sitNum%UPSKILL_NUM_PER_PAGE)/COL_UPSKILL)*111));
		pScrollLayer->addChild(pSkillItem,0,sitNum);
		pSkillItem->release(); // LH0712LEAK
	}	
}

void UpSkillView::loadUPSkillTips(UpGradeInfo *info)
{
	if (!_tipsLayer)
	{
		_tipsLayer = new LayerNode();
		_tipsLayer->setAnchorPoint(CCPointZero);
		_tipsLayer->setIsRelativeAnchorPoint(true);
		_tipsLayer->setPosition(CCPointZero);
		_pContainer->addChild(_tipsLayer,Z_SCROLL,TAG_TIPS);
	}
	char path[64];
	_tipsLayer->removeAllChildrenWithCleanup(true);

	std::map<int/*skillId*/, std::map<int/*lvl*/, LevSkillVo> > * _levskilldic = &SkillManager::Instance()->_levSkillDic;
	std::map<int/*skillId*/, std::map<int/*lvl*/, LevSkillVo> >::iterator iter = _levskilldic->find(info->id);
	if (iter == _levskilldic->end()){return;	}
	std::map<int/*lvl*/, LevSkillVo> * _levSkill = &iter->second;
	std::map<int/*lvl*/, LevSkillVo>::iterator it = _levSkill->find(info->lev);
	if (it == _levSkill->end()){return;	}
	LevSkillVo * _levskillVo = &it->second;

	bool isMaxLev = false;
	if ((!_levskillVo->roleLevel)&&(!_levskillVo->cdTime)&&(!_levskillVo->skillEXP))
	{
		isMaxLev = true;
	}
	
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");

	// icon
	SpriteNode * sIconBg = new SpriteNode();
	memset(path,0,sizeof(path));
	sprintf(path,"pack/unlock.png");
	sIconBg->initWithSpriteFrameName(path);
	sIconBg->setPosition(ccp(POSX(680),POSX(411)));
	sIconBg->setAnchorPoint(ccp(0.5,0.5));
	sIconBg->setIsRelativeAnchorPoint(true);
	_tipsLayer->addChild(sIconBg,0,TAG_TIPS);
	sIconBg->release(); // LH0712LEAK

	SpriteNode * sIcon = new SpriteNode();
	memset(path,0,sizeof(path));
	//sprintf(path,"skill/%d.png",info->id);
	//sIcon->initWithSpriteFrameName(path);

	sprintf(path,"assets/icon/skill/%d.png" , info->id);
	bool var = sIcon->initWithFile(path);
	if (!var)
	{
		sIcon->initWithFile("assets/icon/goods/unknown.png");
	}

	sIcon->setAnchorPoint(ccp(0.5,0.5));
	CCSize size = sIconBg->getContentSize();
	sIcon->setPosition(ccp(size.width/2,size.height/2));
	if (sIconBg->getChildByTag(0))
	{
		sIconBg->removeChildByTag(0,true);
	}	
	sIconBg->addChild(sIcon,0,0);
	sIcon->release(); // LH0712LEAK

	// name level time
	CCLabelTTF * cName = CCLabelTTF::labelWithString(SkillManager::Instance()->getSkill(info->id)->name.c_str(),CCSizeMake(POSX(140),POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(18));
	cName->setColor(ccc3(255,215,0));
	cName->setPosition(ccp(POSX(749),POSX(435)));
	cName->setAnchorPoint(CCPointZero);
	_tipsLayer->addChild(cName,0,TAG_TIPS+1);

	memset(path,0,sizeof(path));
	sprintf(path,ValuesUtil::Instance()->getString("US8").c_str(),info->lev);
	CCLabelTTF * cLev = CCLabelTTF::labelWithString(path,CCSizeMake(POSX(140), POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(18));
	cLev->setColor(ccc3(240,240,240));
	cLev->setPosition(ccp(POSX(749),POSX(405)));
	cLev->setAnchorPoint(CCPointZero);
	_tipsLayer->addChild(cLev,0,TAG_TIPS+2);

	memset(path,0,sizeof(path));
	if (!isMaxLev)
	{
		sprintf(path,ValuesUtil::Instance()->getString("US9").c_str(),_levskillVo->cdTime/60);
	}
	else
	{
		sprintf(path,ValuesUtil::Instance()->getString("US16").c_str(),_levskillVo->cdTime/60);
	}
	
	CCLabelTTF * cTime = CCLabelTTF::labelWithString(path,CCSizeMake(POSX(140), POSX(40)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(18));
	cTime->setColor(ccc3(240,133,25));
	cTime->setPosition(ccp(POSX(749),POSX(350)));
	cTime->setAnchorPoint(CCPointZero);
	_tipsLayer->addChild(cTime,0,TAG_TIPS+3);

	if (RoleManage::Instance()->accountInfo()->practice() < _levskillVo->skillEXP)
	{
		cTime->setString(ValuesUtil::Instance()->getString("US19").c_str());
		cTime->setColor(ccc3(255,10,10));
		//Message::Instance()->show(ValuesUtil::Instance()->getString("US19"),ccc3(255,10,10));
	}

	// describe
	CCLabelTTF * cDes = CCLabelTTF::labelWithString(_levskillVo->des.c_str(),CCSizeMake(POSX(220), POSX(80)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
	cDes->setColor(ccc3(255,215,215));
	cDes->setPosition(ccp(POSX(656),POSX(250))); 
	cDes->setAnchorPoint(CCPointZero);
	_tipsLayer->addChild(cDes,0,TAG_TIPS+4);

	// need
	CCLabelTTF * cNeed = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("US10").c_str(),CCSizeMake(POSX(140), POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(20));
	cNeed->setColor(ccc3(255,215,0));
	cNeed->setPosition(ccp(POSX(656),POSX(210)));
	cNeed->setAnchorPoint(CCPointZero);
	_tipsLayer->addChild(cNeed,0,TAG_TIPS+5);

	// need crystal level
	memset(path,0,sizeof(path));
	if (!isMaxLev)
	{
		if ((_curSelectTab == TAB_PASSIVE)||(_curSelectTab == TAB_FORMATION))
		{
			sprintf(path,ValuesUtil::Instance()->getString("US11").c_str(),_levskillVo->roleLevel);
		}
		else if (_curSelectTab == TAB_TALENT)
		{
			sprintf(path,ValuesUtil::Instance()->getString("US12").c_str(),_levskillVo->roleLevel);
		}
	}
	else
	{
		sprintf(path,ValuesUtil::Instance()->getString("US16").c_str());
	}	
	CCLabelTTF * cNeedLev = CCLabelTTF::labelWithString(path,CCSizeMake(POSX(140), POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(18));
	cNeedLev->setColor(ccc3(12,233,25));
	cNeedLev->setPosition(ccp(POSX(656),POSX(180)));
	cNeedLev->setAnchorPoint(CCPointZero);
	_tipsLayer->addChild(cNeedLev,0,TAG_TIPS+6);

	if (_pCryProxy)
	{
		int lev = _pCryProxy->getCrystalLev(CrystalType::CRYSTAL_FENG); // crystal id = 32
		if (_levskillVo->roleLevel > lev)
		{
			cNeedLev->setColor(ccc3(255,10,10));
		}
	}
	
	// need practices
	memset(path,0,sizeof(path));
	if (!isMaxLev)
	{
		sprintf(path,ValuesUtil::Instance()->getString("US13").c_str(),_levskillVo->skillEXP);
	}
	else
	{
		sprintf(path,ValuesUtil::Instance()->getString("US17").c_str());
	}
	CCLabelTTF * cPractice = CCLabelTTF::labelWithString(path,CCSizeMake(POSX(180), POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(18));
	cPractice->setColor(ccc3(12,233,25));
	cPractice->setPosition(ccp(POSX(656),POSX(150)));
	cPractice->setAnchorPoint(CCPointZero);
	_tipsLayer->addChild(cPractice,0,TAG_TIPS+7);

	// my practice
	{
		char path[128] = {0};
		memset(path,0,sizeof(path));		
		sprintf(path,ValuesUtil::Instance()->getString("ROL101").c_str(), RoleManage::Instance()->accountInfo()->practice());
		CCLabelTTF * pPractice = CCLabelTTF::labelWithString(path,CCSizeMake(POSX(180), POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont, POSX(18));
		pPractice->setColor(ccc3(25,133,233));
		pPractice->setPosition(ccp(POSX(656),POSX(120)));
		pPractice->setAnchorPoint(CCPointZero);
		_tipsLayer->addChild(pPractice,0,TAG_TIPS+8);
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_skill_icon.plist");
}

void UpSkillView::showDefaultTips(int tabID)
{
	_curSelectedItemTag = 0;

	UPSkillCreate * pSkillCreate = 0;
	switch (tabID)
	{
	case TAB_PASSIVE:
		pSkillCreate = g_pPassiveSkillScrollView;
		break;
	case TAB_FORMATION:
		pSkillCreate = g_pFormationScrollView;
		break;
	case TAB_TALENT:
		pSkillCreate = g_pTalentScrollView;
		break;
	}
	if (!pSkillCreate){return;}	

	CCLayer * pScrollLayer = pSkillCreate->getLayerByTag(0);
	if (!pScrollLayer){return;}

	UPSkillItem * pSkillItem = (UPSkillItem *)pScrollLayer->getChildByTag(0);
	if (pSkillItem)
	{
		if (pSkillCreate->spriteLight)
		{
			pSkillCreate->spriteLight->setIsVisible(true);
			pSkillCreate->spriteLight->setPosition(pSkillItem->getPosition());
		}

		if (pSkillItem->_info)
		{
			loadUPSkillTips(pSkillItem->_info);
		}
	}
}

void UpSkillView::enableButton(int tag, bool var)
{
	if (_pContainer)
	{
		CCMenu * pMenuBtn = (CCMenu *)_pContainer->getChildByTag(tag);
		if (pMenuBtn)
		{
			CCMenuItemImage* pBtnImage = (CCMenuItemImage*)pMenuBtn->getChildByTag( TAG_BTN_IMG );
			if(pBtnImage)
			{
				pBtnImage->setIsEnabled(var);
			}
		}
	}
}

void UpSkillView::setBtnState(bool a[])
{
	if (sizeof(a)/sizeof(bool) >= 3)
	{
		enableButton(TAG_BTN_PASSIVE,a[0]);
		enableButton(TAG_BTN_FORMATION,a[1]);
		enableButton(TAG_BTN_TALENT,a[2]);
	}
}

void UpSkillView::onPrePage(CCObject * pSender)
{
	UPSkillCreate * pSkillCreate = 0;
	switch (_curSelectTab)
	{
		case TAB_PASSIVE:
			pSkillCreate = g_pPassiveSkillScrollView;
			break;
		case TAB_FORMATION:
			pSkillCreate = g_pFormationScrollView;
			break;
		case TAB_TALENT:
			pSkillCreate = g_pTalentScrollView;
			break;
	}
	if (!pSkillCreate){return;}
	if (pSkillCreate->currentScreen > 1)
	{
		pSkillCreate->moveToPreviousPage();
	}	
}

void UpSkillView::onNextPage(CCObject * pSender)
{
	UPSkillCreate * pSkillCreate = 0;
	switch (_curSelectTab)
	{
	case TAB_PASSIVE:
		pSkillCreate = g_pPassiveSkillScrollView;
		break;
	case TAB_FORMATION:
		pSkillCreate = g_pFormationScrollView;
		break;
	case TAB_TALENT:
		pSkillCreate = g_pTalentScrollView;
		break;
	}
	if (!pSkillCreate){return;}
	if (pSkillCreate->currentScreen < pSkillCreate->totalScreens)
	{
		pSkillCreate->moveToNextPage();
	}	
}

bool UpSkillView::isCanUpgradeOK(UpGradeInfo * info)
{
	std::map<int/*skillId*/, std::map<int/*lvl*/, LevSkillVo> > * _levskilldic = &SkillManager::Instance()->_levSkillDic;
	std::map<int/*skillId*/, std::map<int/*lvl*/, LevSkillVo> >::iterator iter = _levskilldic->find(info->id);
	if (iter == _levskilldic->end()){return false;	}
	std::map<int/*lvl*/, LevSkillVo> * _levSkill = &iter->second;
	std::map<int/*lvl*/, LevSkillVo>::iterator it = _levSkill->find(info->lev);
	if (it == _levSkill->end()){return false;	}
	LevSkillVo * _levskillVo = &it->second;

	if (_pCryProxy)
	{
		//int lev = _pCryProxy->getCrystalLev(CrystalType::CRYSTAL_FENG); // crystal id = 32
		int lev = RoleManage::Instance()->roleLev();
		if (_levskillVo->roleLevel > lev)
		{
			Message::Instance()->show(ValuesUtil::Instance()->getString("US20") , ccc3(233,12,25) , 1);
			return false;
		}
	}

	if (RoleManage::Instance()->accountInfo()->practice() < _levskillVo->skillEXP)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("US19"),ccc3(255,10,10) , 1);
		return false;
	}

	return true;
}

void UpSkillView::updatePractice()
{
	if (_tipsLayer)
	{
		CCLabelTTF * pTxt = (CCLabelTTF *)_tipsLayer->getChildByTag(8);
		if (pTxt)
		{
			std::string str = "" + RoleManage::Instance()->accountInfo()->practice();
			pTxt->setString(str.c_str());
		}		
	}	
}

CCNode * UpSkillView::getNewHandItem(int id)
{
	switch (id)
	{
	case 100:
		{
			return _btnUpgrade;
		}
		break;
	case 101:
		{

		}
		break;
	default:
		break;
	}
	return 0;
}

void UpSkillView::removeDataObjectChild()
{
	if (ViewManager::getInstance()->_upSkillView)
	{
		ViewManager::getInstance()->_upSkillView = 0;
	}
	UpSkillMediator  * pM = (UpSkillMediator *)g_pFacade->retrieveMediator(AppFacade_SKILL_COMMAND);
	if (pM)
	{
		pM->_upskillView = 0;
	}	
}

UpSkillView::~UpSkillView()
{

	ViewManager::getInstance()->_upSkillView = 0;
	// LH20120108
	if (g_pPassiveSkillScrollView)
	{
		g_pPassiveSkillScrollView->removeAllLayer();
		g_pPassiveSkillScrollView->removeFromParentAndCleanup(true);
		g_pPassiveSkillScrollView = 0;
	}

	if (g_pFormationScrollView)
	{
		g_pFormationScrollView->removeAllLayer();
		g_pFormationScrollView->removeFromParentAndCleanup(true);
		g_pFormationScrollView = 0;
	}

	if (g_pTalentScrollView)
	{
		g_pTalentScrollView->removeAllLayer();
		g_pTalentScrollView->removeFromParentAndCleanup(true);
		g_pTalentScrollView = 0;
	}

	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/icon/res_skill_icon.plist");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/icon/res_skill_icon.pvr.ccz");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/upskill/res_upskill.plist");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/upskill/res_upskill.pvr.ccz");
}
