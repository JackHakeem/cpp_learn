#include "DeathView.h"
#include "CCUIBackground.h"
#include "utils/ScaleUtil.h"
#include "../WorldBossMediator.h"
#include "manager/CDManage.h"
#include "CustomCD.h"
#include "utils/ValuesUtil.h"
#include "model/player/RoleManage.h"
#include "view/fight/callback/FightFollowWorldBossAction.h"
#include "Confirm.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"
#include "model/scene/vo/SceneConst.h"

DeathView::DeathView()
{
	_nCount = 0;
	_isInCD = false;
}

DeathView::~DeathView()
{

}

bool DeathView::init()
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

void DeathView::loadItems()
{
	// background
	CCUIBackground * pBack = new CCUIBackground();
	if (pBack)
	{
		bool bVar = pBack->initWithSpriteFrame("ui.png" , ccp(0,0) , ccp(0,0) , CCSizeMake(POSX(320), POSX(180)) , 255);
		if (bVar)
		{
			CCSize size = pBack->getContentSize();
			pBack->setPosition(ccp(_winSize.width /2 -  size.width/2 , _winSize.height/2 - size.height/2));
			this->addChild(pBack , 0);
			pBack->release();
		}
	}

	// menus
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite || !pPressedSprite || !pSelectdSprite)
	{
		return;
	}
	CCMenuItemSprite *pRebornMenuImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		pSelectdSprite,
		this,
		menu_selector(DeathView::onRequestConfirm));
	//pRebornMenuImg->setIsEnabled(false);
	pRebornMenuImg->setTag(31);
	pRebornMenuImg->setPosition(ccp(POSX(-70), 0));


	CCSize size = pRebornMenuImg->getContentSize();

	CCLabelTTF * pRebornText = new CCLabelTTF();
	if (pRebornText)
	{
		bool var = pRebornText->initWithString(ValuesUtil::Instance()->getString("WBS104").c_str() , 
			CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentCenter , "Arial" ,POSX(24));
		if (var)
		{
			pRebornText->setPosition(ccp(size.width/2 , size.height /2));
			pRebornText->setColor(ccc3(255,233,12));
			pRebornMenuImg->addChild(pRebornText , 0);
			pRebornText->release();
		}
	}

	CCSprite *pNormalSprite1 = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite1 = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite1 = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(!pNormalSprite1 || !pPressedSprite1 || !pSelectdSprite1)
	{
		return;
	}
	CCMenuItemSprite *pReLiveMenuImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite1,
		pPressedSprite1,
		pSelectdSprite1,
		this,
		menu_selector(DeathView::onRequestConfirm));
	pReLiveMenuImg->setTag(32);
	pReLiveMenuImg->setPosition(ccp(POSX(70), 0));

	CCLabelTTF * pReliveText = new CCLabelTTF();
	if (pReliveText)
	{
		bool var = pReliveText->initWithString(ValuesUtil::Instance()->getString("WBS105").c_str() , 
			CCSizeMake(POSX(120) , POSX(30)) , CCTextAlignmentCenter , "Arial" ,POSX(24));
		if (var)
		{
			pReliveText->setPosition(ccp(size.width/2 , size.height /2));
			pReliveText->setColor(ccc3(255,233,12));
			pReLiveMenuImg->addChild(pReliveText , 0);
			pReliveText->release();
		}
	}

	CCMenu * pReliveMenu = CCMenu::menuWithItems(pRebornMenuImg , pReLiveMenuImg , 0);
	pReliveMenu->setTouchLayer(TLE::SceneUILayer);
	pReliveMenu->setPositionY(_winSize.height/2 + POSX(-30));
	this->addChild(pReliveMenu , 1);

	_menuPos = pReliveMenu->getPosition();

}

void DeathView::onRequestConfirm(CCObject * pSender)
{
	if (!pSender)	{		return;	}
	CCMenuItemSprite * pMenu = (CCMenuItemSprite *)pSender;

	std::string strTips("");
	Confirm * pConfirmBuy = new Confirm();

	int tag = pMenu->getTag();
	if (tag == 31)
	{
		pConfirmBuy->initWithParam(
			ValuesUtil::Instance()->getString("WBS114").c_str(),
			this,
			menu_selector(DeathView::requestReborn),
			menu_selector(DeathView::onCancel));
	}
	else if (tag == 32)
	{
		pConfirmBuy->initWithParam(
			ValuesUtil::Instance()->getString("WBS115").c_str(),
			this,
			menu_selector(DeathView::requestRelive),
			menu_selector(DeathView::onCancel));
	}	
	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
	LayerManager::windowLayer->addChild(pConfirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
	pConfirmBuy->release();

}

void DeathView::onCancel(CCObject * pSender)
{
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}  
}

void DeathView::requestReborn(CCObject * pSender)
{
	WorldBossMediator * pWBMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pWBMediator)
	{
		pWBMediator->requestReborn();
	}

	onCancel(0);
}

void DeathView::requestRelive(CCObject * pSender)
{
	WorldBossMediator * pWBMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pWBMediator)
	{
		pWBMediator->requestRelive();
	}

	onCancel(0);
}

void DeathView::updateCD(int nMoveCD)
{
	int type = CDManage::WorldBoss_moveCD;
	/*
	bool isReady = CDManage::Instance()->getCDReady(type);
	if (isReady)
	{
		CDManage::Instance()->addNewCD( type , nMoveCD);
	}
	else
	{
		return;
	}
	*/

	//std::string str = TimerManage::Instance()->formatServerTimeToDate(nMoveCD);

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

		pCustomCD->setPosition(ccp(_menuPos.x - POSX(90), _menuPos.y + POSX(60)));

		this->addChild(pCustomCD , 3);

		pCustomCD->release();
	}
}

void DeathView::runCD()
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(DeathView::step) , this);
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(DeathView::step) , this , 1 ,false);
	_isInCD = true;
}

void DeathView::step(ccTime dt)
{
	_nCount++;

	// forbidden move
	if (ViewManager::getInstance()->_scene 
		&& ViewManager::getInstance()->_scene->_role
		&& ViewManager::getInstance()->_scene->_role->poseState)
	{
		ViewManager::getInstance()->_scene->_role->poseState->state(SceneConst::STAND);
	}

	if (_nCount > 27)
	{
		_nCount = 0;
		_isInCD = false;
		this->setIsVisible(false);

		/*
		// add fight call back
		FightProxy *pFightProxy = (FightProxy *) g_pFacade->retrieveProxy(AppFacade_FIGHT_PROXY_CHANGE);
		if (pFightProxy)
		{
			int curMapID = RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId;
			if (curMapID == 1208)
			{
				pFightProxy->_bData._callbacks.push_back(new FightFollowWorldBossAction());
			}
		}
		*/

		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(DeathView::step) , this);
	}
}

void DeathView::stopCD()
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(DeathView::step) , this);
	_nCount = 0;
	_isInCD = false;
	this->setIsVisible(false);
}