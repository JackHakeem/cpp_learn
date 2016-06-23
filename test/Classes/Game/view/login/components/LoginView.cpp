#include "LoginView.h"
#include "utils/ScaleUtil.h"
#include "utils/ValuesUtil.h"
#include "LoginMain.h"
#include "LoginRegister.h"
#include "LoginCreateRole.h"
#include "LoginServer.h"
#include "events/GameDispatcher.h"
#include "view/scene/components/MainScene.h"
#include "MessageInfoBox.h"
#include "view/scene/components/LoginScene.h"
#include "LoginManage.h"
#include "manager/LayerManager.h"
#include "manager/ConnectionManager.h"
#include "manager/GlobalManage.h"
#include "LoginNewMain.h"

LoginView::LoginView()
{
	_pLoginMainLayer = 0;
	_pNewLoginMainLayer = 0;
	_pRegisterLayer = 0;
	_pServersLayer = 0;
	_pCreateRoleLayer = 0;
	_pos = 0;
	setSelectedArea("");
	setSelectedServ("");
	if (!LayerManager::windowLayer)
	{
		LayerManager::windowLayer = new WindowLayer();
		LayerManager::windowLayer->init();
	}
}

bool LoginView::init()
{
	if(!CCLayer::init())
	{
		return false;
	}

	_winSize = CCDirector::sharedDirector()->getWinSize();

	CCLog("LoginView::test step 1");
	addEventListeners();	

	CCLog("LoginView::test step 2");

	addBackGround();

	CCLog("LoginView::test step 3");

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	//addLoginMainLayer();
	addNewLoginMainLayer();
#else

	CCLog("LoginView::test step 4");
	addNewLoginMainLayer();
#endif	

	//addRegisterLayer();

	CCLog("LoginView::test step 5");
	addServerListLayer();

	CCLog("LoginView::test step 6");
	addCreateRoleLayer();

	CCLog("LoginView::test step 7");
	return true;
}

void LoginView::addEventListeners()
{
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::LOGIN_CREATEROLE,
		this,
		callfuncND_selector(LoginView::onLoginCreateRole));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::LOGIN_UNREGISTER,
		this,
		callfuncND_selector(LoginView::onLoginUnRegister));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::LOGIN_VERSIONERR,
		this,
		callfuncND_selector(LoginView::onLoginVersionErr));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::LOGIN_FORBBIDEN,
		this,
		callfuncND_selector(LoginView::onLoginForbidden));
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::LOGIN_SUCCESS,
		this,
		callfuncND_selector(LoginView::onLoginSuccess));
}

