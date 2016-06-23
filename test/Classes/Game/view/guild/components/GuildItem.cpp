#include "GuildItem.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "model/player/RoleManage.h"
#include "GuildEventConst.h"
#include "GuildDispatcher.h"
#include "manager/TouchLayerEnum.h"
#include "../GuildListenerMediator.h"

const float w_frame = 863;
const float h_frame = 41.0f;
const float FontSize = 30.0f;
const float FontSize3 = 20.0f;
const float FontSize2 = 24.0f;

GuildItem::GuildItem()
{
	_applyText = 0;
	_btnApply = 0;
}

GuildItem::~GuildItem()
{}

bool GuildItem::init(GuildInfoVo guildVo)
{
	if (!LayerNode::init())
		return false;

	_guildVo = guildVo;

	initView();

	if (_guildVo.flag != 0)
	{
		if (!_applyText)
		{
			_applyText = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString("GLD1009").c_str(),
				CCSizeMake(POSX(100), POSX(FontSize3)),
				CCTextAlignmentCenter, "Arial", POSX(FontSize3));
			_applyText->setAnchorPoint(ccp(0, 0));
			_applyText->setPosition(ccp(POSX(675+36-48+10), POSX(15)));
			this->addChild(_applyText);
			_applyText->setColor(ccGRAY);	
		}
	}
	
	return true;
}

void GuildItem::initView()
{
	this->setContentSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));
	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		CCSizeMake(POSX(w_frame), POSX(h_frame-3)));
	this->addChild(_bg1, GuildItemZ_bg1, GuildItemTAG_bg1);
	_bg1->release();

	cocos2d::ccColor3B labelcolor = ccc3(233, 211, 24);
	//float offsetX = -300.0f;
	float fH = POSX(FontSize3+4);
	//����
	{
		char tmp[10];
		sprintf( tmp, "%d", _guildVo.rank );
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			tmp,
			CCSizeMake(POSX(100),
			fH),
			CCTextAlignmentCenter,
			"Arial",
			POSX(FontSize3)
			);
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(26+36-48), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}
	//����
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			_guildVo.name.c_str(),
			CCSizeMake(POSX(150),
			fH),
			CCTextAlignmentCenter,
			"Arial",
			POSX(FontSize3)
			);
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(177+36-48), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}
	//�᳤
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			_guildVo.leaderName.c_str(), 
			CCSizeMake(POSX(150), fH),
			CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(314+36-48), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}
	//�ȼ�
	{
		char tmp[30];
		sprintf(tmp, "%d", _guildVo.emblemGrade);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			tmp,
			CCSizeMake(POSX(100), fH),
			CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(442+36-48), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}
	//����
	{
		char tmp[30];
		sprintf(tmp, "%d/%d",  _guildVo.members, _guildVo.memberLimit);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(tmp,
			CCSizeMake(POSX(100), fH), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(592+36-48), POSX(15-4)));
		this->addChild(pLabel);
		pLabel->setColor(labelcolor);		
	}
	//����
	{
		if (_guildVo.flag == 0)
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
				menu_selector(GuildItem::onApplyBtnClick) );
			_btn->setPosition(ccp(POSX(675+41+36-48+20), POSX(20)));
			_btn->setTag(0);
			_btn->setScale(0.7f);
			_btnApply = CCMenu::menuWithItems(_btn, 0); 
			_btnApply->setPosition( CCPointZero );
			_btnApply->setTouchLayer(TLE::IntervalLayer_guild-1); 
			this->addChild(_btnApply);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString("GLD1000").c_str(),
				CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));
			pLabel->setScale(1.2f);
		}
	}
	//�鿴
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
			menu_selector(GuildItem::onExamineBtnClick) );
		_btn->setPosition(ccp(POSX(770+41+36-48+20), POSX(20)));
		_btn->setTag(0);
		_btn->setScale(0.7f);
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild-1);
		this->addChild(buttonMenu);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(
			ValuesUtil::Instance()->getString("GLD1001").c_str(),
			CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
		pLabel->setScale(1.2f);
	}
}

/**
* �����롱��ť 
*/		
void GuildItem::onApplyBtnClick(CCObject* obj)
{
	int roleLev = RoleManage::Instance()->roleLev();
	if(roleLev < 15)
	{
		//LangManager.alertShow("GLD035");
		LangManager::msgShow("GLD035");
		return;
	}
	GuildDispatcher::getInstance()->dispatchEvent(
		GuildEventConst::APPLY_GUILD, (char*)_guildVo.name.c_str() );
	//_btnApply->setIsVisible(false);
	canApply(false);
}

/**
* ���鿴����ť 
*/		
void GuildItem::onExamineBtnClick(CCObject* obj)
{
	GuildDispatcher::getInstance()->dispatchEvent(
		GuildEventConst::OPEN_GUILD_INFO_VIEW, (char*)&_guildVo );
}
		
/**
* ����Ѽ��빫�ᣬ�����ء����롱��ť 
*/		
void GuildItem::canApply( bool flag )
{
	if ( _btnApply )
	{
		_btnApply->setIsVisible(flag);
	}
	//_item["_txtApplied"].visible = flag;

	if (!flag)
	{
		if ( g_pGuildListenerMediator->_preView->gethasGuild() )
		{
			if (_applyText)
			{
				_applyText->setIsVisible(false);
			}
			
			return;
		}
		
		if (!_applyText)
		{
			_applyText = CCLabelTTF::labelWithString(
				ValuesUtil::Instance()->getString("GLD1009").c_str(),
				CCSizeMake(POSX(100), POSX(FontSize3)),
				CCTextAlignmentCenter, "Arial", POSX(FontSize3));
			_applyText->setAnchorPoint(ccp(0, 0));
			_applyText->setPosition(ccp(POSX(675+36-48+10), POSX(15)));
			this->addChild(_applyText);
			_applyText->setColor(ccGRAY);	
		}		
	}
}
