#include "GuildEditView.h"
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
#include "model/guild/vo/GuildInfoVo.h"

const float FontSize3 = (30.0f);
const float FontSize2 = (30.0f);

GuildEditView::GuildEditView()
{
	m_pTextField1 = 0;
	m_pTextField2 = 0;
	m_pTextField3 = 0;
}

GuildEditView::~GuildEditView()
{}

bool GuildEditView::init(GuildInfoVo* guildInfo)
{
	if (!LayerNode::init())
		return false;
	
	float offsetTextX = 120.0f;

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/guild/res_guild.plist");
	//
	_container = new LayerNode();
	_container->init();
	_container->setPosition(POS(ccp(0, POSX(90)), ScaleUtil::CENTER_TOP));
	this->addChild(_container, 0);
	_container->release();
	//title
	SpriteNode* title = new SpriteNode();
	title->initWithSpriteFrameName("guild/title_edit.png");
	_container->addChild(title, 1);
	title->setPosition(ccp(POSX(488), POSX(640-156)));
	title->release();
	//bg1
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("guild/select.png", ccp(POSX(200), POSX(640-600)),ccp(6,7),
		CCSizeMake(POSX(784-200), POSX(600-154)));
	_container->addChild(_bg1, 0);
	_bg1->release();
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,100));
	this->addChild(blackBG, -1);
	blackBG->setPosition(ccp(0, 0));
	//QQȺ��
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD096").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(243), POSX(640-220)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));
	}
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithSpriteFrame("guild/select.png", ccp(POSX(325), POSX(640-244)),ccp(0,0),
			CCSizeMake(POSX(656-325), POSX(244-180)));
		_container->addChild(_bg, 0);
		_bg->release();
	}
	{
		TextFieldTTF * pTextField = new TextFieldTTF();
		//pTextField->setTag(LoginView::TEXTFIELD_ROLECREATE);
		pTextField->setString(guildInfo->qq);
		pTextField->setIsNumber(true, 10);
		pTextField->m_frame = CCSizeMake(POSX(300), POSX(30));
	//	pTextField->setFieldSize(CCSizeMake(POSX(100),POSX(50)));
	//	pTextField->setUp(this, POSX(380));
		_container->addChild(pTextField, 0);
		pTextField->setPosition(ccp(POSX(370+offsetTextX), POSX(640-215)));
		pTextField->release();
		m_pTextField1 = pTextField;

	}
	//
	//
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD103").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(640), POSX(640-293)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));
	}
	//
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD097").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(243), POSX(640-293)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));
	}
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithSpriteFrame("guild/select.png", ccp(POSX(325), POSX(640-370)),ccp(0,0),
			CCSizeMake(POSX(656-325), POSX(364-240)));
		_container->addChild(_bg, 0);
		_bg->release();
	}
	{
		TextFieldTTF * pTextField = new TextFieldTTF();
		//pTextField->setTag(LoginView::TEXTFIELD_ROLECREATE);
		pTextField->setString(guildInfo->notice);
		pTextField->m_frame = CCSizeMake(POSX(300), POSX(200));
	//	pTextField->m_banjiaoCountMax = 10;
	//	pTextField->setFieldSize(CCSizeMake(POSX(100),POSX(50)));
		//pTextField->setUp(this, POSX(380));
		_container->addChild(pTextField, 0);
		pTextField->setPosition(ccp(POSX(370+offsetTextX), POSX(640-310)));
		pTextField->release();
		m_pTextField2 = pTextField;
	}
	//���ܣ�
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD098").c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(243), POSX(640-426)));
		_container->addChild(pLabel, 1);
		pLabel->setColor(ccc3(233, 211, 24));
	}
	{
		CCUIBackground* _bg = new CCUIBackground();
		_bg->initWithSpriteFrame("guild/select.png", ccp(POSX(325), POSX(640-496)),ccp(0,0),
			CCSizeMake(POSX(656-325), POSX(486-350)));
		_container->addChild(_bg, 0);
		_bg->release();
	}
	{
		TextFieldTTF * pTextField = new TextFieldTTF();
		//pTextField->setTag(LoginView::TEXTFIELD_ROLECREATE);
		pTextField->setString(guildInfo->intr);
		pTextField->m_frame = CCSizeMake(POSX(300), POSX(200));
	//	pTextField->setFieldSize(CCSizeMake(POSX(100),POSX(50)));
		//pTextField->setUp(this, POSX(380));
		_container->addChild(pTextField, 0);
		pTextField->setPosition(ccp(POSX(370+offsetTextX), POSX(640-430)));
		pTextField->release();
		m_pTextField3 = pTextField;
	}
	//ȷ��
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
			menu_selector(GuildEditView::clickOK) );
		_btn->setPosition(ccp(POSX(415), POSX(640-535)));
		_btn->setTag(0);
		_btn->setScale(1.2f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild);
		_container->addChild(buttonMenu, 10);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD099").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setScale(0.8f);
		pLabel->setColor(ccc3(255, 209, 153));	
	}
	//ȡ��
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
			menu_selector(GuildEditView::cancel) );
		_btn->setPosition(ccp(POSX(570), POSX(640-535)));
		_btn->setTag(0);
		_btn->setScale(1.2f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild);
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
			menu_selector(GuildEditView::dispear) );
		_btnX->setPosition(ccp(POSX(818), POSX(640-162)));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnX, NULL);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild);
		_container->addChild(buttonMenu, 1);
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/guild/res_guild.plist");
	return true;
}


void GuildEditView::dispear(CCObject* pSender)
{
	GuildEditView* oldp = (GuildEditView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_editView);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}

void GuildEditView::clickOK(CCObject* pSender)
{
	//CCMD1CE obj;
	/*var qqStr:String = _editPanel["_txtQQ"].text;
	var postStr:String = _editPanel["_txtPost"].text;
	var introStr:String = _editPanel["_txtIntro"].text;
	var vo:EditGuildInfoVo = new EditGuildInfoVo(_editPanel["_txtQQ"].text,_editPanel["_txtPost"].text,_editPanel["_txtIntro"].text);*/
//	this->dispatchEvent(GuildEventConst::EDIT_GUILD_NOTICE,&vo);
	EditGuildInfoVo vo;
	vo.qq = ((KKTextFieldTTF*)m_pTextField1->m_pTrackNode)->getString();
	vo.notice = ((KKTextFieldTTF*)m_pTextField2->m_pTrackNode)->getString();
	vo.intro = ((KKTextFieldTTF*)m_pTextField3->m_pTrackNode)->getString();
	GuildDispatcher::getInstance()->dispatchEvent(GuildEventConst::EDIT_GUILD_NOTICE,&vo);
	//
	GuildEditView* oldp = (GuildEditView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_editView);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}
		
void GuildEditView::cancel(CCObject* pSender)
{
	GuildEditView* oldp = (GuildEditView*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_editView);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}
