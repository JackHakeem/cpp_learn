#include "MineInfo.h"
#include "MineView.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/CDManage.h"
#include "manager/TimerManage.h"
#include "MineRank.h"
#include "manager/LayerManager.h"
#include "model/silverMine/SilverConst.h"
#include "MineTips.h"
#include "model/silverMine/SilverMineProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "CustomCD.h"
#include "manager/CDManage.h"

const float FontSize2 = 20.0f;

MineInfo::MineInfo()
{
	_inMoveCD = false;
	_moveCD = 0;
	_digCD = 0;
	_inDigCD = false;
	_hasStep = false;
	_txtMoveCD = 0;
	_txtDigCD = 0;
	m_txt[0] = 0;
	m_txt[1] = 0;
	_btn_showRank = 0;
	_btn_change = 0;
	m_frame_0[0] = 0;
	m_frame_0[1] = 0;
	m_frame_1[0] = 0;
	m_frame_1[1] = 0;
	m_bg1 = 0;
	m_Label_change = 0;
	m_btnGoldInspire = 0;
	m_btnPracInspire = 0;
	_gIsFull = false;
	_dIsFull = false;
	m_hide = false;

	m_digOffset = 0;
	m_moveOffset = 0;
}

MineInfo::~MineInfo()
{}

void MineInfo::hide(CCObject* pSender)
{
	m_hide = !m_hide;
	if (m_hide)
	{
		CCAction* act = cocos2d::CCMoveTo::actionWithDuration(0.2f, ccp(POSX(-316), POSX(0)));
		//this->setPosition(ccp(POSX(-316), POSX(0)));
		this->runAction(act);
	}
	else
	{
		CCAction* act = cocos2d::CCMoveTo::actionWithDuration(0.2f, ccp(POSX(0), POSX(0)));
		//this->setPosition(ccp(POSX(-316), POSX(0)));
		this->runAction(act);
	}
}

