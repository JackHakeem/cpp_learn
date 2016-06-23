#include "PopUIBg.h"
#include "CCUIBackground.h"
#include "manager/PopManage.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "model/newhand/vo/NewhandConst.h"

PopUIBg::PopUIBg()
{}

PopUIBg::~PopUIBg()
{}

bool PopUIBg::init()
{
	if(!LayerNode::init())
		return false;
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	this->addChild(_bg0, PopUIBgZ_bg0, PopUIBgTAG_bg0);
	_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", POS(ccp(16.0f, 12.0f), ScaleUtil::CENTER_TOP), ccp(0,0), CCSizeMake(w_bg1, h_bg1));
	this->addChild(_bg1, PopUIBgZ_bg1, PopUIBgTAG_bg1);
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png", POS(ccp(25.0f, 32.0f), ScaleUtil::CENTER_TOP), ccp(0,0), CCSizeMake(w_bg2, h_bg2));
	this->addChild(_bg2, PopUIBgZ_bg2, PopUIBgTAG_bg2);
	_bg2->release();

	//
    
	CCSprite *pBackNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_1.png");
	CCSprite *pBackPressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_1.png");
	CCMenuItemSprite *_btnBack = CCMenuItemSprite::itemFromNormalSprite(
		pBackNormalSprite,
		pBackPressedSprite,
		this,
		menu_selector(PopUIBg::clickBackHandler) );
	_btnBack->setPosition(ccp(POSX(64),
		screenSize.height-POSX(54))) ;
	_btnBack->setIsVisible(false);

	CCMenu *buttonMenuBack = new CCMenu();
	buttonMenuBack->init();
	buttonMenuBack->addChild(_btnBack, 0, 0);
	buttonMenuBack->setPosition(ccp(0, 0));
	buttonMenuBack->setTouchLayer(TLE::WindowLayer_PopUIBgTAG_btn_1-2);
	this->addChild(buttonMenuBack, PopUIBgZ_btn_1, PopUIBgTAG_btn_1);
	buttonMenuBack->release();
    
	
	//
	CCSprite *pCloseNormalSprite = new CCSprite();
    pCloseNormalSprite->initWithSpriteFrameName("popuibg/btn_close_normal.png");
	CCSprite *pClosePressedSprite = new CCSprite();
    pClosePressedSprite->initWithSpriteFrameName("popuibg/btn_close_pressed.png");
	CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
		pCloseNormalSprite,
		pClosePressedSprite,
		this, 
		menu_selector(PopUIBg::clickCloseHandler) );
	_btnX->setPosition(ccp(screenSize.width - POSX(32)/*_btnBack->getContentSize().width/4*/,
		screenSize.height- POSX(28)/*_btnBack->getContentSize().height/2*/));
    pCloseNormalSprite->release();
    pClosePressedSprite->release();

	CCMenu *buttonMenu = new CCMenu();
	buttonMenu->init();
	buttonMenu->addChild(_btnX, 0, 0);
	buttonMenu->setPosition(ccp(0, 0));
	buttonMenu->setTouchLayer(TLE::WindowLayer_PopUIBgTAG_btn_X-2);
	this->addChild(buttonMenu, PopUIBgZ_btn_X, PopUIBgTAG_btn_X);
	//NewhandConst::Instance()->registerItem(NewhandConst::ITEM_BAG_CLOSE, buttonMenu);
	buttonMenu->setIsVisible(true);
	buttonMenu->release();


	this->setContentSize(CCSizeMake(w_bg1, h_bg1));
	return true;
}

void PopUIBg::clickBackHandler(CCObject* pSender)
{
	//setisPop(false);
	g_pPopManage->handleBackHandler();
}

void PopUIBg::clickCloseHandler(CCObject* pSender)
{
	//setisPop(false);
	g_pPopManage->handleCloseHandler();
}

void PopUIBg::setBackBtnShow(bool show)
{
	CCMenu *buttonMenuBack = (CCMenu*)this->getChildByTag(PopUIBgZ_btn_1);
	if (!buttonMenuBack) return;
	if (show)
	{
		buttonMenuBack->setIsVisible(true);
	}
	else
	{
		buttonMenuBack->setIsVisible(false);
	}
}