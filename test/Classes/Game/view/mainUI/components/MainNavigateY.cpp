
#include "MainNavigateY.h"
#include "utils/ScaleUtil.h"

const float Ydistance = 90.f;

MainNavigateY::MainNavigateY()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	m_slot = 0;
	m_btnCount = 0;
	m_lastTag = -1;
	m_endPos = POS(ccp(870, 110), ScaleUtil::BOTTOM_RIGHT);
	//m_endPos = ccp(winsize.width - 90, 120);
	//this->setPosition(ccp(m_endPos.x, 0));
	//this->setPosition(ccp(0, m_endPos.y - POSX(Ydistance * m_btnCount)));
	//this->setPosition(POS(CCPointZero, ScaleUtil::BOTTOM_RIGHT));
	//setisMenuOpen(false);
	this->disappear();
    _isMenuOpen = false;

	CCMenu* pMainButtonMenu = new CCMenu();
	pMainButtonMenu->init();
	pMainButtonMenu->setPosition( CCPointZero );
	this->addChild(pMainButtonMenu, MainNavigateYZ_menubtn, MainNavigateYTAG_menubtn);
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());

}

MainNavigateY::~MainNavigateY()
{}



void MainNavigateY::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	//float scale = CCDirector::sharedDirector()->getContentScaleFactor();
    // CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(ccp(0, 121));
    glEnable(GL_SCISSOR_TEST);
	//glScissor(0,0,m_endPos.x, m_endPos.y);
	glScissor(m_endPos.x * scale, m_endPos.y * scale, winsize.width * scale, Ydistance * m_btnCount * scale);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
#else
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	//float scale = CCDirector::sharedDirector()->getContentScaleFactor();
    // CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(ccp(0, 121));
    glEnable(GL_SCISSOR_TEST);
	//glScissor(0,0,m_endPos.x, m_endPos.y);
	glScissor(m_endPos.x * scale, m_endPos.y * scale, winsize.width, Ydistance * m_btnCount);
    CCLayer::visit();
    glDisable(GL_SCISSOR_TEST);
#endif
}

void MainNavigateY::addButton(int32 type, int32 sitNum, CCObject* target, SEL_MenuHandler selector)
{
	CCMenu* menu = (CCMenu*)this->getChildByTag(MainNavigateYTAG_menubtn);
	if (!menu)
	{
		CCLog("error MainNavigateY::addButton 1");
		return;//imposible
	}

	char btnName[40] = "mainUI/mn_btn";
	sprintf(btnName, "mainUI/mny_btn%d_normal.png", type);

	char btnName2[40] = "mainUI/mn_btn";
	sprintf(btnName2, "mainUI/mny_btn%d_pressed.png", type);

	CCNode* pBtn = 0;
	pBtn = this->getChildByTag(type);
	if (pBtn)
	{
		CCLog("error MainNavigateY::addButton 2");
		return;//imposible
	}

	//ÆÁÄ»¿í¸ß
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//¼Ó°´Å¥
	CCSprite *pNormalMainBtnSprite = CCSprite::spriteWithSpriteFrameName(btnName);
	CCSprite *pPressedMainBtnSprite = CCSprite::spriteWithSpriteFrameName(btnName2);
	if(!pNormalMainBtnSprite || !pPressedMainBtnSprite)
	{
		return ;
	}
	CCMenuItemSprite *mainBtn = CCMenuItemSprite::itemFromNormalSprite(
		pNormalMainBtnSprite,
		pPressedMainBtnSprite,
		target, selector);
	//CCSize winsize = CCDirector::sharedDirector()->getWinSize();

	//mainBtn->setPosition(ccp(Xdistance * m_btnCount + mainBtn->getContentSize().width/2, mainBtn->getContentSize().height-45));
	mainBtn->setPosition(/*ccp(POSX(winsize.width - mainBtn->getContentSize().width + 25), POSX(Ydistance * m_btnCount + mainBtn->getContentSize().height/2 + 20))*/
		POS(ccp(870, Ydistance * m_btnCount/* + 20*/), ScaleUtil::BOTTOM_RIGHT));
	mainBtn->setAnchorPoint(CCPointZero);
	menu->addChild(mainBtn, 0, type);
	m_lastTag = type;
	int32 card = 1 << (type-1);
	m_slot += card;
	m_btnCount++;
	//mainBtn->release();
}

bool MainNavigateY::getisMenuOpen()
{
	return _isMenuOpen;
}

void MainNavigateY::disappear()
{
	CCPoint tarpos = ccp(0, m_endPos.y - POSX(Ydistance * m_btnCount));
	this->setPosition(tarpos);
}


void MainNavigateY::setisMenuOpen(bool var)
{
	if (getisMenuOpen() == var)
		return;

	if (var)
	{
		_isMenuOpen = true;
		
		//this->setPosition(ccp(m_endPos.x - Ydistance*m_btnCount, 0));
		this->setPosition(ccp(0, m_endPos.y - POSX(Ydistance * m_btnCount)));
		//CCPoint tarpos = ccp(m_endPos.x, 0);
		CCPoint tarpos = ccp(0, m_endPos.y);

		CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.2f, tarpos));
		this->runAction(changePage);
		//	this->runAction(cocos2d::CCMoveTo::actionWithDuration(ACTIONTIME, tarpos));
	}
	else
	{
		_isMenuOpen = false;

		//this->setPosition(ccp(m_endPos.x, 0));
		this->setPosition(ccp(0, m_endPos.y));
		//CCPoint tarpos = ccp(m_endPos.x - Ydistance*m_btnCount, 0);
		CCPoint tarpos = ccp(0, m_endPos.y - POSX(Ydistance * m_btnCount));

		CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.2f, tarpos));
		this->runAction(changePage);

		//this->runAction(cocos2d::CCMoveTo::actionWithDuration(ACTIONTIME, tarpos));
	}
}

void MainNavigateY::hideButtonByType(int type , bool var)
{
	if (!this->getChildByTag(MainNavigateY::MainNavigateYTAG_menubtn))
	{
		return;
	}	
	CCNode* pBtn = this->getChildByTag(MainNavigateY::MainNavigateYTAG_menubtn)->getChildByTag(type);
	if (pBtn)
	{
		pBtn->setIsVisible(var);
	}
}