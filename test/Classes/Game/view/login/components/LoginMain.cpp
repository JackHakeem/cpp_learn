#include "CCPlatformConfig.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "utils/http/ghttp.h"
#include "netdb.h"
#include "arpa/inet.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "utils/http/ghttp.h"
#include "netdb.h"
#include "arpa/inet.h"
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "Poco/Net/NetException.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
using namespace Poco;
using namespace Poco::Net;
 
#endif

#include "LoginMain.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "UICheckButton/UICheckButton.h"
#include "LoginView.h"
#include "BaseType.h"
#include "LoginRegister.h"
#include "LoginServer.h"
#include "MessageInfoBox.h"
#include "socket/network/GateServerSocket.h"
#include "LoginManage.h"
#include "events/GameDispatcher.h"
#include "Message.h"
#include "manager/TouchLayerEnum.h"
#include "AreaListView.h"
#include "ServerListView.h"
#include "TextFieldTTF.h"
#include "manager/sound/SoundManager.h"
#include "socket/network/GameServerSocket.h"
#include "utils/xml/TinyElementHandler.h"
#include "utils/thread/BaseThread.h"
#include "utils/thread/MessageMgr.h"

bool isContainAlpha(std::string str)
{
	bool isAlpha = false;
	int len = str.length();
	int i = 0;
	while(i < len-1) 
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		{
			isAlpha = true;
			break;
		}
		++i;
	}
	return isAlpha;
}

LoginMain::LoginMain()
{
	_pLoginView = 0;
	m_pThread = 0;
}

bool LoginMain::init()
{
	if (!CCLayer::init())
	{
		return false;
	}

	loadItems();

	return true;
}

