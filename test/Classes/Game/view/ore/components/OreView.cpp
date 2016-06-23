#include "OreView.h"
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
#include "OreItem.h"
#include "manager/LangManager.h"
#include "Confirm.h"
#include "socket/command/c43/CCMD438.h"
#include "socket/network/GameServerSocket.h"
#include "manager/ViewManager.h"
#include "PlantView.h"
#include "OreHelpView.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/LevLimitConst.h"
#include "manager/ButtonIDConst.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"
#include "MessageInfoBox.h"

OreView::OreView()
{
	m_iOreNum = -1;
	m_iBuyCount = 0;
	m_iPlantStates = 0;
	_pContainer = 0;
	_btnClose = 0;
}

OreView::~OreView()
{
		ViewManager::getInstance()->oreView = 0;
}

bool OreView::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	key = 0;
	setNeedBg(NeedBg_NO);

	{
		//
		_pContainer = new LayerNode();
		_pContainer->init();
		_pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
		this->addChild(_pContainer, 1);
		_pContainer->release();
	}

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	this->addChild(_bg0, 0);
	_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(175), POSX(38)), ccp(0,0), CCSizeMake(POSX(610), POSX(564)));
	_pContainer->addChild(_bg1, 1);
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(175+24), POSX(38+25)), ccp(0,0), CCSizeMake(POSX(560), POSX(516)));
	_pContainer->addChild(_bg2, 2);
	_bg2->release();

	//X
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(OreView::clickClose) );
		_btnClose->setPosition(ccp(POSX(175+610), POSX(38+564)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_ore-1);
		_pContainer->addChild(buttonMenu, 5);		
	}
	//水晶原石：
	{
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "ORE01" ).c_str(),
			CCSizeMake(POSX(200), POSX(60)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
		txtLabel->setPosition( ccp(POSX(712-150), POSX(640-120)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5 );
		txtLabel->setColor(ccc3(251, 216, 0));
	}
	//star bg
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/ore/3.png");
		_pContainer->addChild(sp, 4);
		sp->release();
		sp->setPosition(ccp(POSX(175+610/2+18), POSX(38+564/2-26)));
	}
	//title
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/ore/1.png");
		_pContainer->addChild(sp, 4);
		sp->release();
		sp->setPosition(ccp(POSX(565-90), POSX(640-55)));
	}
	//buy stone btn
	{

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::WindowLayer_ore-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(OreView::clickBuyStone) );
		_btn->setPosition(ccp(POSX(765-90), POSX(640-235+90)));


		buttonMenu->addChild(_btn, 0);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ORE16" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
	}
	//help btn
	{

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::WindowLayer_ore-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(OreView::clickHelp) );
		_btn->setPosition(ccp(POSX(376-90), POSX(640-235+90)));


		buttonMenu->addChild(_btn, 0);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ORE17" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
	}

	UpdateOre(0, m_iOreNum, m_iBuyCount);

	return true;
}

void OreView::clickBuyStone(CCObject* pSender)
{
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_BuyOreStone , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_BuyOreStone);
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}

	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		return;
	Confirm* pConfirm = new Confirm();
	char strBuy[180];
	sprintf(strBuy, ValuesUtil::Instance()->getString("ORE15").c_str(), m_iBuyCount+2);
	pConfirm->initWithParam(strBuy, this, menu_selector(OreView::handleBuyStone), menu_selector(OreView::handleBuyStoneCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();	
}

void OreView::handleBuyStone(CCObject* pSender)
{
	//apply buy
	CCMD438 cmd;
	GameServerSocket::getInstance()->sendMessage( &cmd );

	//这里需要同步433
	LayerManager::loadingPic->socketWait( WMSG_ORE_RESPONSE, 0, 0);
	//
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void OreView::handleBuyStoneCancel(CCObject* pSender)
{
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
	//WMSG_ORE_RESPONSE
}

void OreView::clickHelp(CCObject* pSender)
{
	OreHelpView* _OreHelpView = (OreHelpView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_ore_help);
	if (!_OreHelpView)
	{
		_OreHelpView = new OreHelpView();
		_OreHelpView->init();
		LayerManager::intervalLayer->addChild(_OreHelpView, IntervalLayer::IntervalLayerZ_ore_help, IntervalLayer::IntervalLayerTAG_ore_help);
		_OreHelpView->release();

		this->setIsVisible(false);
	}

}

void OreView::clickClose(CCObject* pSender)
{
	if (this->getParent())
	{
		OreMediator * pOreMediator = (OreMediator *)g_pFacade->retrieveMediator(AppFacade_ORE);
		if (pOreMediator)
		{
			pOreMediator->m_pOreView = 0;
		}

		this->setisPop(false);

		ViewManager::getInstance()->oreView = 0;
	}

	// update mainnavigate VScroll  //LH20121204
	if (ViewManager::getInstance()->_pVScrollUI)
	{
		ViewManager::getInstance()->_pVScrollUI->resetListView();
	}

	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Ore) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->touchNextScript("addBtn" , ButtonIDConst::ButtonID_Ore);
	}
	else if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Ore) == NewhandManager::Flag_Done)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Ore , NewhandManager::Flag_Close);
		NewhandManager::Instance()->touchNextEvent(NewhandConst::EVENT_ORE_OVER);
		NewhandManager::Instance()->doTaskFollow();
	}
}

