
#include "MainNavigateX.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

const float Xdistance = 90.f;
const float ACTIONTIME = 0.2f;

const int posMap[] = {1 , 2 , 9 ,  4 ,10 , 13, 6 ,7 , 12/* ,11 */}; // mainnavigateX : posMap[pos] = type;

MainNavigateX::MainNavigateX()
{
	CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	m_slot = 0;
	m_btnCount = 0;
	m_lastTag = -1;
	memset(m_posArr , 0 , sizeof(m_posArr));

	m_endPos = POS(ccp(850, 120), ScaleUtil::BOTTOM_RIGHT);
	//this->setPosition(ccp(m_endPos.x, 0));
	this->setPosition(POS(CCPointZero, ScaleUtil::BOTTOM_RIGHT));

	//setisMenuOpen(false);
	this->disappear();
    _isMenuOpen = false;

	CCMenu* pMainButtonMenu = new CCMenu();
	pMainButtonMenu->init();
	pMainButtonMenu->setPosition( CCPointZero );
	this->addChild(pMainButtonMenu, MainNavigateXZ_menubtn, MainNavigateXTAG_menubtn);
	this->setContentSize(CCDirector::sharedDirector()->getWinSize());
	//this->setIsTouchEnabled (true);
}

MainNavigateX::~MainNavigateX()
{}


void MainNavigateX::visit()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	float scale = ScaleUtil::Instance()->getScaleFactoryOnAndroid(); 
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 0, m_endPos.x * scale, m_endPos.y * scale);
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#else
	float scale = CCDirector::sharedDirector()->getContentScaleFactor();
	glEnable(GL_SCISSOR_TEST);
	glScissor(0, 0, m_endPos.x * scale, m_endPos.y * scale);
	CCLayer::visit();
	glDisable(GL_SCISSOR_TEST);
#endif
	//CCSize winsize = CCDirector::sharedDirector()->getWinSize();
	//float scale = CCDirector::sharedDirector()->getContentScaleFactor();
 //  // CCPoint convertedLocationLowerLeft = this->getParent()->convertToWorldSpace(ccp(0, 121));

}

void MainNavigateX::addButton(int32 type, int32 sitNum, CCObject* target, SEL_MenuHandler selector)
{
	CCMenu* menu = (CCMenu*)this->getChildByTag(MainNavigateXTAG_menubtn);
	if (!menu)
	{
		CCLog("error MainNavigateX::addButton 1");
		return;//imposible
	}


	char btnName[40] = "mainUI/mn_btn";
	sprintf(btnName, "mainUI/mn_btn%d_normal.png", type);

	char btnName2[40] = "mainUI/mn_btn";
	sprintf(btnName2, "mainUI/mn_btn%d_pressed.png", type);

	char btnName3[40] = "mainUI/mn_3btn";
	sprintf(btnName3, "mainUI/mn_3btn%d.png", type);

	CCNode* pBtn = 0;
	pBtn = menu->getChildByTag(type);
	if (pBtn)
	{
		CCLog("error MainNavigateX::addButton 2");
		return;//imposible
	}

	//ÆÁÄ»¿í¸ß
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//¼Ó°´Å¥
	CCSprite *pNormalMainBtnSprite = CCSprite::spriteWithSpriteFrameName(btnName);
	CCSprite *pPressedMainBtnSprite = CCSprite::spriteWithSpriteFrameName(btnName2);

	pPressedMainBtnSprite->setScale(1.2f);

	if(!pNormalMainBtnSprite || !pPressedMainBtnSprite)
	{
		return ;
	}
	CCMenuItemSprite *mainBtn = CCMenuItemSprite::itemFromNormalSprite(
		pNormalMainBtnSprite,
		pPressedMainBtnSprite,
		target,
		selector);
		//mainBtn->setScale(POSX(1.0f));

	CCSize size = pPressedMainBtnSprite->getContentSize();
	float scale = pPressedMainBtnSprite->getScale();
	CCPoint pos = pPressedMainBtnSprite->getPosition();
	pPressedMainBtnSprite->setPosition(ccp(pos.x - size.width*(scale-1)/2 , pos.y));

	if(!mainBtn)
	{
		return ;
	}
	mainBtn->setAnchorPoint(CCPointZero);
	mainBtn->setPosition(ccp(POSX(Xdistance * m_btnCount), POSX(10)));

	menu->addChild(mainBtn, 0, type);
	m_lastTag = type;
	int32 card = 1 << (type-1);
	m_slot += card;

	m_posArr[m_btnCount] = type;

	m_btnCount++;
	//mainBtn->release();


	rePosition();
}

