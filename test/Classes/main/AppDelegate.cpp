#include "AppDelegate.h"

#include "cocos2d.h"
#include "view/scene/components/MainScene.h"
#include "utils/findPath/FindPath8.h"
#include "utils/loader/KKAnimationFactory.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/MessageFactoryManager.h"
#include "LoginManage.h"
#include "utils/loader/AnimationManager.h"

#include "socket/network/GateServerSocket.h"
#include "socket/network/GameServerSocket.h" 
#include "mvc/Facade.h"
#include "control/ModelCommand.h"
#include "control/ViewCommand.h"
#include "control/ControlCommand.h"
#include "model/config/ConfigManager.h"
#include "model/backpack/GoodsManager.h"
#include "model/shop/ShopManage.h"
#include "view/GameView.h"
#include "manager/GlobalManage.h"
#include "utils/ValuesUtil.h"
#include "utils/ScaleUtil.h"
#include "utils/GlobalScale.h"
#include "view/scene/components/LoginScene.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "MobClickManager.h"
#endif  // CC_PLATFORM_IOS

#include "SimpleAudioEngine.h"
#include "manager/ConnectionManager.h"
#include "model/figure/EquipmentManager.h"
#include "model/com/GoodsDynamicManager.h"
#include "manager/sound/SoundManager.h"
#include "manager/BattleManager.h"
#include "utils/thread/BaseThread.h"
#include "view/login/components/LoginNewMain.h"

USING_NS_CC;
using namespace CocosDenshion;


AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
	CC_SAFE_DELETE( g_pConfigManager );
	CC_SAFE_DELETE( g_pGlobalManage );
	CC_SAFE_DELETE( g_pMessageFactoryManager );
	CC_SAFE_DELETE( g_pLoginManage );
	CC_SAFE_DELETE( g_pGoodsManager );
	CC_SAFE_DELETE( g_pShopManage );
	CC_SAFE_DELETE( g_pFacade );
	CC_SAFE_DELETE( g_pKKAnimationFactory );
	CC_SAFE_DELETE(g_pGoodsDynamicManager);
	//MainScene::destroyInstance();
    EquipmentManager::Instance()->DestroyInstance();
} 

bool AppDelegate::initInstance()
{
    bool bRet = false;
    do 
    {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.s
        CCEGLView * pMainWnd = new CCEGLView();
        CC_BREAK_IF(! pMainWnd
            || ! pMainWnd->Create(TEXT("SLCQ"), 1024, 768) );	// 640


#endif  // CC_PLATFORM_WIN32
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        // OpenGLView is initialized in AppDelegate.mm on ios platform, nothing need to do here.
#endif  // CC_PLATFORM_IOS

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)        
        // OpenGLView is initialized in HelloWorld/android/jni/helloworld/main.cpp
		// the default setting is to create a fullscreen view
		// if you want to use auto-scale, please enable view->create(320,480) in main.cpp
#endif  // CC_PLATFORM_ANDROID
        
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WOPHONE)

        // Initialize OpenGLView instance, that release by CCDirector when application terminate.
        // The HelloWorld is designed as HVGA.
        CCEGLView* pMainWnd = new CCEGLView(this);
        CC_BREAK_IF(! pMainWnd || ! pMainWnd->Create(320,480, WM_WINDOW_ROTATE_MODE_CW));

#ifndef _TRANZDA_VM_  
        // on wophone emulator, we copy resources files to Work7/TG3/APP/ folder instead of zip file
        cocos2d::CCFileUtils::setResource("HelloWorld.zip");
#endif

#endif  // CC_PLATFORM_WOPHONE

#if (CC_TARGET_PLATFORM == CC_PLATFORM_AIRPLAY)
		// MaxAksenov said it's NOT a very elegant solution. I agree, haha
		CCDirector::sharedDirector()->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);
#endif
        
        bRet = true;
    } while (0);
    return bRet;
}

