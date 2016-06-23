#include "GlobalManage.h"
#include "ViewManager.h"
#include "view/loading/LoadingView.h"
#include "LayerManager.h"
#include "NewEAlert.h"
#include "utils/ScaleUtil.h"
#include "ConnectionManager.h"
#include "view/appoint/AppointMediator.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "events/GameDispatcher.h"
#include "model/scene/NPCManager.h"
#include "control/scene/SceneCommand.h"
#include "util/TileUtil.h"
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
//#pragma comment(lib , "pthreadVC2.lib")
//#include "../pthread/pthread.h"
//#include "../pthread/semaphore.h"
//#include "CCThread.h"
//#endif
//
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
//#include "pthread.h"
//#include "semaphore.h"
//#include "CCThread.h"
//#endif

#include "model/scene/MonsterManager.h"
#include "model/newhand/NewhandManager.h"
#include "view/newhand/components/NewHandView.h"
#include "model/scene/vo/SceneType.h"
#include "model/scene/SceneManager.h"

GlobalManage* g_pGlobalManage = 0;
//
//static sem_t s_sem;
//static pthread_t s_loadingResThread;
//static pthread_mutex_t		s_asyncLoadingMutex;
//
//
//static void* loadResource(void* data)
//{
//	// create autorelease pool for iOS
//	CCThread thread;
//	thread.createAutoreleasePool();
//
//	while (true)
//	{
//		// wait for rendering thread to ask for loading if s_pAsyncStructQueue is empty
//		sem_wait(&s_sem);
//
//		//pthread_mutex_lock(&s_asyncLoadingMutex);// get async struct from queue
//		//pthread_mutex_unlock(&s_asyncLoadingMutex);
//
//		//CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("grossini_dance_01.png");
//
//
//		CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA4444 );
//		PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
//		if(!info)
//			return 0;
//		std::vector<int> array = NPCManager::Instance()->getNpcsByMapId(info->playerBaseInfo._mapId);
//
//		DWORD d1 = Timer::millisecondNow();
//		CCLog("-------------------loading NPC Sprite Frame begin: %d");
//
//		//g_pGlobalManage->NumberOfSprites( array.size() + 16*4 );
//		//g_pGlobalManage->loadOneProgress( 16 );
//
//		char _assetURL[128];
//		int direction[5] = {1, 2, 4, 7, 8};
//		int frameCnt = 15;
//		for(std::vector<int>::iterator iter = array.begin();
//			iter != array.end(); ++iter)
//		{
//			NPCVo* npcVo = NPCManager::Instance()->getNPC(*iter);
//			if(!npcVo)
//				continue;
//			sprintf( _assetURL, "assets/res/%d/model-%d.pvr.ccz", npcVo->_resId, npcVo->_resId );
//			if ( !BitmapMovieClip::isFileExist( _assetURL ) )
//				continue;
//
//			char path[128] = {0};
//			std::string frameName;
//
//			if(  npcVo->_isMonster ||
//				(npcVo->action==SceneConst::FIGHT) || (npcVo->action==SceneConst::STORY) )
//			{
//				// stand 
//				for ( int i = 0; i < 5; i++ )
//				{
//					sprintf( path, "%d/stand-%d", npcVo->_resId, direction[i] );	// 1/stand-8-9.png
//					frameName = std::string(path) + "-%d.png";
//					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
//
//					char str[100] = {0};
//					for(int i = 0; i < frameCnt; i++)
//					{
//						sprintf(str, frameName.c_str(), i);
//						CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//					}
//				}
//				// walk 
//				for ( int i = 0; i < 5; i++ )
//				{
//					sprintf( path, "%d/walk-%d", npcVo->_resId, direction[i] );	// 1/walk-8-9.png
//					frameName = std::string(path) + "-%d.png";
//					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
//
//					char str[100] = {0};
//					for(int i = 0; i < frameCnt; i++)
//					{
//						sprintf(str, frameName.c_str(), i);
//						CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//					}
//				}
//				// hit 
//				for ( int i = 0; i < 5; i++ )
//				{
//					sprintf( path, "%d/hit-%d", npcVo->_resId, direction[i] );	// 1/hit-8-9.png
//					frameName = std::string(path) + "-%d.png";
//					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
//
//					char str[100] = {0};
//					for(int i = 0; i < frameCnt; i++)
//					{
//						sprintf(str, frameName.c_str(), i);
//						CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//					}
//				}
//				// attack 
//				for ( int i = 0; i < 5; i++ )
//				{
//					sprintf( path, "%d/attack-%d", npcVo->_resId, direction[i] );	// 1/attack-8-9.png
//					frameName = std::string(path) + "-%d.png";
//					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
//
//					char str[100] = {0};
//					for(int i = 0; i < frameCnt; i++)
//					{
//						sprintf(str, frameName.c_str(), i);
//						CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//					}
//				}
//			}
//			else
//			{
//				sprintf( path, "%d/stand-%d", npcVo->_resId, direction[0] );	// 1/stand-8-9.png
//				frameName = std::string(path) + "-%d.png";
//				CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frameName.c_str());
//
//				char str[100] = {0};
//				for(int i = 0; i < frameCnt; i++)
//				{
//					sprintf(str, frameName.c_str(), i);
//					CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(str);
//				}
//			}
//		}
//
//
//		DWORD d2 = Timer::millisecondNow();
//		CCLog("-----------------loading NPC Sprite Frame use: %d ,%f s", (d2-d1), (d2-d1)*0.001 );
//
//		sprintf( _assetURL, "assets/res/%d/model-%d.pvr.ccz", info->playerBaseInfo.cloth, info->playerBaseInfo.cloth );
//		std::string pathKey = _assetURL;
//		CCFileUtils::removeSuffixFromFile(pathKey);
//
//		pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
//		if ( BitmapMovieClip::isFileExist( _assetURL ) )
//		{
//			CCTextureCache::sharedTextureCache()->addPVRImage(pathKey.c_str());
//		}
//		CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );
//	}
//
//	// 
//
//	return 0;
//}

