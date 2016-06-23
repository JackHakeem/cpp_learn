#include "VerifyItem.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "model/player/RoleManage.h"
#include "manager/TouchLayerEnum.h"
#include "socket/command/c1b/CCMD1BD.h"
#include "GuildDispatcher.h"
#include "GuildEventConst.h"

const float w_frame = 915-345;
const float h_frame = 40.0f;
const float FontSize = 30.0f;
const float FontSize3 = 20.0f;
const float FontSize2 = 24.0f;

VerifyItem::VerifyItem()
{
	_guildDispatch = 0;
}

VerifyItem::~VerifyItem()
{}

bool VerifyItem::init(ApplyVo ApplyVo)
{
	if (!LayerNode::init())
		return false;

	_applyVo = ApplyVo;
	_guildDispatch = GuildDispatcher::getInstance();
	initView();
	return true;
}



void VerifyItem::initView()
{
	this->setContentSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));
	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		CCSizeMake(POSX(w_frame), POSX(h_frame-3)));
	this->addChild(_bg1, VerifyItemZ_bg1, VerifyItemTAG_bg1);
	_bg1->release();

	cocos2d::ccColor3B labelcolor = ccc3(233, 211, 24);
	float offsetX = -340.0f;
	//申请人
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(_applyVo.name.c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(386+offsetX), POSX(15)));
		this->addChild(pLabel, VerifyItemZ_txtID, VerifyItemTAG_txtID);
		pLabel->setColor(labelcolor);		
	}
	//等级
	{
		char value[30];
		sprintf(value, "%d", _applyVo.grade);

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(value, CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(500+offsetX), POSX(15)));
		this->addChild(pLabel, VerifyItemZ_txtID, VerifyItemTAG_txtID);
		pLabel->setColor(labelcolor);		
	}
	////称号
	//{
	//	char value[30];
	//	sprintf(value, "%d", _applyVo.grade);

	//	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(value, CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
	//	pLabel->setAnchorPoint(ccp(0, 0));
	//	pLabel->setPosition(ccp(POSX(0), POSX(15)));
	//	this->addChild(pLabel, VerifyItemZ_txtID, VerifyItemTAG_txtID);
	//	pLabel->setColor(labelcolor);		
	//}
	//申请时间
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(_applyVo.ctime.c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(635+offsetX), POSX(15)));
		this->addChild(pLabel, VerifyItemZ_txtID, VerifyItemTAG_txtID);
		pLabel->setColor(labelcolor);		
	}
	//接受
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
			menu_selector(VerifyItem::onYesBtnClick) );
		_btn->setPosition(ccp(POSX(795+offsetX), POSX(17)));
		_btn->setTag(0);
		_btn->setScale(0.7f);
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1-20000);
		this->addChild(buttonMenu, VerifyItemZ_btnyes, VerifyItemTAG_btnyes);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD092").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));
		pLabel->setScale(1.3f);
	}
	//拒绝
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
			menu_selector(VerifyItem::onNoBtnClick) );
		_btn->setPosition(ccp(POSX(880+offsetX), POSX(17)));
		_btn->setTag(0);
		_btn->setScale(0.7f);
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-1-20000);
		this->addChild(buttonMenu, VerifyItemZ_btnno, VerifyItemTAG_btnno);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD093").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
		pLabel->setScale(1.3f);
	}
}

/**
	* “通过”按钮 
	*/		
void VerifyItem::onYesBtnClick(CCObject* pSender)
{
	CCMD1BD obj;
	obj.a_pName = _applyVo.name;
	obj.b_result = 0;
	//在GuildView触发事件
	_guildDispatch->dispatchEvent(GuildEventConst::APPROVE_MEMBER, &obj);
}
		
/**
	* “拒绝”按钮 
	*/		
void VerifyItem::onNoBtnClick(CCObject* pSender)
{
	CCMD1BD obj;
	obj.a_pName = _applyVo.name;
	obj.b_result = 1;
	//在GuildView触发事件
	_guildDispatch->dispatchEvent(GuildEventConst::REFUSE_MEMBER, &obj);
	//在VerifyPanel触发事件

	//this.parent.parent.dispatchEvent(new ParamEvent(VerifyPanel.CHECK_REJECT, this));
}