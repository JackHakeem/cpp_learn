#include "LoginServer.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "LoginView.h"
#include "BaseType.h"
#include "LoginMain.h"
#include "AreaListView.h"
#include "UIListView/CCUIListView.h"
#include "ServerListView.h"
#include "LoginManage.h"
#include "manager/TouchLayerEnum.h"
#include "socket/network/GateServerSocket.h"
#include "manager/sound/SoundManager.h"
#include "CCUIBackground.h"
#include "ServerNewListView.h"

#if (CC_PLATFORM_ANDROID == CC_TARGET_PLATFORM)
#include "jni/slcq/JniManager.h"
#endif
#include "LoginNewMain.h"
#include "CCFileUtils.h"
#include "LHMenuItemLabel.h"

LoginServer::LoginServer()
{
	_pAeraListView = 0;
	_pServListView = 0;
	_pServNewListView = 0;
}

bool LoginServer::init()
{

	if (!CCLayer::init())
	{
		return false;
	}

	_winSize = CCDirector::sharedDirector()->getWinSize();

	loadItems();

	addServQQ();

	return true;
}

void LoginServer::addServQQ()
{
	//CCUIBackground * pServQQBack = new CCUIBackground();
	//pServQQBack->initWithSpriteFrame("ui.png",CCPointZero,CCPointZero,CCSizeMake(POSX(0),POSX(0)));
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_server.plist");
	CCSprite * pServQQBack = CCSprite::spriteWithSpriteFrameName("login/login_area.png");
	pServQQBack->setAnchorPoint(CCPointZero);
	char pTitle[20] = {0}, pContent[20] = {0};
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    sprintf(pTitle, "%s", ValuesUtil::Instance()->getString("WLC0021").c_str());
    sprintf(pContent, "%d", 248480608);
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    sprintf(pTitle, "%s", ValuesUtil::Instance()->getString("WLC0022").c_str());
    sprintf(pContent, "%d", 260062482);
#else
    sprintf(pTitle, "%s", ValuesUtil::Instance()->getString("WLC0022").c_str());
    sprintf(pContent, "%d", 248480608);
#endif
	CCLabelTTF * pLabTxtServQQ = CCLabelTTF::labelWithString(
		pTitle,
		CCSizeMake(POSX(240),POSX(50)),CCTextAlignmentCenter,
		g_sSimHeiFont,POSX(28));
	pLabTxtServQQ->setPosition(ccp(POSX(90),POSX(26)));
	pLabTxtServQQ->setColor(ccc3(12,233,25));
	pServQQBack->addChild(pLabTxtServQQ);

	CCLabelTTF * pLabTxtServQQContent = CCLabelTTF::labelWithString(
		pContent,
		CCSizeMake(POSX(180),POSX(50)),CCTextAlignmentCenter,
		g_sSimHeiFont,POSX(28));
	pLabTxtServQQContent->setPosition(ccp(POSX(240), POSX(26)));
	pLabTxtServQQ->setColor(ccc3(12,233,25));

	pServQQBack->addChild(pLabTxtServQQContent);
	pServQQBack->setTag(TAG_SER_QQ);
	//pServQQBack->setPosition(ccp(POSX(635),POSX(180))); 
	pServQQBack->setPosition(POS(/*ccp((300), (5))*/ccp((320), (80)) ,  ScaleUtil::CENTER_BOTTOM)); 
	pServQQBack->setOpacity(0);
	this->addChild(pServQQBack);
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_server.plist");
}

void LoginServer::visit()
{
	CCUIListView * pListView = (CCUIListView *)_pServNewListView->getChildByTag(ServerNewListView::TAG_LIST);
	if (pListView)
	{
		pListView->setWorldSpaceLeftBottomPoint(ccp(this->getPosition().x + pListView->getPosition().x + _pServNewListView->getPosition().x,
			this->getPosition().y + _pServNewListView->getPosition().y + pListView->getPosition().y));
	}

	CCLayer::visit();
}

