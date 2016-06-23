//#include "Poco/Platform_WIN32.h"
//#include "Poco/Net/NetException.h"
//#include "Poco/Net/HTTPSession.h"
//#include "Poco/Net/HTTPClientSession.h"
//#include "Poco/Net/HTTPRequest.h"
//#include "Poco/Net/HTTPResponse.h"
//#include "Poco/Net/HTTPMessage.h"
#include "LoginRegister.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "LoginView.h"
#include "LoginMain.h"
#include "manager/LayerManager.h"
#include "manager/sound/SoundManager.h"

//using Poco::Net::ConnectionRefusedException;
//using Poco::Timespan;
//using Poco::Net::HTTPSession;
//using Poco::Net::HTTPClientSession;
//using Poco::Net::HTTPRequest;
//using Poco::Net::HTTPResponse;
using namespace cocos2d;

LoginRegister::LoginRegister()
{

}

bool LoginRegister::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	loadItems();

	return true;
}

void LoginRegister::loadItems()
{
	this->setAnchorPoint(CCPointZero);
	this->setIsRelativeAnchorPoint(true);

	// Add frame background.
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_register.plist");
	CCSprite *pRegisterBackgroundSprite = new CCSprite;
	if(pRegisterBackgroundSprite && pRegisterBackgroundSprite->initWithSpriteFrameName("login/bg_login_register.png"))
	{
		pRegisterBackgroundSprite->setAnchorPoint(CCPointZero);
		pRegisterBackgroundSprite->setPosition(POS(ccp(92, 80), ScaleUtil::CENTER));
		pRegisterBackgroundSprite->setOpacity(225);
		this->addChild(pRegisterBackgroundSprite);
		pRegisterBackgroundSprite->setTag(Tag_Bg);
		pRegisterBackgroundSprite->release();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_register.plist");
	}
	// Add text input components.
	// Add account.

	CCLabelTTF* pAccountLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG008").c_str(),
		CCSizeMake(POSX(160), POSX(30)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(30));
	pAccountLabel->setColor(ccc3(255, 215, 10));
	pAccountLabel->setAnchorPoint(CCPointZero);
	pAccountLabel->setIsRelativeAnchorPoint(true);
	pAccountLabel->setPosition( POS(ccp(144, 440), ScaleUtil::CENTER) );
	this->addChild(pAccountLabel);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_input.plist");
	CCSprite *pAccountBackgroundSprite = new CCSprite;
	if(pAccountBackgroundSprite && pAccountBackgroundSprite->initWithSpriteFrameName("login/login_input.png"))
	{
		pAccountBackgroundSprite->setAnchorPoint(CCPointZero);
		pAccountBackgroundSprite->setPosition(POS(ccp(284, 434), ScaleUtil::CENTER));
		this->addChild(pAccountBackgroundSprite);
		pAccountBackgroundSprite->setTag(Tag_Account_Bg);
		pAccountBackgroundSprite->release();
	}

	CCTextFieldTTF *pAccountTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",
		CCSizeMake(POSX(380), POSX(40)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	if(pAccountTextField)
	{
		pAccountTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
		pAccountTextField->setAnchorPoint(CCPointZero);
		pAccountTextField->setPosition(POS(ccp(286, 436), ScaleUtil::CENTER));
		//pAccountTextField->attachWithIME();
		pAccountTextField->setString("");
		pAccountTextField->setTag(LoginView::TEXTFIELD_ACCOUNT);
		this->addChild(pAccountTextField);
	}

	// Add password.
	CCLabelTTF* pPasswdLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG009").c_str(),
		CCSizeMake(POSX(160), POSX(30)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(30));
	pPasswdLabel->setColor(ccc3(255, 215, 10));
	pPasswdLabel->setAnchorPoint(CCPointZero);
	pPasswdLabel->setIsRelativeAnchorPoint(true);
	pPasswdLabel->setPosition( POS(ccp(144, 340), ScaleUtil::CENTER) );
	this->addChild(pPasswdLabel);

	CCSprite *pPasswdBackgroundSprite = CCSprite::spriteWithSpriteFrameName("login/login_input.png");
	if(pPasswdBackgroundSprite)
	{
		pPasswdBackgroundSprite->setAnchorPoint(CCPointZero);
		pPasswdBackgroundSprite->setPosition(POS(ccp(284, 334), ScaleUtil::CENTER));
		this->addChild(pPasswdBackgroundSprite);
	}

	CCTextFieldTTF *pPasswdTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",
		CCSizeMake(POSX(380), POSX(40)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	if(pPasswdTextField)
	{
		pPasswdTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
		pPasswdTextField->setAnchorPoint(CCPointZero);
		pPasswdTextField->setPosition(POS(ccp(286, 336), ScaleUtil::CENTER));
		//pPasswdTextField->attachWithIME();
		pPasswdTextField->setTag(LoginView::TEXTFIELD_PASSWD);
		this->addChild(pPasswdTextField);
	}

	// Add confirm password.
	CCLabelTTF* pPasswdConfirmLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG010").c_str(),
		CCSizeMake(POSX(160), POSX(30)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(30));
	pPasswdConfirmLabel->setColor(ccc3(255, 215, 10));
	pPasswdConfirmLabel->setAnchorPoint(CCPointZero);
	pPasswdConfirmLabel->setIsRelativeAnchorPoint(true);
	pPasswdConfirmLabel->setPosition( POS(ccp(144, 250), ScaleUtil::CENTER) );
	this->addChild(pPasswdConfirmLabel);

	CCSprite *pPasswdConfirmBackgroundSprite = CCSprite::spriteWithSpriteFrameName("login/login_input.png");
	if(pPasswdConfirmBackgroundSprite)
	{
		pPasswdConfirmBackgroundSprite->setAnchorPoint(CCPointZero);
		pPasswdConfirmBackgroundSprite->setPosition(POS(ccp(284, 244), ScaleUtil::CENTER));
		this->addChild(pPasswdConfirmBackgroundSprite);
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_input.plist");

	CCTextFieldTTF *pPasswdConfirmTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",
		CCSizeMake(POSX(380), POSX(40)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	if(pPasswdConfirmTextField)
	{
		pPasswdConfirmTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
		pPasswdConfirmTextField->setAnchorPoint(CCPointZero);
		pPasswdConfirmTextField->setPosition(POS(ccp(286, 246), ScaleUtil::CENTER));
		//pPasswdTextField->attachWithIME();
		pPasswdConfirmTextField->setTag(LoginView::TEXTFIELD_PASSWD_CONFIRM);
		this->addChild(pPasswdConfirmTextField);
	}

	// Add register button.

	
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pRegMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(LoginRegister::onRegisterConfirmMenuClick) );
			pRegMenuItem->setAnchorPoint(CCPointZero);
			pRegMenuItem->setScale(1.3f);
			pRegMenuItem->setPosition( POS(ccp(220, 100), ScaleUtil::CENTER) );
			CCMenu* pRegMenu = CCMenu::menuWithItems(pRegMenuItem, NULL);
			pRegMenu->setPosition( CCPointZero );
			this->addChild(pRegMenu);
		}
	}
	

	CCLabelTTF* pTitleLabelReg = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG014").c_str(),
		CCSizeMake(POSX(168), POSX(32)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(32));
	pTitleLabelReg->setColor(ccc3(255, 255, 0));
	pTitleLabelReg->setAnchorPoint(CCPointZero);
	pTitleLabelReg->setIsRelativeAnchorPoint(true);
	pTitleLabelReg->setPosition( POS(ccp(254, 114), ScaleUtil::CENTER) );
	this->addChild(pTitleLabelReg);

	// Add go back button.
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pServMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(LoginRegister::onBackMenuClick) );
			pServMenuItem->setAnchorPoint(CCPointZero);
			pServMenuItem->setScale(1.3f);
			pServMenuItem->setPosition( POS(ccp(596, 100), ScaleUtil::CENTER) );
			CCMenu* pServMenu = CCMenu::menuWithItems(pServMenuItem, NULL);
			pServMenu->setPosition( CCPointZero );
			this->addChild(pServMenu);
		}
	}



	


	CCLabelTTF* pTitleLabelServ = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG015").c_str(),
		CCSizeMake(POSX(128), POSX(32)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(32));
	pTitleLabelServ->setColor(ccc3(255, 255, 0));
	pTitleLabelServ->setAnchorPoint(CCPointZero);
	pTitleLabelServ->setIsRelativeAnchorPoint(true);
	pTitleLabelServ->setPosition( POS(ccp(630, 114), ScaleUtil::CENTER) );
	this->addChild(pTitleLabelServ);
}

