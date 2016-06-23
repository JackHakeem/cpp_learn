#include "manager/PopEventName.h"
#include "utils/ValuesUtil.h"
#include "Message.h"
#include "events/GameDispatcher.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "GoldLevyPanel.h"
#include "manager/LangManager.h"
#include "model/player/RoleManage.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/LevLimitConst.h"
#include "model/newhand/vo/NewhandConst.h"
#include "model/newhand/NewhandManager.h"
#include "manager/VIPLimitConst.h"
#include "manager/VIPMgr.h"

static const int TAG_PARENT = 99;
static const int Tag_txtVipTip = 100;
static const int Tag_upVipTip = 101;
static const int Tag_spendGold = 102;
static const int Tag_receiveYinbi = 103;
static const int TAG_MENU_ITEM = 104;
static const int TAG_MENU_Levy = 105;
static const int Tag_Jiantou = 106;

GoldLevyPanel::GoldLevyPanel()
{
	_levyCost = 0;
	reward = 0;

	openTxt = 0;
}

bool GoldLevyPanel::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//setNeedBg(NeedBg_NO);
	//// initial key
	//key = PopEventName::GOLD_LEVY;

	CCSize cs( POSX(451), POSX(523) );
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCLayer *pParentLayer = new CCLayer();
	if(!pParentLayer)
	{
		return false;
	}
	pParentLayer->init();
	pParentLayer->setContentSize( cs );
	//pParentLayer->setPosition(POS(ccp((960 - 736) / 2, (640 - 550) / 2), ScaleUtil::CENTER_TOP));
	pParentLayer->setAnchorPoint(CCPointZero);
	pParentLayer->setTag(TAG_PARENT);
	this->addChild( pParentLayer );
	pParentLayer->release(); //

	// Add background2
	CCUIBackground *pBackground2 = new CCUIBackground();
	pBackground2->initWithSpriteFrame(  "ui2.png", 
		CCPointZero,
		ccp(0,0), 
		cs  );
	pParentLayer->addChild(pBackground2);
	pBackground2->release();
	
	// title
	CCSprite* spTitle = new CCSprite;
	if ( spTitle && spTitle->initWithSpriteFrameName("levy/gold_levy.png") )
	{
		spTitle->setAnchorPoint( CCPointZero );
		spTitle->setPosition( ccp(POSX(162), POSX(480)) );
		pParentLayer->addChild( spTitle );
		spTitle->release();
	}

	CCSprite* pGlodDui = new CCSprite;
	if ( pGlodDui && pGlodDui->initWithSpriteFrameName("goldlevy/goldlevy.png") )
	{
		pGlodDui->setAnchorPoint( CCPointZero );
		pGlodDui->setPosition( ccp(POSX(87), POSX(150)) );
		pParentLayer->addChild( pGlodDui );
		pGlodDui->release();
	}

	CCSize csLabel( POSX(448), POSX(40) );
	float fFont( POSX(40) );

	//ÊÇ·ñ¿ªÆô
	if ( RoleManage::Instance()->roleLev() < LevLimitConst::Limit_GoldLevy )
	{
		char path[128] = {0};
		sprintf(path , ValuesUtil::Instance()->getString("LVY029").c_str() , LevLimitConst::Limit_GoldLevy);
		openTxt = CCLabelTTF::labelWithString(
			path,
			csLabel, CCTextAlignmentCenter, g_sSimHeiFont, fFont );
		openTxt->setPosition( ccp( POSX(5), POSX(354) ) );
		openTxt->setAnchorPoint( CCPointZero );
		openTxt->setColor( ccRED );
		pParentLayer->addChild( openTxt );
		return true;
	}

	initGoldPannel();

	return true;
}