void LoginServer::loadItems()
{
	this->setAnchorPoint(CCPointZero);
	this->setIsRelativeAnchorPoint(true);

	// Add frame background.
//	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_server_new.plist");
	CCSprite *pServerBackgroundSprite = new CCSprite;
	if(pServerBackgroundSprite)
	{
		if ( pServerBackgroundSprite->initWithSpriteFrameName("new_res/loginserverbgnew.png"))
		{
			pServerBackgroundSprite->setAnchorPoint(CCPointZero);
			pServerBackgroundSprite->setPosition(POS(ccp(92, 80), ScaleUtil::CENTER_BOTTOM));
			pServerBackgroundSprite->setOpacity(245);
            pServerBackgroundSprite->setTag(Tag_Login_Server_Bg);
			this->addChild(pServerBackgroundSprite);
		}
		pServerBackgroundSprite->release();
		//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_server.plist");
	}

	// add server list
	loadListView();

	// Add comfirm button
#if ( /*CC_TARGET_PLATFORM == CC_PLATFORM_WIN32*/ 1)
	/*
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button3_0.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button3_1.png");
		CCSprite *pSelectdSprite = CCSprite::spriteWithSpriteFrameName("button3_2.png");
		if(pNormalSprite && pPressedSprite && pSelectdSprite)
		{
			CCMenuItemSprite *pRegMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				pSelectdSprite,
				this,
				//menu_selector(LoginServer::onServerConfirmMenuClick));
				menu_selector(LoginServer::onNewServerConfirmMenuClick));
			pRegMenuItem->setAnchorPoint(CCPointZero);
			pRegMenuItem->setScale(1.0f);
			pRegMenuItem->setPosition( POS(ccp((420 + 320), (200 -125)), ScaleUtil::CENTER) );
			//pRegMenuItem->setIsEnabled(false);
			pRegMenuItem->setTag(TAG_MENU_CONFIRM_IMG);
			CCMenu* pRegMenu = CCMenu::menuWithItems(pRegMenuItem, NULL);
			pRegMenu->setPosition( CCPointZero );
			pRegMenu->setTag(TAG_MENU_CONFIRM);
			pRegMenu->setTouchLayer(_pServNewListView->getListTouchPri() - 1);
			this->addChild(pRegMenu);

			CCSize size = pNormalSprite->getContentSize();
			CCLabelTTF* pTitleLabelReg = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG018").c_str(),
				CCSizeMake(POSX(168), POSX(32)), 
				CCTextAlignmentCenter, 
				g_sSimHeiFont,
				POSX(32));
			pTitleLabelReg->setColor(ccc3(255, 255, 0));
			pTitleLabelReg->setPosition( ccp(size.width/2 , size.height/2) );
			pRegMenuItem->addChild(pTitleLabelReg);
		}
	}
	*/
	
	// Add go back button.
	{
		/*
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
		if(pNormalSprite && pPressedSprite)
		{
			CCMenuItemSprite *pServMenuItem = CCMenuItemSprite::itemFromNormalSprite(
				pNormalSprite,
				pPressedSprite,
				this,
				menu_selector(LoginServer::onBackMenuClick));
			pServMenuItem->setAnchorPoint(CCPointZero);
			pServMenuItem->setScale(1.3f);
			pServMenuItem->setPosition( POS(ccp((420), (100)), ScaleUtil::CENTER) );
			CCMenu* pServMenu = CCMenu::menuWithItems(pServMenuItem, NULL);
			//if (g_pLoginManage->getIs91Platform())
			//{
				pServMenu->setIsVisible(false);
			//}
	
			pServMenu->setPosition( CCPointZero );
			this->addChild(pServMenu);
		}
		*/
		
		CCLabelTTF * pLabel = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG043").c_str() , 
			CCSizeMake(POSX(270) , POSX(45)) , 
			CCTextAlignmentLeft , 
			"Arial" , 
			POSX(42));
		pLabel->setColor(ccc3(255,215,0));
		LHMenuItemLabel * pBackMenuItem = new LHMenuItemLabel();
		pBackMenuItem->initWithLabel(pLabel , 
			this,
			menu_selector(LoginServer::onBackMenuClick),
			POSX(42),
			POSX(1),
			ccc3(0,0,0) , 0 ,true , POSX(2));
		pBackMenuItem->setPosition( POS(ccp(150, 40), ScaleUtil::CENTER_BOTTOM) );
		CCMenu* pBackMenu = CCMenu::menuWithItems(pBackMenuItem, NULL);
		pBackMenuItem->release();
		pBackMenu->setPosition( CCPointZero );
		pBackMenu->setTouchLayer(-1301);
		this->addChild(pBackMenu);

	}
	

	CCLabelTTF* pTitleLabelServ = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("LG015").c_str(),
		CCSizeMake(POSX(128), POSX(32)), 
		CCTextAlignmentLeft, 
		g_sSimHeiFont, 
		POSX(32));
	pTitleLabelServ->setColor(ccc3(255, 255, 0));
	pTitleLabelServ->setAnchorPoint(CCPointZero);
	pTitleLabelServ->setIsRelativeAnchorPoint(true);
	pTitleLabelServ->setPosition( POS(ccp((454), (114)), ScaleUtil::CENTER_BOTTOM) );
	this->addChild(pTitleLabelServ);
    //if (g_pLoginManage->getIs91Platform())
	//{
	pTitleLabelServ->setIsVisible(false);
	//}

	// last login server
	{
		CCLabelTTF * pLabelLast = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("WLC007").c_str() , CCSizeMake(POSX(320) , POSX(36)) , CCTextAlignmentLeft , "Arial" , POSX(26));
		pLabelLast->setPosition( POS(ccp(310, 498), ScaleUtil::CENTER_BOTTOM) );
		pLabelLast->setColor(ccc3(233 , 173 ,25));
		this->addChild(pLabelLast , 1);

		CCLabelTTF * pLabelLastTxt = CCLabelTTF::labelWithString("" , CCSizeMake(POSX(320) , POSX(36)) , CCTextAlignmentLeft , "Arial" , POSX(24));
		pLabelLastTxt->setPosition( POS(ccp(435, 498), ScaleUtil::CENTER_BOTTOM) );
		pLabelLastTxt->setColor(ccc3(233 , 233 ,233));
		pLabelLastTxt->setTag(TAG_Last_Server);
		this->addChild(pLabelLastTxt , 1);
	}

	// recommended server
	{
		CCLabelTTF * pLabelRecomm = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("WLC008").c_str() , CCSizeMake(POSX(320) , POSX(36)) , CCTextAlignmentLeft , "Arial" , POSX(24));
		pLabelRecomm->setPosition( POS(ccp(675, 498), ScaleUtil::CENTER_BOTTOM) );
		pLabelRecomm->setColor(ccc3(233 , 173 ,25));
		this->addChild(pLabelRecomm , 1);

		CCLabelTTF * pLabelRecommTxt = CCLabelTTF::labelWithString("" , CCSizeMake(POSX(320) , POSX(36)) , CCTextAlignmentLeft , "Arial" , POSX(24));
		pLabelRecommTxt->setPosition( POS(ccp(790, 498), ScaleUtil::CENTER_BOTTOM) );
		pLabelRecommTxt->setColor(ccc3(233 , 233 ,233));
		pLabelRecommTxt->setTag(TAG_Recommended_Server);
		this->addChild(pLabelRecommTxt , 1);
		//
		std::vector<ServerListVo> *pServList = &g_pLoginManage->getServerList();
		if (pServList && !pServList->empty())
		{
			setRecommendedServer((*pServList)[0].servName);
		}
		
	}
	/*
	// selected server
	{
		CCLabelTTF * pLabelSelected = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("WLC009").c_str() , CCSizeMake(POSX(320) , POSX(36)) , CCTextAlignmentLeft , "Arial" , POSX(24));
		pLabelSelected->setPosition( POS(ccp(490, 100), ScaleUtil::CENTER) );
		pLabelSelected->setColor(ccc3(233 , 173 ,25));
		this->addChild(pLabelSelected , 1);

		CCLabelTTF * pLabelSelectedTxt = CCLabelTTF::labelWithString("" , CCSizeMake(POSX(320) , POSX(36)) , CCTextAlignmentLeft , "Arial" , POSX(24));
		pLabelSelectedTxt->setPosition( POS(ccp(630, 100), ScaleUtil::CENTER) );
		pLabelSelectedTxt->setColor(ccc3(12 , 233 ,25));
		pLabelSelectedTxt->setTag(TAG_Selected_Server);
		this->addChild(pLabelSelectedTxt , 1);
		}
		*/