void LoginRegister::onBackMenuClick(CCObject *pSender)
{
	LoginView * pLoginView = (LoginView *)this->getParent();

	if (pLoginView)
	{
		pLoginView->removeChildByTag(LoginView::TAG_RegisterLayer,false);
		pLoginView->addChild(pLoginView->_pLoginMainLayer);
	}

	SoundManager::Instance()->playButtonEffectSound();
}

void LoginRegister::onRegisterConfirmMenuClick(CCObject *pSender)
{
	//Poco::Net::HTTPClientSession session("api.p.m.4399.com", Poco::Net::HTTPSession::HTTP_PORT);	
	//Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST,"/oauth2/authorize?client_id=1338694911363750&redirect_uri=http://localhost&response_type=token&state=66666666666",Poco::Net::HTTPMessage::HTTP_1_1);

	//// sy platform
	////http://api.p.m.4399.com/oauth2/authorize?client_id=1338694911363750&redirect_uri=http://localhost&response_type=token&state=66666666666
	////192.168.101.45  api.p.m.4399.com
	////http://api.p.m.4399.com/service/user/get_my_balance?oauth_token=aa52438321acbf7eccca8373015201ab

	//request.setContentType("application/x-www-form-urlencoded");

// 	request.add("appId","www_home");
// 	request.add("crossDomainIFrame","");
// 	request.add("crossDomainUrl","");
// 	request.add("css","");
// 	request.add("displayMode","embed");
// 	request.add("email","lhclumsy@163.com");
// 	request.add("gameId","");
// 	request.add("mainDivId","embed_login_div");
// 	request.add("manualReg","true");
// 	request.add("noEmail","false");
// 	request.add("password","123123123");
// 	request.add("passwordveri","123789456lh");
// 	request.add("postLoginHandler","default");//&displayMode=embed&appId=www_home&gameId=&css=&redirectUrl=&manualReg=true&sessionId=&regIdcard=false&noEmail=false&crossDomainIFrame=&crossDomainUrl=&mainDivId=embed_login_div&showRegInfo=true&username=longhui00001&password=3771279000&passwordveri=3771279000&email=304319271&reg_eula_agree=on
// 	request.add("redirectUrl","");
// 	request.add("reg_eula_agree","on");
// 	request.add("regIdcard","false");
// 	request.add("sessionId","");
// 	request.add("showRegInfo","true");
// 	request.add("username","kongkong123");

//	request.setContentLength(317);
	/*session.sendRequest(request);
	

	char buffer[8096] = {0};
	Poco::Net::HTTPResponse response;
	session.receiveResponse(response).read(buffer,8096);
	int len = sizeof(buffer);
	CCLog("%s",buffer);*/
	//CCLog("Response code:%d,%s",response.getStatus(),response.getReason());

	SoundManager::Instance()->playButtonEffectSound();
}

LoginRegister::~LoginRegister()
{
	//CCSprite* pS = (CCSprite*)this->getChildByTag(Tag_Bg);
	//if (pS)
	//{
	//	CCTexture2D* pTex = pS->getTexture();
	//	pS->removeFromParentAndCleanup(true);
	//	CCTextureCache::sharedTextureCache()->removeTexture(pTex);
	//}

	//pS = (CCSprite*)this->getChildByTag(Tag_Account_Bg);
	//if (pS)
	//{
	//	CCTexture2D* pTex = pS->getTexture();
	//	pS->removeFromParentAndCleanup(true);
	//	CCTextureCache::sharedTextureCache()->removeTexture(pTex);
	//}

	this->removeAllChildrenWithCleanup(true);
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_input.pvr.ccz");
}
