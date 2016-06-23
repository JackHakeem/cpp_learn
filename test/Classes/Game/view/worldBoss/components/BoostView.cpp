#include "BoostView.h"
#include "../WorldBossMediator.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "Confirm.h"
#include "model/player/RoleManage.h"
#include "Alert.h"

BoostView::BoostView()
{

}

BoostView::~BoostView()
{

}

bool BoostView::init()
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

void BoostView::loadItems()
{
	// Gold boost button 
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/worldboss/res_worldboss_en.plist");
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("worldboss/golden0.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("worldboss/golden1.png");
	if(!pNormalSprite || !pPressedSprite)
	{
		return ;
	}
	CCMenuItemSprite *pGoldBoostImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this,
		menu_selector(BoostView::onRequestConfirm));
	pGoldBoostImg->setTag(31);
	pGoldBoostImg->setPosition(ccp(POSX(-70), 0));
	
	// Practice boost button
	CCSprite *pNormalSprite1 = CCSprite::spriteWithSpriteFrameName("worldboss/pracen0.png");
	CCSprite *pPressedSprite1 = CCSprite::spriteWithSpriteFrameName("worldboss/pracen1.png");
	if(!pNormalSprite1 || !pPressedSprite1)
	{
		return ;
	}
	CCMenuItemSprite *pPracBoostImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite1,
		pPressedSprite1,
		this,
		menu_selector(BoostView::onRequestConfirm));
	pPracBoostImg->setTag(32);
	pPracBoostImg->setPosition(ccp(POSX(70), 0));

	CCMenu * pBoostMenu = CCMenu::menuWithItems(pGoldBoostImg , pPracBoostImg , 0);
	pBoostMenu->setTouchLayer(TLE::SceneUILayer);
	//pBoostMenu->setPosition(ccp( POSX(0) , POSX(0)));
	this->addChild(pBoostMenu , 0);

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/worldboss/res_worldboss_en.plist");

	// boost result text
	char path[32] = {0};
	printf(path , ValuesUtil::Instance()->getString("WBS001").c_str() , 0);
	CCLabelTTF * pBoostText = CCLabelTTF::labelWithString(
		path,
		CCSizeMake(POSX(600) , POSX(30)), 
		CCTextAlignmentCenter,
		"Arial",
		POSX(24));
	pBoostText->setTag(TAG_Boost_text);
	pBoostText->setColor(ccc3(12,233,25));
	pBoostText->setPosition(ccp(pBoostMenu->getPosition().x , pBoostMenu->getPosition().y + POSX(50)));
	this->addChild(pBoostText , 2);

}

void BoostView::requestGoldBoost(CCObject * pSender)
{
	WorldBossMediator * pWBMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pWBMediator)
	{
		pWBMediator->requestGoldBoost();
	}

	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(
		WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy && _confirmBuy->m_alert && _confirmBuy->m_alert->pMenu)
	{
		int btncount = _confirmBuy->m_alert->pMenu->getChildren()->count();
		for (int i = 0; i < btncount; i++)
		{
			CCMenuItemSprite *newButton = (CCMenuItemSprite*)_confirmBuy->m_alert->pMenu->getChildByTag(i);
			newButton->setIsEnabled(false);
		}
	}
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(BoostView::lockBtn),
		this,0.2f,false);
}

void BoostView::lockBtn(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(BoostView::lockBtn), this);
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(
		WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy && _confirmBuy->m_alert && _confirmBuy->m_alert->pMenu)
	{
		int btncount = _confirmBuy->m_alert->pMenu->getChildren()->count();
		for (int i = 0; i < btncount; i++)
		{
			CCMenuItemSprite *newButton = (CCMenuItemSprite*)_confirmBuy->m_alert->pMenu->getChildByTag(i);
			newButton->setIsEnabled(true);
		}
	}
}

void BoostView::requestPracBoost(CCObject * pSender)
{
	WorldBossMediator * pWBMediator = (WorldBossMediator *)g_pFacade->retrieveMediator(AppFacade_WorldBoss_Mediator);
	if (pWBMediator)
	{
		pWBMediator->requestPracBoost();
	}
}

void BoostView::resetBoostResultText(int percent)
{
	char path[128] = {0};
	sprintf(path , ValuesUtil::Instance()->getString("WBS001").c_str() , percent);

	CCLabelTTF * pBoostText = (CCLabelTTF *)this->getChildByTag(TAG_Boost_text);
	if (pBoostText)
	{
		pBoostText->setString(path);
	}
}

void BoostView::onRequestConfirm(CCObject * pSender)
{
	if (!pSender)	{		return;	}
	CCMenuItemImage * pMenu = (CCMenuItemImage *)pSender;

	std::string strTips("");
	Confirm * pConfirmBuy = new Confirm();

	int tag = pMenu->getTag();
	if (tag == 31)
	{
		pConfirmBuy->initWithParam(
			ValuesUtil::Instance()->getString("WBS125").c_str(),
			this,
			menu_selector(BoostView::requestGoldBoost),
			menu_selector(BoostView::onCancel));
	}
	else if (tag == 32)
	{
		char path[256] = {0};
		int lev = RoleManage::Instance()->roleLev() * 9.5;
		sprintf(path , ValuesUtil::Instance()->getString("WBS126").c_str() , lev);
		pConfirmBuy->initWithParam(
			path,
			this,
			menu_selector(BoostView::requestPracBoost),
			menu_selector(BoostView::onCancel));
	}	
	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
	LayerManager::windowLayer->addChild(pConfirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
	pConfirmBuy->release();

}

void BoostView::onCancel(CCObject * pSender)
{
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}  
}