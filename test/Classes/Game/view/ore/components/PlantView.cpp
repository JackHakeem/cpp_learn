#include "PlantView.h"
#include "manager/LangManager.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LayerManager.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "manager/PopEventName.h"
#include "CCUIBackground.h"
#include "manager/ViewManager.h"
#include "OreView.h"
#include "PlantItem.h"
#include "socket/command/c43/CCMD436.h"
#include "socket/command/c43/CCMD437.h"
#include "Confirm.h"
#include "model/newhand/NewhandManager.h"
#include "model/newhand/vo/NewhandConst.h"
#include "manager/LevLimitConst.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"
#include "MessageInfoBox.h"

PlantView::PlantView()
{
	m_iOreID = 0;
	m_iPlantState = 0;
	_plantbtn = 0;
	_btnClose = 0;
}

PlantView::~PlantView()
{}

bool PlantView::init(uint32 oreID)
{
	if (oreID < 0 || oreID > 4)
		return false;

	if (!LayerNode::init())
		return false;

	m_iOreID = oreID;

	{
		//
		_pContainer = new LayerNode();
		_pContainer->init();
		_pContainer->setPosition(POS(ccp(0, 0), ScaleUtil::CENTER));
		this->addChild(_pContainer, 0);
		_pContainer->release();
	}

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

	CCUIBackground* _bg0 = new CCUIBackground();
	_bg0->initWithSpriteFrame("ui2.png", CCPointZero,CCPointZero,screenSize);
	_pContainer->addChild(_bg0, 0);
	_bg0->release();

	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(55), POSX(640-448)), ccp(0,0), CCSizeMake(POSX(820-55), POSX(448-110)));
	_pContainer->addChild(_bg1, 1);
	_bg1->release();

	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(82), POSX(640-380)), ccp(0,0), CCSizeMake(POSX(792-82), POSX(380-127)));
	_pContainer->addChild(_bg2, 2);
	_bg2->release();


	//title
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/ore/1.png");
		_pContainer->addChild(sp, 6);
		sp->release();
		sp->setPosition(ccp(POSX(438), POSX(640-117)));
	}

	//X
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
		_btnClose = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(PlantView::clickClose) );
		_btnClose->setPosition(ccp(POSX(817), POSX(640-112)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_ore-1);
		_pContainer->addChild(buttonMenu, 5);		
	}

	//plant btn
	{

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_ore-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		_plantbtn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(PlantView::clickPlant) );
		_plantbtn->setPosition(ccp(POSX(441), POSX(640-415)));


		buttonMenu->addChild(_plantbtn, 0);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ORE18" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_plantbtn->getContentSize().width/2, _plantbtn->getContentSize().height/2+2.0f));
		_plantbtn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
	}
	//refresh btn
	{

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_ore-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(PlantView::clickRefresh) );
		_btn->setPosition(ccp(POSX(592), POSX(640-336)));


		buttonMenu->addChild(_btn, 0);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ORE19" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
	}
	//full lv  btn
	{

		CCMenu *buttonMenu = new CCMenu();
		buttonMenu->init();
		buttonMenu->setPosition(ccp(POSX(0), POSX(0)));
		buttonMenu->setTouchLayer(TLE::IntervalLayer_ore-1);
		_pContainer->addChild(buttonMenu, 5);	
		buttonMenu->release();

		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(PlantView::clickFullLv) );
		_btn->setPosition(ccp(POSX(730), POSX(640-336)));


		buttonMenu->addChild(_btn, 0);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString( "ORE20" ).c_str(), CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentCenter, "Arial", POSX(24));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(251, 216, 0));
	}
	//原石品质：
	{
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "ORE21" ).c_str(),
			CCSizeMake(POSX(200), POSX(60)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
		txtLabel->setPosition( ccp(POSX(102), POSX(640-335)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5 );
		txtLabel->setColor(ccc3(251, 216, 0));
	}
	//加工收益：
	{
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( "ORE22" ).c_str(),
			CCSizeMake(POSX(200), POSX(60)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
		txtLabel->setPosition( ccp(POSX(102), POSX(640-380)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5 );
		txtLabel->setColor(ccc3(251, 216, 0));
	}

	//5 plant bg
	for (int i = 0; i < 5; i++)
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/ore/6.png");
		_pContainer->addChild(sp, 4);
		sp->release();
		sp->setPosition(ccp(POSX(150+i*145), POSX(640-200)));
	}
	//4 arrow
	for (int i = 0; i < 4; i++)
	{
		SpriteNode* sp = new SpriteNode();
		sp->initWithFile("assets/ui/ore/4.png");
		_pContainer->addChild(sp, 4);
		sp->release();
		sp->setPosition(ccp(POSX(223+i*145), POSX(640-200)));
	}
	//
	ccColor3B pinzhi[5] = 
	{
		ccc3(255,255,255),
		ccc3(0,128,128),
		ccc3(0, 240, 240),
		ccc3(140, 26, 255),
		ccc3(236, 6, 64)
	};
	for (int i = 0; i < 5; i++)
	{
		char str[20];
		sprintf(str, "ORE2%d", i+3);
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( str ).c_str(),
			CCSizeMake(POSX(200), POSX(60)), CCTextAlignmentCenter, g_sSimHeiFont, POSX(24) );
		txtLabel->setPosition(ccp(POSX(150+i*145), POSX(640-270)));
		_pContainer->addChild( txtLabel, 6 );
		txtLabel->setColor(pinzhi[i]);
	}



	if (ViewManager::getInstance()->oreView)
		ViewManager::getInstance()->oreView->setIsVisible(false);


	return true;

}