GlobalManage::GlobalManage():gameView(0)
{
	//_FocusGIDFactory = 0;
	setIsStorySystemOpen(false);
	setCurFocusGID(0);
	guild = 0;
	isGm = false;
	_isEnterGame = false;
	isReport = false;

	isInDream = false;
	_isInFight = false;
	isInStory = false;
	isGuest = false;
	_isFCM = false;
	_isOnBusiness = false;
	_isOnMeditation = false;
	_canMove = true;
	bFollowerId = 0;
	followerId = 0;
	isGm = false;
	isSmallMapReady = false;
	isInArmyFight = false;
	isRoleHidden = false;
	guild = 0;
	_inMineTime = false;
	_inGongTime = false;
	canOperate = true;
	_isShowAllUILock = false;
	m_iTowerGUA = 0;
	m_iDunGUA = 0;
	m_iDunGUAMapid = 0;
    _isShowEndFightButton = false;

	_isChangeScene = false;
	m_nNumberOfSprites = 0;
	m_nNumberOfLoadedSprites = 0;
	m_canSCMD133Enable = 0;

	g_netDelay = 0;
	_exchangeType = 0;
	_curNewTips = 0;
#if ((CC_TARGET_PLATFORM  == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM  == CC_PLATFORM_IOS))
	setRoleSpeed(POSX(502));
#else
    setRoleSpeed(POSX(502 * 2));
#endif

	setIsHasPop(false);
	setIsInWordMap(false);
	setIsHideOtherPlayers(false);
	setIsInWorldBoss(false);

	d1 = 0;
	d2 = 0;

	m_bLoadingOver = false;

	needCreatTraderPlayer = false;
	_tradeMapLimit = false;

	m_bBattleEffectOn = false;
}
//GlobalManage::GlobalManage():gameView(0)
//{
//	//_FocusGIDFactory = 0;
//	setCurFocusGID(0);
//	guild = 0;
//	isGm = false;
//	_isEnterGame = false;
//	isReport = false;
//
//	isInDream = false;
//	_isInFight = false;
//	isInStory = false;
//	isGuest = false;
//	_isFCM = false;
//	_isOnBusiness = false;
//	_isOnMeditation = false;
//	_canMove = true;
//	bFollowerId = 0;
//	followerId = 0;
//	isGm = false;
//	isSmallMapReady = false;
//	isInArmyFight = false;
//	isRoleHidden = false;
//	guild = 0;
//	_inMineTime = false;
//	canOperate = true;
//	_isShowAllUILock = false;
//    _isShowEndFightButton = false;
//    
//	_isChangeScene = false;
//	m_nNumberOfSprites = 0;
//	m_nNumberOfLoadedSprites = 0;
//	g_isRedMonster = false;
//
//	_exchangeType = 0;
//	_curNewTips = 0;
//#if ((CC_TARGET_PLATFORM  == CC_PLATFORM_ANDROID) || (CC_TARGET_PLATFORM  == CC_PLATFORM_IOS))
//	setRoleSpeed(POSX(502));
//#else
//    setRoleSpeed(POSX(502 * 3));
//#endif
//
//	setIsHasPop(false);
//	setIsInWordMap(false);
//	setIsHideOtherPlayers(false);
//
//	d1 = 0;
//	d2 = 0;
//
//	m_bLoadingOver = false;
//}