void GoldLevyPanel::initGoldPannel()
{
	CCNode* pParentLayer = this->getChildByTag( TAG_PARENT );
	if (!pParentLayer)
	{
		return;
	}
	CCSize csLabel( POSX(448), POSX(40) );
	float fFont( POSX(40) );

	// vip txt cnt
	CCLabelTTF* _txtVipTip = CCLabelTTF::labelWithString( "",
		csLabel, CCTextAlignmentCenter, g_sSimHeiFont, fFont );
	_txtVipTip->setPosition( ccp( POSX(5), POSX(441-10) ) );
	_txtVipTip->setAnchorPoint( CCPointZero );
	_txtVipTip->setColor( ccRED );
	_txtVipTip->setTag( Tag_txtVipTip );
	pParentLayer->addChild( _txtVipTip );

	csLabel = CCSizeMake( POSX(448), POSX(28) );
	fFont = POSX(28);
	// vip up txt
	CCLabelTTF* _txtupVipTip = CCLabelTTF::labelWithString( "",
		csLabel, CCTextAlignmentCenter, g_sSimHeiFont, fFont );
	_txtupVipTip->setPosition( ccp( POSX(5), POSX(441-144/2 + 30) ) );
	_txtupVipTip->setAnchorPoint( CCPointZero );
	_txtupVipTip->setColor( ccWHITE );
	_txtupVipTip->setTag( Tag_upVipTip );
	pParentLayer->addChild( _txtupVipTip );

	// spendGold txt
	CCLabelTTF* _txtSpendGold = CCLabelTTF::labelWithString( "",
		CCSizeMake(POSX(163), POSX(28)), CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	_txtSpendGold->setPosition( ccp( POSX(5 + 40), POSX(90) ) );
	_txtSpendGold->setAnchorPoint( CCPointZero );
	_txtSpendGold->setColor( ccYELLOW );
	_txtSpendGold->setTag( Tag_spendGold );
	pParentLayer->addChild( _txtSpendGold );

	/*
	CCSprite* pJiantou = new CCSprite;
	if ( pJiantou && pJiantou->initWithSpriteFrameName("levy/jiantou.png") )
	{
		pJiantou->setAnchorPoint( CCPointZero );
		pJiantou->setPosition( ccp(POSX(5+140), POSX(441-144)) );
		pJiantou->setTag(Tag_Jiantou);
		pParentLayer->addChild( pJiantou );
		pJiantou->release();
	}
	*/

	// Reward yinbi txt
	CCLabelTTF* _txtReceiveYinbi = CCLabelTTF::labelWithString( "",
		CCSizeMake(POSX(332), POSX(28)), CCTextAlignmentLeft, g_sSimHeiFont, fFont );
	_txtReceiveYinbi->setPosition( ccp( POSX(5+/*234*/230), POSX(90) ) );
	_txtReceiveYinbi->setAnchorPoint( CCPointZero );
	_txtReceiveYinbi->setColor( ccGREEN );
	_txtReceiveYinbi->setTag( Tag_receiveYinbi );
	pParentLayer->addChild( _txtReceiveYinbi );

	// _levy btn
	CCSize csBt( POSX(121), POSX(49) );
	if ( RoleManage::Instance()->roleLev() >= LevLimitConst::Limit_GoldLevy )
	{
		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_GoldItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(GoldLevyPanel::onGoldLevy) );
			_GoldItem->setPosition( ccp( POSX(172), POSX(15) ) );
			_GoldItem->setAnchorPoint( CCPointZero );
			_GoldItem->setTag( TAG_MENU_ITEM );

			CCMenu* _levy = CCMenu::menuWithItems(_GoldItem, 0);
			_levy->setTouchLayer( TLE::WindowLayer_Common_btn );
			_levy->setPosition( CCPointZero );
			_levy->setTag( TAG_MENU_Levy );
			pParentLayer->addChild( _levy );
			string txt = ValuesUtil::Instance()->getString( "LVY027" );
			CCLabelTTF* txtLabel = CCLabelTTF::labelWithString( txt.c_str(), csBt, CCTextAlignmentCenter, g_sSimHeiFont, fFont );
			txtLabel->setPosition( ccp( csBt.width/2, csBt.height/2 ) );
			_GoldItem->addChild( txtLabel );
		}
		
	}
}

void GoldLevyPanel::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::WindowLayer_Common_btn, true );
}