#endif
}

void LoginServer::loadListView()
{
	/*
	if (!_pAeraListView)
	{
		_pAeraListView = new AreaListView();
		if (_pAeraListView&&_pAeraListView->init())
		{
			//_pAeraListView->setPosition(CCPOINT_AREA_LIST);
			//Doyagn 20120822
			//_pAeraListView->setPosition(ccp(POSX(120),POSX(160)));
			_pAeraListView->setPosition(POS(ccp(120, 160), ScaleUtil::CENTER_BOTTOM));
			_pAeraListView->setAnchorPoint(CCPointZero);

			CCUIListView * pListView = (CCUIListView *)_pAeraListView->getChildByTag(AreaListView::TAG_LIST);
			if (pListView)
			{
				pListView->setWorldSpaceLeftBottomPoint(ccp(this->getPosition().x + pListView->getPosition().x + _pAeraListView->getPosition().x,
			this->getPosition().y + _pAeraListView->getPosition().y + pListView->getPosition().y));
			}
			_pAeraListView->setTag(TAG_AREA_LIST);
			_pAeraListView->setIsTouchEnabled(false);
			this->addChild(_pAeraListView,Z_LISTVIEW);
//            _pAeraListView->release();
			_pAeraListView->setIsVisible(false);
		}
	}

	if (!_pServListView)
	{
		_pServListView = new ServerListView();
		if (_pServListView&&_pServListView->init())
		{
			//_pServListView->setPosition(CCPOINT_AREA_LIST);
			//Doyagn 20120822
			_pServListView->setPosition(POS(ccp(630, 160), ScaleUtil::CENTER_BOTTOM));
			//_pServListView->setPosition(ccp(POSX(630),POSX(160)));
			_pServListView->setAnchorPoint(CCPointZero);

			CCUIListView * pListView = (CCUIListView *)_pServListView->getChildByTag(AreaListView::TAG_LIST);
			if (pListView)
			{
				pListView->setWorldSpaceLeftBottomPoint(ccp(this->getPosition().x + pListView->getPosition().x + _pServListView->getPosition().x,
					this->getPosition().y + _pServListView->getPosition().y + pListView->getPosition().y));
			}
			_pServListView->setTag(TAG_SERV_LIST);
			_pServListView->setIsTouchEnabled(false);
			this->addChild(_pServListView,Z_LISTVIEW);
            _pServListView->release();
			_pServListView->setIsVisible(false);
		}
	}
	*/

	// new UI
	if (!_pServNewListView)
	{
		_pServNewListView = new ServerNewListView();
		if (_pServNewListView&&_pServNewListView->init())
		{
			//_pServListView->setPosition(CCPOINT_AREA_LIST);
			//Doyagn 20120822
			_pServNewListView->setPosition(POS(ccp(120, 160), ScaleUtil::CENTER_BOTTOM));
			//_pServListView->setPosition(ccp(POSX(630),POSX(160)));
			_pServNewListView->setAnchorPoint(CCPointZero);

			CCUIListView * pListView = (CCUIListView *)_pServNewListView->getChildByTag(ServerNewListView::TAG_LIST);
			if (pListView)
			{
				pListView->setWorldSpaceLeftBottomPoint(ccp(this->getPosition().x + pListView->getPosition().x + _pServNewListView->getPosition().x,
					this->getPosition().y + _pServNewListView->getPosition().y + pListView->getPosition().y));
			}
			_pServNewListView->setTag(TAG_SERV_LIST);
			_pServNewListView->setIsTouchEnabled(false);
			this->addChild(_pServNewListView,Z_LISTVIEW + 1);
			_pServNewListView->release();
		}
	}

}