bool MineInfo::init(MineView* pContainer)
{
	if (!LayerNode::init())
		return false;

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	this->pContainer = pContainer;
	//hide_btn_0
	{
		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("hide_btn_0.png");
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("hide_btn_0.png");
		CCMenuItemSprite* _btn = CCMenuItemImage::itemFromNormalSprite(
			p1, 
			p2, 
			this, 
			menu_selector(MineInfo::hide) );
		//_btn->setPosition(ccp(POSX(346), POSX(640-175)));
		_btn->setPosition(ccp(POSX(346), winSize.height-POSX(175)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);
		this->addChild(buttonMenu, -1);	

		SpriteNode* p = new SpriteNode();
		p->initWithSpriteFrameName("hide_btn_label.png");
		p->setPosition(ccp(POSX(345), winSize.height-POSX(170)));
		this->addChild(p, 3);
		p->release();
	}
	
	//
	{
/*		_txtMoveCD = CCLabelTTF::labelWithString("", CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentLeft, "Arial", POSX(22.0f));
		_txtMoveCD->setPosition(ccp(POSX(200), winSize.height-POSX(242)+POSX(2*55)));
		_txtMoveCD->setAnchorPoint(ccp(0, 0));
		this->addChild(_txtMoveCD, 2);
		_txtMoveCD->setColor(ccc3(240, 210, 68));*/	

		//Custom CD
		_txtMoveCD = new CustomCD( CDManage::SILVERMINE_MOVE );
		_txtMoveCD->setPosition(ccp(POSX(120), winSize.height-POSX(246)+POSX(2*55)));
		this->addChild( _txtMoveCD, 2);

		_txtMoveCD->release(); 
		_txtMoveCD->reinit();
	}
	//
	{
		//_txtDigCD = CCLabelTTF::labelWithString("", CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentLeft, "Arial", POSX(22.0f));
		//_txtDigCD->setPosition(ccp(POSX(200), winSize.height-POSX(242)+POSX(1*55)));
		//_txtDigCD->setAnchorPoint(ccp(0, 0));
		//this->addChild(_txtDigCD, 2);
		//_txtDigCD->setColor(ccc3(240, 210, 68));
		_txtDigCD = new CustomCD( CDManage::SILVERMINE_DIG );
		_txtDigCD->setPosition(ccp(POSX(120), winSize.height-POSX(246)+POSX(1*55)));
		this->addChild( _txtDigCD, 2);

		_txtDigCD->release(); 
		_txtDigCD->reinit();
	}
	//攻击加成
	{
		m_txtGW1 = CCLabelTTF::labelWithString("0%", CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentLeft, "Arial", POSX(22.0f));
		m_txtGW1->setPosition(ccp(POSX(200), winSize.height-POSX(242)+POSX(2*55)));
		m_txtGW1->setAnchorPoint(ccp(0, 0));
		this->addChild(m_txtGW1, 2);
		m_txtGW1->setColor(ccc3(240, 210, 68));	
	}
	//防御加成
	{
		m_txtGW2 = CCLabelTTF::labelWithString("0%", CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentLeft, "Arial", POSX(22.0f));
		m_txtGW2->setPosition(ccp(POSX(200), winSize.height-POSX(242)+POSX(1*55)));
		m_txtGW2->setAnchorPoint(ccp(0, 0));
		this->addChild(m_txtGW2, 2);
		m_txtGW2->setColor(ccc3(240, 210, 68));	
	}
	

	//btnClick_showRank
	
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btn_showRank = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
				menu_selector(MineInfo::btnClick_showRank) );
			_btn_showRank->setPosition(ccp(POSX(240), winSize.height-POSX(245)));
			_btn_showRank->setTag(0);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn_showRank, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);
			this->addChild(buttonMenu, 2);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM056").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn_showRank->getContentSize().width/2, _btn_showRank->getContentSize().height/2+2.0f));
			_btn_showRank->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));	
		}
	}

	//btnClick_change
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btn_change = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
				menu_selector(MineInfo::showUI) );
			_btn_change->setPosition(ccp(POSX(88), winSize.height-POSX(245)));//88 305
			_btn_change->setTag(0);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn_change, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);
			this->addChild(buttonMenu, 2);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM061").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn_change->getContentSize().width/2, _btn_change->getContentSize().height/2+2.0f));
			_btn_change->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));	
			m_Label_change = pLabel;
		}
	}

	//m_btnGoldInspire
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnGoldImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
				menu_selector(MineInfo::goldInspire) );
			_btnGoldImg->setPosition(ccp(POSX(88), winSize.height-POSX(235)));//88 305
			_btnGoldImg->setTag(0);

			m_btnGoldInspire = _btnGoldImg;
			CCMenu *buttonMenu = CCMenu::menuWithItems(_btnGoldImg, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);
			this->addChild(buttonMenu, 2);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM062").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btnGoldImg->getContentSize().width/2, _btnGoldImg->getContentSize().height/2+2.0f));
			_btnGoldImg->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));
		}
	//	m_Label_change = pLabel;
	}

	//m_btnPracInspire
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			_btnPracImg = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
				menu_selector(MineInfo::pracInspire) );
			_btnPracImg->setPosition(ccp(POSX(240), winSize.height-POSX(235)));//88 305
			_btnPracImg->setTag(0);

			m_btnPracInspire = _btnPracImg;
			CCMenu *buttonMenu = CCMenu::menuWithItems(_btnPracImg, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);
			this->addChild(buttonMenu, 2);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM063").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btnPracImg->getContentSize().width/2, _btnPracImg->getContentSize().height/2+2.0f));
			_btnPracImg->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));	
		}
	//	m_Label_change = pLabel;
	}


	
	showUI(0);
	return true;
}

