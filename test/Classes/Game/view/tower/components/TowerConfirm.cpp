#include "TowerConfirm.h"
#include "Alert.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

TowerConfirm::TowerConfirm()
{}

TowerConfirm::~TowerConfirm()
{}

bool TowerConfirm::initWithParam(std::string str,
	CCObject* target, SEL_MenuHandler selector, SEL_MenuHandler selector2, string TowerConfirmStr )
{
	if (!LayerNode::init())
		return false;
	m_alert = new Alert();
	if (!m_alert) 
		return false;
	else
		this->addChild(m_alert);

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	this->setPosition(ccp(winsize.width/2, winsize.height/2));
	//Ãû×Ö
	std::string explain = str;
	UTF8(explain);
	m_alert->addStr(explain, ccc3(254, 189, 0));

	if ( TowerConfirmStr == "" )
	{
		m_alert->addButton(ValuesUtil::Instance()->getString("CF001").c_str(), target, selector);
	}
	else
	{
		m_alert->addButton( TowerConfirmStr.c_str(), target, selector );
	}
	m_alert->addButton(ValuesUtil::Instance()->getString("CF002").c_str(), target, selector2);
	m_alert->centerShow();

	//// close
	//CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
	//CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
	//CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
	//	pCloseNormalSprite,
	//	pClosePressedSprite,
	//	this, 
	//	menu_selector(TowerConfirm::diappear) );
	//_btnX->setPosition(ccp(POSX(2*121*0.7f+2*10), POSX(120)) );
	//CCMenu *buttonMenu = new CCMenu();
	//buttonMenu->init();
	//buttonMenu->addChild(_btnX, 0, 0);
	//buttonMenu->setPosition(ccp(0, 0));
	//buttonMenu->setTouchLayer(TLE::TipsLayer_Alert);
	//m_alert->addChild(buttonMenu);
	//buttonMenu->setIsVisible(true);
	//buttonMenu->release();

	return true;
}

bool TowerConfirm::initWithString(std::string str)
{
	if (!LayerNode::init())
		return false;
	m_alert = new Alert();
	if (!m_alert) 
		return false;
	else
		this->addChild(m_alert);

	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	this->setPosition(ccp(winsize.width/2, winsize.height/2));
	//Ãû×Ö
	std::string explain = str;
	UTF8(explain);
	m_alert->addStr(explain, ccc3(254, 189, 0));
	m_alert->addButton(ValuesUtil::Instance()->getString("CF001").c_str(),
		this, menu_selector(TowerConfirm::handleCancel));
	m_alert->centerShow();
	int btncount = m_alert->pMenu->getChildren()->count();
	for (int i = 0; i < btncount; i++)
	{
		m_alert->pMenu->getChildByTag(i)->setScale(1.0f);
		m_alert->pMenu->getChildByTag(i)->setPosition(ccp(
			(POSX(-464/2) + m_alert->pMenu->getChildByTag(i)->getContentSize().width/2 + POSX(170)),
			POSX(-130/2+40)));
	}

	//// close
	//CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
	//CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
	//CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
	//	pCloseNormalSprite,
	//	pClosePressedSprite,
	//	this, 
	//	menu_selector(TowerConfirm::diappear) );
	//_btnX->setPosition(ccp(POSX(2*121*0.7f+2*10), POSX(120)) );
	//CCMenu *buttonMenu = new CCMenu();
	//buttonMenu->init();
	//buttonMenu->addChild(_btnX, 0, 0);
	//buttonMenu->setPosition(ccp(0, 0));
	//buttonMenu->setTouchLayer(TLE::TipsLayer_Alert);
	//m_alert->addChild(buttonMenu);
	//buttonMenu->setIsVisible(true);
	//buttonMenu->release();

	return true;
}

void TowerConfirm::handleCancel(CCObject* pSender)
{
	if (this->getParent())
		this->getParent()->removeChild(this, true);
}

void TowerConfirm::diappear( CCObject* pSender )
{
	if (this->getParent())
		this->getParent()->removeChild(this, true);
}


void TowerConfirm::onEnter()
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::PreTipsLayer, true);
	CCLayer::onEnter();
}

void TowerConfirm::onExit()
{
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}	

bool TowerConfirm::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}