void LoginView::addBackGround()
{
	// Add fullscreen background.
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//jae note
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_bg.plist");
	CCSprite *pBackgroundSprite = new CCSprite();
	if(pBackgroundSprite && pBackgroundSprite->initWithFile( "assets/ui/login/loginnewmain/back.jpg" ))
	{
		float scaleFactory = CCDirector::sharedDirector()->getContentScaleFactor();



		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		float orginScale = (float) 960 / (float) 640;
		float currentScale = winSize.width / winSize.height;

		if(orginScale > currentScale)
		{
			pBackgroundSprite->setScaleY(orginScale / currentScale);
		}
		else if(orginScale < currentScale)
		{
			pBackgroundSprite->setScaleX(currentScale / orginScale);
		}
		else
		{

		}
		pBackgroundSprite->setAnchorPoint(ccp(0.5, 0.5));
		pBackgroundSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        pBackgroundSprite->setTag( TAG_LoginBg1 );
		this->addChild(pBackgroundSprite,0);
		pBackgroundSprite->release();
	}

	// cloud
	{
		CCSprite * pSpriteCloud1 = new CCSprite();
		if (pSpriteCloud1 && pSpriteCloud1->initWithFile("assets/ui/login/loginnewmain/cloud.png"))
		{
			pSpriteCloud1->setPosition(ccp(POSX(100), _winSize.height - POSX(100)));
			pSpriteCloud1->setTag(TAG_Cloud1);
			this->addChild(pSpriteCloud1 , 1);
			pSpriteCloud1->release();
			runMyAction(pSpriteCloud1 , getMyAction(ActType_Cloud1));
		}

		CCSprite * pSpriteCloud2 = new CCSprite();
		if (pSpriteCloud2 && pSpriteCloud2->initWithFile("assets/ui/login/loginnewmain/cloud.png"))
		{
			pSpriteCloud2->setPosition(ccp(_winSize.width - POSX(200) , POSX(240)));
			pSpriteCloud2->setTag(TAG_Cloud2);
			pSpriteCloud2->setScale(0.4);
			this->addChild(pSpriteCloud2 , 3);
			pSpriteCloud2->release();
			runMyAction(pSpriteCloud2 , getMyAction(ActType_Cloud2));
		}
	}

	CCNode* p = this->getChildByTag(TAG_LoginBg1);

	CCSprite *pBackgroundSprite1 = new CCSprite;
	if( pBackgroundSprite1 && pBackgroundSprite1->initWithFile("assets/ui/login/loginnewmain/front.png"))
	{
		pBackgroundSprite1->setAnchorPoint(CCPointZero);
		//pBackgroundSprite1->setPosition(POS(ccp(92, 80), ScaleUtil::CENTER));
		pBackgroundSprite1->setOpacity(225);
		pBackgroundSprite1->setAnchorPoint(ccp(0.5, 0.5));
		pBackgroundSprite1->setPosition(ccp(winSize.width / 2, winSize.height / 2));
		pBackgroundSprite1->setTag(TAG_LoginBg2);
		this->addChild(pBackgroundSprite1,2);
		pBackgroundSprite1->release();

		// scale

		float scaleFactory = CCDirector::sharedDirector()->getContentScaleFactor();
		float orginScale = (float) 960 / (float) 640;
		float currentScale = winSize.width / winSize.height;

		if(orginScale > currentScale)
		{
			pBackgroundSprite1->setScaleY(orginScale / currentScale);
		}
		else if(orginScale < currentScale)
		{
			pBackgroundSprite1->setScaleX(currentScale  / orginScale);
		}
		else
		{

		}
		//pBackgroundSprite->setScale(0.85);

		//runMyAction(pBackgroundSprite , getMyAction(ActType_LRMove));
	}
	//CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/login/res_login_bg.plist");
}

void LoginView::addLoginMainLayer()
{
	if (!_pLoginMainLayer)
	{
		_pLoginMainLayer = new LoginMain();
		if(_pLoginMainLayer && _pLoginMainLayer->init())
		{
			_pLoginMainLayer->setAnchorPoint(CCPointZero);
			_pLoginMainLayer->setPosition(CCPointZero);
			_pLoginMainLayer->setIsRelativeAnchorPoint(true);
			_pLoginMainLayer->setTag(TAG_UserPwdLayer);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID )
			_pLoginMainLayer->setIsVisible(false);
#endif
			this->addChild(_pLoginMainLayer,10);
            _pLoginMainLayer->setIsVisible(true);//kevin0917
			//_pLoginMainLayer->release();
		}
	}

	//jae 20120/831
	//g_pGlobalManage->loadUIImages();
}

void LoginView::addNewLoginMainLayer()
{
	if (!_pNewLoginMainLayer)
	{
		_pNewLoginMainLayer = new LoginNewMain();
		if(_pNewLoginMainLayer && _pNewLoginMainLayer->init())
		{
			_pNewLoginMainLayer->setAnchorPoint(CCPointZero);
			_pNewLoginMainLayer->setPosition(CCPointZero);
			_pNewLoginMainLayer->setIsRelativeAnchorPoint(true);
			_pNewLoginMainLayer->setTag(TAG_UserPwdLayer_new);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32  )
			_pNewLoginMainLayer->setIsVisible(true);
#endif
			this->addChild(_pNewLoginMainLayer,10);
			//_pLoginMainLayer->setIsVisible(true);//kevin0917
			//pNewLoginMainLayer->release();
		}
	}

	//jae 20120/831
	//g_pGlobalManage->loadUIImages();
}

