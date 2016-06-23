#include "OreItem.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "PopUIBg.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "CCUIBackground.h"
#include "view/ore/OreMediator.h"
#include "control/AppFacade.h"
#include "Confirm.h"
#include "socket/network/GameServerSocket.h"
#include "socket/command/c43/CCMD432.h"
#include "socket/command/c43/CCMD434.h"
#include "PlantView.h"
#include "CustomCD.h"
#include "manager/CDManage.h"
#include "manager/ViewManager.h"
#include "OreView.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/LevLimitConst.h"

const int UP_ORE_NEED_GOLD[5] = {0, 200, 300, 400, 800};

OreItem::OreItem()
{
	m_oreID = 0;
	_btnOre = 0;
	_plant = 0;
}

OreItem::~OreItem()
{}

bool OreItem::init(uint32 oreID, bool opened)
{
	if (oreID < 0 || oreID > 4)
		return false;
	if (!LayerNode::init())
		return false;

	m_oreID = oreID;
	//bg
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/ore/6.png");
		this->addChild(sp, 0);
		sp->release();
		sp->setPosition(ccp(POSX(0), POSX(0)));
		//sp->setScale(0.3f);
	}
	//ore%d
	{
		if (opened)
		{
			char str[30];
			sprintf(str, "assets/ui/ore/ore%d.png", oreID);
			_btnOre = CCMenuItemImage::itemFromNormalImage(
				str,
				str,
				this, 
				menu_selector(OreItem::clickOre) );		
		}
		else
		{
			_btnOre = CCMenuItemImage::itemFromNormalImage(
				"assets/ui/ore/ore_ignore.png",
				"assets/ui/ore/ore_ignore.png",
				this, 
				menu_selector(OreItem::clickOreOpen) );					
		}

		_btnOre->setPosition(ccp(POSX(0), POSX(0)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnOre, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_ore-1);
		this->addChild(buttonMenu, 5);	
	}

	{
		CustomCD* cd = new CustomCD( CDManage::ORE_0+oreID );
		cd->setPosition(ccp(POSX(-80), POSX(-80)));
		this->addChild( cd, 7, 10);

		cd->release(); 
		cd->reinit();
	}


	return true;
}

void OreItem::clickOre(CCObject* pSender)
{
	if (isInCD())
	{
		return;
	}
	if (LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ore_plant))
	{
		return;
	}
	_plant = new PlantView();
	_plant->init(m_oreID);
	_plant->setPosition(ccp(0, 0));
	LayerManager::intervalLayer->addChild(_plant, IntervalLayer::IntervalLayerZ_ore_plant, IntervalLayer::IntervalLayerTAG_ore_plant);
	_plant->release();

	//
	CCMD434 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );

	// new hand
 	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Ore) == NewhandManager::Flag_New)
 	{
 		NewhandManager::Instance()->touchNextEvent(202);
 	}
}

bool OreItem::isInCD()
{
	bool isInCD = false;

	CustomCD * pCustomCD = (CustomCD *)this->getChildByTag(10);
	if (pCustomCD)
	{
		if (pCustomCD->getIsLock())
		{
			isInCD = true;
		}
		else
		{
			isInCD = false;
		}
	}
	
	return isInCD;
}

void OreItem::clickOreOpen(CCObject* pSender)
{
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		return;
	Confirm* pConfirm = new Confirm();
	char strBuy[180];
	sprintf(strBuy, ValuesUtil::Instance()->getString("ORE14").c_str(), UP_ORE_NEED_GOLD[ViewManager::getInstance()->oreView->m_iOreNum]);
	pConfirm->initWithParam(strBuy, this, menu_selector(OreItem::handleBuy), menu_selector(OreItem::handleBuyCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();
}

void OreItem::handleBuy(CCObject* pSender)
{
	//apply buy
	CCMD432 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );
	//这里需要同步433
	LayerManager::loadingPic->socketWait( WMSG_ORE_RESPONSE, 0, 0);
	//
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void OreItem::handleBuyCancel(CCObject* pSender)
{
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
	//WMSG_ORE_RESPONSE
}