void LoginMain::loadItems()
{
	this->setAnchorPoint(CCPointZero);
	this->setIsRelativeAnchorPoint(true);

	//
//	setDefaultServerAndPort();
	// read ServInfo from file
	readFavorServInfoFromFile();

	// Add frame background.

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_frame.plist");

	CCSprite *pUserPassBackgroundSprite = new CCSprite;
	if( pUserPassBackgroundSprite && pUserPassBackgroundSprite->initWithSpriteFrameName("login/login_frame.png"))
	{
		pUserPassBackgroundSprite->setAnchorPoint(CCPointZero);
		pUserPassBackgroundSprite->setPosition(POS(ccp(92, 80), ScaleUtil::CENTER));
		pUserPassBackgroundSprite->setOpacity(225);
        pUserPassBackgroundSprite->setTag(Tag_UserPass_Bg);
		this->addChild(pUserPassBackgroundSprite);
		pUserPassBackgroundSprite->release();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_frame.plist");
	}

	// Add text input components.
	// Add account.

	CCLabelTTF* pAccountLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG004").c_str(),
		CCSizeMake(POSX(120), POSX(30)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(30));
	pAccountLabel->setColor(ccc3(255, 215, 10));
	pAccountLabel->setAnchorPoint(CCPointZero);
	pAccountLabel->setIsRelativeAnchorPoint(true);
	pAccountLabel->setPosition( POS(ccp(144, 420), ScaleUtil::CENTER) );

	this->addChild(pAccountLabel);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_input.plist");
	CCSprite *pAccountBackgroundSprite = new CCSprite;
	if( pAccountBackgroundSprite && pAccountBackgroundSprite->initWithSpriteFrameName("login/login_input.png"))
	{
		pAccountBackgroundSprite->setAnchorPoint(CCPointZero);
		pAccountBackgroundSprite->setPosition(POS(ccp(234, 414), ScaleUtil::CENTER));
        pAccountBackgroundSprite->setTag(Tag_Account_Bg);
		this->addChild(pAccountBackgroundSprite);
		pAccountBackgroundSprite->release();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_input.plist");
	}	
	//insert passwd
	{
		TextFieldTTF * pTextField = new TextFieldTTF();
		pTextField->setTag(LoginView::TEXTFIELD_PASSWD);
		this->addChild(pTextField,1000);
		pTextField->release();

		//pTextField->attachWithIME();
		pTextField->setPosition(POS(ccp(550, 354), ScaleUtil::CENTER));	
	}
	
	//insert account
	
	{
		TextFieldTTF * pTextField = new TextFieldTTF();
		pTextField->setTag(LoginView::TEXTFIELD_ACCOUNT);


		pTextField->setString("315125723");
		//pTextField->setString("306559992");

		this->addChild(pTextField,1000);
		pTextField->release();
	//	CCTextFieldTTF* oo = (CCTextFieldTTF*)pTextField->m_pTrackNode;
		//oo->setString("longhui2");
	//	oo->attachWithIME();

		pTextField->setPosition(POS(ccp(550, 434), ScaleUtil::CENTER));
	}
	/*kevinchange*/
	


	/*kevinchange
	CCTextFieldTTF *pAccountTextField = CCTextFieldTTF::textFieldWithPlaceHolder("",
		CCSizeMake(POSX(380), POSX(40)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));
	if(pAccountTextField)
	{
		pAccountTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
		pAccountTextField->setAnchorPoint(CCPointZero);
		pAccountTextField->setPosition(POS(ccp(236, 416), ScaleUtil::CENTER));
		pAccountTextField->attachWithIME();
		pAccountTextField->setString("longhui2");
		pAccountTextField->setTag(LoginView::TEXTFIELD_ACCOUNT);
		this->addChild(pAccountTextField);
	}
	*/

	// Add password.
	CCLabelTTF* pPasswdLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG005").c_str(),
		CCSizeMake(POSX(120), POSX(30)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(30));
	pPasswdLabel->setColor(ccc3(255, 215, 10));
	pPasswdLabel->setAnchorPoint(CCPointZero);
	pPasswdLabel->setIsRelativeAnchorPoint(true);
	pPasswdLabel->setPosition( POS(ccp(144, 340), ScaleUtil::CENTER) );
	pPasswdLabel->setTag(TAG_PWD_TEXT);
	this->addChild(pPasswdLabel);

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_input.plist");
	CCSprite *pPasswdBackgroundSprite = new CCSprite();
	if(pPasswdBackgroundSprite && pPasswdBackgroundSprite->initWithSpriteFrameName("login/login_input.png"))
	{
		pPasswdBackgroundSprite->setAnchorPoint(CCPointZero);
		pPasswdBackgroundSprite->setPosition(POS(ccp(234, 334), ScaleUtil::CENTER));
		pPasswdBackgroundSprite->setTag(TAG_PWD_LABBG);
		this->addChild(pPasswdBackgroundSprite);
		pPasswdBackgroundSprite->release();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_input.plist");
	}
	//
	
/*kevinchange
	CCTextFieldTTF *pPasswdTextField = CCTextFieldTTF::textFieldWithPlaceHolder("sdfsdfsdf",
		CCSizeMake(POSX(380), POSX(40)),
		CCTextAlignmentLeft,
		g_sSimHeiFont,
		POSX(28));	

	if(pPasswdTextField)
	{
		pPasswdTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
		pPasswdTextField->setAnchorPoint(CCPointZero);
		pPasswdTextField->setPosition(POS(ccp(236, 336), ScaleUtil::CENTER));
		//pPasswdTextField->attachWithIME();
		pPasswdTextField->setTag(LoginView::TEXTFIELD_PASSWD);
		this->addChild(pPasswdTextField);
	}
	*/
	// guest login describe text
	CCLabelTTF* pGuestDesTxtLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG025").c_str(),
		CCSizeMake(POSX(640), POSX(80)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(30));
	pGuestDesTxtLabel->setColor(ccc3(12, 233, 25));
	pGuestDesTxtLabel->setAnchorPoint(CCPointZero);
	pGuestDesTxtLabel->setIsRelativeAnchorPoint(true);
	pGuestDesTxtLabel->setPosition( POS(ccp(146, 316), ScaleUtil::CENTER) );
	pGuestDesTxtLabel->setTag(TAG_GUESTLOGIN_DES_TEXT);
	pGuestDesTxtLabel->setIsVisible(false);
	this->addChild(pGuestDesTxtLabel);

	// Add area.
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_server.plist");
	CCSprite *pAreaBackgroundSprite = new CCSprite();
	if(pAreaBackgroundSprite && pAreaBackgroundSprite->initWithSpriteFrameName("login/login_area.png"))
	{
		pAreaBackgroundSprite->setAnchorPoint(CCPointZero);
		pAreaBackgroundSprite->setPosition(POS(ccp(260, 270), ScaleUtil::CENTER));
		pAreaBackgroundSprite->setScaleX(1.5);
		pAreaBackgroundSprite->setScaleY(1.2);
		pAreaBackgroundSprite->setTag(TAG_AREA);
		this->addChild(pAreaBackgroundSprite);
		pAreaBackgroundSprite->release();
		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_server.plist");
	}

	setAreaText();
	

	{
		// Add login button.
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pLoginMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(LoginMain::onLoginMenuClick));
			pLoginMenuItem->setAnchorPoint(CCPointZero);
			pLoginMenuItem->setScale(1.3f);
			pLoginMenuItem->setPosition( POS(ccp(636, 125), ScaleUtil::CENTER) );
			CCMenu* pLoginMenu = CCMenu::menuWithItems(pLoginMenuItem, NULL);
			pLoginMenu->setPosition( CCPointZero );
			pLoginMenu->setTouchLayer(-7301);
			this->addChild(pLoginMenu);
		}
	}

	CCLabelTTF* pTitleLabelLogin = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG002").c_str(),
		CCSizeMake(POSX(128), POSX(32)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(32));
	pTitleLabelLogin->setColor(ccc3(255, 255, 0));
	pTitleLabelLogin->setAnchorPoint(CCPointZero);
	pTitleLabelLogin->setIsRelativeAnchorPoint(true);
	pTitleLabelLogin->setPosition( POS(ccp(650, 139), ScaleUtil::CENTER) );
	this->addChild(pTitleLabelLogin);

	// Add register button.
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pRegMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				menu_selector(LoginMain::onRegisterMenuClick) );
			pRegMenuItem->setAnchorPoint(CCPointZero);
			pRegMenuItem->setScale(1.3f);
			pRegMenuItem->setIsEnabled(false);// not open  LH0718
			pRegMenuItem->setPosition( POS(ccp(180, 125), ScaleUtil::CENTER) );
			CCMenu* pRegMenu = CCMenu::menuWithItems(pRegMenuItem, NULL);
			pRegMenu->setPosition( CCPointZero );
			pRegMenu->setTouchLayer(-1301);
			this->addChild(pRegMenu);
		}
	}

	CCLabelTTF* pTitleLabelReg = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG001").c_str(),
		CCSizeMake(POSX(168), POSX(32)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(32));
	pTitleLabelReg->setColor(ccc3(255, 255, 0));
	pTitleLabelReg->setAnchorPoint(CCPointZero);
	pTitleLabelReg->setIsRelativeAnchorPoint(true);
	pTitleLabelReg->setPosition( POS(ccp(194, 139), ScaleUtil::CENTER) );
	this->addChild(pTitleLabelReg);

	// Add server button.
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pServMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
			menu_selector(LoginMain::onServerMenuClick));
			pServMenuItem->setAnchorPoint(CCPointZero);
			pServMenuItem->setScale(1.3f);
			pServMenuItem->setPosition( POS(ccp(408, 125), ScaleUtil::CENTER) );
			CCMenu* pServMenu = CCMenu::menuWithItems(pServMenuItem, NULL);
			pServMenu->setPosition( CCPointZero );
			pServMenu->setTouchLayer(-1301);
			this->addChild(pServMenu);
		}
	}

	CCLabelTTF* pTitleLabelServ = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG003").c_str(),
		CCSizeMake(POSX(128), POSX(32)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(32));
	pTitleLabelServ->setColor(ccc3(255, 255, 0));
	pTitleLabelServ->setAnchorPoint(CCPointZero);
	pTitleLabelServ->setIsRelativeAnchorPoint(true);
	pTitleLabelServ->setPosition( POS(ccp(422, 139), ScaleUtil::CENTER) );

	this->addChild(pTitleLabelServ);

	
}

