#include "GuestRegisterView.h"

GuestRegisterView::GuestRegisterView()
{
	_pRegisterLayer = 0;
}


bool GuestRegisterView::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	/*
	if (!_pRegisterLayer)
	{
		_pRegisterLayer = new CCLayer();
		if(_pRegisterLayer && _pRegisterLayer->init())
		{
			_pRegisterLayer->setAnchorPoint(CCPointZero);
			_pRegisterLayer->setPosition(CCPointZero);
			_pRegisterLayer->setIsRelativeAnchorPoint(true);
			_pRegisterLayer->setTag(TAG_RegisterLayer);
			_pRegisterLayer->setIsVisible(false);
			this->addChild(_pRegisterLayer);
		}
	}

	if (_pRegisterLayer)
	{
		// Add frame background.
		CCSprite *pRegisterBackgroundSprite = CCSprite::spriteWithFile("assets/ui/login/bg_login_register.png");
		if(pRegisterBackgroundSprite)
		{
			pRegisterBackgroundSprite->setAnchorPoint(CCPointZero);
			pRegisterBackgroundSprite->setPosition(POS(ccp(POSX(92), POSX(80)), ScaleUtil::CENTER));
			_pRegisterLayer->addChild(pRegisterBackgroundSprite);
		}

		// Add text input components.
		// Add account.
		CCLabelTTF* pAccountLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG008").c_str(),
			CCSizeMake(POSX(160), POSX(30)), 
			CCTextAlignmentLeft, 
			"hyzyj", 
			POSX(30));
		pAccountLabel->setColor(ccc3(255, 215, 10));
		pAccountLabel->setAnchorPoint(CCPointZero);
		pAccountLabel->setIsRelativeAnchorPoint(true);
		pAccountLabel->setPosition( POS(ccp(144, 440), ScaleUtil::CENTER) );
		_pRegisterLayer->addChild(pAccountLabel);

		CCSprite *pAccountBackgroundSprite = CCSprite::spriteWithFile("assets/ui/login/login_input.png");
		if(pAccountBackgroundSprite)
		{
			pAccountBackgroundSprite->setAnchorPoint(CCPointZero);
			pAccountBackgroundSprite->setPosition(POS(ccp(284, 434), ScaleUtil::CENTER));
			_pRegisterLayer->addChild(pAccountBackgroundSprite);
		}

		CCTextFieldTTF *pAccountTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",
			CCSizeMake(POSX(380), POSX(40)),
			CCTextAlignmentLeft,
			"hyzyj",
			POSX(28));
		if(pAccountTextField)
		{
			pAccountTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
			pAccountTextField->setAnchorPoint(CCPointZero);
			pAccountTextField->setPosition(POS(ccp(286, 436), ScaleUtil::CENTER));
			//pAccountTextField->attachWithIME();
			pAccountTextField->setString("");
			pAccountTextField->setTag(TEXTFIELD_ACCOUNT);
			_pRegisterLayer->addChild(pAccountTextField);
		}

		// Add password.
		CCLabelTTF* pPasswdLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG009").c_str(),
			CCSizeMake(POSX(160), POSX(30)), 
			CCTextAlignmentLeft, 
			"hyzyj", 
			POSX(30));
		pPasswdLabel->setColor(ccc3(255, 215, 10));
		pPasswdLabel->setAnchorPoint(CCPointZero);
		pPasswdLabel->setIsRelativeAnchorPoint(true);
		pPasswdLabel->setPosition( POS(ccp(144, 340), ScaleUtil::CENTER) );
		_pRegisterLayer->addChild(pPasswdLabel);

		CCSprite *pPasswdBackgroundSprite = CCSprite::spriteWithFile("assets/ui/login/login_input.png");
		if(pPasswdBackgroundSprite)
		{
			pPasswdBackgroundSprite->setAnchorPoint(CCPointZero);
			pPasswdBackgroundSprite->setPosition(POS(ccp(284, 334), ScaleUtil::CENTER));
			_pRegisterLayer->addChild(pPasswdBackgroundSprite);
		}

		CCTextFieldTTF *pPasswdTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",
			CCSizeMake(POSX(380), POSX(40)),
			CCTextAlignmentLeft,
			"hyzyj",
			POSX(28));
		if(pPasswdTextField)
		{
			pPasswdTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
			pPasswdTextField->setAnchorPoint(CCPointZero);
			pPasswdTextField->setPosition(POS(ccp(286, 336), ScaleUtil::CENTER));
			//pPasswdTextField->attachWithIME();
			pPasswdTextField->setTag(TEXTFIELD_PASSWD);
			_pRegisterLayer->addChild(pPasswdTextField);
		}

		// Add confirm password.
		CCLabelTTF* pPasswdConfirmLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG010").c_str(),
			CCSizeMake(POSX(160), POSX(30)), 
			CCTextAlignmentLeft, 
			"hyzyj", 
			POSX(30));
		pPasswdConfirmLabel->setColor(ccc3(255, 215, 10));
		pPasswdConfirmLabel->setAnchorPoint(CCPointZero);
		pPasswdConfirmLabel->setIsRelativeAnchorPoint(true);
		pPasswdConfirmLabel->setPosition( POS(ccp(144, 250), ScaleUtil::CENTER) );
		_pRegisterLayer->addChild(pPasswdConfirmLabel);

		CCSprite *pPasswdConfirmBackgroundSprite = CCSprite::spriteWithFile("assets/ui/login/login_input.png");
		if(pPasswdConfirmBackgroundSprite)
		{
			pPasswdConfirmBackgroundSprite->setAnchorPoint(CCPointZero);
			pPasswdConfirmBackgroundSprite->setPosition(POS(ccp(284, 244), ScaleUtil::CENTER));
			_pRegisterLayer->addChild(pPasswdConfirmBackgroundSprite);
		}

		CCTextFieldTTF *pPasswdConfirmTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",
			CCSizeMake(POSX(380), POSX(40)),
			CCTextAlignmentLeft,
			"hyzyj",
			POSX(28));
		if(pPasswdConfirmTextField)
		{
			pPasswdConfirmTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
			pPasswdConfirmTextField->setAnchorPoint(CCPointZero);
			pPasswdConfirmTextField->setPosition(POS(ccp(286, 246), ScaleUtil::CENTER));
			//pPasswdTextField->attachWithIME();
			pPasswdConfirmTextField->setTag(TEXTFIELD_PASSWD);
			_pRegisterLayer->addChild(pPasswdConfirmTextField);
		}

		// Add register button.
		CCMenuItemImage *pRegMenuItem = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/button.png",
			"assets/ui/button1.png",
			this,
			menu_selector(LoginView::onRegisterMenuClick) );
		pRegMenuItem->setAnchorPoint(CCPointZero);
		pRegMenuItem->setScale(1.3f);
		pRegMenuItem->setPosition( POS(ccp(220, 100), ScaleUtil::CENTER) );
		CCMenu* pRegMenu = CCMenu::menuWithItems(pRegMenuItem, NULL);
		pRegMenu->setPosition( CCPointZero );
		_pRegisterLayer->addChild(pRegMenu);

		CCLabelTTF* pTitleLabelReg = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG014").c_str(),
			CCSizeMake(POSX(168), POSX(32)), 
			CCTextAlignmentLeft, 
			"hyzyj", 
			POSX(32));
		pTitleLabelReg->setColor(ccc3(255, 255, 0));
		pTitleLabelReg->setAnchorPoint(CCPointZero);
		pTitleLabelReg->setIsRelativeAnchorPoint(true);
		pTitleLabelReg->setPosition( POS(ccp(254, 114), ScaleUtil::CENTER) );
		_pRegisterLayer->addChild(pTitleLabelReg);

		// Add go back button.
		CCMenuItemImage *pServMenuItem = CCMenuItemImage::itemFromNormalImage(
			"assets/ui/button.png",
			"assets/ui/button1.png",
			this,
			menu_selector(LoginView::onBackMenuClick) );
		pServMenuItem->setAnchorPoint(CCPointZero);
		pServMenuItem->setScale(1.3f);
		pServMenuItem->setPosition( POS(ccp(596, 100), ScaleUtil::CENTER) );
		CCMenu* pServMenu = CCMenu::menuWithItems(pServMenuItem, NULL);
		pServMenu->setPosition( CCPointZero );
		_pRegisterLayer->addChild(pServMenu);

		CCLabelTTF* pTitleLabelServ = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG015").c_str(),
			CCSizeMake(POSX(128), POSX(32)), 
			CCTextAlignmentLeft, 
			"hyzyj", 
			POSX(32));
		pTitleLabelServ->setColor(ccc3(255, 255, 0));
		pTitleLabelServ->setAnchorPoint(CCPointZero);
		pTitleLabelServ->setIsRelativeAnchorPoint(true);
		pTitleLabelServ->setPosition( POS(ccp(630, 114), ScaleUtil::CENTER) );
		_pRegisterLayer->addChild(pTitleLabelServ);
	}
	*/

	return true;
}
