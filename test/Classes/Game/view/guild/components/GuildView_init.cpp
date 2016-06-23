
#include "manager/PopEventName.h"
#include "GuildView.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "GuildTabPanel.h"
#include "KKLabelTTF.h"

static const int TAG_PARENT = 1001;
static float FontSize = 26.0f;
static float FontSize2 = 20.0f;
static float FontSize3 = 22.0f;

void GuildView::changeIcon(int emblemGrade)
{
	SpriteNode* _icon = (SpriteNode*)_container->getChildByTag(GuildViewTAG_icon);
	if (_icon)
	{
		_icon->removeFromParentAndCleanup(true);
	}
	char path[100];
	_icon = new SpriteNode();
	sprintf(path, "guild/icon_%d.png", 0);
	bool bVar = _icon->initWithSpriteFrameName(path);
	if (bVar)
	{
		_icon->setPosition(ccp(POSX(100), POSX(640-150)));
		_container->addChild(_icon, GuildViewZ_icon,GuildViewTAG_icon);
		_icon->release();
	}
}

void GuildView::initView()
{
	/*_container->setPosition(POS(ccp(0,0), ScaleUtil::CENTER_TOP));
	_container->setAnchorPoint(CCPointZero);*/

	//bg1
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(35), POSX(640-600)),ccp(0,0),
		CCSizeMake(POSX(320-35), POSX(600-90)));
	_container->addChild(_bg1, GuildViewZ_bg1, GuildViewTAG_bg1);
	_bg1->release();
	//bg2
	CCUIBackground* _bg2 = new CCUIBackground();
	_bg2->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(45), POSX(640-540)),ccp(0,0),
		CCSizeMake(POSX(300-45), POSX(540-400)));
	_container->addChild(_bg2, GuildViewZ_bg2, GuildViewTAG_bg2);
	_bg2->release();
	//bg3
	CCUIBackground* _bg3 = new CCUIBackground();
	_bg3->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(332), POSX(640-600)),ccp(0,0),
		CCSizeMake(POSX(926-335), POSX(600-90)));
	_container->addChild(_bg3, GuildViewZ_bg3, GuildViewTAG_bg3);

	_bg3->release();
	
	//char pIconPath[128];
	//sprintf(pIconPath, "guild/arrow_white.png");
	//CCSprite *pIcon = CCSprite::spriteWithSpriteFrameName("guild/arrow_white.png");
	//icon
	changeIcon(0);
	//title
	{
		SpriteNode* _title = new SpriteNode();
		_title->initWithSpriteFrameName("guild/title.png");
		_title->setPosition(ccp(POSX(495), POSX(640-75)));
		_container->addChild(_title, GuildViewZ_icon);
		_title->release();
	}
	//
	//��յȼ�?
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD001").c_str(), CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(162), POSX(640-133)));
		_container->addChild(pLabel, GuildViewZ_junhuidengji_name, GuildViewTAG_junhuidengji_name);
		pLabel->setColor(ccc3(251, 0, 255));
	}
	//%d��
	{
		char value[100];
		sprintf(value, ValuesUtil::Instance()->getString("GUILD002").c_str(), 1);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(value, CCSizeMake(POSX(100), POSX(FontSize)), CCTextAlignmentLeft, "Arial", POSX(FontSize));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(268), POSX(640-133)));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtLevel);
		pLabel->setColor(ccc3(193, 255, 51));
	}
	//����
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return ;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(GuildView::updateEmblemDispatcher) );
		_btn->setPosition(ccp(POSX(210), POSX(640-175)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1);
		_container->addChild(buttonMenu, GuildViewZ_btUpgrade, GuildViewTAG_btUpgrade);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD003").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//�������?
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD004").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(50), POSX(640-235)));
		_container->addChild(pLabel, GuildViewZ_txt);
		pLabel->setColor(ccc3(255, 209, 51));
	}
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(150), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(159), POSX(640-235)));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtName);
		pLabel->setColor(ccc3(255, 255, 255));		
	}
	//�����?
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD005").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(50), POSX(640-268)));
		_container->addChild(pLabel, GuildViewZ_txt);
		pLabel->setColor(ccc3(255, 209, 51));
	}
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(150), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(159), POSX(640-268)));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtID);
		pLabel->setColor(ccc3(255, 255, 255));		
	}
	//��������
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD006").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(50), POSX(640-300)));
		_container->addChild(pLabel, GuildViewZ_txt);
		pLabel->setColor(ccc3(255, 209, 51));
	}
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(159), POSX(640-300)));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtRank);
		pLabel->setColor(ccc3(255, 255, 255));		
	}
	//��Ա����
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD007").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(50), POSX(640-332)));
		_container->addChild(pLabel, GuildViewZ_txt);
		pLabel->setColor(ccc3(255, 209, 51));
	}
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(159), POSX(640-332)));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtOnline);
		pLabel->setColor(ccc3(255, 255, 255));		
	}
	//����ʱ��
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD008").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(50), POSX(640-364)));
		_container->addChild(pLabel, GuildViewZ_txt);
		pLabel->setColor(ccc3(255, 209, 51));
	}
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(159), POSX(640-364)));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtTime);
		pLabel->setColor(ccc3(255, 255, 255));		
	}
	//����QQ
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD009").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(50), POSX(640-396)));
		_container->addChild(pLabel, GuildViewZ_txt);
		pLabel->setColor(ccc3(255, 209, 51));
	}
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(140), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(159), POSX(640-396)));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtQQ);
		pLabel->setColor(ccc3(255, 255, 255));		
	}
	//���ṫ��
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GUILD010").c_str(), CCSizeMake(POSX(200), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(52), POSX(640-432)));
		_container->addChild(pLabel, GuildViewZ_txt);
		pLabel->setColor(ccc3(255, 209, 51));
	}
	{
		//CCLabelTTF* pLabel = CCLabelTTF::labelWithString("none", CCSizeMake(POSX(250), POSX(FontSize3*4)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		//pLabel->setAnchorPoint(ccp(0, 0));
		//pLabel->setPosition(ccp(POSX(52), POSX(640-462)));
		//_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtPost);
		//pLabel->setColor(ccc3(255, 255, 255));	
		KKLabelTTF* pLabel = new KKLabelTTF();
		pLabel->init(18, 20.0f, CCSizeMake(POSX(200), POSX(200)));
		pLabel->setPosition(ccp(POSX(52), POSX(640-462)));
		std::string value = "";
		pLabel->add(value, ccc3(255, 255, 255));
		_container->addChild(pLabel, GuildViewZ_txt, GuildViewTAG_txtPost);
		pLabel->release();

	}		
	//�޸���Ϣ
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(GuildView::editGuildInfo) );
		_btn->setPosition(ccp(POSX(97), POSX(640-570)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
		_container->addChild(buttonMenu, GuildViewTAG_btnEditInfo, GuildViewTAG_btnEditInfo);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD094").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//��ɢ����
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(GuildView::abortGuildDispatcher) );
		_btn->setPosition(ccp(POSX(250), POSX(640-570)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
		_container->addChild(buttonMenu, GuildViewZ_btnAbort, GuildViewTAG_btnAbort);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD095").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//ȡ����?
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(GuildView::abortCancelDispatcher) );
		_btn->setPosition(ccp(POSX(250), POSX(640-570)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
		_container->addChild(buttonMenu, GuildViewZ_btnCancelAbort, GuildViewTAG_btnCancelAbort);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD102").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//�˳��?
	{
		CCSprite *pNormalNewSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectedNewSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(!pNormalNewSprite || !pPressedNewSprite || !pSelectedNewSprite)
		{
			return;
		}
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalNewSprite,
			pPressedNewSprite,
			pSelectedNewSprite,
			this, 
			menu_selector(GuildView::exitGuildDispatcher) );
		_btn->setPosition(ccp(POSX(250), POSX(640-570)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Arena-1);
		_container->addChild(buttonMenu, GuildViewZ_btnQuit, GuildViewTAG_btnQuit);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD1019").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//�м����弯

	_tabPanel = new GuildTabPanel();
	_tabPanel->guildView = this;
	_tabPanel->init();
	_container->addChild(_tabPanel, GuildViewZ_tabPanel, GuildViewTAG_tabPanel);	
	_tabPanel->release();
}

