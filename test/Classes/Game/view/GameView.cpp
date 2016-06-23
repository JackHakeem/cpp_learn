#include "GameView.h"
#include "manager/LayerManager.h"
#include "manager/GlobalManage.h"
#include "view/GameViewMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "scene/layer/FightLayer.h"
#include "scene/components/BattlePlay.h"
#include "utils/ScaleUtil.h"
#include "loading/LoadingView.h"
#include "view/ce/components/ceView.h"

//#include <vld.h>

GameView* g_pGameView = 0;

GameView::GameView()
{
	init();
}

void GameView::init()
{

	//Popup window
	if (!LayerManager::windowLayer)
	{
		LayerManager::windowLayer = new WindowLayer();
		LayerManager::windowLayer->init();
	}
	if (LayerManager::windowLayer->getParent())
	{
		return;
	}
	
	if (!LayerManager::windowLayer) {cocos2d::CCLog("void GameView::init() fail");}
	this->addChild(LayerManager::windowLayer, 100);

	//preTipsLayer
	LayerManager::preTipsLayer = new PreTipsLayer();
	LayerManager::preTipsLayer->init();
	if (!LayerManager::preTipsLayer) {cocos2d::CCLog("void GameView::init() fail");}
	this->addChild(LayerManager::preTipsLayer,205);
	LayerManager::preTipsLayer->release();

	//TIPS
	LayerManager::tipsLayer = new TipsLayer();
	LayerManager::tipsLayer->init();
	if (!LayerManager::tipsLayer) {cocos2d::CCLog("void GameView::init() fail");}
	this->addChild(LayerManager::tipsLayer,201);

	LoadingView* pLoadingView = new LoadingView; //kevinz
	pLoadingView->init();
	LayerManager::tipsLayer->addChild( pLoadingView, TipsLayer::WindowLayerZ_Loading, TipsLayer::WindowLayerTAG_Loading );
	pLoadingView->release();
	CCLog("------------------GameView::init:%x", pLoadingView);

	g_pGlobalManage->NumberOfSprites( 76 );

	//silverMineLayer
	LayerManager::silverMineLayer = new SilverMineLayer();
	LayerManager::silverMineLayer->init();
	if (!LayerManager::silverMineLayer) {cocos2d::CCLog("void GameView::init() fail");}
	this->addChild(LayerManager::silverMineLayer,101);

	//intervallayer
	LayerManager::intervalLayer = new IntervalLayer();
	LayerManager::intervalLayer->init();
	if (!LayerManager::intervalLayer) {cocos2d::CCLog("void GameView::init() fail");}
	this->addChild(LayerManager::intervalLayer,200);

	// ?¨¢??1¨¬?¡§????¦Ì?UI2?
	LayerManager::sceneUILayer = new SceneUILayer();
	LayerManager::sceneUILayer->init();
	if(LayerManager::sceneUILayer && LayerManager::sceneUILayer->init())
	{
		this->addChild(LayerManager::sceneUILayer,99);
	}
	

	g_pGlobalManage->gameView = this;

	LayerManager::battleLayer = new CCLayer();
	LayerManager::battleLayer->init();
	if(LayerManager::battleLayer)
	{
		this->addChild(LayerManager::battleLayer, 105);
		CCSprite* sp1 = BattlePlay::getInstance()->getBattleSprite();
		if(sp1)
			LayerManager::battleLayer->addChild(sp1);
	}

	// Loading pic icon
	LayerManager::loadingPic = new LoadingLayer();
	LayerManager::loadingPic->init();
	if( LayerManager::loadingPic && LayerManager::loadingPic->init() )
	{
		this->addChild( LayerManager::loadingPic, 9999 );
	}



	// Newhand
	LayerManager::newhandLayer = new NewhandLayer();
	LayerManager::newhandLayer->init();
	if(LayerManager::newhandLayer)
	{
		CCLayerColor *testLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(128, 128, 128, 128),
			CCDirector::sharedDirector()->getWinSize().width,
			CCDirector::sharedDirector()->getWinSize().height);
		testLayer->setPosition(CCPointZero);
		testLayer->setAnchorPoint(CCPointZero); 
		//LayerManager::newhandLayer->addChild(testLayer);

		//Doyang 20120724
		this->addChild(LayerManager::newhandLayer, 1020);
	}

	// charLayer
	LayerManager::chatLayer = new LayerNode();
	LayerManager::chatLayer->init();
	if(LayerManager::chatLayer)
	{
		this->addChild(LayerManager::chatLayer, 100);
	}

	////ceView
	//{
	//	ceView* pce = ceView::Instance();
	//	pce->init();
	//	LayerManager::intervalLayer->addChild(pce, PreTipsLayer::PreTipsLayerZ_ce+1000, PreTipsLayer::PreTipsLayerTAG_ce+1000);
	//	pce->release();
	//}

}

GameView::~GameView()
{
	if ( LayerManager::windowLayer )
	{
		LayerManager::windowLayer->removeAllChildrenWithCleanup(true);
		if ( LayerManager::windowLayer->getParent() )
		{
			LayerManager::windowLayer->removeFromParentAndCleanup(true);
		}
		LayerManager::windowLayer->release();
	}
	if ( LayerManager::tipsLayer )
	{
		LayerManager::tipsLayer->removeAllChildrenWithCleanup(true);
		if ( LayerManager::tipsLayer->getParent() )
		{
			LayerManager::tipsLayer->removeFromParentAndCleanup(true);
		}
		LayerManager::tipsLayer->release();
	}
	if ( LayerManager::sceneUILayer )
	{
		//LayerManager::sceneUILayer->removeAllChildrenWithCleanup(true);
		//if ( LayerManager::sceneUILayer->getParent() )
		//{
		//	LayerManager::sceneUILayer->removeFromParentAndCleanup(true);
		//}
		//LayerManager::sceneUILayer->release();
	}
	if ( LayerManager::battleLayer )
	{
		LayerManager::battleLayer->removeAllChildrenWithCleanup(true);
		if ( LayerManager::battleLayer->getParent() )
		{
			LayerManager::battleLayer->removeFromParentAndCleanup(true);
		}
		LayerManager::battleLayer->release();
	}
	if ( LayerManager::loadingPic )
	{
		//LayerManager::loadingPic->removeAllChildrenWithCleanup(true);
		//if ( LayerManager::loadingPic->getParent() )
		//{
		//	LayerManager::loadingPic->removeFromParentAndCleanup(true);
		//}
		LayerManager::loadingPic->release();
	}
	if ( LayerManager::newhandLayer )
	{
		LayerManager::newhandLayer->removeAllChildrenWithCleanup(true);
		if ( LayerManager::newhandLayer->getParent() )
		{
			LayerManager::newhandLayer->removeFromParentAndCleanup(true);
		}
		LayerManager::newhandLayer->release();
	}
}
