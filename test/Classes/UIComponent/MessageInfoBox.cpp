#include "MessageInfoBox.h"
#include "BaseType.h"
#include "CCUIBackground.h"
#include "utils/ValuesUtil.h"
#include "manager/LayerManager.h"
#include "utils/ScaleUtil.h"
#include "manager/layer/SceneUILayer.h"
#include "manager/TouchLayerEnum.h"
#include "manager/GlobalManage.h"
#include "view/scene/components/LoginScene.h"
#include "view/login/components/LoginView.h"
#include "LoginManage.h"

MessageInfoBox::MessageInfoBox()
{
	if (!init())	{return;}
	m_pri = -2000;
	_pBack = 0;
	_pBtnMenu = 0;
	_pBtnText = 0;
	winSize = CCDirector::sharedDirector()->getWinSize();
	this->setIsTouchEnabled(true);
}

bool MessageInfoBox::init()
{
	if (!CCLayer::init())
	{
		return false;
	}
	return true;
}

void MessageInfoBox::addBackGround()
{
	_pBack = new CCUIBackground();
	_pBack->initWithSpriteFrame("ui.png",ccp(POSX(0),POSX(0)),ccp(POSX(0),POSX(0)),CCSizeMake(POSX(300),POSX(160)));
	/*CCSize sz = _pBack->getContentSize();
	_pBack->setPosition(ccp(winSize.width/2,winSize.height/2));
	_pBack->setAnchorPoint(ccp(0.5, 0.5));*/
	_pBack->setPosition(CCPointZero);
	_pBack->setAnchorPoint(CCPointZero);
	_pBack->setIsTouchEnabled(true);
	this->addChild(_pBack);
	_pBack->release();
}

void MessageInfoBox::addContent()
{
	CCLabelTTF * _pContent = CCLabelTTF::labelWithString(_content.c_str(),CCSizeMake(POSX(280), POSX(120)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(24));
	CCSize sz = _pBack->getContentSize();
	_pContent->setPosition(ccp(sz.width/2,sz.height/2+ POSX(30)));
	_pContent->setColor(_ccc3);
	_pBack->addChild(_pContent);
}

void MessageInfoBox::addButton(std::string btnText,SEL_MenuHandler selector)
{
	SEL_MenuHandler pSelector = (selector == 0) ? (menu_selector(MessageInfoBox::clickClose)) : (selector);


	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(!pNormalSprite || !pPressedSprite)
	{
		return;
	}
	CCMenuItemSprite *_pMenuImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite,
		this, 
		pSelector);

	_pBtnMenu = CCMenu::menuWithItem(_pMenuImg);
	_pBtnMenu->setContentSize(_pMenuImg->getContentSize());
	//_pBtnMenu->setTouchLayer(m_pri - 1);
	CCSize sz = _pBack->getContentSize();
	_pBtnMenu->setScale(1.0);
	_pBtnMenu->setTouchLayer(TLE::TipsLayer *2);
	_pBtnMenu->setPosition(ccp(sz.width/2,sz.height/5+ POSX(5)));

	std::string srtButtonText = (btnText == "") ? (ValuesUtil::Instance()->getString("OKC")) : (btnText);
	_pBtnText = CCLabelTTF::labelWithString(srtButtonText.c_str(),CCSizeMake(POSX(120), POSX(30)),CCTextAlignmentCenter,g_sSimHeiFont, POSX(26));
	_pBtnText->setPosition(_pBtnMenu->getPosition());
	_pBtnText->setColor(ccc3(255,215,0));

	_pBack->addChild(_pBtnMenu,Z_BTN+10,TAG_BTN);
	_pBack->addChild(_pBtnText,Z_TXT+11,TAG_TXT);
}

void MessageInfoBox::clickClose(CCObject * pSender)
{
	this->removeAllChildrenWithCleanup(true);
	if (this->getParent())
	{
		this->getParent()->removeChild(this,true);
	}
}

void MessageInfoBox::show(std::string content,ccColor3B ccc3,SEL_MenuHandler selector,std::string btnText)
{
// 	if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
// 	{
// 		return;
// 	}
	this->removeAllChildrenWithCleanup(true);
	if (this->getParent())
	{
		this->removeFromParentAndCleanup(true);
	}
	_content = content;
	_ccc3 = ccc3;
	addBackGround();
	addContent();
	addButton(btnText,selector);

	this->setContentSize(_pBack->getContentSize());
	this->setAnchorPoint(ccp(0.5, 0.5));
	this->setIsRelativeAnchorPoint(true);
	this->setPosition(ccp(winSize.width / 2,
		winSize.height /2) );

	if (g_pGlobalManage->getIsInGame())
	{
		/*
		if (LayerManager::windowLayer)
		{
			if (LayerManager::windowLayer->getChildByTag(WindowLayer::WindowLayerTAG_confirmFrame))
			{
				LayerManager::windowLayer->removeChildByTag(WindowLayer::WindowLayerTAG_confirmFrame,true);
			}
			LayerManager::windowLayer->addChild(this,WindowLayer::WindowLayerZ_confirmFrame,WindowLayer::WindowLayerTAG_confirmFrame);
		}
		*/
		if (LayerManager::tipsLayer)
		{
			if (LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerZ_msgInfoBox))
			{
				LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerZ_msgInfoBox,true);
			}
			LayerManager::tipsLayer->addChild(this,TipsLayer::TipsLayerZ_msgInfoBox,TipsLayer::TipsLayerTAG_msgInfoBox);
		}
	}
	else
	{
		LoginView * pLoginView = g_pLoginManage->_pLoginView;
		if (pLoginView)
		{
			pLoginView->addChild(this,1001,1001);
		}		
	}
}