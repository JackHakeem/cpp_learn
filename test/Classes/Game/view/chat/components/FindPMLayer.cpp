#include "FindPMLayer.h"
#include "utils/ValuesUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "CCUIBackground.h"

const float FontSize = 30.0f;

FindPMLayer::FindPMLayer()
{}

FindPMLayer::~FindPMLayer()
{}

//menu_selector(ChatPopContainer::onChannelChange) 
bool FindPMLayer::init()
{
	if (!LayerNode::init())
		return false;

	//
	CCUIBackground* _bg1 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_6.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		CCSizeMake(POSX(500),POSX(300)));
	this->addChild(_bg1, FindPMLayerZ_bg1, FindPMLayerTAG_bg1);
	_bg1->release();
	//
	CCUIBackground* _bg2 = new CCUIBackground();
	_bg1->initWithSpriteFrame("chat/chat_10.png", ccp(POSX(0), POSX(0)),ccp(0,0),
		CCSizeMake(POSX(400),POSX(200)));
	this->addChild(_bg1, FindPMLayerZ_bg1, FindPMLayerTAG_bg1);
	_bg1->release();


	return true;	
	//
	//this->setPosition(ccp(0, 0));
	////
	//{
	//	CCMenuItemImage *_btn = CCMenuItemImage::itemFromNormalImage(
	//		"assets/ui/chat/chat_5.png", 
	//		"assets/ui/chat/chat_5.png", 
	//		target0, 
	//		selector0);

	//	_btn->setPosition(ccp(POSX(96), POSX(40+56)));
	//	_btn->setTag(1);//设置TAG为1 方便回调函数操作
	//	CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
	//	buttonMenu->setPosition( CCPointZero );
	//	buttonMenu->setTouchLayer(TLE::TipsLayer_Alert-1);
	//	this->addChild(buttonMenu, 0, 0);
	//	//世界
	//	CCLabelTTF* label = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("CHT044").c_str(), 
	//		CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "hyzyj", POSX(FontSize));
	//	_btn->addChild(label, 0, 1);
	//	label->setColor(ccc3(255, 255, 255));
	//	label->setPosition(ccp(61, 26));
	//}
	////
	//{
	//	CCMenuItemImage *_btn = CCMenuItemImage::itemFromNormalImage(
	//		"assets/ui/chat/chat_5.png", 
	//		"assets/ui/chat/chat_5.png", 
	//		target1, 
	//		selector1);

	//	_btn->setPosition(ccp(POSX(96), POSX(40+56*2)));
	//	_btn->setTag(3);//设置TAG为2 方便回调函数操作
	//	CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
	//	buttonMenu->setPosition( CCPointZero );
	//	buttonMenu->setTouchLayer(TLE::TipsLayer_Alert-1);
	//	this->addChild(buttonMenu, 0, 1);
	//	//世界
	//	CCLabelTTF* label = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("CHT046").c_str(), 
	//		CCSizeMake(POSX(200), POSX(FontSize)), CCTextAlignmentCenter, "hyzyj", POSX(FontSize));
	//	_btn->addChild(label, 0, 1);
	//	label->setColor(ccc3(255, 255, 255));
	//	label->setPosition(ccp(61, 26));
	//}
	
}