void LoginView::addRegisterLayer()
{
	if (!_pRegisterLayer)
	{
		_pRegisterLayer = new LoginRegister();
		if(_pRegisterLayer && _pRegisterLayer->init())
		{
			_pRegisterLayer->setAnchorPoint(CCPointZero);
			_pRegisterLayer->setPosition(CCPointZero);
			_pRegisterLayer->setIsRelativeAnchorPoint(true);
			_pRegisterLayer->setTag(TAG_RegisterLayer);
			//this->addChild(_pRegisterLayer,5);
		}
	}
	else
	{
		this->addChild(_pRegisterLayer);
	}
}

void LoginView::addServerListLayer()
{
	if (!_pServersLayer)
	{
		_pServersLayer = new LoginServer();
		if(_pServersLayer && _pServersLayer->init())
		{
			_pServersLayer->setAnchorPoint(CCPointZero);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
			//_pServersLayer->setPosition(CCPointZero);
			_pServersLayer->setPosition(ccp(0,_winSize.height));
#else
			//_pServersLayer->setPosition(CCPointZero);
			_pServersLayer->setPosition(ccp(0,_winSize.height));
#endif
			_pServersLayer->setIsRelativeAnchorPoint(true);
			_pServersLayer->setTag(TAG_ServersLayer);
			//this->addChild(_pServersLayer,0);

			/*
			pAccountTextField->setString("longhui2");
			pAccountTextField->setContentSize(CCSizeMake(POSX(380), POSX(40)));
			pAccountTextField->setAnchorPoint(CCPointZero);
			pAccountTextField->setPosition(POS(ccp(226, 376), ScaleUtil::CENTER));
			pAccountTextField->attachWithIME();
		//	pAccountTextField->setString("Doyang1");

			pAccountTextField->setTag(TEXTFIELD_ACCOUNT);
			pLoginFrameLayer->addChild(pAccountTextField);
			*/
		}
	}
	else
	{
		this->addChild(_pServersLayer , 10);
	}
}

void LoginView::addCreateRoleLayer()
{
	if (!_pCreateRoleLayer)
	{
		_pCreateRoleLayer = new LoginCreateRole();
		if(_pCreateRoleLayer && _pCreateRoleLayer->init())
		{
			_pCreateRoleLayer->setAnchorPoint(CCPointZero);
			_pCreateRoleLayer->setPosition(CCPointZero);
			_pCreateRoleLayer->setIsRelativeAnchorPoint(true);
			_pCreateRoleLayer->setTag(TAG_CreateRoleLayer);
			//this->addChild(_pCreateRoleLayer,8);
		}
	}
}

void LoginView::onLoginCreateRole( CCNode *pNode, void *data )
{
#if ( CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 )
	//this->removeChildByTag(LoginView::TAG_UserPwdLayer,false);
	this->removeChildByTag(LoginView::TAG_UserPwdLayer_new,false);
#else
	this->removeChildByTag(LoginView::TAG_UserPwdLayer_new,false);
#endif
	
    if ( !_pCreateRoleLayer )   return; // Jae note
	if (!this->getChildByTag(LoginView::TAG_CreateRoleLayer))
	{
		this->addChild(_pCreateRoleLayer , 10);
		_pCreateRoleLayer->setTag(LoginView::TAG_CreateRoleLayer);
	}
	
	/*
	CCTextFieldTTF *pRoleNameTextField = (CCTextFieldTTF *)this->_pCreateRoleLayer->getChildByTag(TEXTFIELD_ROLECREATE);
	if(pRoleNameTextField)
	{
		pRoleNameTextField->attachWithIME();
	}
	*/
}

void LoginView::onLoginUnRegister( CCNode *pNode, void *data )
{
//	MessageInfoBox::Instance()->show("unregister",ccc3(12,233,25));
//	clearChilds();
}