void LoginMain::setDefaultServerAndPort()
{
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > * _servListVoDic = &g_pLoginManage->_serverListVoDic;
	std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _servListVoDic->find(0);
	if (iter != _servListVoDic->end())
	{
		std::map<int/*servID*/,ServerListVo>::iterator it = iter->second.begin();
		if (it != iter->second.end())
		{
			ServerListVo * pSerListVo = &it->second;
			if (pSerListVo)
			{
				setSelectedArea(pSerListVo->areaName);
				setSelectedServ(pSerListVo->servName);
				g_pLoginManage->setServIPAddr(pSerListVo->ip);
				g_pLoginManage->setServIPPort(pSerListVo->port);
			}
		}
	}
}

void LoginMain::readFavorServInfoFromFile()
{
	FILE * pFile = fopen("assets/config/config_bak/server.dat","r");
	if (!pFile) {return;}
	
	char buf[256] = {0};
	fread((void *)buf,sizeof(buf),1,pFile);
	fclose(pFile);

	std::list<std::string> strList = splitStringByCharacter( buf , ";" );
	if (strList.empty())	{return;	}	

	setSelectedArea(strList.front());
	g_pLoginManage->_CurServListVo.areaName = strList.front();
	strList.pop_front();
	if (strList.empty())	{return;	}	

	setSelectedServ(strList.front());
	g_pLoginManage->_CurServListVo.servName = strList.front();
	strList.pop_front();
	if (strList.empty())	{return;	}
	
	if (!g_pLoginManage)	{return;	}	
	g_pLoginManage->setServIPAddr(strList.front());
	g_pLoginManage->_CurServListVo.ip = strList.front();
	strList.pop_front();
	if (strList.empty())	{return;	}

	if (!strList.front().empty())
	{
		g_pLoginManage->setServIPPort(string2Int(strList.front()));
		g_pLoginManage->_CurServListVo.port = string2Int(strList.front());
	}	
	strList.pop_front();
	if (strList.empty())	{return;	}

	if (!strList.front().empty())
	{
		g_pLoginManage->setServState(string2Int(strList.front()));
		g_pLoginManage->_CurServListVo.state = string2Int(strList.front());
	}	
	strList.pop_front();
	if (strList.empty())	{return;	}

	if (!strList.front().empty())
	{
		g_pLoginManage->setExchargeServerId(strList.front());
		g_pLoginManage->_CurServListVo.exchargeServerId = strList.front();
	}
	strList.pop_front();
	if (strList.empty())	{return;	}

}

