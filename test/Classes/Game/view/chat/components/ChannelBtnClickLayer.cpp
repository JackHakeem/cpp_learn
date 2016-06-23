#include "ChannelBtnClickLayer.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"

const float FontSize = 30.0f;

ChannelBtnClickLayer::ChannelBtnClickLayer()
{}

ChannelBtnClickLayer::~ChannelBtnClickLayer()
{}

//menu_selector(ChatPopContainer::onChannelChange) 
bool ChannelBtnClickLayer::initWithParam(
	CCObject* target0, SEL_MenuHandler selector0,
	CCObject* target1, SEL_MenuHandler selector1)
{
	if (!LayerNode::init())
		return false;
	//
	this->setPosition(ccp(0, 0));
	//
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_5.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_5.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			target0, 
			selector0);

		_btn->setPosition(ccp(POSX(126), POSX(40+56)));
		_btn->setTag(1);//设置TAG为1 方便回调函数操作
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_Alert-1);
		this->addChild(buttonMenu, 0, 0);
		//世界
		CCLabelTTF* label = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("CHT044").c_str(), 
			CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
		_btn->addChild(label, 0, 1);
		label->setColor(ccc3(255, 255, 255));
		label->setPosition(ccp(POSX(61), POSX(26)));
	}
	//CHT045
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_5.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_5.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			target0, 
			selector0);

		_btn->setPosition(ccp(POSX(106), POSX(40+56*2)));
		_btn->setTag(2);//设置TAG为1 方便回调函数操作
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_Alert-1);
		this->addChild(buttonMenu, 0, 0);
		//世界
		CCLabelTTF* label = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("CHT045").c_str(), 
			CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
		_btn->addChild(label, 0, 1);
		label->setColor(ccc3(255, 255, 255));
		label->setPosition(ccp(POSX(61), POSX(26)));
	}
	//
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_5.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("chat/chat_5.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			target1, 
			selector1);

		_btn->setPosition(ccp(POSX(86), POSX(40+56*3)));
		_btn->setTag(3);//设置TAG为2 方便回调函数操作
		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::TipsLayer_Alert-1);
		this->addChild(buttonMenu, 0, 1);
		//世界
		CCLabelTTF* label = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("CHT046").c_str(), 
			CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "Arial", POSX(FontSize));
		_btn->addChild(label, 0, 1);
		label->setColor(ccc3(255, 255, 255));
		label->setPosition(ccp(POSX(61), POSX(26)));
	}

	return true;
}