bool AppDelegate::applicationDidFinishLaunching()
{
#if (CC_PLATFORM_IOS == CC_TARGET_PLATFORM || CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
	GlobalScale::Instance()->setStandard(960, 640, 1);
#endif

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //MobClickManager::getInstance()->startWithAppkey("4fed29075270153ef7000004");
#endif  // CC_PLATFORM_IOS
   
	// initialize director
	CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(&CCEGLView::sharedOpenGLView());

    // enable High Resource Mode(2x, such as iphone4) and maintains low resource on other devices.
    //pDirector->enableRetinaDisplay(true);

	// sets landscape mode
	// pDirector->setDeviceOrientation(kCCDeviceOrientationLandscapeLeft);

	// turn on display FPS
	//pDirector->setDisplayFPS(true);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
	// pDirector->setDisplayFPS(true);
#endif
	//pDirector->setAlphaBlending( true );

    
	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );
	CCTexture2D::PVRImagesHavePremultipliedAlpha(true);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    
	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 30);
#else
    
	// set FPS. the default value is 1.0/60 if you don't call this
	pDirector->setAnimationInterval(1.0 / 30);
#endif
    

	//Solve the border of the map loading is a problem, but don't work, in Bgbitmap installed inside the elf textture method
	// then solve the problems on the ipad in flash.
	pDirector->setProjection(CCDirectorProjection2D);
	pDirector->setDepthTest(false); // Kenfly 20121201
	//////////////////

	//pDirector->setContentScaleFactor(768/320.0f);

	GlobalScale *pScaleUtil = GlobalScale::Instance();

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	CCSize winSize2 = CCDirector::sharedDirector()->getWinSizeInPixels();
	float scaleFactor, scaleFactorWidth, scaleFactorHeight;
	scaleFactorWidth =  (float) pScaleUtil->getStandardWidth() / winSize.width;
	scaleFactorHeight = (float) pScaleUtil->getStandardHeight()  / winSize.height;
	float expandWidth, expandHeight;

	if(pScaleUtil->getStandardHeight() / scaleFactorWidth < winSize.height)
	{
		scaleFactor = scaleFactorWidth;
		expandWidth = 0;
		expandHeight = pScaleUtil->getStandardHeight() / scaleFactor - winSize.height;
	}
	else
	{
		scaleFactor = scaleFactorHeight;
		expandWidth = pScaleUtil->getStandardWidth() / scaleFactor - winSize.width;
		expandHeight = 0;
	}

	CCLog("App %f", scaleFactor);
	
	pDirector->setContentScaleFactor(scaleFactor);
#if (CC_PLATFORM_IOS == CC_TARGET_PLATFORM || CC_PLATFORM_WIN32 == CC_TARGET_PLATFORM)
	GlobalScale::Instance()->setStandard(960, 640, scaleFactor);
#endif
	//pDirector->setContentScaleFactor(768 / pDirector->getWinSize().height);

	//1 Global management class
	g_pGlobalManage = new GlobalManage();

	//////////////////
	g_pMessageFactoryManager = new MessageFactoryManager();
    g_pMessageFactoryManager->Init();
    g_pLoginManage = new LoginManage();

	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA8888 );

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/figure/res_figure_blood_bg.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/res_close_1.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/arena/res_arena_ic.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/chat/res_chat.plist");
	
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/friend/res_friend.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/upskill/res_upskill.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/vip/res_vip.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/popuibg/res_popuibg.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mail/res_mail.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/map/res_map.plist");

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/crystal/res_crystal.plist");//不用了这系统

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/pack/res_pack.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/loading/res_loading.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(
		"assets/ui/npc_thing/npcthing_icon/npcthing_icon.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/npcdialog/npcdialog.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/res_btn.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/res_btn_new.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/newhand/res_newhand_arrow.plist");
	
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/tower/res_tower.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/tower/res_tower_other.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/train/res_train.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/levy/res_levy.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/CD/res_cd.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/report/res_report.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/effect/findpath/res_autofind.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/guild/res_guild.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/guild/res_guild_o.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_icon.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/formation/res_formation_1.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/formation/res_formation_2.plist");

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/head/res_head.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/loading/res_loading.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/res_ui_back.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_skill_icon.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/arena/res_arena.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/arena/res_arena_close.plist");
/*#if (RESOLUTION_480X320 == RESOLUTION_PIXELS)*/
	if(pScaleUtil->getScaleFromStandard() != 1)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/mapassets/exit/res_exit.plist");
	}
	else
	{
//#else
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/mapassets/exit/res_exit1.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/mapassets/exit/res_exit2.plist");
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/mapassets/exit/res_exit3.plist");
	}