GlobalManage::~GlobalManage()
{
	CCLog("~GlobalManage");
	ViewManager::detroyInstance();
}
//CC_PROPERTY(int32, _FocusGIDFactory, FocusGIDFactory)
//int32 GlobalManage::getFocusGIDFactory()
//{
//	return _FocusGIDFactory++;
//}



//CC_PROPERTY(int32, _CurFocusGID, CurFocusGID)
int32 GlobalManage::getCurFocusGID()
{
	return _CurFocusGID;
}

void GlobalManage::setCurFocusGID(int32 var)
{
	_CurFocusGID = var;
}

bool GlobalManage::isFCM()
{
	return _isFCM;
}

void GlobalManage::isFCM(bool value)
{
	_isFCM = value;
	//dispatchEvent(new Event(FCM_STATE_CHANGE));
}

bool GlobalManage::isEnterGame()
{
	return _isEnterGame;
}

void GlobalManage::isEnterGame(bool value)
{
	_isEnterGame = value;
	//dispatchEvent(new Event(ENTIRELY_ENTER_GAME));
}


bool GlobalManage::isOnBusiness()
{
	return _isOnBusiness;
}

void GlobalManage::isOnBusiness(bool value)
{
	_isOnBusiness = value;
	_canMove = !value;
	//dispatchEvent(new Event(BUSINESS_STATE_CHANGE));
}

bool GlobalManage::isOnMeditation()
{
	return _isOnMeditation;
}

void GlobalManage::isOnMeditation(bool value)
{
	_isOnMeditation = value;
	_canMove = !value;
	//dispatchEvent(new Event(MEDITATION_STATE_CHANGE));
}

bool GlobalManage::canMove()
{
	return _canMove;
}

void GlobalManage::canMove(bool value)
{
	_canMove = value;
	//dispatchEvent(new Event(CAN_MOVE_CHANGE));
}

bool GlobalManage::inMineTime()
{
	return _inMineTime;
}

void GlobalManage::inMineTime(bool value)
{
	if(_inMineTime != value)
	{
		_inMineTime = value;
		dispatchEvent(GlobalManage::MINE_TIME_CHANGE, 0);
	}
}

bool GlobalManage::inGongTime()
{
	return _inGongTime;
}

void GlobalManage::inGongTime(bool value)
{
	if(_inGongTime != value)
	{
		_inGongTime = value;
		//dispatchEvent(GlobalManage::MINE_TIME_CHANGE, 0);
	}
}


void GlobalManage::setisInFight( bool bValue )
{
	_isInFight = bValue;
}

bool GlobalManage::getisInFight()
{
	return _isInFight;
}

bool GlobalManage::getIsInGame()
{
	return _isInGame;
}

void GlobalManage::setIsInGame(bool isInGame)
{
	_isInGame = isInGame;
}

