#include "DonateView.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "TextFieldTTF.h"
#include "socket/command/c1d/CCMD1D1.h"
#include "manager/LayerManager.h"
#include "GuildEventConst.h"
#include "model/player/RoleManage.h"
const float FontSize2 = 20.f;

DonateView::DonateView()
{
	_money = 0;
	_techID = 0;
	_donateMax = 0;
	_donateMax = 9999999;
	_ownedMoney = 0;
	_limit = 0;
}

DonateView::~DonateView()
{
}

bool DonateView::init(int techID)
{
	if (!LayerNode::init())
		return false;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/guild/res_guild.plist");

	_techID = techID;
	//获取玩家银币数量
	_ownedMoney = RoleManage::Instance()->_accountInfo._silver;
	
	//bg1
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_6.png", ccp(POSX(240), POSX(640-460)),ccp(0,0),
		CCSizeMake(POSX(775-240), POSX(460-150)));
	this->addChild(_bg1, 0);
	_bg1->release();
	//bg2
	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(255), POSX(640-440)),ccp(0,0),
		CCSizeMake(POSX(760-255), POSX(440-170)));
	this->addChild(_bg2, 0);
	_bg2->release();
	float btnScaleX = 0.5f;
	float btnTTFScaleX = 1.6f;
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,100));
	this->addChild(blackBG, -1);
	//_btnCut
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return false;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(DonateView::onBtnAdd) );
		_btn->setPosition(ccp(POSX(535), POSX(640-240)));
		_btn->setTag(0);
		_btn->setScaleX(btnScaleX);
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		this->addChild(buttonMenu, Z_btnCut, TAG_btnCut);	

		SpriteNode* p = new SpriteNode();
		p->initWithSpriteFrameName("guild/arrow_white.png");
		p->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
		_btn->addChild(p);
		p->release();
		p->setScaleX(btnTTFScaleX);
	}
	//_btnAdd
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return false;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(DonateView::onBtnCut) );
		_btn->setPosition(ccp(POSX(610), POSX(640-240)));
		_btn->setTag(0);
		_btn->setScaleX(btnScaleX);
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		this->addChild(buttonMenu, Z_btnAdd, TAG_btnAdd);	

		SpriteNode* p = new SpriteNode();
		p->initWithSpriteFrameName("guild/arrow_white.png");
		p->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2));
		_btn->addChild(p);
		p->release();
		p->setScaleX(btnTTFScaleX);
		p->setRotation(180.0f);
	}
	//TAG_btnMax
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return false;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite, 
			this, 
			menu_selector(DonateView::onBtnMax) );
		_btn->setPosition(ccp(POSX(700), POSX(640-240)));
		_btn->setTag(0);
		_btn->setScaleX(btnScaleX);
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		this->addChild(buttonMenu, Z_btnAdd, TAG_btnAdd);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD1012").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
		pLabel->setScaleX(btnTTFScaleX);
	}
	//TAG_btnOK
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return false;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(DonateView::onBtnOK) );
		_btn->setPosition(ccp(POSX(442), POSX(640-390)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		this->addChild(buttonMenu, Z_btnOK, TAG_btnOK);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD1013").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
		
	}
	//TAG_btnCancel
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return false;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(DonateView::onBtnCancel) );
		_btn->setPosition(ccp(POSX(600), POSX(640-390)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		this->addChild(buttonMenu, Z_btnCancel, TAG_btnCancel);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD1014").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//今日最大上限
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD1015").c_str(), CCSizeMake(POSX(250), POSX(FontSize2)), CCTextAlignmentLeft, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(POSX(363), POSX(325)));
		pLabel->setAnchorPoint(ccp(0,0));
		this->addChild(pLabel, 1);
		pLabel->setColor(ccc3(255, 255, 255));	
	}
	//0/5000  GLD1016
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("0/0", CCSizeMake(POSX(300), POSX(FontSize2)), CCTextAlignmentLeft, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(POSX(530), POSX(325)));
		pLabel->setAnchorPoint(ccp(0,0));
		this->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 255, 255));	
		_limit = pLabel;
	}
	//frame
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithSpriteFrame("guild/select.png", ccp(POSX(269), POSX(640-265)),ccp(0,0),
			CCSizeMake(POSX(493-280), POSX(265-210)));
		this->addChild(_bg, 0);
		_bg->release();
	}
	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(DonateView::dispear) );
		_btnX->setPosition(ccp(POSX(805), POSX(640-125)));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnX, NULL);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild);
		this->addChild(buttonMenu, 1);
	}
	//
	{
		TextFieldTTF * pTextField = new TextFieldTTF();
		//pTextField->setTag(LoginView::TEXTFIELD_ROLECREATE);
		//pTextField->setString("aaa");
		pTextField->m_frame = CCSizeMake(POSX(493-300), POSX(265-210));
	//	pTextField->setFieldSize(CCSizeMake(POSX(100),POSX(50)));
		//pTextField->setUp(this,POSX(100));
		pTextField->setString("0");
		pTextField->setIsNumber(true, 9);
		this->addChild(pTextField, 0);
		pTextField->setPosition(ccp(POSX(380), POSX(640-235)));
		pTextField->release();
		_money = pTextField;
		
	}
	//
	update();	//更新捐献上限

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/guild/res_guild.plist");
	return true;
}