void LoginServer::onBackMenuClick(CCObject *pSender)
{	
	LoginView * pLoginView = (LoginView *)this->getParent();	
	if (pLoginView)
	{
		pLoginView->getChildByTag(LoginView::TAG_ServersLayer)->setPosition(ccp(0,_winSize.height));
		pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
		
	}

	if (!pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer_new))
	{
		//pLoginView->addChild(pLoginView->_pLoginMainLayer);
		pLoginView->addChild(pLoginView->_pNewLoginMainLayer);
	} 

	SoundManager::Instance()->playButtonEffectSound();
}

void LoginServer::setDefaultServerAndPort()
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
				g_pLoginManage->setServIPAddr(pSerListVo->ip);
				g_pLoginManage->setServIPPort(pSerListVo->port);
				g_pLoginManage->setServState(pSerListVo->state);
			}
			LoginView * pLoginView = (LoginView *)this->getParent();
			if (pLoginView)
			{
				pLoginView->setSelectedArea(pSerListVo->areaName);
				pLoginView->setSelectedServ(pSerListVo->servName);
			}
		}
	}
}  

void LoginServer::onServerConfirmMenuClick(CCObject *pSender)
{
	SoundManager::Instance()->playButtonEffectSound();

	/*
	AreaListView * pAreaListView = (AreaListView *)this->getChildByTag(TAG_AREA_LIST);
	if (!pAreaListView){return;}
	ServerListView * pServListView = (ServerListView *)this->getChildByTag(TAG_SERV_LIST);
	if (!pServListView){return;}
	*/

	if (!g_pLoginManage){return;}

	/*
	if ( !pAreaListView->getIsAreaSelected() && !pServListView->getIsServSelected() )
	{
		setDefaultServerAndPort();
	}
	*/

	//
	saveFavorServInfo();

	//
	LoginView * pLoginView = (LoginView *)this->getParent();
	if(!pLoginView){return;}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (g_pLoginManage->getServState() == -1)
    {
        char path[256] = {0};
        sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , g_pLoginManage->_CurServListVo.areaName.c_str() , g_pLoginManage->_CurServListVo.servName.c_str());
        CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
        return;
    }
    
    LoginMain * pLoginMain = pLoginView->_pLoginMainLayer;
    if (pLoginMain)
    {
        pLoginMain->parseUrlAndLogin();
		//
		saveFavorServInfo();

		//
    }
    bool result = GateServerSocket::getInstance()->connect(g_pLoginManage->getServIPAddr()/*"113.107.110.141"*/, /*83*/g_pLoginManage->getServIPPort());//"113.107.110.141", 83     115.238.73.228 121   
    if (result)
    {
        g_pLoginManage->gSocketConnectHandler();
        
        if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
        {
            pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
        }

		// Doyang 20121130
		callPlatformAnaly(g_pLoginManage->getExchargeServerId().c_str());	
    }
    else
    {
        CCMessageBox(ValuesUtil::Instance()->getString("LG023").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
    }
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    
    if (g_pLoginManage->getServState() == -1)
    {
        char path[256] = {0};
        sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , g_pLoginManage->_CurServListVo.areaName.c_str() , g_pLoginManage->_CurServListVo.servName.c_str());
        CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
        return;
    }
    
    LoginMain * pLoginMain = pLoginView->_pLoginMainLayer;
    if (pLoginMain)
    {
        if (!pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer))
        {
            pLoginView->addChild(pLoginMain);
        }			
        pLoginMain->setAreaText();
    }
    
    if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
    {
        pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
    } 
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (!g_pLoginManage->getIs91Platform())
	{
		if (g_pLoginManage->getServState() == -1)
		{
			char path[256] = {0};
			sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , g_pLoginManage->_CurServListVo.areaName.c_str() , g_pLoginManage->_CurServListVo.servName.c_str());
			CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
			return;
		}
        
		LoginMain * pLoginMain = pLoginView->_pLoginMainLayer;
		if (pLoginMain)
		{
			if (!pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer))
			{
				pLoginView->addChild(pLoginMain);
			}			
			pLoginMain->setAreaText();
		}
        
		if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
		{
			pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
		}
		
	}
	else
	{
		if (g_pLoginManage->getServState() == -1)
		{
			char path[256] = {0};
			sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , g_pLoginManage->_CurServListVo.areaName.c_str() , g_pLoginManage->_CurServListVo.servName.c_str());
			CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
			return;
		}
        
        //Doyang 20120827
        LoginMain * pLoginMain = pLoginView->_pLoginMainLayer;
		if (pLoginMain)
		{
            pLoginMain->parseUrlAndLogin();
			//
			saveFavorServInfo();

			//
        }
		bool result = GateServerSocket::getInstance()->connect(g_pLoginManage->_CurServListVo.ip/*"113.107.110.141"*/, /*83*/g_pLoginManage->_CurServListVo.port);//"113.107.110.141", 83     115.238.73.228 121   
		if (result)
		{
			g_pLoginManage->gSocketConnectHandler();
            
			if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
			{
				pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
			}			
		}
		else
		{
			CCMessageBox(ValuesUtil::Instance()->getString("LG023").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		}
	}