void OreView::UpdateOre(uint32 stoneNum, uint32 oreNum, uint32 buyCount)
{
	m_iBuyCount = buyCount;

	if (_pContainer->getChildByTag(9))
		_pContainer->removeChildByTag(9, true);
	{
		char str[50];
		sprintf(str, "%d%s", stoneNum, ValuesUtil::Instance()->getString( "ORE02" ).c_str());
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			str, CCSizeMake(POSX(200), POSX(60)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
		txtLabel->setPosition( ccp(POSX(712-30), POSX(640-120)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5, 9);
		txtLabel->setColor(ccc3(235, 235, 255));
	}

	//星星状态
	if (m_iOreNum != oreNum)
	{
		
		if (_pContainer->getChildByTag(10))
			_pContainer->removeChildByTag(10, true);

		SpriteNode* sp = new SpriteNode();
		if (oreNum == 5)
			sp->initWithFile("assets/ui/ore/2.png");
		else
			sp->initWithFile("assets/ui/ore/5.png");
		_pContainer->addChild(sp, 5, 10);
		sp->release();
		sp->setPosition(ccp(POSX(175+610/2), POSX(38+564/2)));
	}

	CCPoint offset = ccp(-90, 90);
	CCPoint itemPos[5] = 
	{
		ccp(POSX(565-90), POSX(640-237 + 90)),
		ccp(POSX(762-90), POSX(640-385 + 90)),
		ccp(POSX(680-90), POSX(640-583 + 100)),
		ccp(POSX(450-70), POSX(640-583 + 100)),
		ccp(POSX(370-80), POSX(640-385 + 90))
	};

	for (int i = 0; i < 5; i++)
	{
		if (_pContainer->getChildByTag(i))
			_pContainer->removeChildByTag(i, true);

		bool opened = false;//((oreNum-1) >= i)?true:false;

		if ((int)oreNum-1 >= i)
		{
			opened = true;
		}
		else
		{
			opened = false;
		}

		OreItem* node = new OreItem();
		
		node->init(i, opened);
		_pContainer->addChild(node, 6, i);
		node->release();
		node->setPosition(itemPos[i]);
	}
	m_iOreNum = oreNum;

	//new hand
// 	if (!NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Ore))
// 	{
// 		NewhandManager::Instance()->touchNextScript("p" , "ORE");
// 	}
}

void OreView::HandleResponse(uint32 flag)
{
	switch (flag)
	{
	case 0:
		{
			LangManager::msgShow("ORE03");
		}
		break;
	case 1:
		{
			LangManager::msgShow("ORE04");
		}
		break;
	case 2:
		{
			LangManager::msgShow("ORE05");
		}
		break;
	case 3:
		{
			LangManager::msgShow("ORE06");
		}
		break;
	case 4:
		{
			LangManager::msgShow("ORE07");
		}
		break;
	case 5:
		{
			LangManager::msgShow("ORE08");
		}
		break;
	case 6:
		{
			LangManager::msgShow("ORE09");
		}
		break;
	case 7:
		{
			LangManager::msgShow("ORE10");
		}
		break;
	case 8:
		{
			LangManager::msgShow("ORE11");
		}
		break;
	case 9:
		{
			LangManager::msgShow("ORE12");
		}
		break;
	case 10:
		{
			LangManager::msgShow("ORE13");
		}
		break;
	case 11:
		{
			LangManager::msgShow("ORE30");
		}
		break;
	case 12:
		{
			LangManager::msgShow("ORE31");
		}
		break;
	case 13:
		{
			LangManager::msgShow("ORE32");
		}
		break;
	default:
		break;
	}
}

PlantView* OreView::getCurPlantView()
{
	PlantView* p = (PlantView*)LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ore_plant);
	if (p)
		return p;
	else
		return 0;
}

void OreView::UpdatePlantProgress(uint32 progress)
{
	m_iPlantStates = progress;
	PlantView* pPV = getCurPlantView();
	if (pPV)
	{
		uint32 state = GetPlantStateByOreID(pPV->m_iOreID);
		pPV->UpdatePlantState(state);
	}
}

uint32 OreView::GetPlantStateByOreID(uint32 oreID)
{
    if (oreID < 0 || oreID > 4)                                                                                                                                                                     
        return 0;                                                                                                                                                                                   
                                                                                                                                                                                                    
    uint32 wanwei = 10;                                                                                                                                                                              
    for (int i = 0; i < oreID; i++)                                                                                                                                                                 
    {                                                                                                                                                                                               
        wanwei *= 10;                                                                                                                                                                               
    }                                                                                                                                                                                               
                                                                                                                                                                                                    
    uint32 rnt = m_iPlantStates%wanwei;   
	rnt /= (wanwei/10);
    return rnt; 
}

void OreView::clickCloseHandler(CCObject* pSender)
{
	PopContainer::clickCloseHandler(pSender);

	// update mainnavigate VScroll
	if (ViewManager::getInstance()->_pVScrollUI)
	{
		ViewManager::getInstance()->_pVScrollUI->resetListView();
	}

	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Ore) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->touchNextScript("addBtn" , ButtonIDConst::ButtonID_Ore);
	}
	
}

CCNode * OreView::getNewHandItem(int id)
{
	if (!_pContainer)
	{
		return 0;
	}	
	switch (id)
	{
	case 100:
		{
			if (_pContainer->getChildByTag(0))
			{
				return ((OreItem *)_pContainer->getChildByTag(0))->_btnOre;
			}			
		}
		break;
	case 101:
		{
			if (_pContainer->getChildByTag(0)
				&& ((OreItem *)_pContainer->getChildByTag(0))->_plant)
			{
				return ((OreItem *)_pContainer->getChildByTag(0))->_plant->_plantbtn;
			}	
		}
		break;
	case 103:
		{
			return _btnClose;	
		}
		break;
	case 102:
		{
			if (_pContainer->getChildByTag(0)
				&& ((OreItem *)_pContainer->getChildByTag(0))->_plant)
			{
				return ((OreItem *)_pContainer->getChildByTag(0))->_plant->_btnClose;
			}	
		}
		break;
	default:
		break;
	}
	return 0;
}