int GlobalManage::getTowerGUA()
{
	return m_iTowerGUA;
}

void GlobalManage::setTowerGUA(int value)
{
	m_iTowerGUA = value;
}

int GlobalManage::getDunGUA()
{
	return m_iDunGUA;
}

void GlobalManage::setDunGUA(int value)
{
	m_iDunGUA = value;
}

void GlobalManage::setDunMapId(int value)
{
	m_iDunGUAMapid = value;
}

int GlobalManage::getDunMapId()
{
	return m_iDunGUAMapid;
}

void GlobalManage::showAllUI(bool bValue)
{
	//if(!_isInFight && !isInStory) return;
	if(_isShowAllUILock)
	{
		return;
	}

	if (RoleManage::Instance()->roleInfo() 
		&& (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1208))
	{
		if (isInStory || _isInFight)
		{
			if (ViewManager::getInstance()->_pWBMainView)
			{
				ViewManager::getInstance()->_pWBMainView->setIsVisible(false);
			}
		}
		else
		{
			if (ViewManager::getInstance()->_pWBMainView)
			{
				ViewManager::getInstance()->_pWBMainView->setIsVisible(true);
			}
		}

		bValue = false;
	}

	ViewManager * pViewMgr = ViewManager::getInstance();
	if (!pViewMgr){return;}

	CCNode * pUIItem = 0;
	pUIItem = pViewMgr->_roleUI;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (RoleManage::Instance()->roleInfo() 
			&& (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1208)
			&& (!isInStory && !_isInFight))
		{
			pUIItem->setIsVisible(true);
		}		
	}
	pUIItem = pViewMgr->mainNavigate;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (RoleManage::Instance()->roleInfo() 
			&& (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1208)
			&& (!isInStory && !_isInFight))
		{
			pUIItem->setIsVisible(true);
		}
	}
	pUIItem = pViewMgr->taskFollowView;
	if (pUIItem){pUIItem->setIsVisible(bValue);}

	pUIItem = pViewMgr->_pVScrollUI;
	if (pUIItem){pUIItem->setIsVisible(bValue);}

	pUIItem = pViewMgr->_taskUIView;
	if (pUIItem){pUIItem->setIsVisible(bValue);}

	pUIItem = pViewMgr->_taskUIView;
	if (pUIItem){pUIItem->setIsVisible(bValue);}

	pUIItem = pViewMgr->_secNavigate;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		SceneProxy* pSceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
		SceneInfoVo* sceneInfoVo = pSceneProxy->sceneInfoVo();
		((SecNavigate *)pUIItem)->setIsShowCenterTopItems(sceneInfoVo->type == SceneType::CITY);
	}

	if (LayerManager::tipsLayer
		&& LayerManager::tipsLayer->getChildByTag( 6001))
	{
		LayerManager::tipsLayer->getChildByTag( 6001)->setIsVisible(bValue);
		((CCLayerColor *)(LayerManager::tipsLayer->getChildByTag( 6001)))->setIsTouchEnabled(bValue);
	}

	/*
	if (pViewMgr->_pVScrollUI)
	{
		if (!pViewMgr->_pVScrollUI->getIsHide() && !bValue)
		{
			pViewMgr->_pVScrollUI->clickHideVscroll();
		}

		if (pViewMgr->_pVScrollUI->getIsHide() && bValue && RoleManage::Instance()->roleLev() >= 2)
		{
			pViewMgr->_pVScrollUI->clickHideVscroll();
		}		
	}
	*/

	/*
	pUIItem = pViewMgr->_mailButton;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (getIsInCopyMap())
		{
			pUIItem->setIsVisible(false);
		}
	}
	pUIItem = pViewMgr->_mailText;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (getIsInCopyMap())
		{
			pUIItem->setIsVisible(false);
		}
	}
	pUIItem = pViewMgr->_mailLight;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (getIsInCopyMap())
		{
			pUIItem->setIsVisible(false);
		}
	}
	*/
	
	if(!bValue && pViewMgr->mainNavigate)
	{
		pViewMgr->mainNavigate->setisMainBtnOpen(false);
	}
	if(!bValue && pViewMgr->taskFollowView)
	{
		pViewMgr->taskFollowView->dismissTaskFollowLayer();
	}
	// hide obtain new objects tips
	
	if (bValue)
	{
		
		if (_curNewTips && !LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert))
		{
			LayerManager::tipsLayer->addChild(_curNewTips,0,TipsLayer::TipsLayerTAG_NewEAlert);
			_curNewTips = 0;
		}
	}
	else
	{
		_curNewTips = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert);
		if (_curNewTips)
		{
			LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_NewEAlert,false);
		}
	}
	
	/*
	// hide dialogView
	if (pViewMgr->dialogView)
	{
		if (!bValue && pViewMgr->dialogView->getIsVisible())
		{
			pViewMgr->dialogView->setIsVisible(false);
			pViewMgr->dialogView->setIsTouchEnabled(false);
			setIsHasPop(true);
		}
		if (bValue && getIsHasPop() && !pViewMgr->dialogView->getIsVisible())
		{
			pViewMgr->dialogView->setIsVisible(true);
			pViewMgr->dialogView->setIsTouchEnabled(true);
			setIsHasPop(false);
		}
	}
	*/

	// hide newhand tips
	
  	if (LayerManager::newhandLayer)
  	{
		if (isInStory || _isInFight)
		{
			LayerManager::newhandLayer->setIsVisible(false);
			LayerManager::newhandLayer->setIsTouchEnabled(false);
		}
		else
		{
			LayerManager::newhandLayer->setIsVisible(true);
		}
	}

	// notify newhand
	NewHandView::Instance()->onMainNavigateChange(bValue);
	
	// 
	if (ViewManager::getInstance()->getInstance()->mainNavigate)
	{
		if (SceneManager::Instance()->getCurMapType() == SceneType::CITY)
		{
			ViewManager::getInstance()->getInstance()->mainNavigate->showVScrollAndTaskUIView(true);
		}
	}
	
}


