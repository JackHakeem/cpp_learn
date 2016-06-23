#include "view/scene/components/MainScene.h"
#include "socket/network/GateServerSocket.h"
#include "socket/network/GameServerSocket.h"
#include "LoginManage.h"
//#include "manager/SceneManager.h"
#include "view/GameView.h"
#include "model/com/GoodsDynamicManager.h"
#include "manager/PopManage.h"
//#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "view/dialog/components/DialogView.h"
#include "view/dialog/DialogMediator.h"
#include "control/AppFacade.h"
#include "control/scene/SceneCommand.h"
#include "view/scene/SceneMediator.h"
#include "view/backpack/components/BagCreate.h"
#include "manager/OverPanelManage.h"
#include "view/figure/FigureMediator.h"
#include "../layer/FightLayer.h"
#include "manager/GlobalManage.h"
#include "manager/BattleManager.h"
#include "view/crystal/components/CrystalView.h"
#include "manager/RenderManage.h"
#include "model/notice/NoticeManager.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "jni/slcq/JniManager.h"
#include "CCKeypadDispatcher.h"
#endif

static MainScene * m_pMainSceneInstance;

MainScene::MainScene(void)
{
	m_pMainSceneInstance = NULL;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    CCKeypadDispatcher::sharedDispatcher()->addDelegate(this);
#endif
}

MainScene::~MainScene(void)
{
	CCLog( "MainScene release." );//jae note
	//CC_SAFE_DELETE( g_pGameView );

	//GameServerSocket::destroyInstance();
	//GateServerSocket::destroyInstance();
	CC_SAFE_DELETE( g_pPopManage );
	CC_SAFE_DELETE( g_pGoodsDynamicManager );
	CC_SAFE_DELETE( g_pOverPanelManage );
	CC_SAFE_DELETE( g_pNoticeManager );

	//g_pGameView->removeFromParentAndCleanup(true);
	g_pGameView->release();

	//GameServerSocket::destroyInstance();
	//GateServerSocket::destroyInstance();

	//CCArray* pArray = this->getChildren();
	//CCNode* pObject = NULL;
	//for ( int i = 0; i < pArray->count(); i++ )
	//{
	//	pObject = (CCNode*)pArray->objectAtIndex(i);
	//	if(pObject == NULL)
	//		break;
	//	pObject->removeFromParentAndCleanup(true);
	//	//pObject->release();
	//}
}

MainScene * MainScene::Instance()
{
    if(m_pMainSceneInstance == NULL)
    {
        m_pMainSceneInstance = new MainScene();
    }
    return m_pMainSceneInstance;
}


MainScene * MainScene::getInstance()
{
    if(m_pMainSceneInstance == NULL)
    {
        //m_pMainSceneInstance = MainScene::node();
		m_pMainSceneInstance = new MainScene();
    }
	if(m_pMainSceneInstance)
	{
		return m_pMainSceneInstance;
	}
	return NULL;
}

bool MainScene::init()
{
    if ( !CCScene::init() )
    {
        return false;
    }

    //this->addChild(MapLayer::newMapLayer(),-100);

	//SceneCommand* cmd = (SceneCommand*)g_pFacade->retrieveController(AppFacade_SCENE_COMMAND);
	//char data[5] = "1001";
	//cmd->excute(0, data);
	
	//g_pFacade->sendNotification(Facade_Command, AppFacade_SCENE_COMMAND, data, 0);

	//SceneMediator* p = (SceneMediator*)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	//p->addToLayer();

 
	//this->addChild((CCLayer*)FightLayer::getInstance(), -97);  


    g_pGameView = new GameView();
	if (g_pGlobalManage->gameView)
		this->addChild(g_pGlobalManage->gameView, -10);

	g_pPopManage = new PopManage();
	g_pPopManage->setlayer(LayerManager::windowLayer);

	g_pGoodsDynamicManager = new GoodsDynamicManager();
	g_pOverPanelManage = new OverPanelManage();
	
	g_pNoticeManager = new NoticeManager();
	g_pNoticeManager->init();

    GateServerSocket* pGateSocket = GateServerSocket::getInstance();
    this->addChild(pGateSocket, 0);
	pGateSocket->release();
    GameServerSocket* pSocketGame = GameServerSocket::getInstance();
    this->addChild(pSocketGame, 0);
	pSocketGame->release();
    
 

 //   //bool result = pGateSocket->connect("115.238.73.228",121);//"115.238.73.228",121  pGateSocket->connect("192.168.22.104", 81);
	//bool result = pGateSocket->connect("113.107.110.141", 83);//"113.107.110.141", 83     115.238.73.228 121   
 //   if (result)
 //   {
 //       CCLOG(">Connect to GateServer succ");
 //       g_pLoginManage->gSocketConnectHandler();
 //   }
 //   else
 //   {
 //       CCLOG(">Connect GateServer fail");
 //   }

	RenderManage* renderManager = RenderManage::Instance();
	if(renderManager)
		addChild(renderManager);

	//for figure view test
// 	FigureMediator* figureM = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
// 	figureM->openFigureView();

    return true;
}

void MainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void  MainScene::destroyInstance()
{
	CC_SAFE_DELETE( m_pMainSceneInstance );
}

void MainScene::keyBackClicked()
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    callOutOfGame();
#endif
}

void MainScene::keyMenuClicked()
{
    
}