// 金币鼓舞
void MineInfo::goldInspire(CCObject* pSender)
{
	static int s_count = -1;//每一次启动机器第一次出框
	s_count++;
	if (s_count == 0)
	{
		MineTips* oldp = (MineTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
		if (!oldp)
		{
			oldp = new MineTips();
			oldp->init(MineTips::guwu_gold, pContainer);
			LayerManager::intervalLayer->addChild(oldp, IntervalLayer::IntervalLayerZ_guild_silverMineTips, IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
			oldp->release();
		}	
	}
	else
	{
		int i = 0;
		pContainer->dispatchEvent(SilverConst::DO_INSPIRE, &i);			
	}

	if (_btnGoldImg)
	{
		_btnGoldImg->setIsEnabled(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(MineInfo::lockBtn),
			this,0.2f,false);
	}

}

void MineInfo::lockBtn(ccTime dt)
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(MineInfo::lockBtn), this);
	if (_btnGoldImg)
	{
		_btnGoldImg->setIsEnabled(true);
	}
	if (_btnPracImg)
	{
		_btnPracImg->setIsEnabled(true);
	}
	
}

// 历练鼓舞 
void MineInfo::pracInspire(CCObject* pSender)
{
	static int s_count = -1;//每一次启动机器第一次出框
	s_count++;
	if (s_count == 0)
	{
		MineTips* oldp = (MineTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
		if (!oldp)
		{
			oldp = new MineTips();
			oldp->init(MineTips::guwu_lilian, pContainer);
			LayerManager::intervalLayer->addChild(oldp, IntervalLayer::IntervalLayerZ_guild_silverMineTips, IntervalLayer::IntervalLayerTAG_guild_silverMineTips);
			oldp->release();
		}	
	}
	else
	{
		int i = 1;
		pContainer->dispatchEvent(SilverConst::DO_INSPIRE, &i);	
	}
	if (_btnPracImg)
	{
		_btnPracImg->setIsEnabled(false);
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(MineInfo::lockBtn),
			this,0.2f,false);
	}

}