void GlobalManage::showAllUIEx(bool bValue)
{
	if (RoleManage::Instance()->roleInfo() 
		&& (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1208))
	{
		if (isInStory || _isInFight)
		{
			if (ViewManager::getInstance()->_pWBMainView)
			{
				ViewManager::getInstance()->_pWBMainView->setIsVisible(false);
			}
		}
		else
		{
			if (ViewManager::getInstance()->_pWBMainView)
			{
				ViewManager::getInstance()->_pWBMainView->setIsVisible(true);
			}
		}

		bValue = false;
	}

	ViewManager * pViewMgr = ViewManager::getInstance();
	if (!pViewMgr){return;}

	CCNode * pUIItem = 0;
	pUIItem = pViewMgr->_roleUI;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (RoleManage::Instance()->roleInfo() 
			&& (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1208)
			&& (!isInStory && !_isInFight))
		{
			pUIItem->setIsVisible(true);
		}		
	}
	pUIItem = pViewMgr->mainNavigate;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (RoleManage::Instance()->roleInfo() 
			&& (RoleManage::Instance()->roleInfo()->playerBaseInfo._mapId == 1208)
			&& (!isInStory && !_isInFight))
		{
			pUIItem->setIsVisible(true);
		}
	}
	pUIItem = pViewMgr->taskFollowView;
	if (pUIItem){pUIItem->setIsVisible(bValue);}
	pUIItem = pViewMgr->_secNavigate;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
	}
	/*
	pUIItem = pViewMgr->_mailButton;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (getIsInCopyMap())
		{
			pUIItem->setIsVisible(false);
		}
	}
	pUIItem = pViewMgr->_mailText;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (getIsInCopyMap())
		{
			pUIItem->setIsVisible(false);
		}
	}
	pUIItem = pViewMgr->_mailLight;
	if (pUIItem)
	{
		pUIItem->setIsVisible(bValue);
		if (getIsInCopyMap())
		{
			pUIItem->setIsVisible(false);
		}
	}
	*/
	/*
	if (pViewMgr->_pVScrollUI)
	{
		if (!pViewMgr->_pVScrollUI->getIsHide() && !bValue)
		{
			pViewMgr->_pVScrollUI->clickHideVscroll();
		}

		if (pViewMgr->_pVScrollUI->getIsHide() && bValue && RoleManage::Instance()->roleLev() >= 2)
		{
			pViewMgr->_pVScrollUI->clickHideVscroll();
		}		
	}
	*/
	
	if(!bValue && pViewMgr->mainNavigate)
	{
		pViewMgr->mainNavigate->setisMainBtnOpen(false);
	}
	if(!bValue && pViewMgr->taskFollowView)
	{
		pViewMgr->taskFollowView->dismissTaskFollowLayer();
	}
	// hide obtain new objects tips
	
	if (bValue)
	{
		
		if (_curNewTips && !LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert))
		{
			LayerManager::tipsLayer->addChild(_curNewTips,0,TipsLayer::TipsLayerTAG_NewEAlert);
			_curNewTips = 0;
		}
	}
	else
	{
		_curNewTips = LayerManager::tipsLayer->getChildByTag(TipsLayer::TipsLayerTAG_NewEAlert);
		if (_curNewTips)
		{
			LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_NewEAlert,false);
		}
	}
	
	if (LayerManager::tipsLayer
		&& LayerManager::tipsLayer->getChildByTag( 6001))
	{
		LayerManager::tipsLayer->getChildByTag( 6001)->setIsVisible(bValue);
		((CCLayerColor *)(LayerManager::tipsLayer->getChildByTag( 6001)))->setIsTouchEnabled(bValue);
	}

	/*
	// hide dialogView
	if (pViewMgr->dialogView)
	{
		if (!bValue && pViewMgr->dialogView->getIsVisible())
		{
			pViewMgr->dialogView->setIsVisible(false);
			pViewMgr->dialogView->setIsTouchEnabled(false);
			setIsHasPop(true);
		}
		if (bValue && getIsHasPop() && !pViewMgr->dialogView->getIsVisible())
		{
			pViewMgr->dialogView->setIsVisible(true);
			pViewMgr->dialogView->setIsTouchEnabled(true);
			setIsHasPop(false);
		}
	}
	*/

	// hide newhand tips
	
  	if (LayerManager::newhandLayer)
  	{
		if (isInStory || _isInFight)
		{
			LayerManager::newhandLayer->setIsVisible(false);
			LayerManager::newhandLayer->setIsTouchEnabled(false);
		}
		else
		{
			LayerManager::newhandLayer->setIsVisible(true);
			//LayerManager::newhandLayer->setIsTouchEnabled(true);
		}
	}
	
	// 
	if (ViewManager::getInstance()->getInstance()->mainNavigate)
	{
		if (SceneManager::Instance()->getCurMapType() == SceneType::CITY)
		{
			ViewManager::getInstance()->getInstance()->mainNavigate->showVScrollAndTaskUIView(true);
		}
	}
}

