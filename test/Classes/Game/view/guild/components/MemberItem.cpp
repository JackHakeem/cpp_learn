#include "MemberItem.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "model/player/RoleManage.h"
#include "manager/LayerManager.h"
#include "manager/ViewManager.h"
#include "GuildTabPanel.h"
#include "manager/TouchLayerEnum.h"

const float w_frame = 915-345;
const float h_frame = 40.0f;
const float FontSize = 30.0f;
const float FontSize3 = 20.0f;
const float FontSize2 = 20.0f;

MemberItem::MemberItem()
{}

MemberItem::~MemberItem()
{}

bool MemberItem::init(MemberVo memberVo, int tag)
{
	if (!LayerNode::init())
		return false;

	_memberVo = memberVo;

	initView(tag);
	return true;
}



void MemberItem::initView(int tag)
{
	this->setContentSize(CCSizeMake(POSX(w_frame), POSX(h_frame)));
	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_7.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		CCSizeMake(POSX(w_frame), POSX(h_frame-3)));
	this->addChild(_bg1, MemberItemZ_bg1, MemberItemTAG_bg1);
	_bg1->release();

	cocos2d::ccColor3B labelcolor = ccc3(233, 211, 24);
	//ְλ
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(_memberVo.duty.c_str(), CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(0), POSX(10)));
		this->addChild(pLabel, MemberItemZ_txtClass, MemberItemTAG_txtClass);
		pLabel->setColor(labelcolor);		
	}
	//����
	{
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(_memberVo.name.c_str(), CCSizeMake(POSX(160), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(50), POSX(10)));
		this->addChild(pLabel, MemberItemZ_txtID, MemberItemTAG_txtID);
		pLabel->setColor(labelcolor);		
	}
	//�ȼ�
	{
		char value[30];
		sprintf(value, "%d", _memberVo.level);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(value, CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(180), POSX(10)));
		this->addChild(pLabel, MemberItemZ_txtCon, MemberItemTAG_txtCon);
		pLabel->setColor(labelcolor);		
	}
	//���׶�
	{
		char value[30];
		sprintf(value, "%d", _memberVo.contribution);
		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(value, CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(270), POSX(10)));
		this->addChild(pLabel, MemberItemZ_txtCon, MemberItemTAG_txtCon);
		pLabel->setColor(labelcolor);		
	}
	////�ƺ�
	//{
	//	char value[30];
	//	sprintf(value, "%d", _memberVo.contribution);
	//	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(value, CCSizeMake(POSX(100), POSX(FontSize3)), CCTextAlignmentLeft, "Arial", POSX(FontSize3));
	//	pLabel->setAnchorPoint(ccp(0, 0));
	//	pLabel->setPosition(ccp(POSX(300), POSX(15)));
	//	this->addChild(pLabel, MemberItemZ_txtCon, MemberItemTAG_txtCon);
	//	pLabel->setColor(ccc3(255, 255, 255));		
	//}
	//״̬
	{
		char value[50];


		//���ߡ�����״̬
		cocos2d::ccColor3B color;
		
		if(_memberVo.state == "-1")//��Ա����
		{			
			if(_memberVo.id == RoleManage::Instance()->_accountInfo.accountId)
				color = ccc3(217, 58, 255);
			else 
				color = ccc3(0, 255, 0);
			if(_memberVo.duty == ValuesUtil::Instance()->getString("GLD038"))
				sprintf(value, ValuesUtil::Instance()->getString("GLD049").c_str(), "*");
			else 
				sprintf(value, ValuesUtil::Instance()->getString("GLD049").c_str(),"");
		}
		else if(_memberVo.state == "0")
		{	//��Ա������
			sprintf(value, ValuesUtil::Instance()->getString("GLD050").c_str());
			color = ccc3(126, 109, 79);
		}
		else
		{
			sprintf(value, ValuesUtil::Instance()->getString("GLD050").c_str());
			//sprintf(value, ValuesUtil::Instance()->getString("GLD051").c_str(), _memberVo.state.c_str());
			color = ccc3(126, 109, 79);
		}

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(value, CCSizeMake(POSX(150), POSX(FontSize3)), CCTextAlignmentCenter, "Arial", POSX(FontSize3));
		pLabel->setAnchorPoint(ccp(0, 0));
		pLabel->setPosition(ccp(POSX(360), POSX(10)));
		this->addChild(pLabel, MemberItemZ_txtLine, MemberItemTAG_txtLine);
		pLabel->setColor(color);		
	}
	//����ť
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
			getMemberPanel(), 
			menu_selector(MemberPanel::onListItemClick) );
		_btn->setPosition(ccp(POSX(530), POSX(17)));
		_btn->setTag(tag);
		_btn->setScale(0.7f);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_guild-10);//TLE::WindowLayer_guild-10);
		this->addChild(buttonMenu, MemberItemZ_btn, MemberItemTAG_btn);	

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("GLD101").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
		pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
		_btn->addChild(pLabel, 0, 0);
		pLabel->setColor(ccc3(255, 209, 153));	
		pLabel->setScale(1.3f);
	}
}

MemberPanel* MemberItem::getMemberPanel()
{
	GuildTabPanel* pGTP = (GuildTabPanel*)ViewManager::getInstance()->guildView->_container->getChildByTag(GuildView::GuildViewTAG_tabPanel);
	if (pGTP)
	{
		MemberPanel* rnt = pGTP->_memberPanel;
		return rnt;
	}
	return 0;
}
