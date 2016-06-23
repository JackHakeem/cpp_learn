#include "EndBtnTips.h"
#include "CCUIBackground.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "manager/CDManage.h"
#include "manager/TimerManage.h"
#include "LoginManage.h"

#include "manager/LayerManager.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#import "Connect91Handler.h"
#endif


#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/slcq/JniManager.h"
#endif

const float FontSize2 = 20.0f;

EndBtnTips::EndBtnTips()
{
}

EndBtnTips::~EndBtnTips()
{

}

void EndBtnTips::close(CCObject* pSender)
{
	EndBtnTips* oldp = (EndBtnTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_EndBtnTips);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}

void EndBtnTips::confirm(CCObject* pSender)
{
	#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		callExcharge("1000", g_pLoginManage->getExchargeServerId().c_str());
	#endif

	#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
		[[Connect91Handler sharedTo91] buyGold:1000];
	#endif

	EndBtnTips* oldp = (EndBtnTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_EndBtnTips);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}

}

void EndBtnTips::cancel(CCObject* pSender)
{
	EndBtnTips* oldp = (EndBtnTips*)LayerManager::intervalLayer->getChildByTag(IntervalLayer::IntervalLayerTAG_EndBtnTips);
	if (oldp)
	{
		oldp->removeFromParentAndCleanup(true);
	}
}

bool EndBtnTips::init()
{
	if (!LayerNode::init())
		return false;

	//m_bg1
	{
		CCUIBackground* _bg1 = new CCUIBackground();
		_bg1->initWithSpriteFrame("guild/select.png", ccp(POSX(240), POSX(640-500)),ccp(6,7),
			CCSizeMake(POSX(960-240*2), POSX(500-70)));
		this->addChild(_bg1, 0);
		_bg1->release();
	}
	//
	CCLayerColor* blackBG = cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,100));
	this->addChild(blackBG, -1);
	blackBG->setPosition(ccp(0, 0));
	//close
	{
		CCSprite *pCloseNormalSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_normal.png");
		CCSprite *pClosePressedSprite = CCSprite::spriteWithSpriteFrameName("popuibg/btn_close_pressed.png");
		CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
			pCloseNormalSprite,
			pClosePressedSprite,
			this, 
			menu_selector(EndBtnTips::close) );
		_btn->setPosition(ccp(POSX(960-240), POSX(570)));
		_btn->setTag(0);

		CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
		buttonMenu->setPosition( CCPointZero );
		buttonMenu->setTouchLayer(TLE::IntervalLayer_endBtnTips);
		this->addChild(buttonMenu);	
	}
	//confirm
	
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this, 
				menu_selector(EndBtnTips::confirm) );
			_btn->setPosition(ccp(POSX(480-140), POSX(640-420)));
			_btn->setTag(0);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::IntervalLayer_endBtnTips);
			this->addChild(buttonMenu, 2);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM075").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));	
		}
	}
	//cancel
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *_btn = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite, 
				this, 
				menu_selector(EndBtnTips::cancel) );
			_btn->setPosition(ccp(POSX(480+140), POSX(640-420)));
			_btn->setTag(0);

			CCMenu *buttonMenu = CCMenu::menuWithItems(_btn, 0); 
			buttonMenu->setPosition( CCPointZero );
			buttonMenu->setTouchLayer(TLE::IntervalLayer_endBtnTips);
			this->addChild(buttonMenu, 2);	

			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM076").c_str(), CCSizeMake(POSX(200), POSX(FontSize2)), CCTextAlignmentCenter, "Arial", POSX(FontSize2));
			pLabel->setPosition(ccp(_btn->getContentSize().width/2, _btn->getContentSize().height/2+2.0f));
			_btn->addChild(pLabel, 0, 0);
			pLabel->setColor(ccc3(255, 209, 153));	
		}
	}
	

	////
	//{
	//	CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("SLM065").c_str(), CCSizeMake(POSX(400), POSX(40.0f)), CCTextAlignmentCenter, "Arial", POSX(40.0f));
	//	_txt->setPosition(ccp(POSX(960/2), POSX(500)));
	//	this->addChild(_txt, 2);
	//	_txt->setColor(ccc3(240, 210, 68));	
	//}
	//
	{
		CCLabelTTF* _txt = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("FT013").c_str(), CCSizeMake(POSX(400), POSX(24.0f*3)), CCTextAlignmentCenter, "Arial", POSX(24.0f));
		_txt->setPosition(ccp(POSX(960/2), POSX(400)));
		this->addChild(_txt, 2);
		_txt->setColor(ccc3(240, 210, 68));	
	}
	

	return true;
}