void GlobalManage::loadOneProgress( int iGoCnt )
{
	if ( m_nNumberOfSprites == 0 )
	{
		return;
	}
	
	m_nNumberOfLoadedSprites += iGoCnt;
}

void GlobalManage::setExchangeType( int type )
{
	if(_exchangeType != type)
	{
		_exchangeType = type;
		//this.dispatchEvent(new Event(APPOINT_BLESS_EXCHANGE));
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::APPOINT_BLESS_EXCHANGE, NULL);
	}
}

void GlobalManage::startResourceLoadingSync()
{
	//LoadingView* pLoadingView = (LoadingView*)LayerManager::tipsLayer->getChildByTag(TipsLayer::WindowLayerTAG_Loading );


	////////////////load npc texture begin
	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA4444 );
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;
	std::vector<int> array = NPCManager::Instance()->getNpcsByMapId(info->playerBaseInfo._mapId);

	DWORD d1 = Timer::millisecondNow();
	CCLog("-------------------loading NPC pvr image begin: %d");

	//g_pGlobalManage->NumberOfSprites( array.size() + 16*4 );
	//g_pGlobalManage->loadOneProgress( 16 );

	char _assetURL[128];
	for(std::vector<int>::iterator iter = array.begin();
		iter != array.end(); ++iter)
	{
		NPCVo* npcVo = NPCManager::Instance()->getNPC(*iter);
		if(!npcVo)
			continue;
		


		sprintf( _assetURL, "assets/res/%d/model-%d.pvr.ccz", npcVo->_resId, npcVo->_resId );
		std::string pathKey = _assetURL;
		CCFileUtils::removeSuffixFromFile(pathKey);

		pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
		if ( BitmapMovieClip::isFileExist( _assetURL ) )
		{
			CCTextureCache::sharedTextureCache()->addPVRImage(pathKey.c_str());
		}
		g_pGlobalManage->loadOneProgress( 1 );
	}

	//DWORD d2 = Timer::millisecondNow();
	//CCLog("-----------------loading NPC pvr image use: %d ,%f s", (d2-d1), (d2-d1)*0.001 );

	//Doyang 20120903
	int resId = info->playerBaseInfo.cloth; 
	if( resId > 0 )
	{
		sprintf( _assetURL, "assets/res/%d/model-%d.pvr.ccz", resId, resId );
		std::string pathKey = _assetURL;
		CCFileUtils::removeSuffixFromFile(pathKey);	

		pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
		if ( BitmapMovieClip::isFileExist( _assetURL ) )
		{
			CCTextureCache::sharedTextureCache()->addPVRImage(pathKey.c_str());
		}
	}
	//DWORD d3 = Timer::millisecondNow();
	//CCLog("-----------------loading player pvr image use: %d ,%f s", (d3-d2), (d3-d2)*0.001 );

	///////////////Monster
	std::list<GMProgressVo*> arrayMonster =
		MonsterManager::Instance()->getGroupMonsterByMapId(info->playerBaseInfo._mapId);

	for(std::list<GMProgressVo*>::iterator iter = arrayMonster.begin();
		iter != arrayMonster.end(); ++iter)
	{
		if(!(*iter))
			continue;

		//if(_sceneProxy->shootDic.find((*iter)->id) != _sceneProxy->shootDic.end())
		//{
		//	continue;
		//}

		if((*iter)->mgId == 0)
		{
			continue;
		}

		//if(isHide && _sceneProxy->isInProgress((*iter)->id))
		//{
		//	continue;
		//}
		NPCVo* npcVo = MonsterManager::Instance()->getMonsterGroup((*iter)->mgId);
		if(!npcVo)
			continue;

		sprintf( _assetURL, "assets/res/%d/model-%d.pvr.ccz", npcVo->_resId, npcVo->_resId );
		std::string pathKey = _assetURL;
		CCFileUtils::removeSuffixFromFile(pathKey);
		pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
		if ( BitmapMovieClip::isFileExist( _assetURL ) )
		{
			CCTextureCache::sharedTextureCache()->addPVRImage(pathKey.c_str());
		}
		g_pGlobalManage->loadOneProgress( 1 );
	}

	////////////////monster end
	DWORD d2 = Timer::millisecondNow();
	CCLog("-----------------loading res pvr image use: %d ,%f s", (d2-d1), (d2-d1)*0.001 );
	CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );
	////////////////load npc texture end

	
	////////////////////////// load map pic
	SceneCommand* cmd = 0;
	if(g_pFacade)//jae no
	{
		cmd = (SceneCommand*)g_pFacade->retrieveController(AppFacade_SCENE_COMMAND);
		if(cmd)
		{
			cmd->excute(0, NULL);
		}
	}
	//std::string path = sceneInfoVo->sceneRoot+"front/";
	//sceneInfoVo->sceneRoot = "assets/mapassets/scene/1002/front/"
	SceneInfoVo sceneInfoVo = cmd->_sceneInfo;
	CCPoint pos = TileUtil::Instance()->changeTileToPixs(ccp(info->playerBaseInfo.x,info->playerBaseInfo.y));
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(pos.x <= size.width / 2.0f)
	{
		pos.x = sceneInfoVo.width / 2.0f;
	}
	else if(pos.x >= (sceneInfoVo.width - size.width / 2.0f))
	{
		pos.x = - sceneInfoVo.width / 2.0f + size.width;
	}
	else
		pos.x = - pos.x + sceneInfoVo.width / 2.0f + size.width / 2.0f;


	if(pos.y < size.height / 2.0f)
	{
		pos.y = - sceneInfoVo.height / 2.0f + size.height;
	}
	else if(pos.y > (sceneInfoVo.height - size.height / 2.0f))
	{
		pos.y = sceneInfoVo.height / 2.0f;
	}
	else
	{
		pos.y = - sceneInfoVo.height / 2.0f + size.height / 2.0f + pos.y;
	}

	int bmCol = sceneInfoVo.mapCols;
	int bmRow = sceneInfoVo.mapRoWs;
	int _picWidth = TileUtil::Instance()->getPicWidth();
	int _picHeight = TileUtil::Instance()->getPicHeight();
	int _totalWidth = bmCol * _picWidth;
	int _totalHeight = bmRow * _picHeight;
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	int width_left = _totalWidth / 2 - POSX(300);
	int width_right = _totalWidth / 2 + screenSize.width + POSX(300);
	int height_top = _totalHeight / 2 - screenSize.height - POSX(300);
	int height_bottom = _totalHeight / 2 + POSX(300);
	int width_left_ = width_left - pos.x;
	int width_right_ = width_right - pos.x;
	int height_top_ = height_top + pos.y;
	int height_bottom_ = height_bottom + pos.y;
	std::string rootPath = sceneInfoVo.sceneRoot + "front/%d_%d.jpg";
	char p[50] = {0};
	// Kenfly 20121114 
	//for(int i = 0; i < bmRow; ++i)
	//{
	//	for(int j = 0; j< bmCol; ++j)
	//	{
	//		if((i * bmCol + j) >= MAP_SPRITE_MAX)
	//			break;

	//		if(j * _picWidth  >= width_left_ && (j + 1) * _picWidth < width_right_
	//			&& i * _picHeight >= height_top_ && (i + 1) * _picHeight < height_bottom_)
	//		{
	//			sprintf(p, rootPath.c_str(), j, i);
	//			CCTextureCache::sharedTextureCache()->addImage(p);
	//			/*CCTextureCache::sharedTextureCache()->addImageAsync(
	//				p,
	//				pLoadingView,
	//				callfuncO_selector(LoadingView::loadOneProgress)
	//				);*/
	//		}
	//	}
	//}

	//loadUIImages();
	//////////////loading map pic end

}

