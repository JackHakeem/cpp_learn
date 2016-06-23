#include "AccountSettingLayer.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include "SettingView.h"
#include "utils/ValuesUtil.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "Connect91Handler.h"
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/slcq/JniManager.h"
//#include "Connect4399Handler.h"
#endif
const float FontSize = 36.f;

AccountSettingLayer::AccountSettingLayer()
{}

AccountSettingLayer::~AccountSettingLayer()
{}

//bool MainSettingLayer::initWithParam(CCObject* target, SEL_MenuHandler selectorAccount, SEL_MenuHandler selectorMusic)
bool AccountSettingLayer::init()
{
	if (!LayerNode::init())
		return false;

	this->setAnchorPoint(ccp(0, 0));

	//accountbtn
	{
		
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this, 
				menu_selector(AccountSettingLayer::center) );
			_btn->setPosition(ccp(POSX(0), POSX(0)));
			_btn->setScaleX(2.0f);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::WindowLayer_Setting-1);
			this->addChild(buttonMenu, AccountSettingLayerZ_centerBtn, AccountSettingLayerTAG_centerBtn);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("WLC006").c_str(), CCSizeMake(POSX(230), POSX(FontSize)),CCTextAlignmentLeft, "Arial", POSX(FontSize));
			if (pLabel)
			{
				pLabel->setPosition(ccp(POSX(70), POSX(25)));
				_btn->addChild(pLabel, 0, 1);
				pLabel->setColor(ccc3(254, 189, 0));	
				pLabel->setScaleX(0.5f);
			}
		}
		
	}

	return true;
}
 
void AccountSettingLayer::center(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    [Connect91Handler enterPlatform];
#endif
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    callOutOfGameForce();
#endif
}
