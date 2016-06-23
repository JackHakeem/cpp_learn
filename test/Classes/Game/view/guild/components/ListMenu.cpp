#include "ListMenu.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include <cmath>
#include "manager/LayerManager.h"
#include "MemberPanel.h"

const float FontSize2 = 20.0f;

ListMenu::ListMenu()
{
	m_ptarget = 0;
}

ListMenu::~ListMenu()
{}

bool ListMenu::init(CCObject* target)
{
	if (!LayerNode::init())
		return false;

	m_ptarget = target;

	m_btns.clear();
	
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,150));
	this->addChild(blackBG, -1);
	//
	m_buttonMenu = new CCMenu();
	m_buttonMenu->init();
	m_buttonMenu->setTouchLayer(TLE::IntervalLayer_guild);
	this->addChild(m_buttonMenu, 1);
	m_buttonMenu->release();
	m_buttonMenu->setPosition(CCPointZero);
	//
	//X
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btnX = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(ListMenu::dispear) );
		_btnX->setPosition(ccp(POSX(590), POSX(640-100)));


		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnX, NULL);
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_guild);
		this->addChild(buttonMenu, 1);
	}

	addBtn(menu_selector(MemberPanel::onFuncClick), MemberPanel::ListMenu_ShiftLeader, ValuesUtil::Instance()->getString("GLD057").c_str());
	addBtn(menu_selector(MemberPanel::onFuncClick), MemberPanel::ListMenu_ViceLeader, ValuesUtil::Instance()->getString("GLD039").c_str());
	addBtn(menu_selector(MemberPanel::onFuncClick), MemberPanel::ListMenu_Officer, ValuesUtil::Instance()->getString("GLD058").c_str());
	addBtn(menu_selector(MemberPanel::onFuncClick), MemberPanel::ListMenu_Member, ValuesUtil::Instance()->getString("GLD059").c_str());
	addBtn(menu_selector(MemberPanel::onFuncClick), MemberPanel::ListMenu_ExpelledMember, ValuesUtil::Instance()->getString("GLD060").c_str());

	paiban(0);
	return true;
}

void ListMenu::addBtn(SEL_MenuHandler selector, int tag, const char* label)
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
		m_ptarget, 
		selector);
	_btn->setTag(tag);

	m_buttonMenu->addChild(_btn, 1);

	CCLabelTTF* pLabel = CCLabelTTF::labelWithString(label, CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
	pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
	_btn->addChild(pLabel, 0, 0);
	pLabel->setColor(ccc3(255, 209, 153));	

	m_btns.push_back(_btn);
}

void ListMenu::paiban(int type)
{
	float btnInterval = POSX(60.0f);
	int count = m_btns.size();
	if (count<=0)return;
	if (type == 0)
	{
		float heightBtns = count*btnInterval;
		float x = POSX(960/2);
		float y = (POSX(640)-heightBtns)/2+heightBtns;
		for (int i = 0; i < count; i++)
		{
			CCMenuItemSprite* btn = m_btns[i];
			if (btn)
				btn->setPosition(ccp(x, y-i*btnInterval));
		}
		//bg1
		CCUIBackground* _bg1 = new CCUIBackground();
		_bg1->initWithSpriteFrame("guild/select.png", ccp(POSX(960/2-104/2-22), (POSX(640)-heightBtns)/2+6),ccp(6,7),
			CCSizeMake(POSX(150), heightBtns+40));
		this->addChild(_bg1, 0);
		_bg1->release();
	}


}

void ListMenu::dispear(CCObject* pSender)
{
	//删除成员查看列表
	ListMenu* oldp = (ListMenu*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_guild_memberListMenu);
	if (oldp)
		LayerManager::intervalLayer->removeChildByTag(IntervalLayer::IntervalLayerTAG_guild_memberListMenu, true);
}

/**
	* 禁用所有菜单条目 
	* @param value 是否禁用（false为禁用，true为启用）
	*/		
void ListMenu::itemEnableAll(bool value)
{
	if (!value)
	for (int i = 0; i < m_btns.size(); i++)
	{
		CCMenuItemSprite* btn = m_btns[i];
		if (btn)
			btn->setIsEnabled(false);
	}
}