void MineInfo::showUI(CCObject* pSender)
{
	int tag;
	if (pSender == 0)
	{
		tag = 0;
	}
	else
	{
		CCMenuItemImage* _btn = (CCMenuItemImage*)pSender;
		tag = _btn->getTag();
	}

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	if (tag == 0)
	{//显示CD面板
		//m_bg1
		{
			if (m_bg1)
				m_bg1->removeFromParentAndCleanup(true);
			m_bg1 = new CCUIBackground();
			m_bg1->initWithSpriteFrame("bg1.png",
				ccp(POSX(10), winSize.height-POSX(295)), ccp(0,0), CCSizeMake(POSX(316-10), POSX(295-82)));
			this->addChild(m_bg1, 0);
			m_bg1->release();	
		}
		//
		for (int i = 1; i < 3; i++)
		{
			//_frame_1
			{
				if (m_frame_1[i-1]) m_frame_1[i-1]->removeFromParentAndCleanup(true);
				m_frame_1[i-1] = new CCUIBackground();
				m_frame_1[i-1]->initWithSpriteFrame("_frame_1.png", ccp(POSX(24), winSize.height-POSX(252)+POSX(i*55)), ccp(0,0), CCSizeMake(POSX(145-24), POSX(252-210)));
				this->addChild(m_frame_1[i-1], 1);
				m_frame_1[i-1]->release();	
			}
			//_frame_0
			{
				if (m_frame_0[i-1]) m_frame_0[i-1]->removeFromParentAndCleanup(true);
				m_frame_0[i-1] = new CCUIBackground();
				m_frame_0[i-1]->initWithFile("assets/ui/_frame_0.png", ccp(POSX(145), winSize.height-POSX(252)+POSX(i*55)), ccp(0,0), CCSizeMake(POSX(305-145), POSX(252-210)));
				this->addChild(m_frame_0[i-1], 1);
				m_frame_0[i-1]->release();	
			}
			char str[10];
			sprintf(str, "SLM05%d", i+3);
			if (m_txt[i-1]) m_txt[i-1]->removeFromParentAndCleanup(true);
			m_txt[i-1] = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString(str).c_str(), CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentLeft, "Arial", POSX(22.0f));
			m_txt[i-1]->setPosition(ccp(POSX(32), winSize.height-POSX(242)+POSX(i*55)));
			m_txt[i-1]->setAnchorPoint(ccp(0, 0));
			this->addChild(m_txt[i-1], 2);
			m_txt[i-1]->setColor(ccc3(240, 210, 68));
		}
		//
		_txtMoveCD->setIsVisible(true);
		_txtDigCD->setIsVisible(true);
		//
		_btn_showRank->setPosition(ccp(POSX(240), winSize.height-POSX(245)));
		//
		_btn_change->setPosition(ccp(POSX(88), winSize.height-POSX(245)));
		_btn_change->setTag(1);
		//char CD面板
		m_Label_change->setString(ValuesUtil::Instance()->getString("SLM061").c_str());
		//
		m_btnGoldInspire->setIsVisible(false);
		m_btnPracInspire->setIsVisible(false);
		//
		m_txtGW1->setIsVisible(false);
		m_txtGW2->setIsVisible(false);
	}
	else
	{//显示鼓舞面板
		//m_bg1
		{
			if (m_bg1)
				m_bg1->removeFromParentAndCleanup(true);
			m_bg1 = new CCUIBackground();
			m_bg1->initWithSpriteFrame("bg1.png", ccp(POSX(10), winSize.height-POSX(345)), ccp(0,0), CCSizeMake(POSX(316-10), POSX(345-82)));
			this->addChild(m_bg1, 0);
			m_bg1->release();	
		}
		//
		for (int i = 1; i < 3; i++)
		{
			//_frame_1
			{
				if (m_frame_1[i-1]) m_frame_1[i-1]->removeFromParentAndCleanup(true);
				m_frame_1[i-1] = new CCUIBackground();
				m_frame_1[i-1]->initWithSpriteFrame("_frame_1.png", ccp(POSX(24), winSize.height-POSX(252)+POSX(i*55)), ccp(0,0), CCSizeMake(POSX(145-24), POSX(252-210)));
				this->addChild(m_frame_1[i-1], 1);
				m_frame_1[i-1]->release();	
			}
			//_frame_0
			{
				if (m_frame_0[i-1]) m_frame_0[i-1]->removeFromParentAndCleanup(true);
				m_frame_0[i-1] = new CCUIBackground();
				m_frame_0[i-1]->initWithFile("assets/ui/_frame_0.png", ccp(POSX(145), winSize.height-POSX(252)+POSX(i*55)), ccp(0,0), CCSizeMake(POSX(305-145), POSX(252-210)));
				this->addChild(m_frame_0[i-1], 1);
				m_frame_0[i-1]->release();	
			}
			char str[10];
			sprintf(str, "SLM05%d", i+7);
			if (m_txt[i-1]) m_txt[i-1]->removeFromParentAndCleanup(true);
			m_txt[i-1] = CCLabelTTF::labelWithString( ValuesUtil::Instance()->getString(str).c_str(), CCSizeMake(POSX(500), POSX(22.0f)), CCTextAlignmentLeft, "Arial", POSX(22.0f));
			m_txt[i-1]->setPosition(ccp(POSX(32), winSize.height-POSX(242)+POSX(i*55)));
			m_txt[i-1]->setAnchorPoint(ccp(0, 0));
			this->addChild(m_txt[i-1], 2);
			m_txt[i-1]->setColor(ccc3(240, 210, 68));
		}
		//
		_txtMoveCD->setIsVisible(false);
		_txtDigCD->setIsVisible(false);
		//
		_btn_showRank->setPosition(ccp(POSX(240), winSize.height-POSX(305)));
		//
		_btn_change->setPosition(ccp(POSX(88), winSize.height-POSX(305)));
		_btn_change->setTag(0);
		//char 鼓励面板
		m_Label_change->setString(ValuesUtil::Instance()->getString("SLM060").c_str());
		//
		m_btnGoldInspire->setIsVisible(true);
		m_btnPracInspire->setIsVisible(true);
		//
		m_txtGW1->setIsVisible(true);
		m_txtGW2->setIsVisible(true);

	}
}

// 更新攻击加成 
void MineInfo::updateAttPlus(int plus)
{
	char str[10];
	sprintf(str, "%d%%", plus);
	m_txtGW1->setString(str);

	bool isFull = false;
	if (plus >= 40)
	{
		isFull = true;
	}
	if (isFull)
	{
		_gIsFull = isFull;
		isAllFull();
	}
}


		
// 更新防御加成 
void MineInfo::updateDefPlus(int plus)
{
	char str[10];
	sprintf(str, "%d%%", plus);
	m_txtGW2->setString(str);

	bool isFull = false;
	if (plus >= 40)
	{
		isFull = true;
	}
	if (isFull)
	{
		_dIsFull = isFull;
		isAllFull();
	}
}

