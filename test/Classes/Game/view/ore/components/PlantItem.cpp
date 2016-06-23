#include "PlantItem.h"
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


PlantItem::PlantItem()
{
	m_iOreID = 0;
	m_iPlantID = 0;
}

PlantItem::~PlantItem()
{}

bool PlantItem::init(uint32 oreID, uint32 plantID, bool opened)
{
	if (plantID < 0 || plantID > 4)
		return false;

	if (!LayerNode::init())
		return false;

	m_iPlantID = plantID;
	m_iOreID = oreID;
	//X_0 X-1
	{
		CCMenuItemImage *_btn = 0;
		if (opened)
		{
			char str[30];
			sprintf(str, "assets/ui/ore/plant/%d_0.png", m_iOreID);
			_btn = CCMenuItemImage::itemFromNormalImage(
				str,
				str,
				this, 
				menu_selector(PlantItem::clickPlant) );		
		}
		else
		{
			char str[30];
			sprintf(str, "assets/ui/ore/plant/%d_1.png", m_iOreID);
			_btn = CCMenuItemImage::itemFromNormalImage(
				str,
				str,
				this, 
				menu_selector(PlantItem::clickPlant) );					
		}

		_btn->setPosition(ccp(POSX(0), POSX(0)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_ore-1);
		this->addChild(buttonMenu, 5);	
	}

	return true;
}

void PlantItem::clickPlant(CCObject* pSender)
{
	//if (LayerManager::tipsLayer->getChildByTag( TipsLayer::TipsLayerTAG_ore_plant))
	//{
	//	return;
	//}
	//PlantView* _plant = new PlantView();
	//_plant->init();
	//_plant->setPosition(ccp(0, 0));
	//LayerManager::tipsLayer->addChild(_plant, TipsLayer::TipsLayerZ_ore_plant, TipsLayer::TipsLayerTAG_ore_plant);
	//_plant->release();

	////
	//CCMD434 cmd;
	//GameServerSocket::getInstance()->sendMessage( &cmd );
}

void PlantItem::clickPlantOpen(CCObject* pSender)
{
	//if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
	//	return;
	//Confirm* pConfirm = new Confirm();
	//char strBuy[180];
	//sprintf(strBuy, ValuesUtil::Instance()->getString("ORE14").c_str(), UP_ORE_NEED_GOLD[m_oreID]);
	//pConfirm->initWithParam(strBuy, this, menu_selector(PlantItem::handleBuy), menu_selector(PlantItem::handleBuyCancel));
	//LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	//pConfirm->release();
}