int LoginMain::string2Int(std::string str)
{
	std::string strTmp = str;
	int len = strTmp.length();
	if (!len)	{	return (-1);}

	bool isNegative = false;

	if (strTmp[0] == '-')
	{
		isNegative = true;
		strTmp.substr(1,strTmp.length()-1);
	}

	len = strTmp.length();
	int result = 0;
	for (int i = 0;i < len;i++)
	{
		result = result * 10 + ( strTmp[i] - '0');
	}

	if (isNegative)
	{
		result = (-1) * result;
	}
	return result;
}

std::list<std::string> LoginMain::splitStringByCharacter( string o_str, string sCharacter )
{
	std::list<std::string> str_list; // ��ŷָ����ַ�?	int comma_n = 0;
	do
	{
		std::string tmp_s = "";
		int comma_n = o_str.find( sCharacter );
		if( -1 == comma_n )
		{
			tmp_s = o_str.substr( 0, o_str.length() );
			str_list.push_back( tmp_s );
			break;
		}
		tmp_s = o_str.substr( 0, comma_n );
		o_str.erase( 0, comma_n+1 );
		str_list.push_back( tmp_s );
	}
	while(true);
	return str_list;
}

void LoginMain::setAreaText()
{
	if (this->getChildByTag(TAG_AREA_TEXT))
	{
		this->removeChildByTag(TAG_AREA_TEXT,true);
	}
	std::string szAreaServ("");

	// LH 20121119
	setSelectedArea(g_pLoginManage->_CurServListVo.areaName);
	setSelectedServ(g_pLoginManage->_CurServListVo.servName);
	/*
	LoginView * pLoginView = g_pLoginManage->_pLoginView;
	if (pLoginView)
	{
		if (pLoginView->getSelectedArea()!="")
		{
			this->setSelectedArea(pLoginView->getSelectedArea());
		}
		if (pLoginView->getSelectedServ()!="")
		{
			this->setSelectedServ(pLoginView->getSelectedServ());
		}
	}
	*/

	szAreaServ.append(getSelectedArea());
	szAreaServ.append( "-" );
	szAreaServ.append(getSelectedServ());
	CCLabelTTF * pLabText = CCLabelTTF::labelWithString(szAreaServ.c_str(),CCSizeMake(POSX(250),POSX(30)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(26));
	pLabText->setColor(ccc3(12,233,25));
	pLabText->setAnchorPoint(CCPointZero);
	pLabText->setPosition(POS(ccp(270, 277), ScaleUtil::CENTER));
	pLabText->setTag(TAG_AREA_TEXT);
	this->addChild(pLabText,1);
}

void LoginMain::onRegisterMenuClick(CCObject *pSender)
{
	LoginView * pLoginView = (LoginView *)this->getParent();
	if (pLoginView)
	{
		pLoginView->removeChildByTag(LoginView::TAG_UserPwdLayer,false);
		pLoginView->addChild(pLoginView->_pRegisterLayer);
	}

	SoundManager::Instance()->playButtonEffectSound();
}

void LoginMain::onServerMenuClick(CCObject *pSender)
{
	
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::LOGIN_RESETSERVLIST ,this , callfuncND_selector(LoginMain::resetServList));
 	
	m_pThread = new BaseThread((void *)&getServerInfoFromRemote,0);
	m_pThread->run();
	
	//getServerInfoFromRemote();

	
	LoginView * pLoginView = (LoginView *)this->getParent();
	if (pLoginView)
	{
		_pLoginView = pLoginView;

		pLoginView->removeChildByTag(LoginView::TAG_UserPwdLayer,false);

		if (pLoginView->_pServersLayer)
		{
			pLoginView->addChild(pLoginView->_pServersLayer);	

			//pLoginView->_pServersLayer->resetListView();

			// 20121119 LH for new UI
			//std::string str(getSelectedArea());
			//str.append("-");
			std::string str(g_pLoginManage->_CurServListVo.servName);
			pLoginView->_pServersLayer->setLastLoginServer(str);
			pLoginView->_pServersLayer->setSelectedServer(str);

			// 20121119 LH recommended server for new UI
			std::vector<ServerListVo> list = g_pLoginManage->getServerList();
			for (int i = 0 ; i < list.size() ; i++)
			{
				if (list[i].state == 3)
				{
					//std::string str(list[i].areaName);
					//str.append("-");
					std::string str(list[i].servName);
					pLoginView->_pServersLayer->setRecommendedServer(str);
					break;
				}				
			}			
		}
	}
	SoundManager::Instance()->playButtonEffectSound();
}

