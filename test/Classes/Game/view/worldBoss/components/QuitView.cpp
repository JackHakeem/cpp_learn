#include "QuitView.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "../WorldBossMediator.h"
#include "utils/ValuesUtil.h"
#include "manager/CDManage.h"
#include "CustomCD.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"
#include "BossHPView.h"

QuitView::QuitView()
{
	_nTimeCount = 1800;
	_nLeftTime = 0;
}

QuitView::~QuitView()
{

}

bool QuitView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	_winSize = CCDirector::sharedDirector()->getWinSize();
	this->setIsTouchEnabled(false);
	loadItems();

	return true;
}

void QuitView::loadItems()
{
	// background
	/*
	CCUIBackground * pBack = new CCUIBackground();
	if (pBack)
	{
		bool bVar = pBack->initWithSpriteFrame("ui.png" , ccp(0,0) , ccp(0,0) , CCSizeMake(POSX(200) , POSX(100)) , 255);
		if (bVar)
		{
			this->addChild(pBack , 0);
			pBack->release();
		}
	}
	*/

	// Timer 
	//

	// quit menu
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite || !pPressedSprite || !pSelectdSprite)
	{
		return;
	}
	CCMenuItemSprite *pQuitMenuImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		pSelectdSprite,
		this,
		menu_selector(QuitView::onClickQuit));

	CCSize size = pQuitMenuImg->getContentSize();

	CCMenu * pQuitMenu = CCMenu::menuWithItem(pQuitMenuImg);	
	pQuitMenu->setTouchLayer(TLE::SceneUILayer);
	this->addChild(pQuitMenu , 1);

	_menuPos = pQuitMenu->getPosition();

	CCLabelTTF * pQuitText = new CCLabelTTF();
	if (pQuitText)
	{
		bool var = pQuitText->initWithString(ValuesUtil::Instance()->getString("WBS103").c_str() , 
			CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentCenter , "Arial" ,POSX(24));
		if (var)
		{
			pQuitText->setPosition(ccp(size.width/2 , size.height /2));
			pQuitText->setColor(ccc3(255,233,12));
			pQuitMenuImg->addChild(pQuitText , 0);
			pQuitText->release();
		}
	}

	// CD text
	CCLabelTTF * pActivityCDText = new CCLabelTTF();
	if (pActivityCDText)
	{
		bool var = pActivityCDText->initWithString("" , 
			CCSizeMake(POSX(240) , POSX(30)) , CCTextAlignmentCenter , "Arial" ,POSX(24));
		if (var)
		{
			pActivityCDText->setTag(TAG_CD_Second);
			pActivityCDText->setColor(ccc3(233,133,25));
			pActivityCDText->setPosition(ccp(_winSize.width + POSX(280) , _winSize.height-POSX(80)));
			this->addChild(pActivityCDText , 8);
			pActivityCDText->release();
		}
	}
}

void QuitView::onClickQuit(CCObject * pSender)
{
	WorldBossMediator * pMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pMediator)
	{
		pMediator->requestQuit();
	}
}

void QuitView::updateCD(int nActivityCD)
{
	int type = CDManage::WorldBoss_activityCD;
	CDManage::Instance()->addNewCD( type , nActivityCD);

	//std::string str = TimerManage::formatServerTimeToDate(nActivityCD);
	//CCLog("***************%s" , str.c_str());

	if (this->getChildByTag(TAG_CD + type))
	{
		if (CDManage::Instance()->getCustomCD(type))
		{
			CDManage::Instance()->deleteCustomCD(type);
		}			
		this->removeChildByTag(TAG_CD + type , true);
	}
	/*
	bool isReady = CDManage::Instance()->getCDReady(type);
	if (isReady)
	{
		this->setIsVisible(false);
	}
	else
	{
		this->setIsVisible(true);
	}		
	*/
	CustomCD * pCustomCD = new CustomCD(type);
	if (pCustomCD)
	{			
		//pCustomCD->setPosition(ccp(POSX(620),POSX(315 - (i-begin)*40)));
		pCustomCD->setTag(TAG_CD + type);

		pCustomCD->reinit();

		pCustomCD->setPosition(ccp(_menuPos.x + POSX(140), _menuPos.y - POSX(40)));

		this->addChild(pCustomCD , 3);

		pCustomCD->release();
	}
}

void QuitView::runActivityCD( int lefttime)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(QuitView::step) , this);

	_nLeftTime = lefttime;
	if (_nLeftTime <= 1)
	{
		// send quit request and show quit tips
		updateCDText(0);
		onClickQuit(0);
		return;
	}
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(QuitView::step) , this ,1 ,false);
}

void QuitView::step(ccTime dt)
{
	--_nLeftTime;
	updateCDText(_nLeftTime);

	if (_nLeftTime <= 1)
	{
		// send quit request and show quit tips
		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(QuitView::step) , this);
		updateCDText(0);
		onClickQuit(0);
		return;
	}

	if (_nLeftTime > 600)
	{
		updateBossHP((float)_nLeftTime/1800);
	}
}

void QuitView::updateCDText(int timeSecond)
{
	char path[128] = {0};
	sprintf(path , ValuesUtil::Instance()->getString("WBS121").c_str() , timeSecond);

	CCLabelTTF * pActivityCDText = (CCLabelTTF *)this->getChildByTag(TAG_CD_Second);
	if (pActivityCDText)
	{
		pActivityCDText->setString(timeSecond ? path : ValuesUtil::Instance()->getString("WBS122").c_str());
	}
}

void QuitView::updateBossHP(float percent)
{
	WorldBossMainView * pWBMainView = ViewManager::getInstance()->_pWBMainView;	
	if ( pWBMainView )
	{
		BossHPView * pBossHPView = (BossHPView * )pWBMainView->getChildByTag(WorldBossMainView::TAG_BossHPView);
		if (pBossHPView)
		{
			pBossHPView->updateHP(0.1 , -1 , -1 , percent);
		}
	}
}