#endif
	/*
	pServListView->setPreSeclecedItem(0);
	pAreaListView->setPreSeclecedItem(0);
	*/
}

void LoginServer::onNewServerConfirmMenuClick(CCObject *pSender)
{
	SoundManager::Instance()->playButtonEffectSound();

	this->stopAllActions();

	/*
	AreaListView * pAreaListView = (AreaListView *)this->getChildByTag(TAG_AREA_LIST);
	if (!pAreaListView){return;}
	ServerListView * pServListView = (ServerListView *)this->getChildByTag(TAG_SERV_LIST);
	if (!pServListView){return;}
	*/

	if (!g_pLoginManage){return;}

	/*
	if ( !pAreaListView->getIsAreaSelected() && !pServListView->getIsServSelected() )
	{
		setDefaultServerAndPort();
	}
	*/

	//
	saveFavorServInfo();

	//
	LoginView * pLoginView = (LoginView *)this->getParent();
	if(!pLoginView){return;}
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    if (g_pLoginManage->getServState() == -1)
    {
        char path[256] = {0};
        sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , g_pLoginManage->_CurServListVo.areaName.c_str() , g_pLoginManage->_CurServListVo.servName.c_str());
        CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
        return;
    }
    
	LoginNewMain * pLoginMain = pLoginView->_pNewLoginMainLayer;
	if (pLoginMain)
	{
		if (!pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer_new))
		{
			pLoginView->addChild(pLoginMain);
		}			
		pLoginMain->setAreaText();
	}

	if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
	{
		pLoginView->getChildByTag(LoginView::TAG_ServersLayer)->setPosition(ccp(0,_winSize.height));
		pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
	} 

	/*
    LoginNewMain * pLoginMain = pLoginView->_pNewLoginMainLayer;
    if (pLoginMain)
    {
        pLoginMain->parseUrlAndLogin();
		//
		saveFavorServInfo();

		//
    }
	
    bool result = GateServerSocket::getInstance()->connect(g_pLoginManage->getServIPAddr(), g_pLoginManage->getServIPPort());
    if (result)
    {
        g_pLoginManage->gSocketConnectHandler();
        
		if (pLoginMain)
		{
			if (!pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer_new))
			{
				pLoginView->addChild(pLoginMain);
			}			
			pLoginMain->setAreaText();
		}

        if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
        {
			pLoginView->getChildByTag(LoginView::TAG_ServersLayer)->setPosition(ccp(0,_winSize.height));
            pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
        }

		// Doyang 20121130
		callPlatformAnaly(g_pLoginManage->getExchargeServerId().c_str());	
    }
    else
    {
        CCMessageBox(ValuesUtil::Instance()->getString("LG023").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
    }
	*/
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
    
    if (g_pLoginManage->getServState() == -1)
    {
        char path[256] = {0};
        sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , g_pLoginManage->_CurServListVo.areaName.c_str() , g_pLoginManage->_CurServListVo.servName.c_str());
        CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
        return;
    }
    
    LoginNewMain * pLoginMain = pLoginView->_pNewLoginMainLayer;
    if (pLoginMain)
    {
        if (!pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer_new))
        {
            pLoginView->addChild(pLoginMain);
        }			
        pLoginMain->setAreaText();
    }
    
    if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
    {
		pLoginView->getChildByTag(LoginView::TAG_ServersLayer)->setPosition(ccp(0,_winSize.height));
		pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
    } 