void LoginMain::onLoginMenuClick( CCObject *pSender )
{
	if (g_pLoginManage->getServState() == -1)
	{
		char path[256] = {0};
		LoginView * pLoginView = (LoginView *)this->getParent();
		sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , pLoginView ? pLoginView->getSelectedArea().c_str() : "", pLoginView ? pLoginView->getSelectedServ().c_str() : "");
		CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
		return;
	}

	string account = "";
	string passwd = "";

	TextFieldTTF *pAccountTextField = (TextFieldTTF *)this->getParent()
		->getChildByTag(LoginView::TAG_UserPwdLayer)->getChildByTag(LoginView::TEXTFIELD_ACCOUNT);
	if(pAccountTextField)
	{
		CCTextFieldTTF * pccTextField = (CCTextFieldTTF*)pAccountTextField->m_pTrackNode;
		 if (pccTextField)
		 {
			account = pccTextField->getString();
		 }
	}
	//	account = pAccountTextField->m_getString();
	
	TextFieldTTF *pPasswdTextField = (TextFieldTTF *)this->getParent()
		->getChildByTag(LoginView::TAG_UserPwdLayer)->getChildByTag(LoginView::TEXTFIELD_PASSWD);
	if(pPasswdTextField)
	{
		CCTextFieldTTF * pccTextField = (CCTextFieldTTF*)pPasswdTextField->m_pTrackNode;
		 if (pccTextField)
		 {
			passwd = pccTextField->getString();
		 }
	}
	/**/