void MainNavigateX::rePosition()
{
	CCMenu* pMenu = (CCMenu*)this->getChildByTag(MainNavigateXTAG_menubtn);
	if (pMenu)
	{
		int a[32] = {0};
		memcpy((void *)&a , (void *)m_posArr , sizeof(m_posArr));
		reSort(a , sizeof(a)/sizeof(int));
		for (int i = 0 ; i <  sizeof(a)/sizeof(int); i ++)
		{
			int k = a[i];
			CCMenuItemSprite * pMenuSprite = (CCMenuItemSprite * )pMenu->getChildByTag(a[i]);
			if (pMenuSprite && a[i])
			{
				pMenuSprite->setPosition(ccp(POSX(Xdistance * i), POSX(10)));
			}
		}
	}
}

void MainNavigateX::reSort(int a[], int len)
{
	for (int i = 0 ; i < len ; i++)
	{
		for (int j = i+1 ; j < len ; j++)
		{
			if (!a[i] || !a[j])
			{
				continue;
			}			
			if (getIndex(a[j]) < getIndex(a[i]))
			{
				int p = a[j];
				a[j] = a[i];
				a[i] = p;
			}
		}
	}
}

int MainNavigateX::getIndex(int n )
{
	int len = sizeof(posMap)/sizeof(int);
	for (int i = 0 ; i < len ; i++)
	{
		if (posMap[i] == n)
		{
			return i;
		}		
	}
	return -1;
}

bool MainNavigateX::getisMenuOpen()
{
	return _isMenuOpen;
}

void MainNavigateX::disappear()
{

	CCPoint tarpos = ccp(m_endPos.x, 0);

	this->setPosition(tarpos);
}

void MainNavigateX::setisMenuOpen(bool var)
{
	if (getisMenuOpen() == var)
		return;

	if (var)
	{
		_isMenuOpen = true;

		this->setPosition(ccp(m_endPos.x, 0));
		CCPoint tarpos = ccp(m_endPos.x - POSX(Xdistance*m_btnCount), 0);


		CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.2f, tarpos));
		this->runAction(changePage);


		//this->runAction(cocos2d::CCMoveTo::actionWithDuration(ACTIONTIME, tarpos));
	}
	else
	{
		_isMenuOpen = false;

		this->setPosition(ccp(m_endPos.x - POSX(Xdistance*m_btnCount), 0));

		CCPoint tarpos = ccp(m_endPos.x, 0);

		CCEaseBounce* changePage = CCEaseBounce::actionWithAction(CCMoveTo::actionWithDuration(0.2f, tarpos));
		this->runAction(changePage);
		//	this->runAction(cocos2d::CCMoveTo::actionWithDuration(ACTIONTIME, tarpos));
	}
}

void MainNavigateX::registerWithTouchDispatcher()
{
	this->setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::SceneUILayer+2, false);
}

bool MainNavigateX::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CCLog("TLE====>MainNavigateX");

	CCMenu* menu = (CCMenu*)this->getChildByTag(MainNavigateXTAG_menubtn);
	if (menu)
	{
		menu->kkTouchBegan(touch, event);
		return true;
	}
	
	return false;	
}

void MainNavigateX::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	CCMenu* menu = (CCMenu*)this->getChildByTag(MainNavigateXTAG_menubtn);
	if (menu)
		menu->kkTouchEnded(touch, event);	
}