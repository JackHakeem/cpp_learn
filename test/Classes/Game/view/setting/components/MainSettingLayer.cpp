#include "MainSettingLayer.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "SettingView.h"
#include "utils/ValuesUtil.h"

const float FontSize = 36.f;

MainSettingLayer::MainSettingLayer()
{}

MainSettingLayer::~MainSettingLayer()
{}

bool MainSettingLayer::initWithParam(CCObject* target, SEL_MenuHandler selectorAccount, SEL_MenuHandler selectorMusic)
{
	if (!LayerNode::init())
		return false;

	this->setAnchorPoint(ccp(0, 0));

	//accountbtn
	{
		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("setting/main/5.png");
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("setting/main/5.png");
		CCMenuItemSprite *_btnAccount = CCMenuItemImage::itemFromNormalSprite(
			p1, 
			p2,
			target, 
			selectorAccount );
		_btnAccount->setPosition(ccp(POSX(-200), POSX(0)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnAccount, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Setting-1);
		this->addChild(buttonMenu, MainSettingLayerZ_accountBtn, MainSettingLayerTAG_accountBtn);	

		SpriteNode* bg = new SpriteNode();
		bg->initWithSpriteFrameName("setting/main/3.png");
		_btnAccount->addChild(bg);
		bg->setAnchorPoint(ccp(0, 0));
		bg->setPosition(ccp(0, 0));
		bg->release();

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SET001").c_str(), CCSizeMake(POSX(230), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
		if (pLabel)
		{
			pLabel->setPosition(ccp(POSX(115), POSX(-30)));
			_btnAccount->addChild(pLabel, 0, 1);
			pLabel->setColor(ccc3(254, 189, 0));		
		}

	}
	//musicbtn
	{
		CCSprite* p1 = CCSprite::spriteWithSpriteFrameName("setting/main/5.png");
		CCSprite* p2 = CCSprite::spriteWithSpriteFrameName("setting/main/5.png");
		CCMenuItemSprite *_btnMusic = CCMenuItemImage::itemFromNormalSprite(
			p1, 
			p2,
			target, 
			selectorMusic );
		_btnMusic->setPosition(ccp(POSX(200), POSX(0)));

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btnMusic, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::WindowLayer_Setting-1);
		this->addChild(buttonMenu, MainSettingLayerZ_musicBtn, MainSettingLayerTAG_musicBtn);	

		SpriteNode* bg = new SpriteNode();
		bg->initWithSpriteFrameName("setting/main/4.png");
		_btnMusic->addChild(bg);
		bg->setAnchorPoint(ccp(0, 0));
		bg->setPosition(ccp(0, 0));
		bg->release();

		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SET002").c_str(), CCSizeMake(POSX(230), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
		if (pLabel)
		{
			pLabel->setPosition(ccp(POSX(115), POSX(-30)));
			_btnMusic->addChild(pLabel, 0, 1);
			pLabel->setColor(ccc3(254, 189, 0));		
		}
	}
	return true;
}