/*
	CCTextFieldTTF *pPasswdTextField = (CCTextFieldTTF *)this->getParent()
		->getChildByTag(LoginView::TAG_UserPwdLayer)->getChildByTag(LoginView::TEXTFIELD_PASSWD);
	if(pPasswdTextField)
		passwd = pPasswdTextField->getString();
	
	CCTextFieldTTF *pAccountTextField = (CCTextFieldTTF *)this->getParent()
		->getChildByTag(LoginView::TAG_UserPwdLayer)->getChildByTag(LoginView::TEXTFIELD_ACCOUNT);
	if(pAccountTextField)
		account = pAccountTextField->getString();
	CCTextFieldTTF *pPasswdTextField = (CCTextFieldTTF *)this->getParent()
		->getChildByTag(LoginView::TAG_UserPwdLayer)->getChildByTag(LoginView::TEXTFIELD_PASSWD);
	if(pPasswdTextField)
		passwd = pPasswdTextField->getString();
		*/
	if(account == "")
	{
		// Account must not be empty!
		CCMessageBox(ValuesUtil::Instance()->getString("LG006").c_str(),"");
		//Message::Instance()->show(ValuesUtil::Instance()->getString("LG006").c_str(),ccc3(12,233,25));
		return;
	}

	if(account.length() > 10)
	{
		// Account ugly!
		CCMessageBox(ValuesUtil::Instance()->getString("LG007").c_str(),"");
		//Message::Instance()->show(ValuesUtil::Instance()->getString("LG007").c_str(),ccc3(12,233,25),1);
		return;
	}

	g_pLoginManage->setAccount(account);
	g_pLoginManage->setPasswd(passwd);

    parseUrlAndLogin();
    
    bool result = GateServerSocket::getInstance()->connect(g_pLoginManage->getServIPAddr(), g_pLoginManage->getServIPPort());
	if (result)
	{
		CCLog(">Connect to GateServer succ");
		g_pLoginManage->gSocketConnectHandler();
	}
	else
	{
		CCLog(">Connect GateServer fail");
		CCMessageBox(ValuesUtil::Instance()->getString("LG023").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		//MessageInfoBox::Instance()->show(ValuesUtil::Instance()->getString("LG023"),ccc3(12,233,25));
		//GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::GATE_SERVER_CONNECT_FAILED, NULL);
	}
    
	SoundManager::Instance()->playButtonEffectSound();
}

void LoginMain::parseUrlAndLogin()
{
	std::string strDomainOrIP = g_pLoginManage->getServIPAddr();
	if (isContainAlpha(strDomainOrIP))
	{
		hostent * pHost = gethostbyname(strDomainOrIP.c_str());
		if (!pHost)
		{
			CCMessageBox(ValuesUtil::Instance()->getString("LG040") .c_str() , ValuesUtil::Instance()->getString("LG033") .c_str());
			return;
		}
		
		sockaddr_in sa;
		std::string strHostIP("");
		int port = 0;
		std::list<std::string> IPList;
		for (int nAdapter= 0; pHost->h_addr_list[nAdapter] ; nAdapter++)
		{
			memcpy(&sa.sin_addr.s_addr , pHost->h_addr_list[nAdapter] , pHost->h_length);
			strHostIP = inet_ntoa(sa.sin_addr);
			IPList.push_back(strHostIP);
			//port = sa.sin_port;
		}
        
//		port = g_pLoginManage->getServIPPort();
//		CCLog("IPAddress : %s , Port : %d" , strHostIP.c_str() , port);
        g_pLoginManage->setServIPAddr(IPList.front());
		g_pLoginManage->_CurServListVo.ip = IPList.front();
//		result = GateServerSocket::getInstance()->connect(IPList.front(), port);
	}
	else
	{
//		result = GateServerSocket::getInstance()->connect(g_pLoginManage->getServIPAddr(), g_pLoginManage->getServIPPort());
	}
    
	//bool result = GateServerSocket::getInstance()->connect(/*"192.168.101.10"*/"183.60.47.21"/*"113.107.110.141"*/, 83);//"113.107.110.141", 83     115.238.73.228 121  

}

void LoginMain::onNormalLoginMenuClick(CCObject *pSender)
{
	UICheckButton * pGuestLoginMenu = (UICheckButton *)this->getChildByTag(LoginView::GUEST_CHECK_BTN);
	if (pGuestLoginMenu)
	{
		pGuestLoginMenu->setIsCheck(false);
	}
	UICheckButton * pNormalLoginMenu = (UICheckButton *)this->getChildByTag(LoginView::NORMAL_CHECK_BTN);
	if (pNormalLoginMenu)
	{
		pNormalLoginMenu->setIsCheck(true);
	}
	//
	CCLabelTTF * pDesTxt = (CCLabelTTF *)this->getChildByTag(TAG_GUESTLOGIN_DES_TEXT);
	if (pDesTxt)
	{
		pDesTxt->setIsVisible(false);
	}
	//
	CCLabelTTF * pLabTxt = (CCLabelTTF *)this->getChildByTag(TAG_PWD_TEXT);
	if (pLabTxt)
	{
		pLabTxt->setIsVisible(true);
	}
	CCSprite * pSpriteBg = (CCSprite *)this->getChildByTag(TAG_PWD_LABBG);
	if (pSpriteBg)
	{
		pSpriteBg->setIsVisible(true);
	}
	CCTextFieldTTF * pLabTxtField = (CCTextFieldTTF *)this->getChildByTag(LoginView::TEXTFIELD_PASSWD);
	if (pLabTxtField)
	{
		pLabTxtField->setIsVisible(true);
	}
	//
	g_pLoginManage->setIsGuestLogin(false);
}

