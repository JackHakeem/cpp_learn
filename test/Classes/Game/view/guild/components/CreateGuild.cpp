#include "CreateGuild.h"
#include "GuildView.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "GuildTabPanel.h"
#include "manager/LayerManager.h"
#include "socket/command/c1e/CCMD1CE.h"
#include "GuildEventConst.h"
#include "TextFieldTTF.h"
#include "model/guild/vo/EditGuildInfoVo.h"
#include "GuildDispatcher.h"

const float FontSize3 = 30.0f;
const float FontSize2 = 30.0f;

CreateGuild::CreateGuild()
{
	m_pTextField1 = 0;
}

CreateGuild::~CreateGuild()
{}

bool CreateGuild::init()
{
	if (!LayerNode::init())
		return false;

	float offsetTextX = 120.0f;
	//
	_container = new LayerNode();
	_container->init();
	this->addChild(_container, 0);
	_container->release();
	//title
	SpriteNode* title = new SpriteNode();
	title->initWithSpriteFrameName("guild/create_guild.png");
	_container->addChild(title, 1);
	title->setPosition(ccp(POSX(488), POSX(640-156)));
	title->release();
	//bg1
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("guild/select.png", ccp(POSX(242), POSX(183)),ccp(6,7),
		CCSizeMake(POSX(496), POSX(302)));
	_container->addChild(_bg1, 0);
	_bg1->release();
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,100));
	_container->addChild(blackBG, -1);
	//输入你公会的大名
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1008").c_str(),
			CCSizeMake(POSX(278), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(281), POSX(418)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));
	}
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithSpriteFrame("guild/select.png", ccp(POSX(281), POSX(314)),ccp(0,0),
			CCSizeMake(POSX(416), POSX(54)));
		_container->addChild(_bg, 0);
		_bg->release();
	}
	{
		TextFieldTTF * pTextField = new TextFieldTTF();
		//pTextField->setTag(LoginView::TEXTFIELD_ROLECREATE);
		//pTextField->setString("aaa");
		pTextField->m_frame = CCSizeMake(POSX(416), POSX(49));
		pTextField->setEmojiRefuse(true);
	//	pTextField->setFieldSize(CCSizeMake(POSX(100),POSX(50)));
		//pTextField->setUp(this,POSX(100));
		_container->addChild(pTextField, 0);
		pTextField->setPosition(ccp(POSX(281+416/2+20), POSX(314+25)));
		pTextField->release();
		m_pTextField1 = pTextField;

	}
	//确定
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
			menu_selector(CreateGuild::clickOK) );
		_btn->setPosition(ccp(POSX(375+50), POSX(216+25)));
		_btn->setTag(0);
		_btn->setScale(1.2f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		_container->addChild(buttonMenu, 10);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1007").c_str(),
			CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setScale(0.8f);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//取消
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
			menu_selector(CreateGuild::cancel) );
		_btn->setPosition(ccp(POSX(518+50), POSX(216+25)));
		_btn->setTag(0);
		_btn->setScale(1.2f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		_container->addChild(buttonMenu, 10);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD100").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setScale(0.8f);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(CreateGuild::dispear) );
		_btnX->setPosition(ccp(POSX(769), POSX(514)));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnX, NULL);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		this->addChild(buttonMenu, 1);
	}

	this->setIsTouchEnabled(true);
	return true;
}


void CreateGuild::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::IntervalLayer_guild, true );
}

bool CreateGuild::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void CreateGuild::dispear(CCObject* pSender)
{
	CreateGuild* oldp = (CreateGuild*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_guild_createGuild);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}

void CreateGuild::clickOK(CCObject* pSender)
{
	string name = ((KKTextFieldTTF*)m_pTextField1->m_pTrackNode)->getString();
	if(name == "")
	{
		LangManager::msgShow("GLD032");
		return;
	}
	GuildDispatcher::getInstance()->dispatchEvent(GuildEventConst::CREAT_GUILD, (char*)name.c_str());
	//
	CreateGuild* oldp = (CreateGuild*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_guild_createGuild);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}
		
void CreateGuild::cancel(CCObject* pSender)
{
	CreateGuild* oldp = (CreateGuild*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_guild_createGuild);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}