void DonateView::dispear(CCObject* pSender)
{
	//删除成员查看列表
	DonateView* oldp = (DonateView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_donateview);
	if (oldp)
		LayerManager::intervalLayer->removeChildByTag(IntervalLayer::IntervalLayerTAG_guild_donateview, true);
}

int DonateView::getmoneytext()
{
	if (_money)
	{
		string value = ((KKTextFieldTTF*)_money->m_pTrackNode)->getString();
		return atoi(value.c_str());
	}
	return 0;
}

void DonateView::setmoneytext(int value)
{
	char valuestr[30];
	sprintf(valuestr, "%d", value);
	((KKTextFieldTTF*)_money->m_pTrackNode)->setString(valuestr);
}

/**
* 减少捐献银币数量按钮 
* @param e
*/		
void DonateView::onBtnCut(CCObject* pSender)
{
	int money = getmoneytext() - 100;
	if(money<0) 
		money = 0;
	setmoneytext(money);
}
		
/**
	* 增加捐献银币数量按钮 
	* @param e
	*/		
void DonateView::onBtnAdd(CCObject* pSender)
{
	int money = getmoneytext() + 100;
	money = onMoneyCheck(money);
	setmoneytext(money);
}

/**
	* 检查捐献的银币是否超出最大值 
	* @param money 捐献的银币
	* @return 返回能够捐献的银币
	*/		
int DonateView::onMoneyCheck(int money)
{
	int max = (_donateMax - _donated) < _ownedMoney ? _donateMax - _donated : _ownedMoney;
	if(money > max) money = max;
	return money;
}

		
/**
	* 最大捐献银币数量按钮 
	* @param e
	*/		
void DonateView::onBtnMax(CCObject* pSender)
{
	int max = (_donateMax - _donated) < _ownedMoney ? _donateMax - _donated : _ownedMoney;
	setmoneytext(max);
}

/**
	* 确定按钮 
	* @param e
	*/		
void DonateView::onBtnOK(CCObject* pSender)
{
	if(getmoneytext() != 0){
		CCMD1D1 cmd;
		cmd.a_id = _techID;
		cmd.b_money = getmoneytext();
		this->dispatchEvent(GuildEventConst::DONATE_MONEY, &cmd);
		setmoneytext(0);
	}
	DonateView* _donateView = (DonateView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_donateview);
	if (_donateView)
	{
		_donateView->removeFromParentAndCleanup(true);
	}
}

/**
	* 关闭按钮 
	* @param e
	*/		
void DonateView::onBtnCancel(CCObject* pSender)
{
	DonateView* _donateView = (DonateView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_donateview);
	if (_donateView)
	{
		_donateView->removeFromParentAndCleanup(true);
	}	
}

/**
	* 更新今日捐献上限数据 
	*/		
void DonateView::update()
{
	char value[50];
	sprintf(value, "%d/%d", _donated, _donateMax);
	_limit->setString(value);
}

void DonateView::setdonated(uint value)
{
	_donated = value;
}

void DonateView::setdonateMax(uint value)
{
	_donateMax = value;
}