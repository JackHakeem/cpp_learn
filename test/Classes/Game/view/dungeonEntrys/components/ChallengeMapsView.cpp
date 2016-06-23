#include "ChallengeMapsView.h"
#include "manager/PopEventName.h"
#include "utils/ScaleUtil.h"
#include "manager/LangManager.h"
#include "manager/TouchLayerEnum.h"
#include "Confirm.h"
#include "manager/LayerManager.h"
#include "../DungeonEntrysMediator.h"
#include "manager/ViewManager.h"
#include "manager/VIPMgr.h"
#include "manager/VIPLimitConst.h"
#include "MessageInfoBox.h"

ChallengeMapsView::ChallengeMapsView()
{
	_challengeMapLists = NULL;
	layer = NULL;

	_container1        = NULL;
	_container2        = NULL;
	_canChallengeTimes = 0;
	_buyTimes          = 0;
	_buttonBuy         = NULL;
	_lableChaTimes     = NULL;
	//_Tips              = NULL;
	//_TipsContent       = NULL;
}

bool ChallengeMapsView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/entrance/entranceIcon/res_entrance_ic.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
		"assets/ui/entrance/res_entrance.plist");

	this->key = PopEventName::CHALLENGEMAP_COPYS;
	this->setIsTouchEnabled(true);
	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(CCPointZero);
	this->setPosition(ccp(0, 0));
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	setContentSize(winSize);
	setPopContentSize(winSize);
	addScrollViews();
	//=>hwj
	float fFont( POSX(28) );
	CCLabelTTF* pLabel = CCLabelTTF::labelWithString( LangManager::getText("DNE010").c_str(),
		CCSizeMake(POSX(240), POSX(28)), CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	pLabel->setPosition( ccp( POSX(40), POSX(400) ) );
	pLabel->setAnchorPoint( CCPointZero );
	pLabel->setColor( ccc3(0xff, 0xc6, 0x00) );
	layer->addChild( pLabel );

	CCLabelTTF* Tips = CCLabelTTF::labelWithString( LangManager::getText("DNE011").c_str(),
		CCSizeMake(POSX(200), POSX(28)), CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	Tips->setPosition( ccp( POSX(40), POSX(180) ) );
	Tips->setAnchorPoint( CCPointZero );
	Tips->setColor( ccc3(0xff, 0xc6, 0x00) );
	layer->addChild( Tips );

	CCLabelTTF* TipsContent = CCLabelTTF::labelWithString( LangManager::getText("DNE012").c_str(),
		CCSizeMake(POSX(200), POSX(60)), CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	TipsContent->setPosition( ccp( POSX(40), POSX(100) ) );
	TipsContent->setAnchorPoint( CCPointZero );
	TipsContent->setColor( ccGRAY );//ccc3(0xff, 0xc6, 0x00)
	layer->addChild( TipsContent );

	float fFont2( POSX(36) );
	_lableChaTimes = CCLabelTTF::labelWithString( "", 
		CCSizeMake(POSX(70), POSX(36)), CCTextAlignmentCenter, g_sSimHeiFont, fFont2 );
	_lableChaTimes->setPosition( ccp( POSX(140), POSX(350) ) );
	//_lableChaTimes->setAnchorPoint( CCPointZero );
	_lableChaTimes->setColor( ccRED );//ccc3(0x30, 0xff, 0x00)
	layer->addChild( _lableChaTimes );

	CCSize csBt( POSX(121), POSX(49) );
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
	if(pNormalSprite && pPressedSprite && pSelectdSprite)
	{
		_buttonSprit = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			pSelectdSprite,
			this,
			menu_selector(ChallengeMapsView::onBuy) );
		_buttonSprit->setPosition( ccp( POSX(91)+csBt.width/2, POSX(250)+csBt.height/2 ) );
		_buttonSprit->setTag( CHALLENGEMAP_BUY );
		_buttonBuy = CCMenu::menuWithItems(_buttonSprit, 0);
		_buttonBuy->setTouchLayer( TLE::WindowLayer_Common_btn );
		_buttonBuy->setPosition( CCPointZero );
		layer->addChild( _buttonBuy );
		string txt = ValuesUtil::Instance()->getString( "SHOP001" );
		CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, fFont );
		txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
		_buttonSprit->addChild( txtLabel );
	}
	//<=
	return true;
}

void ChallengeMapsView::clickCloseHandler(CCObject* pSender)//kevinshit
{
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
	//	"assets/ui/entrance/entranceIcon/res_entrance_ic.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
	//	"assets/ui/entrance/res_entrance.plist");

	//CCTextureCache::sharedTextureCache()->removeTextureForKey(
	//	"assets/ui/entrance/entranceIcon/res_entrance_ic.pvr.ccz");
	//CCTextureCache::sharedTextureCache()->removeTextureForKey(
	//	"assets/ui/entrance/res_entrance.pvr.ccz");

	setisPop(false);
}