//#endif	
//	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/setting/res_setting.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/story/res_story.plist");

	
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/streng/res_streng_common.plist");

	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/silvermine/res_silvermine1.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/silvermine/res_silvermine2.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/silvermine/res_silvermine3.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/silvermine/res_silvermine_icon5.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/res_act_other.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/figure/res_figure.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/res_right_pannel.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/vip/res_viplev.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_bgdir.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_newui.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_small.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_map.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_sec_btn.plist");

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainUI_train.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/train/res_train_dragon.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/mainUI/res_mainui_backlight.plist");
	
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/icon/res_tower_goods.plist");
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/login/res_login_server_new.plist");//
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/onlineReward/res_onlinereward_reward.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/formation/res_formationOrder.plist");
	//CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/levy/res_goldlevy.plist");
	
	
	//Configuration information must be in new ConfigManager before
	g_pGoodsManager = new GoodsManager();

	g_pShopManage = new ShopManage();
	g_pBattleManager = new BattleManager();

	DWORD d1 = Timer::millisecondNow();
	CCLog("-------------------loading ConfigManager begin: %d");

	g_pConfigManager = new ConfigManager();
	if (g_pConfigManager)
		g_pConfigManager->loadConfig();

	DWORD d2 = Timer::millisecondNow();
	CCLog("-------------------loading ConfigManager end: %d");
	CCLog("-----------------loading ConfigManager use: %d ,%f s", (d2-d1), (d2-d1)*0.001 );

	// values
	ValuesUtil::Instance()->init();

	// scale
	//ScaleUtil::init();

	//MVC
	g_pFacade = new Facade();
    ModelCommand tmpModelCommand;
	tmpModelCommand.execute(0,0);
	ViewCommand tmpViewCommand;
	tmpViewCommand.execute(0,0);
	ControlCommand tmpControlCommand;
	tmpControlCommand.execute(0,0);

    
    g_pKKAnimationFactory = new KKAnimationFactory();
    
    

    //anim1 = AnimationManager::getAction(1001);
    //anim2 = AnimationManager::getAction(1002);

	/*MainScene *pScene = MainScene::getInstance();
	pScene->init();*/
	
	/*
	LoginScene *pScene = LoginScene::getInstance();
	pScene->init();
	*/

	// LH20130126 added for login , get server list
	//BaseThread * pThread = new BaseThread((void *)&LoginNewMain::getServerInfoFromRemote,0);
	//pThread->run();

		LoginScene *pScene = LoginScene::node();
	// run
	pDirector->runWithScene(pScene);
	//pScene->release();//jae note 20120718
    
    //pScene->schedule(schedule_selector(MainScene::test),0.02f);
    
    //this->test()

//	CCDirector::sharedDirector()->setProjection(kCCDirectorProjection2D); 

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    //Doyang 20120724
	CCDirector::sharedDirector()->stopAnimation();
    
     CCDirector::sharedDirector()->pause();

	 GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::ENTER_BACKGROUND, NULL);

	// if you use SimpleAudioEngine, it must be pause
	 SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	 SimpleAudioEngine::sharedEngine()->stopAllEffects();
   /* 
	if(g_pLoginManage)
	{
		g_pLoginManage->_enterBackground = true;
		g_pLoginManage->_ignoreSoketsList[LoginManage::IS_SCMD107] = true;
	}*/


}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
	
	// if you use SimpleAudioEngine, it must resume here
	if (SoundManager::Instance()->getIsSoundOpen())
	{
		SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
	}
	if (SoundManager::Instance()->getIsEffectOpen())
	{
		//SimpleAudioEngine::sharedEngine()->resumeAllEffects();
	}

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::ENTER_FOREGROUND, NULL);
	
	//Doyang 20120724
    CCDirector::sharedDirector()->startAnimation();
    
	//Doyang 20120727 for debug
//    ConnectionManager::Instance()->ReConnect(NULL);
    //

}