void GlobalManage::loadUIImages()
{

	LoadingView* pLoadingView = (LoadingView*)LayerManager::tipsLayer->getChildByTag(
		TipsLayer::WindowLayerTAG_Loading );

	///////////load ui resource
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/effect/finTask/finTask.png" 			,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/effect/map/mapExit.png" 				,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/effect/mouse/mouseClick.png" 			,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/effect/recvTask/recvTask.png" 		,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/task/TaskCanBtnNormal.png" 			,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/task/TaskCanBtnPressed.png" 			,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/task/TaskListBg.png" 					,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/task/btn_task_normal.png" 			,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/task/btn_task_pressed.png" 			,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/ui/map/btn1.png" 						,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/ui/map/btn2.png" 						,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/ui/newhand/point_up.png" 				,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "assets/ui/notice.png" 						,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );
	CCTextureCache::sharedTextureCache()->addImageAsync(  "role/icon/shadow.png" 						,pLoadingView, callfuncOD_selector(LoadingView::loadOneProgress)  );

}

//void GlobalManage::startLoading()
//{
//	// lazy init
//	static bool firstRun = true;
//	if (firstRun)
//	{
//		pthread_mutex_init(&s_asyncLoadingMutex, NULL);
//		sem_init(&s_sem, 0, 0);
//		pthread_create(&s_loadingResThread, NULL, loadResource, NULL);
//
//		firstRun = false;
//	}
//
//	sem_post(&s_sem);
//}
