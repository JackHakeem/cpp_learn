#include "GuildInfoView.h"
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

GuildInfoView::GuildInfoView(GuildInfoVo guildVo)
{
	_guildVo = guildVo;
}

GuildInfoView::~GuildInfoView()
{}

bool GuildInfoView::init()
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
	title->initWithSpriteFrameName("guild/title.png");
	_container->addChild(title, 1);
	title->setPosition(ccp(POSX(494+15), POSX(485)));
	title->release();
	//bg1
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("popuibg/bg1.png", ccp(POSX(285), POSX(97)),ccp(6,7),
		CCSizeMake(POSX(453), POSX(388)));
	_container->addChild(_bg1, 0);
	_bg1->release();
	
	//bg2
	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("ui2.png", ccp(POSX(301), POSX(114)),ccp(6,7),
		CCSizeMake(POSX(420), POSX(353)));
	_container->addChild(_bg2, 0);
	_bg2->release();

	//bg3
	CCUIBackground* _bg3 = new CCUIBackground();
	_bg3->initWithSpriteFrame("popuibg/bg2.png", ccp(POSX(326), POSX(128)),ccp(6,7),
		CCSizeMake(POSX(384), POSX(192)));
	_container->addChild(_bg3, 0);
	_bg3->release();
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,100));
	_container->addChild(blackBG, -1);


	CCUIBackground* selectedSpriteImage = new CCUIBackground();
	selectedSpriteImage->initWithSpriteFrame( "ui.png",
		CCPointZero, ccp(POSX(0),POSX(0)), CCSizeMake( POSX(100), POSX(100) ) );
	_container->addChild( selectedSpriteImage );
	selectedSpriteImage->setAnchorPoint(CCPointZero);
	selectedSpriteImage->setPosition(ccp(POSX(326), POSX(349)));
	selectedSpriteImage->release();

	char path[100];
	SpriteNode* _icon = new SpriteNode();
	sprintf(path, "guild/icon_%d.png", 0);
	_icon->initWithSpriteFrameName(path);
	_icon->setAnchorPoint(CCPointZero);
	_icon->setPosition(ccp(POSX(13), POSX(10)));
	selectedSpriteImage->addChild(_icon);
	_icon->release();

	//名称
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1010").c_str(),
			CCSizeMake(POSX(67), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(438), POSX(423)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));

		pLabel = CCLabelTTF::labelWithString(
			_guildVo.name.c_str(),
			CCSizeMake(POSX(200), POSX(24+4)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(505), POSX(423-4)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccWHITE);
	}
	//会长
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1004").c_str(),
			CCSizeMake(POSX(67), POSX(24+4)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(438), POSX(423-31-4)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));

		pLabel = CCLabelTTF::labelWithString(
			_guildVo.leaderName.c_str(), 
			CCSizeMake(POSX(200), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(505), POSX(423-31)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccWHITE);
	}
	//等级
	{
		char tmp[30];
		sprintf(tmp, "%d", _guildVo.emblemGrade);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1005").c_str(),
			CCSizeMake(POSX(67), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(438), POSX(423-31*2)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));

		pLabel = CCLabelTTF::labelWithString(
			tmp, 
			CCSizeMake(POSX(200), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(505), POSX(423-31*2)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccWHITE);
	}
	//人数
	{
		char tmp[30];
		sprintf(tmp, "%d/%d",  _guildVo.members, _guildVo.memberLimit);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1006").c_str(),
			CCSizeMake(POSX(67), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(438), POSX(423-31*3)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));

		pLabel = CCLabelTTF::labelWithString(
			tmp, 
			CCSizeMake(POSX(200), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(505), POSX(423-31*3)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccWHITE);
	}
	//介绍
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1011").c_str(),
			CCSizeMake(POSX(121), POSX(24)), CCTextAlignmentLeft, "Arial", POSX(24));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(334), POSX(289)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));

		pLabel = CCLabelTTF::labelWithString(
			_guildVo.intr.c_str(), 
			CCSizeMake(POSX(383), POSX(153)), CCTextAlignmentLeft, "Arial", POSX(22));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(330), POSX(126)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccWHITE);
	}


	////取消
	//{
	//	CCMenuItemImage* _btn = CCMenuItemImage::itemFromNormalImage(
	//		"assets/ui/button3_0.png", 
	//		"assets/ui/button3_1.png", 
	//		"assets/ui/button3_2.png", 
	//		this, 
	//		menu_selector(GuildInfoView::dispear) );
	//	_btn->setPosition(ccp(POSX(514), POSX(151)));
	//	_btn->setTag(0);
	//	_btn->setScale(1.2f);

	//	CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
	//	buttonMenu->setPosition( CCPointZero );
	//	buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
	//	_container->addChild(buttonMenu, 10);	

	//	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD100").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
	//	pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
	//	_btn->addChild(pLabel, 0, 0);
	//	pLabel->setScale(0.8f);
	//	pLabel->setColor(ccc3(255, 209, 153));	
	//}
	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(GuildInfoView::dispear) );
		_btnX->setPosition(ccp(POSX(769), POSX(514)));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnX, NULL);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		this->addChild(buttonMenu, 1);
	}

	this->setIsTouchEnabled(true);
	return true;
}


void GuildInfoView::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate( this, TLE::IntervalLayer_guild-1, true );
}

bool GuildInfoView::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

void GuildInfoView::dispear(CCObject* pSender)
{
	GuildInfoView* oldp = (GuildInfoView*)LayerManager::intervalLayer->getChildByTag(
		IntervalLayer::IntervalLayerTAG_guild_info);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}