#include "MineOpt.h"
#include "MineView.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "model/silverMine/SilverMineManage.h"
#include "manager/LangManager.h"
#include "model/silverMine/SilverConst.h"
#include "MineTips.h"
#include "CCUIBackground.h"
#include "manager/CDManage.h"
#include "manager/TimerManage.h"
#include "MineRank.h"
#include "manager/LayerManager.h"

const float FontSize = 20.f;

MineOpt::MineOpt()
{
	_txtPercent = 0;
	pContainer = 0;
	_btnDig = 0;
	_btnDig2 = 0;
	//_btnDig3 = 0;
}

MineOpt::~MineOpt()
{}


bool MineOpt::init(MineView* pContainer)
{
	if (!LayerNode::init())
		return false;

	this->pContainer = pContainer;
	//_btnDig3
	//{
	//	CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("_btnDig3_0.png");
	//	CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("_btnDig3_1.png");
	//	CCSprite* p3 = CCSprite::spriteWithSpriteFrameName("_btnDig3_1.png");
	//	CCMenuItemSprite* _btn = CCMenuItemImage::itemFromNormalSprite(
	//		p1, 
	//		p2, 
	//		p3,
	//		this, 
	//		menu_selector(MineOpt::digClick3) );
	//	_btn->setPosition(ccp(POSX(630), POSX(640-578)));

	//	CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
	//	buttonMenu->setPosition( CCPointZero );
	//	buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
	//	this->addChild(buttonMenu, 0);	
	//	_btnDig3 = _btn;
	//}
	//_btnDig2
	{
		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("_btnDig2_1.png");
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("_btnDig2_0.png");
		CCSprite* p3 = CCSprite::spriteWithSpriteFrameName("_btnDig2_0.png");
		CCMenuItemSprite* _btn = CCMenuItemImage::itemFromNormalSprite(
			p1, 
			p2, 
			p3,
			this, 
			menu_selector(MineOpt::digClick2) );
		_btn->setPosition(ccp(POSX(765), POSX(640-578)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
		this->addChild(buttonMenu, 0);	
		_btnDig2 = _btn;
	}
	//_btnDig
	{
		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("_btnDig_1.png");
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("_btnDig_0.png");
		CCSprite* p3 = CCSprite::spriteWithSpriteFrameName("_btnDig_0.png");
		CCMenuItemSprite* _btn = CCMenuItemImage::itemFromNormalSprite(
			p1, 
			p2, 
			p3,
			this, 
			menu_selector(MineOpt::digClick) );
		_btn->setPosition(ccp(POSX(900), POSX(640-578)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
		this->addChild(buttonMenu, 0);	
		_btnDig = _btn;
	}
	//_btnSearch
	{
		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("_btnSearch_1.png");
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("_btnSearch_0.png");
		CCSprite* p3 = CCSprite::spriteWithSpriteFrameName("_btnSearch_0.png");
		CCMenuItemSprite* _btn = CCMenuItemImage::itemFromNormalSprite(
			p1, 
			p2, 
			p3,
			this, 
			menu_selector(MineOpt::searchClick) );
		_btn->setPosition(ccp(POSX(495), POSX(640-578)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
		this->addChild(buttonMenu, 0);	
		buttonMenu->setIsVisible(false);
	}
	//
	{
		_txtPercent = CCLabelTTF::labelWithString("", CCSizeMake(POSX(500), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		_txtPercent->setPosition(ccp(POSX(300), POSX(640-610)));
		_txtPercent->setAnchorPoint(ccp(0, 0));
		this->addChild(_txtPercent, 0);
		_txtPercent->setColor(ccc3(254, 255, 0));
	}
	{
		SpriteNode* bg = new SpriteNode();
		bg->initWithSpriteFrameName("bg_opt.png");
		this->addChild(bg, -1);
		bg->setPosition(ccp(POSX(600), POSX(640-610)));
		bg->setScaleX(POSX(2.0f));
		bg->setRotation(180.0f);
		bg->release();
	}
	return true;
}

void MineOpt::updateMineInfo(int mineId, int onMine)
{
	BasicMineVo basicVo = SilverMineManage::Instance()->getBasicCfgByID(mineId);
	                          
	_capacity = getCapacity(basicVo.mineLev);
	_online = onMine;
			
	setDescription();
}

//				100%(富裕，小于银矿容纳量2/3）
//				80%（正常，2/3到1）
//				40%（拥挤，1到2）
//				20%（人海，2以上）

std::string MineOpt::getFlourish(int online, int capacity)
{
	std::string descript;
	float flourish = online/5;
	if(flourish<0.66){
		descript = LangManager::getText("SLM011");//富裕
	}else if(flourish<=1){
		descript = LangManager::getText("SLM012");//正常
	}else if(flourish<2){
		descript = LangManager::getText("SLM013");//拥挤
	}else{
		descript = LangManager::getText("SLM014");//人海
	}
	return descript;
			
}

void MineOpt::setDigBtnEnable(bool value)
{
	//_btnDig2->setIsEnabled(value);
	//_btnDig3->setIsEnabled(value);
	//_btnDig->setIsEnabled(value);
	if(false==value){
		//Utils.applyBlackAndWhiteFilter(_btnDig);
	}else{
		//_btnDig.filters = [];
	}
}
		
void MineOpt::setSearchBtnEnable(bool value)
{
	_btnSearch->setIsEnabled(value);
	if(value){
		//Utils.applyBlackAndWhiteFilter(_btnSearch);
	}else{
		//_btnSearch.filters = [];
	}
}

// 挖矿
void MineOpt::digClick(CCObject* pSender)
{
	int i = 0;
 	pContainer->dispatchEvent(SilverConst::DIG_MINE, &i);
}
		
// 黄金挖矿
void MineOpt::digClick2(CCObject* pSender)
{
	static int s_count = -1;
	s_count++;
	if (s_count == 0)
	{
		MineTips* oldp = (MineTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
		if (!oldp)
		{
			oldp = new MineTips();
			oldp->init(MineTips::huangjin, pContainer);
			LayerManager::intervalLayer->addChild(oldp, IntervalLayer::IntervalLayerZ_guild_silverMineTips, IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
			oldp->release();
		}
	}
	else
	{
		int i = 1;
		pContainer->dispatchEvent(SilverConst::DIG_MINE, &i);
	}
}
		
// 白金挖矿
void MineOpt::digClick3(CCObject* pSender)
{
	static int s_count = -1;
	s_count++;
	if (s_count == 0)
	{
		MineTips* oldp = (MineTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
		if (!oldp)
		{
			oldp = new MineTips();
			oldp->init(MineTips::baijin, pContainer);
			LayerManager::intervalLayer->addChild(oldp, IntervalLayer::IntervalLayerZ_guild_silverMineTips, IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
			oldp->release();
		}
	}
	else
	{
		int i = 2;
		pContainer->dispatchEvent(SilverConst::DIG_MINE, &i);
	}

}
		
// 侦查  令牌ID——0【袭】；1【扰】；2【驰】；3【查】
void MineOpt::searchClick(CCObject* pSender)
{
	int i = SilverConst::TOKEN_SEARCH;
	pContainer->dispatchEvent(SilverConst::CLICK_TOKEN, &i);
}

void MineOpt::setDescription()
{
	char value[100];//分母改成5
	sprintf(value, "%s %d/%d %s", ValuesUtil::Instance()->getString("SLM052").c_str(), _online, 5, getFlourish(_online, 5).c_str());
	_txtPercent->setString(value);
}

int MineOpt::getCapacity(int level)
{
	int capacity = 0;
	switch(level)
	{
		case 1:
			capacity = 12;
			break;
		case 2:
			capacity = 8;
			break;
		case 3:
			capacity = 6;
			break;
		case 4:
			capacity = 3;
			break;
		case 5:
			capacity = 2;
			break;
		default:
			capacity = 2;
			break;
	}
	return capacity;
}