void LoginMain::onGuestLoginMenuClick(CCObject *pSender)
{
	/*
	UICheckButton * pGuestLoginMenu = (UICheckButton *)this->getChildByTag(LoginView::GUEST_CHECK_BTN);
	if (pGuestLoginMenu)
	{
		pGuestLoginMenu->setIsCheck(true);
	}
	UICheckButton * pNormalLoginMenu = (UICheckButton *)this->getChildByTag(LoginView::NORMAL_CHECK_BTN);
	if (pNormalLoginMenu)
	{
		pNormalLoginMenu->setIsCheck(false);
	}
	//
	CCLabelTTF * pDesTxt = (CCLabelTTF *)this->getChildByTag(TAG_GUESTLOGIN_DES_TEXT);
	if (pDesTxt)
	{
		pDesTxt->setIsVisible(true);
	}
	//
	CCLabelTTF * pLabTxt = (CCLabelTTF *)this->getChildByTag(TAG_PWD_TEXT);
	if (pLabTxt)
	{
		pLabTxt->setIsVisible(false);
	}
	CCSprite * pSpriteBg = (CCSprite *)this->getChildByTag(TAG_PWD_LABBG);
	if (pSpriteBg)
	{
		pSpriteBg->setIsVisible(false);
	}
	CCTextFieldTTF * pLabTxtField = (CCTextFieldTTF *)this->getChildByTag(LoginView::TEXTFIELD_PASSWD);
	if (pLabTxtField)
	{
		pLabTxtField->setIsVisible(false);
	}
	//
	g_pLoginManage->setIsGuestLogin(true);
	*/
}

void LoginMain::registerWithTouchDispatcher( void )
{
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this,-5500, true);
}

bool LoginMain::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	return true;
}

LoginMain::~LoginMain()
{
	if (m_pThread)
	{
		delete m_pThread;
	}
	//CCSprite* pS = (CCSprite*)this->getChildByTag(Tag_UserPass_Bg);
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

	//pS = (CCSprite*)this->getChildByTag(TAG_PWD_LABBG);
	//if (pS)
	//{
	//	CCTexture2D* pTex = pS->getTexture();
	//	pS->removeFromParentAndCleanup(true);
	//	CCTextureCache::sharedTextureCache()->removeTexture(pTex);
	//}

	//pS = (CCSprite*)this->getChildByTag(TAG_AREA);
	//if (pS)
	//{
	//	CCTexture2D* pTex = pS->getTexture();
	//	pS->removeFromParentAndCleanup(true);
	//	CCTextureCache::sharedTextureCache()->removeTexture(pTex);
	//}
	this->removeAllChildrenWithCleanup(true);

	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_frame.pvr.ccz");

	CCTexture2D* pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/res_login_server.pvr.ccz");
	if (pText && (pText->retainCount()==1))
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_server.pvr.ccz");
	
	pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/res_login_input.pvr.ccz");
	if (pText && (pText->retainCount()==1))
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_input.pvr.ccz");
}

void LoginMain::getServerInfoFromRemote()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    char pUrl[128] = "http://api.slcq.4399sy.com/ios/v1.2.7.0/get_server_list.php";
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    char pUrl[128] = "http://api.slcq.4399sy.com/android/v1.2.4.0/get_server_list.php";
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )

	ghttp_request *request = NULL;
	ghttp_status status;
	char *buf;
	int bytes_read;

	request = ghttp_request_new();
	if(ghttp_set_uri(request, pUrl) == -1)
		exit(-1);
	if(ghttp_set_type(request, ghttp_type_get) == -1)
		exit(-1);
	ghttp_set_sync(request, ghttp_async);
	ghttp_prepare(request);

	while(1) 
	{
		status = ghttp_process(request);
		if(status == ghttp_error)
		{
			CCMessageBox("http error", "Login");
			break;
		}
		buf = ghttp_get_body(request);
		bytes_read = ghttp_get_body_len(request);
		if(status == ghttp_done) 
		{
//			printf("%s", buf);
//			printf("\n");
//			printf("number:%d", bytes_read);
			break;
		}
		else
		{
//			printf("false\n");
		}
	}
    //Doyang 20120907
    if(bytes_read <= 0)
    {
        CCMessageBox("http error", "Login");
        return;
    }
    
    
	char* usefulBuff = new char[bytes_read+1];
	strncpy(usefulBuff, buf, bytes_read);
	usefulBuff[bytes_read] = '\0';

	loadServerListXMLBuffer(usefulBuff, bytes_read +1 , TIXML_ENCODING_UTF8);

	delete []usefulBuff;
	usefulBuff = 0;
	ghttp_request_destroy(request);