#endif
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    if (!g_pLoginManage->getIs91Platform())
	{
		if (g_pLoginManage->getServState() == -1)
		{
			char path[256] = {0};
			sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , g_pLoginManage->_CurServListVo.areaName.c_str() , g_pLoginManage->_CurServListVo.servName.c_str());
			CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
			return;
		}
        
		LoginNewMain * pLoginMain = pLoginView->_pNewLoginMainLayer;
		if (pLoginMain)
		{
			if (!pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer_new))
			{
				pLoginView->addChild(pLoginMain);
			}			
			pLoginMain->setAreaText();
		}
        
		if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
		{
			pLoginView->getChildByTag(LoginView::TAG_ServersLayer)->setPosition(ccp(0,_winSize.height));
			pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
		}
		
	}
	else
	{
		if (g_pLoginManage->getServState() == -1)
		{
			char path[256] = {0};
			sprintf(path,ValuesUtil::Instance()->getString("LG039").c_str() , g_pLoginManage->_CurServListVo.areaName.c_str() , g_pLoginManage->_CurServListVo.servName.c_str());
			CCMessageBox(path, ValuesUtil::Instance()->getString("LG033").c_str());
			return;
		}
        
		LoginNewMain * pLoginMain = pLoginView->_pNewLoginMainLayer;
		if (pLoginMain)
		{
			if (!pLoginView->getChildByTag(LoginView::TAG_UserPwdLayer_new))
			{
				pLoginView->addChild(pLoginMain);
			}			
			pLoginMain->setAreaText();
		}

		if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
		{
			pLoginView->getChildByTag(LoginView::TAG_ServersLayer)->setPosition(ccp(0,_winSize.height));
			pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
		}

        //Doyang 20120827
		/*
        LoginNewMain * pLoginMain = pLoginView->_pNewLoginMainLayer;
		if (pLoginMain)
		{
            pLoginMain->parseUrlAndLogin();
			//
			saveFavorServInfo();

			//
        }
		bool result = GateServerSocket::getInstance()->connect(g_pLoginManage->_CurServListVo.ip, g_pLoginManage->_CurServListVo.port);
		if (result)
		{
			g_pLoginManage->gSocketConnectHandler();
            
			if (pLoginView->getChildByTag(LoginView::TAG_ServersLayer))
			{
				pLoginView->getChildByTag(LoginView::TAG_ServersLayer)->setPosition(ccp(0,_winSize.height));
				pLoginView->removeChildByTag(LoginView::TAG_ServersLayer,false);
			}			
		}
		else
		{
			CCMessageBox(ValuesUtil::Instance()->getString("LG023").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
		}
		*/
	}