void ChallengeMapsView::addScrollViews()
{
	if(!layer)
	{
		layer = new CCLayer();
		layer->init();
		//layer->setPosition(POS(ccp(24, 32), ScaleUtil::BOTTOM_LEFT));
		layer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
		layer->setAnchorPoint(CCPointZero);
		this->addChild(layer, CHALLENGEMAP_LAYER);
		layer->release();
	}
	///=>hwj
	if(!_container1)
	{
		_container1 = new CCUIBackground();
		_container1->initWithSpriteFrame("ui2.png", ccp(POSX(26), POSX(20)), ccp(0, 0), CCSizeMake(POSX(240), POSX(525)));
		layer->addChild(_container1, CHALLENGEMAP_CONTAINER1);
		_container1->release();
	}

	if(!_container2)
	{
		_container2 = new CCUIBackground();
		_container2->initWithSpriteFrame("ui2.png", ccp(POSX(266), POSX(20)), ccp(0, 0), CCSizeMake(POSX(670), POSX(525)));
		layer->addChild(_container2, CHALLENGEMAP_CONTAINER2);
		_container2->release();
	}
	//<=end_hwj

	/*CCLayerColor *pTestLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(255, 0, 0, 128),
		CCDirector::sharedDirector()->getWinSize().width,
		CCDirector::sharedDirector()->getWinSize().height);
	pTestLayer->setAnchorPoint(CCPointZero);
	pTestLayer->setPosition(CCPointZero);
	layer->addChild(pTestLayer);*/

	if(!_challengeMapLists)
	{
		_challengeMapLists = new ChallengeMapLists();
		if(_challengeMapLists->getParent() == NULL)
			layer->addChild(_challengeMapLists);
		_challengeMapLists->release();
		_challengeMapLists->startListViewHandler();
	}
}

void ChallengeMapsView::setViewAdapter()
{
	if(_challengeMapLists)
		_challengeMapLists->setViewAdapter();
}

void ChallengeMapsView::addIcons(std::vector<MapData>& data)
{
	if(!_challengeMapLists)
		return;

	std::vector<MapData>::iterator iter = data.begin();
	for(; iter != data.end(); ++iter)
	{
		_challengeMapLists->initDataList(*iter, true);
	}

	if(_challengeMapLists)
		_challengeMapLists->setViewAdapter();
}

void ChallengeMapsView::setChallengeTimes(uint8 times)
{
	_canChallengeTimes = times;
	char txt[20];
	sprintf(txt,"%d",times);
	_lableChaTimes->setString(txt);
}

void ChallengeMapsView::onBuy(CCObject* pSender)
{
	if (!VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_BuyChallegeCount , RoleManage::Instance()->accountInfo()->vipLev()))
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("WLC010").c_str() , VIPLimitConst::VIP_BuyChallegeCount);
		MessageInfoBox::Instance()->show(path,ccc3(12,233,25));
		return;
	}

	Confirm * _confirmBuy = new Confirm();
	char str[64];
	uint16 neddGold = (_buyTimes + 1) * 200;
	sprintf(str,ValuesUtil::Instance()->getString("DNE013").c_str(),neddGold);
	_confirmBuy->initWithParam(
		str,
		this,
		menu_selector(ChallengeMapsView::clickOK),
		menu_selector(ChallengeMapsView::clickCancel));
	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
	{
		LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}
	LayerManager::windowLayer->addChild(_confirmBuy,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
	_confirmBuy->release();
}

void ChallengeMapsView::clickCancel(CCObject * pSender)
{
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	}  
}

void ChallengeMapsView::clickOK(CCObject * pSender)
{	
	DungeonEntrysMediator* m = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	if(m)
	{
		m->applyForBuyChaTimes();
	}
	Confirm * _confirmBuy = (Confirm *)LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame);
	if (_confirmBuy&&_confirmBuy->getParent())
	{
		_confirmBuy->getParent()->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
	} 	
}

ChallengeMapsView::~ChallengeMapsView()
{
	DungeonEntrysMediator* pMeditor = (DungeonEntrysMediator*)g_pFacade->retrieveMediator(AppFacade_DungeonEntrysMediator);
	pMeditor->challengeMapsView = 0;
	ViewManager::getInstance()->challengeMapsView = 0;

	if (_challengeMapLists)
	{
		_challengeMapLists->removeFromParentAndCleanup(true);
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
		"assets/ui/entrance/entranceIcon/res_entrance_ic.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile(
		"assets/ui/entrance/res_entrance.plist");
	
	CCTextureCache::sharedTextureCache()->removeTextureForKey(
		"assets/ui/entrance/entranceIcon/res_entrance_ic.pvr.ccz");
	CCTextureCache::sharedTextureCache()->removeTextureForKey(
		"assets/ui/entrance/res_entrance.pvr.ccz");
}
