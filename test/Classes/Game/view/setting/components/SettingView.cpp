#include "SettingView.h"
#include "manager/PopEventName.h"

#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "manager/layer/WindowLayer.h"
#include "manager/LayerManager.h"
#include "manager/TouchLayerEnum.h"
#include "manager/LangManager.h"
#include "MainSettingLayer.h"
#include "AccountSettingLayer.h"
#include "SoundSetLayer.h"
#include "manager/sound/SoundManager.h"
#include "LoginManage.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/slcq/JniManager.h"
#endif
#include "manager/ViewManager.h"

SettingView::SettingView()
{
}
/*
	enum
	{
		SettingViewZ_main,
		SettingViewZ_account,
		SettingViewZ_music,
	};

	enum
	{
		SettingViewTAG_main,
		SettingViewTAG_account,
		SettingViewTAG_music,
	};
*/
bool SettingView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	//��ʼ��key
	key = PopEventName::SETTING;	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/setting/res_setting.plist");

	this->setAnchorPoint(ccp(0, 0));

	//mainSetting
	MainSettingLayer* mainSetting = new MainSettingLayer();
	mainSetting->initWithParam(this, menu_selector(SettingView::clickAccount), menu_selector(SettingView::clickMusic));
	this->addChild(mainSetting, SettingViewZ_main, SettingViewTAG_main);
	mainSetting->release();
	//accountSetting
	AccountSettingLayer* accountSetting = new AccountSettingLayer();
	accountSetting->init();
	this->addChild(accountSetting, SettingViewZ_account, SettingViewTAG_account);	
	accountSetting->setIsVisible(false);
	accountSetting->release();
	//soundSetting
	SoundSetLayer* pSoundSetLayer = new SoundSetLayer();
	pSoundSetLayer->init();
	this->addChild(pSoundSetLayer, SettingViewZ_music, SettingViewTAG_music);	
	pSoundSetLayer->setIsVisible(false);
	pSoundSetLayer->release();
	
	//title
	SpriteNode* title = new SpriteNode();
	title->initWithSpriteFrameName("setting/title.png");
	title->setPosition(ccp(0, 240));
	this->addChild(title);
	title->release();

	return true;
}

void SettingView::clickAccount(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (g_pLoginManage->getIs91Platform()) 
    {
        MainSettingLayer* mainSetting = (MainSettingLayer*)this->getChildByTag(SettingViewTAG_main);
        if (mainSetting)
            mainSetting->setIsVisible(false);
        
        AccountSettingLayer* accountSetting = (AccountSettingLayer*)this->getChildByTag(SettingViewTAG_account);
        if (accountSetting)
            accountSetting->setIsVisible(true);
        
        SoundManager::Instance()->playButtonEffectSound();
    }
    else
    {
        
    }
    
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
    callEnterGamecenter();
#endif

}

void SettingView::clickMusic(CCObject* pSender)
{
	MainSettingLayer* mainSetting = (MainSettingLayer*)this->getChildByTag(SettingViewTAG_main);
	if (mainSetting)
		mainSetting->setIsVisible(false);
	SoundSetLayer * pSoundSetLayer = (SoundSetLayer *)this->getChildByTag(SettingViewTAG_music);
	if (pSoundSetLayer)
	{
		pSoundSetLayer->setIsVisible(true);
		pSoundSetLayer->setIsTouchEnabled(true);
	}

	SoundManager::Instance()->playButtonEffectSound();
}

void SettingView::clickCloseHandler(CCObject* pSender)
{
	//MainSettingLayer* mainSetting = (MainSettingLayer*)this->getChildByTag(SettingViewTAG_main);
	//if (mainSetting)
	//	mainSetting->setIsVisible(true);

	//AccountSettingLayer* accountSetting = (AccountSettingLayer*)this->getChildByTag(SettingViewTAG_account);
	//if (accountSetting)
	//	accountSetting->setIsVisible(false);
	//SoundSetLayer * pSoundSetLayer = (SoundSetLayer *)this->getChildByTag(SettingViewTAG_music);
	//if (pSoundSetLayer)
	//{
	//	pSoundSetLayer->setIsVisible(false);
	//}

	PopContainer::clickCloseHandler(pSender);
}

SettingView::~SettingView()
{
	ViewManager::getInstance()->_settingView = 0;
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/setting/res_setting.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/setting/res_setting.pvr.ccz");
}