#endif
	/*
	pServListView->setPreSeclecedItem(0);
	pAreaListView->setPreSeclecedItem(0);
	*/
}

void LoginServer::EnableConfirmButton(bool var)
{
	CCMenu * pConfirmButton = (CCMenu *)this->getChildByTag(TAG_MENU_CONFIRM);
	if (pConfirmButton)
	{
		CCMenuItemImage * pMenuImg = (CCMenuItemImage *)pConfirmButton->getChildByTag(TAG_MENU_CONFIRM_IMG);
		if (pMenuImg)
		{
			pMenuImg->setIsEnabled(var);
		}		
	}	
}

void LoginServer::resetListView()
{
	/*
	// area
	if (_pAeraListView)
	{
        _pAeraListView->refresh();
	}

	// server list
	if (_pServListView)
	{
        _pServListView->refresh();
	}
	*/

	// new server list
	if (_pServNewListView)
	{
		_pServNewListView->refresh();
	}
}

void LoginServer::saveFavorServInfo()
{
	std::string strInfo("");
	
	//strInfo.append(pLoginView ? pLoginView->getSelectedArea() : "");
	strInfo.append(g_pLoginManage->_CurServListVo.areaName);
	strInfo.append(";");
	//strInfo.append(pLoginView ? pLoginView->getSelectedServ() : "");
	strInfo.append(g_pLoginManage->_CurServListVo.servName);
	strInfo.append(";");

	//strInfo.append(g_pLoginManage->getServIPAddr());
	strInfo.append(g_pLoginManage->_CurServListVo.ip);
	strInfo.append(";");

	char path[64] = {0};
	//sprintf(path,"%d",g_pLoginManage->getServIPPort());
	sprintf(path , "%d", g_pLoginManage->_CurServListVo.port);
	strInfo.append(path);
	strInfo.append(";");

	memset(path,0,sizeof(path));
	//sprintf(path,"%d",g_pLoginManage->getServState());
	sprintf(path,"%d",g_pLoginManage->_CurServListVo.state);
	strInfo.append(path);
	strInfo.append(";");

	//strInfo.append(g_pLoginManage->getExchargeServerId());
	strInfo.append(g_pLoginManage->_CurServListVo.exchargeServerId);
	
	//save to file
#if (CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM || CC_PLATFORM_IOS == CC_TARGET_PLATFORM)
	std::string filePath = CCFileUtils::fullPathFromRelativePath("assets/config/config_bak/server.dat");
#else
	std::string filePath = CCFileUtils::fullPathFromSDCard("assets/config/config_bak/server.dat");
#endif

	FILE * pFile = fopen(filePath.c_str(),"wb+");
	if (pFile)
	{
		fwrite(strInfo.c_str(),1,strInfo.length(),pFile);
		fclose(pFile);
	}
}