void LoginView::onLoginVersionErr( CCNode *pNode, void *data )
{
	CCMessageBox(ValuesUtil::Instance()->getString("LG035").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
//	MessageInfoBox::Instance()->show("VersionErr �r(�s_�t)�q",ccc3(12,233,25));
//	clearChilds();
}

void LoginView::onLoginForbidden( CCNode *pNode, void *data )
{
	CCMessageBox(ValuesUtil::Instance()->getString("LG034").c_str(),ValuesUtil::Instance()->getString("LG033").c_str());
//	MessageInfoBox::Instance()->show("Forbidden",ccc3(12,233,25));
//	clearChilds();
}

void LoginView::onLoginSuccess( CCNode *pNode, void *data )
{
	CCLOG("LoginView::before connect");
	//	clearChilds();
	ConnectionManager::Instance()->run();

	CCLOG("LoginView::before create mainscene");

	MainScene *pScene = MainScene::getInstance();

	CCLOG("LoginView::before init mainscene");

	pScene->init();

	CCLOG("LoginView::before replace scene");

	CCDirector::sharedDirector()->replaceScene(pScene);
	pScene->release();

	g_pGlobalManage->d1 = Timer::millisecondNow();
	//CCDirector::sharedDirector()->pushScene( pScene );
	//ConnectionManager * p = new ConnectionManager();
}

LoginView::~LoginView()
{
	CC_SAFE_DELETE(_pos);
	//jae note:20120718
	if ( _pLoginMainLayer )
	{
		if ( _pLoginMainLayer->getParent() )
			_pLoginMainLayer->removeFromParentAndCleanup(true);

		_pLoginMainLayer->release();
	}
	if ( _pNewLoginMainLayer )
	{
		if ( _pNewLoginMainLayer->getParent() )
			_pNewLoginMainLayer->removeFromParentAndCleanup(true);

		_pNewLoginMainLayer->release();
	}
	if ( _pRegisterLayer )
	{
		if ( _pRegisterLayer->getParent() )
		{
			_pRegisterLayer->removeFromParentAndCleanup(true);
		}
		_pRegisterLayer->release();
	}
	if ( _pServersLayer )
	{
		if ( _pServersLayer->getParent() )
			_pServersLayer->removeFromParentAndCleanup(true);
		_pServersLayer->release();
	}
 	if ( _pCreateRoleLayer )
 	{
 		if ( _pCreateRoleLayer->getParent() )
 			_pCreateRoleLayer->removeFromParentAndCleanup(true);
 		_pCreateRoleLayer->release();
 	}
	
	//
	this->removeAllChildrenWithCleanup(true);

	//jae 20130125
	CCTexture2D* pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/loginnewmain/back.jpg");
	if (pText && (pText->retainCount()==1))
	{
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/loginnewmain/back.jpg");
	}

	pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/loginnewmain/front.png");
	if (pText && (pText->retainCount()==1))
	{
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/loginnewmain/front.png");
	}

	pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/loginnewmain/cloud.png");
	if (pText && (pText->retainCount()==1))
	{
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/loginnewmain/cloud.png");
	}
	
	pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/res_login_server.pvr.ccz");
	if (pText && (pText->retainCount()==1))
	{
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_server.pvr.ccz");
	}

	pText = CCTextureCache::sharedTextureCache()->textureForKey("assets/ui/login/res_login_bg.pvr.ccz");
	if (pText && (pText->retainCount()==1))
	{
		CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/login/res_login_bg.pvr.ccz");
	}

	CCLog( "LoginView release." );	
}

void LoginView::resetPos(CCNode * pTarget,void *pData)
{
	if (!pData)
	{
		return;
	}
	
	CCPoint * pos = (CCPoint *)pData;
	CCSprite * pSpriteCloud1 = (CCSprite *)this->getChildByTag(TAG_Cloud1);
	if (pSpriteCloud1 && pSpriteCloud1->getPosition().x > _winSize.width)
	{
		pSpriteCloud1->setPositionX(pos->x);
	}

	CCSprite * pSpriteCloud2 = (CCSprite *)this->getChildByTag(TAG_Cloud2);
	if (pSpriteCloud2 && pSpriteCloud2->getPosition().x < 0)
	{
		pSpriteCloud2->setPositionX(pos->x);
	}

	CCSprite * pSpriteCloud3 = (CCSprite *)this->getChildByTag(TAG_Cloud3);
	if (pSpriteCloud3 && pSpriteCloud3->getPosition().x < 0)
	{
		pSpriteCloud3->setPositionX(pos->x);
	}
	//CC_SAFE_DELETE(pos);
}

CCAction * LoginView::getMyAction(int type)
{
	CCAction * pAction = 0;
	switch (type)
	{
	case ActType_LRMove:
		{
			CCFiniteTimeAction * pMove1 = CCMoveBy::actionWithDuration(12.0f , ccp(POSX(50) , 0));
			CCFiniteTimeAction * pMove2 = pMove1->reverse(); // CCMoveBy::actionWithDuration(0.1f , ccp(POSX(2) , 0));
			pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pMove1 , pMove2 )) ;
		}
		break;
	case ActType_FallDown:
		{
			CCFiniteTimeAction * pMove1 = CCMoveBy::actionWithDuration(0.5f , ccp(POSX(0) , (-1)*_winSize.height));
			CCFiniteTimeAction * pMove2 = CCMoveBy::actionWithDuration(0.1f , ccp(POSX(0) , POSX(30)));
			CCFiniteTimeAction * pMove3 = pMove2->reverse();
			CCFiniteTimeAction * pMove4 = CCMoveBy::actionWithDuration(0.1f , ccp(POSX(0) , POSX(10)));
			CCFiniteTimeAction * pMove5 = pMove4->reverse();
			pAction = CCSequence::actions(pMove1,pMove2,pMove3,pMove4,pMove5,0);
		}
		break;
	case ActType_Cloud1:
		{
			_pos = new CCPoint(0,0);
			CCFiniteTimeAction * pMove = CCMoveBy::actionWithDuration(0.5f , ccp(POSX(5) , 0));
			CCCallFuncND * pCallBack = CCCallFuncND::actionWithTarget(this , callfuncND_selector(LoginView::resetPos) , (void *)_pos);
			pAction = CCRepeatForever::actionWithAction( CCSequence::actionOneTwo(pMove , pCallBack));
		}
		break;
	case ActType_Cloud2:
		{
			_pos = new CCPoint(_winSize.width - POSX(200) , POSX(240));
			CCFiniteTimeAction * pMove = CCMoveBy::actionWithDuration(0.5f , ccp(POSX(-10) , 0));
			CCCallFuncND * pCallBack = CCCallFuncND::actionWithTarget(this , callfuncND_selector(LoginView::resetPos) , (void *)_pos);
			pAction = CCRepeatForever::actionWithAction( CCSequence::actionOneTwo(pMove , pCallBack));
		}
		break;
	case ActType_Fade1:
		{
			CCActionInterval* pFadeOut = CCFadeOut::actionWithDuration(0.5f);
			pAction = CCSequence::actions(
				pFadeOut,
				CCCallFuncND::actionWithTarget(this , callfuncND_selector(LoginView::doCallback), 0),
				NULL
				);
		}
		break;
	case ActType_Orbit1:
		{
			CCActionInterval* pOrbitAction = CCOrbitCamera::actionWithDuration(1.5f, 0.1f, 0, 90, 88, 0, 0);
			CCActionInterval* pFadeout = CCFadeOut::actionWithDuration(0.2f);
			pAction = CCSequence::actions(
				pOrbitAction,
				CCCallFuncND::actionWithTarget(this , callfuncND_selector(LoginView::doCallback), 0),
				NULL
				);
		}
		break;
	default:
		{

		}
		break;
	}
	return pAction;
}

void LoginView::runMyAction(CCNode * pNode , CCAction * pAction)
{
	if (!pNode || !pAction)
	{
		return;
	}

	pNode->runAction(pAction);	
}

void LoginView::doCallback(CCNode * pNode , void * data)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

	if (_pServersLayer)
	{
		_pServersLayer->onNewServerConfirmMenuClick(0);
	}

#else

	if (_pServersLayer)
	{
		_pServersLayer->onNewServerConfirmMenuClick(0);
	}

#endif
}