#endif	

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	Poco::Net::HTTPClientSession session("api.slcq.4399sy.com", Poco::Net::HTTPSession::HTTP_PORT);	
	Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, /*"/android/v1.1.0.1/get_server_list.php"*/"/windows/get_server_list.php",Poco::Net::HTTPMessage::HTTP_1_1);

	try
	{
		session.sendRequest(request);
	}
	catch (Poco::Net::NetException * e)
	{
		CCMessageBox(e->name() , ValuesUtil::Instance()->getString("LG033").c_str());
		return;
	}

	char buffer[8192] = {0};
	Poco::Net::HTTPResponse response;
	try
	{
		session.receiveResponse(response).read(buffer,8096);
	}
	catch (Poco::Net::NetException* e)
	{
		CCMessageBox(e->name() , ValuesUtil::Instance()->getString("LG033").c_str());
		return;
	}

	int len = sizeof(buffer);

	CCLog("%s" , buffer);

	if (len)
	{
		loadServerListXMLBuffer(buffer,sizeof(buffer),TiXmlEncoding::TIXML_ENCODING_UTF8);
	}
	
#endif

	MessageMgr::Instance()->sendMessage(GameDispatcher::LOGIN_RESETSERVLIST,0);

}

void LoginMain::resetServList(CCNode * pTarget,void *pData)
{
	if (_pLoginView)
	{
		if (_pLoginView->_pServersLayer)
		{
			_pLoginView->_pServersLayer->resetListView();


			std::string str(g_pLoginManage->_CurServListVo.servName);
			_pLoginView->_pServersLayer->setLastLoginServer(str);
			_pLoginView->_pServersLayer->setSelectedServer(str);
		}
	}

	GameDispatcher::getInstance()->removeEventListener(GameDispatcher::LOGIN_RESETSERVLIST);
}

int LoginMain::loadServerListXMLBuffer( char *arr, int length, TiXmlEncoding encoding )
{
	if (!arr)
		return 1;

	TiXmlDocument xmlDoc(arr); 
    CCLog("1-----------\n%s", arr);
	bool sus = xmlDoc.loadFileWithCharArr(arr, length, encoding);  
	if (!sus)
		return 1;

	CCLog("2-----------\n%s", arr);

	TiXmlElement* pRootElement = xmlDoc.RootElement();  
	if(!pRootElement)  
		return 1;  

	TiXmlNode* pNode = NULL;
	for(pNode = pRootElement->FirstChildElement();pNode;pNode=pNode->NextSiblingElement())  
	{  
		int t = pNode->Type();
		switch(t)
		{
		case TiXmlText::TINYXML_ELEMENT:
			//ITEM each
			{
				TiXmlElement* pEle = pNode->ToElement();
				if (!pEle)
				{
					//Abnormal warning
				}
				TinyElementHandler elehandler(pEle);

				// add code here
				ServerListVo servListVo;
				elehandler.get(servListVo.areaID);
				elehandler.get(servListVo.areaName);
				elehandler.get(servListVo.serverID);
				elehandler.get(servListVo.servName);
				elehandler.get(servListVo.ip);

				int port;
				elehandler.get(port);
				servListVo.port = port & 0x0000ffff;

				elehandler.get(servListVo.state);
				elehandler.get(servListVo.exchargeServerId);

				std::map<int/*servID*/,ServerListVo> servListVoMap;
				servListVoMap.insert(make_pair(servListVo.serverID,servListVo));

				std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> > *_serverListVoDic = &g_pLoginManage->_serverListVoDic;
				std::map<int/*areaID*/,std::map<int/*servID*/,ServerListVo> >::iterator iter = _serverListVoDic->find(servListVo.areaID);
				if (iter != _serverListVoDic->end())
				{
					iter->second.insert(make_pair(servListVo.serverID,servListVo));
				}
				else
				{
					_serverListVoDic->insert(make_pair(servListVo.areaID,servListVoMap));
				}
				
			}
			break;
		default:
			break;
		}
	}
	// convert map to list
	g_pLoginManage->saveServerMap2List();

	return 0;
}