void PlantView::clickPlant(CCObject* pSender)
{
	//new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Ore) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_Ore , NewhandManager::Flag_Done);
		NewhandManager::Instance()->touchNextEvent(204);
	}
	

	//
	CCMD437 cmd;
	cmd.a_oreID = m_iOreID;
	GameServerSocket::getInstance()->sendMessage( &cmd );
	//这里需要同步433
	LayerManager::loadingPic->socketWait( WMSG_ORE_RESPONSE, 0, 0);

	
	//close
	clickClose(0);
	
}

void PlantView::clickRefresh(CCObject* pSender)
{
	static int firstClickCount = 0;
	
	if (firstClickCount == 0)
	{
		firstClickCount++;

		if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
			return;
		Confirm* pConfirm = new Confirm();
		char str[180];
		sprintf(str, ValuesUtil::Instance()->getString("ORE28").c_str());
		pConfirm->initWithParam(str, this, menu_selector(PlantView::handleRefresh), menu_selector(PlantView::handleRefreshCancel));
		LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
		pConfirm->release();
	}
	else
	{
		firstClickCount++;

		handleRefresh(0);
	}

	
}

void PlantView::handleRefresh(CCObject* pSender)
{
	//apply refresh
	CCMD436 cmd;
	cmd.a_oreID = m_iOreID;
	cmd.b_refreshType = 0;
	GameServerSocket::getInstance()->sendMessage( &cmd );
	//这里需要同步433
	LayerManager::loadingPic->socketWait( WMSG_ORE_RESPONSE, 0, 0);
	//
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void PlantView::handleFullLv(CCObject* pSender)
{
	//apply refresh
	CCMD436 cmd;
	cmd.a_oreID = m_iOreID;
	cmd.b_refreshType = 1;
	GameServerSocket::getInstance()->sendMessage( &cmd );
	//这里需要同步433
	LayerManager::loadingPic->socketWait( WMSG_ORE_RESPONSE, 0, 0);
	//
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void PlantView::handleRefreshCancel(CCObject* pSender)
{
	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_confirmFrame, true);
}

void PlantView::clickFullLv(CCObject* pSender)
{
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_Ore_A , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_Ore_A);
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}

	if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_confirmFrame))
		return;
	Confirm* pConfirm = new Confirm();
	char str[180];
	sprintf(str, ValuesUtil::Instance()->getString("ORE29").c_str());
	pConfirm->initWithParam(str, this, menu_selector(PlantView::handleFullLv), menu_selector(PlantView::handleRefreshCancel));
	LayerManager::tipsLayer->addChild(pConfirm,TipsLayer::TipsLayerZ_confirmFrame, TipsLayer::TipsLayerTAG_confirmFrame);
	pConfirm->release();
}

void PlantView::clickClose(CCObject* pSender)
{
	if (ViewManager::getInstance()->oreView)
		ViewManager::getInstance()->oreView->setIsVisible(true);

	PlantView* p = (PlantView*)LayerManager::intervalLayer->getChildByTag( IntervalLayer::IntervalLayerTAG_ore_plant);
	if (p)
	{
		p->removeFromParentAndCleanup(true);
	}

	//new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Ore) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->touchNextScript("p" , "ORE");
	}
	else if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_Ore) == NewhandManager::Flag_Done)
	{
		NewhandManager::Instance()->touchNextEvent(204);
	}
}

void PlantView::UpdatePlantState(uint32 plantState)
{
	m_iPlantState = plantState;
	//
	int lev = RoleManage::Instance()->roleLev();
	int awardSilver = (int)(lev/10) * 5000;

	switch (m_iPlantState)                  
    {                                  
    case 0:                            
        {                              
            awardSilver *= 2;          
        }                              
        break;                         
    case 1:                            
        {                              
            awardSilver *= 3;          
        }                              
        break;                         
    case 2:                            
        {                              
            awardSilver *= 5;          
        }                              
        break;                         
    case 3:                            
        {                              
            awardSilver *= 8;          
        }                              
        break;                         
    case 4:                            
        {                              
            awardSilver *= 16;         
        }                              
        break;                         
    default:                           
        break;                         
    }        

	//原石品质内容
	{
		if (_pContainer->getChildByTag(1))
			_pContainer->removeChildByTag(1, true);

		char str[20];
		sprintf(str, "ORE2%d", m_iPlantState+3);
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString( str ).c_str(),
			CCSizeMake(POSX(200), POSX(60)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
		txtLabel->setPosition( ccp(POSX(102+150), POSX(640-335)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5, 1 );
		txtLabel->setColor(ccc3(251, 216, 0));
	}

	//加工收益数值
	{
		if (_pContainer->getChildByTag(2))
			_pContainer->removeChildByTag(2, true);

		char str[30];
		sprintf(str, "%d", awardSilver);
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString(
			str,
			CCSizeMake(POSX(200), POSX(60)), CCTextAlignmentLeft, g_sSimHeiFont, POSX(24) );
		txtLabel->setPosition( ccp(POSX(102+150), POSX(640-380)) );
		txtLabel->setAnchorPoint(ccp(0,0));
		_pContainer->addChild( txtLabel, 5, 2);
		txtLabel->setColor(ccc3(251, 216, 0));
	}

	for (int i = 0; i < 5; i++)
	{
		if (_pContainer->getChildByTag(i+1000))
			_pContainer->removeChildByTag(i+1000, true);

		bool opened = false;

		if (m_iPlantState == i)
		{
			opened = true;
		}
		else
		{
			opened = false;
		}

		PlantItem* node = new PlantItem();
		
		node->init(m_iOreID, i, opened);
		_pContainer->addChild(node, 6, i+1000);
		node->release();
		node->setPosition(ccp(POSX(150+i*145), POSX(640-200)));
	}
}