void MineInfo::isAllFull()
{
	if(_gIsFull && _dIsFull)
	{
	//	m_btnGoldInspire.mouseEnabled = false;
		m_btnGoldInspire->setIsEnabled(false);
		//Utils.applyBlackAndWhiteFilter(this._btnGoldInspire);
		m_btnPracInspire->setIsEnabled(false);
	//	this._btnPracInspire.enabled = false;
	//	Utils.applyBlackAndWhiteFilter(this._btnPracInspire);
	}
}

void MineInfo::btnClick_showRank(CCObject* pSender)
{
	MineRank* oldp = (MineRank*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_silverMineRank);
	if (!oldp)
	{
		oldp = new MineRank();
		oldp->init();
		oldp->updateRank(pContainer->m_arr);
		oldp->updateSilver(pContainer->m_silver_forRank);
		LayerManager::intervalLayer->addChild(oldp, IntervalLayer::IntervalLayerZ_guild_silverMineRank, IntervalLayer::IntervalLayerTAG_guild_silverMineRank);
		oldp->release();
	}
}

void MineInfo::updateDigCD(uint digCD, bool inCD)
{
 	this->_digCD = digCD;
//			this._inDigCD = inCD;  由 cd来判断 
			
	uint severTimer = CDManage::Instance()->getServerTime() *0.001;	 // 秒数 
	int dValue = digCD-severTimer;
	if(dValue<=0){
		this->_inDigCD = false;
		m_digOffset = 0;
	}else{
		this->_inDigCD = true;
	}
			
	if(!_hasStep)
	{
		_hasStep = true;
		step();
		TimerManage::Instance()->add( 1.0f, schedule_selector( MineInfo::step ), this );
	}
			
}

void MineInfo::updateMoveCD(uint moveCD, bool inCD)
{
	this->_moveCD = moveCD;
	uint severTimer = CDManage::Instance()->getServerTime()*0.001;	 // 秒数 
	int mValue = moveCD-severTimer;
	if(mValue<=0){
		this->_inMoveCD = false;
		m_moveOffset = 0;
	}else{
		this->_inMoveCD = true;
	}
			
	if(!_hasStep)
	{
		_hasStep = true;
		step();
		TimerManage::Instance()->add( 1.0f,schedule_selector( MineInfo::step ), this );
	}
}

void MineInfo::step(float dt)
{
	uint severTimer = CDManage::Instance()->getServerTime() *0.001;	 // 秒数
	int dValue = _digCD-severTimer/*-m_digOffset*/; 

	int mValue = _moveCD-severTimer/*-m_moveOffset*/;

	if(dValue<=0){
		_inDigCD = false;
		dValue = 0;
	}else{
		_inDigCD = true;
	}
			
	if(mValue<=0){
		_inMoveCD = false;
		mValue = 0;
	}else{
		_inMoveCD = true;
	}
			
	std::string dStr = formatData(dValue);
	std::string mStr = formatData(mValue);
			
	setDigCD(dStr);
	setMoveCD(mStr);
 
}

void MineInfo::setDigCD(std::string str)
{
	//var colorStr:String = _inDigCD?"#ff0000":"0FF660";
	//_txtDigCD->setString(str.c_str());
//	_txtDigCD.htmlText = "<font color='" + colorStr + "'>"+str+"</font>";  // var colorStr:String = inCD?"#ff0000":"0FF660";
	//pContainer->setDigEnable(!_inDigCD);
}

void MineInfo::setMoveCD(std::string str)
{
//	_txtMoveCD->setString(str.c_str());
}

std::string MineInfo::formatData(int value)
{
	int minute = floorf((value/60)%60);
	int second = floorf(value%60);
			
	char str[50];
	sprintf(str, "%02d:%02d", minute, second);

	return str;
}
		