void LoginServer::setLastLoginServer(std::string str)
{
	CCLabelTTF * pLabel = (CCLabelTTF *)this->getChildByTag(TAG_Last_Server);
	if (pLabel)
	{
		pLabel->setString(str.c_str());
	}
}

void LoginServer::setRecommendedServer(std::string str)
{
	CCLabelTTF * pLabel = (CCLabelTTF *)this->getChildByTag(TAG_Recommended_Server);
	if (pLabel)
	{
		pLabel->setString(str.c_str());
	}
}

void LoginServer::setSelectedServer(std::string str)
{
	CCLabelTTF * pLabel = (CCLabelTTF *)this->getChildByTag(TAG_Selected_Server);
	if (pLabel)
	{
		pLabel->setString(str.c_str());
		if (str.empty())
		{
			enableConfirmButton(false);
		}		
	}
}

void LoginServer::enableConfirmButton(bool var)
{
	CCMenu* pEnterMenu = (CCMenu *)this->getChildByTag(TAG_MENU_CONFIRM);
	if (pEnterMenu)
	{
		CCMenuItemSprite *pEnterMenuItem = (CCMenuItemSprite *)pEnterMenu->getChildByTag(TAG_MENU_CONFIRM_IMG);
		if (pEnterMenuItem)
		{
			pEnterMenuItem->setIsEnabled(var);
		}		
	}
}

LoginServer::~LoginServer()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_server_new.plist");
 //	CCSprite* pS = (CCSprite*)this->getChildByTag(Tag_Login_Server_Bg);
 //	if (pS)
 //	{
 //		pS->removeFromParentAndCleanup(true);
	//}
	this->removeAllChildrenWithCleanup(true);

	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_server_new.pvr.ccz");

	CCTexture2D* pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/res_login_server.pvr.ccz");
	if (pText && (pText->retainCount()==1))
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_server.pvr.ccz");
}