bool GoldLevyPanel::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void GoldLevyPanel::setInfo( int cost, int reward, int restNum )
{
	CCNode* pParentLayer = this->getChildByTag( TAG_PARENT );
	if (!pParentLayer)
	{
		return;
	}
	CCLabelTTF* _txtVipTip = (CCLabelTTF*)pParentLayer->getChildByTag(Tag_txtVipTip);
	CCLabelTTF* _txtUpVipTip = (CCLabelTTF*)pParentLayer->getChildByTag(Tag_upVipTip);
	CCLabelTTF* _txtSpendGold = (CCLabelTTF*)pParentLayer->getChildByTag(Tag_spendGold);
	CCLabelTTF* _txtReceiveYinbi = (CCLabelTTF*)pParentLayer->getChildByTag(Tag_receiveYinbi);
	CCMenu* _levyMenu = (CCMenu*)pParentLayer->getChildByTag(TAG_MENU_Levy);
	CCNode* pJiantou = pParentLayer->getChildByTag(Tag_Jiantou);

	_levyCost = cost;
	if (!_txtSpendGold)
	{
		return;
	}
	_txtSpendGold->setString(LangManager::getText("LVY018", cost).c_str());
	_txtReceiveYinbi->setString(LangManager::getText("LVY019", reward).c_str());
	
	int viplv = RoleManage::Instance()->accountInfo()->vipLev();
	if( (restNum>0) || (viplv!=0) || RoleManage::Instance()->accountInfo()->trialVip() )
	{
		if ( viplv == 0 )
		{
			_txtVipTip->setString( LangManager::getText("LVY021", restNum).c_str() );
		}

		_txtSpendGold->setIsVisible(true);
		_txtReceiveYinbi->setIsVisible(true);

		if (_levyMenu)
		{
			_levyMenu->setIsTouchEnabled(true);
			_levyMenu->setIsVisible(true);
		}
		if (pJiantou)
		{
			pJiantou->setIsVisible(true);
		}
	}
	else 
	{
		_txtVipTip->setString( LangManager::getText("LVY022").c_str() );

		_txtSpendGold->setIsVisible(false);
		_txtReceiveYinbi->setIsVisible(false);

		if (_levyMenu)
		{
			_levyMenu->setIsTouchEnabled(false);
			_levyMenu->setIsVisible(false);
		}
		if (pJiantou)
		{
			pJiantou->setIsVisible(false);
		}
	}
	
	if ( (VIPMgr::Instance()->hasVIPFunc(VIPLimitConst::VIP_LevyNoLimit , RoleManage::Instance()->accountInfo()->vipLev()))
		|| RoleManage::Instance()->accountInfo()->trialVip() )
	{
		_txtUpVipTip->setIsVisible(false);
		_txtVipTip->setIsVisible(false);
	}
	else
		_txtUpVipTip->setString(LangManager::getText("LVY016").c_str());
}

void GoldLevyPanel::onGoldLevy(CCObject* obj)
{
	//qiangzheng
	if ( RoleManage::Instance()->accountInfo()->gold() >= _levyCost )
	{
		int param = 2;
		GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::LEVY_TYPE, &param );
		//GameDispatcher::instance->dispatchEvent(new ParamEvent(GameDispatcher.LEVY_TYPE,2));
	}
	else
	{
		LangManager::msgShow("LVY023");
	}

	if (_GoldItem)
	{
		_GoldItem->setIsEnabled(false);

		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(GoldLevyPanel::lockBtn),
			this,0.2f,false);
	}

	// new hand
	// new hand
	if (NewhandManager::Instance()->getNewHandStateByType(LevLimitConst::Limit_GoldLevy) == NewhandManager::Flag_New)
	{
		NewhandManager::Instance()->setNewHandStateByType(LevLimitConst::Limit_GoldLevy , NewhandManager::Flag_Done);
		NewhandManager::Instance()->touchNextEvent(502);
	}
}

void GoldLevyPanel::lockBtn(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(GoldLevyPanel::lockBtn), this);
	if (_GoldItem)
	{
		_GoldItem->setIsEnabled(true);
	}
}