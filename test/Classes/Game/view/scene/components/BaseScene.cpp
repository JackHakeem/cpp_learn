#include "BaseScene.h"
#include <math.h>
#include "BaseType.h"
#include "model/scene/NPCManager.h"
#include "manager/ViewManager.h"
#include "view/figure/FigureMediator.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "model/scene/MonsterManager.h"
#include "manager/BattleManager.h"
#include <math.h>
#include "util/TileUtil.h"
#include "Exit.h"
#include "manager/RenderManage.h"
#include "events/GameDispatcher.h"
#include "utils/loader/KKAnimationFactory.h"
#include "model/scene/NPCManager.h"
#include "MapNPC.h"
#include "model/scene/vo/SceneConst.h"
#include "utils/ScaleUtil.h"
#include "manager/TouchLayerEnum.h"
#include <algorithm>

Player* g_pHero = 0;
FigureMediator* figureM = NULL;

BaseScene::BaseScene(void):m_needStep(false)
{
	_frontbg = NULL;
	_role = NULL;
	m_mapWidth = 0.0f;
	m_mapHeight = 0.0f;
	//_MapNPCDic.clear();
	//_MapMonstersDic.clear();
	_isHidePlayer = false;
	_depthChanged = false;
	curFrame = 0;
	_mapRank = 1;

	_depthChanged = false;
	_positionChanged = false;

	_isHidePlayer = false;
	autoMove = true;
	//int curFrame = 0;
	clickTarget = NULL;
	_moveElement = NULL;
	_clickEffectMc = NULL;
	clickEffect = NULL;
	init();
	startListener();
	g_pHero = 0;
	setIsTouchMoveBegin(false);
}

BaseScene::~BaseScene(void)
{
}

bool BaseScene::init()
{
    if ( !CCLayer::init() )
	{
		return false;
	}
    
	_frontBGLayer = new LayerNode();
	_faceLayer = new LayerNode();
	_elementLayer = new LayerNode();
	//_frontLayer = new LayerNode(); // LH0713
	//_effectLayer = new LayerNode(); // LH0713
	_fightLayer = new LayerNode();
	_storyLayer = new LayerNode();
	_mouseLayer = new LayerNode();
	_movingLayer = new LayerNode();

	_movingLayer->addChild(_frontBGLayer);
	_movingLayer->addChild(_faceLayer);
	_movingLayer->addChild(_elementLayer);
	_movingLayer->addChild(_storyLayer);
	_movingLayer->addChild(_fightLayer);
	_movingLayer->addChild(_mouseLayer);
	//Doyang 20120712
	_frontBGLayer->release();
	_faceLayer->release();
	_elementLayer->release();
	_storyLayer->release();
	_fightLayer->release();
	_mouseLayer->release();

	
	addChild(_movingLayer);
	//Doyang 20120712
	_movingLayer->release();

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    m_screenWidth = screenSize.width;
    m_screenHeight = screenSize.height;

    this->setIsTouchEnabled(true);

	clickEffect = g_pKKAnimationFactory->registAni("assets/effect/mouse/mouseClick.plist", "mouse_%d.png", 9, 0.1f);
	//_clickEffectMc = CCSprite::spriteWithFile("HelloWorld.png");
	_clickEffectMc = new CCSprite();
	_clickEffectMc->init();
	_clickEffectMc->setIsVisible(false);
	_mouseLayer->addChild(_clickEffectMc);
	//Doyang 20120712
	_clickEffectMc->release();

	return true;
}

void BaseScene::startListener()
{
	addEventListener(SceneConst::CHANGE_POSITION_Y, this, callfuncND_selector(BaseScene::playerChangePositionHandler));
}

void BaseScene::playerChangePositionHandler(CCNode* n, void* data)
{
	_depthChanged = true;
}

void BaseScene::buildScene(int width, int height, int mapRank, int offsetX, int offsetY,std::string path, CCPoint focusPos)
{
	dispose();

	if(_frontbg == NULL)
	{
		_frontbg = new BgBitmap;
		_frontbg->init();//kevinz
	}
	//if(_frontbg->getParent() == NULL)
	//	_frontBGLayer->addChild(_frontbg);

	_frontbg->build(width, height, path, offsetX, offsetY);

	_frontbg->load(NULL, focusPos, NULL, NULL); //Kenfly 20121114

	if(_frontbg->getParent() == NULL)
	{
		_frontBGLayer->addChild(_frontbg);
	}
	_movingLayer->setPosition(focusPos);

	setIsVisible(true);

	//addMapNPC();

	//GPH 2012.3.27 
	//addMapGroupMonster();


	
}

//void BaseScene::addRole()
//{
//	if(_role == NULL)
//    _role = new Player();
//    CCSprite * playerSprite = _role->loadPlayer();
//	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
//	if(!info)
//		return;
//
//    CCPoint cp = ccp(info->playerBaseInfo.x, info->playerBaseInfo.y);
//
//	CCPoint pos = _frontbg->getMapPos();
//	CCSize size = _frontbg->getMapSizeV();
//	_role->setStartPointByMapCell(cp, pos, size.height, size.width);
//
//	
//
//	SceneProxy* sp = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
//	if((!sp) || (!sp->_sceneInfoVo))
//		return;
//
//	int map_w = int(ceil((sp->_sceneInfoVo->width) / 60.0f));
//	int map_h = int(ceil((sp->_sceneInfoVo->height) / 30.0f));
//
//	_role->setFindPath8((char**)(sp->_sceneInfoVo->mapData), map_h, map_w);
//
//
//	_role->setPlayerVo(info->playerBaseInfo,1);
//	//this->addChild(playerSprite);
//	addChild(_role);
//	g_pHero = _role;
//}

CCPoint BaseScene::getElemenetPosition(float vx, float vy)
{
	CCPoint point = TileUtil::Instance()->changeTileToPixs( ccp(vx, vy));
	CCPoint pos = ccp(0.0f, 0.0f);
	CCSize size;
	if(_frontbg)
	{
		pos = _frontbg->getPosition();
		size = _frontbg->getMapSizeV();
	}
	else
	{
		pos.x = m_screenWidth / 2;
		pos.y = m_screenHeight / 2;
		size.width = m_screenWidth;
		size.height = m_screenHeight;
	}
	//CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCPoint cp;
	cp.x = point.x + pos.x - (float)(size.width) / 2.0f;
	cp.y = pos.y + (float)(size.height) / 2.0f - point.y;
	return cp;
}

CCPoint BaseScene::getElemenetPositionByRealPos(float vx, float vy)
{
	return ccp(vx, vy);//kevinchange1
	CCPoint point =ccp(vx, vy);
	CCPoint pos = ccp(0.0f, 0.0f);
	CCSize size;
	if(_frontbg)
	{
		pos = _frontbg->getPosition();
		size = _frontbg->getMapSizeV();
	}
	else
	{
		pos.x = m_screenWidth / 2;
		pos.y = m_screenHeight / 2;
		size.width = m_screenWidth;
		size.height = m_screenHeight;
	}
	//CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCPoint cp;
	cp.x = point.x + pos.x - (float)(size.width) / 2.0f;
	cp.y = pos.y + (float)(size.height) / 2.0f - point.y;
	return cp;
}

/**
*  
* @param focusPos
* 
*/
void BaseScene::focusPosChangeHandler(CCPoint focusPos)
{
	_focusPos = focusPos;
	_positionChanged = true;
	//_frontBGLayer->setPosition(focusPos);
	//_frontbg->load(NULL, focusPos);
	_oldPos = focusPos;

}

void BaseScene::step_old(ccTime dt)
{
    setPlayerCenter();

	/*if(getDistanceBetweenTwoSprite(_role->getPlayerSprite(), npc1->getNpcSprite()) < 20)
	{
		CCLog("begin fighting------");
		this->unschedule(schedule_selector(BaseScene::step));
		g_pBattleManager->sendBattleRequestHandler();
	}*/

	//mapNPCStep();
	//mapMonstersStep();
}

void BaseScene::mapNPCStep()
{
	// NPC distance Temp!!!
	/*std::map<int, MapNPC*>::iterator it = _MapNPCDic.begin();
	while( it != _MapNPCDic.end() )
	{
		MapNPC* pMapNPC = it->second;
		if ( pMapNPC->canTalk() )
		{
			if ( pMapNPC->getTalkVisible() )
			{
				if ( pMapNPC->m_TalkVisibleTimer->isExpired() )
				{
					pMapNPC->setTalkVisible( false );
				}

			} 
			else
			{
				CCPoint pos1 = ccp(0.0f, 0.0f);
				CCPoint pos2 = ccp(0.0f, 0.0f);

				if(g_pHero)
					pos1 = g_pHero->getPosition();

				if(pMapNPC->getNpcSprite())
					pos2 = pMapNPC->getNpcSprite()->getPosition();

				if(  getDistanceBetweenTwoSprite(pos1, pos2) < MapNPC::gsTalkDistance  )
				{
					pMapNPC->setTalkVisible( true );
				}
			}

		}
		it++;
	}*/

	//// view 
	//DialogView* pDialogueView = ViewManager::getInstance()->dialogView;
	//if ( pDialogueView && pDialogueView->getisPop() )
	//{
	//	pDialogueView->setisPop( false );
	//}
}

void BaseScene::setPlayerCenter()
{
	if(!_frontbg)
		return;

	CCSprite* sprite = NULL;
	if(_role)
      sprite =_role->getPlayerSprite();
    
    if(sprite == NULL)
    {
        CCLog("Player sprite null in BaseScene::setPlayerCenter()");
        return;
    }

    CCPoint pt = sprite->getPosition();
    CCPoint pt_layer = this->getPosition();
	CCPoint pt_map = _frontbg->getMapPos();
    float x = pt.x - m_screenWidth / 2.0f + pt_layer.x;
    float y = pt.y - m_screenHeight / 2.0f + pt_layer.y;
    
    if(x == 0.0f && y == 0.0f && m_needStep)
    {
        //this->unschedule(schedule_selector(BaseScene::step));
        m_needStep = false;
        return;
    }
    
    float r = sqrt(x * x + y * y);
    float rate_x = x / r * 3.0f;
    float rate_y = y / r * 3.0f;

    
    
    float scale_x = pt_map.x + pt_layer.x - rate_x;
    float scale_y = pt_map.y + pt_layer.y - rate_y;
    
	m_mapHeight = (float)(_frontbg->_h);
	m_mapWidth = (float)(_frontbg->_w);
	
    if((scale_x < (m_screenWidth - (m_mapWidth / 2.0f)))
       || (scale_x > (m_mapWidth / 2.0f)))
    {
        //CCLog("Set rate_x to 0");
        rate_x = 0.0f;
    }
    
    if((scale_y < (m_screenHeight - (m_mapHeight / 2.0f)))
       || (scale_y > m_mapHeight / 2.0f))
    {
        //CCLog("Set rate_y to 0");
        rate_y = 0.0f;
    }
    
    if(rate_x == 0.0f && rate_y == 0.0f)
    {
        //this->unschedule(schedule_selector(BaseScene::step));
        return;
    }
    
    this->setPosition(ccp(pt_layer.x - rate_x, pt_layer.y - rate_y));
    
    if(x <= 3.0f && x >= -3.0f && rate_y == 0.0f)
    {
        this->setPosition(ccp(m_screenWidth / 2.0f - pt.x, pt_layer.y));
        //this->unschedule(schedule_selector(MapLayer::step));
    }
    else if(y <= 3.0f && y >= -3.0f && rate_x == 0.0f)
    {
        this->setPosition(ccp(pt_layer.x, m_screenHeight / 2.0f - pt.y));
        //this->unschedule(schedule_selector(MapLayer::step));
    }
    else if(x <= 3.0f && x >= -3.0f && y <= 3.0f && y >= -3.0f)
    {
        
        this->setPosition(ccp(m_screenWidth / 2.0f - pt.x, m_screenHeight / 2.0f - pt.y));
        //this->unschedule(schedule_selector(MapLayer::step));
    }
    
    pt_layer = this->getPosition();
	_frontbg->load(this, pt_layer, NULL, NULL); //Kenfly 20121114
}

void BaseScene::clickSceneHandler(CCPoint point)
{
}

void BaseScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
    if(pTouches->count())
    {
    }

// 	if(figureM == NULL)
// 	{
// 		figureM = (FigureMediator*)g_pFacade->retrieveMediator(AppFacade_FIGURE_MEDIATOR);
//		figureM->openFigureView();
// 	}
// 	else
// 	{
// 		figureM->closeFigureView();
// 		figureM = NULL;
// 	}
	


    
    CCSetIterator iteratorTouch = pTouches->begin();
    CCTouch  * touchPoint = (cocos2d::CCTouch *)(* iteratorTouch);
    CCPoint pointLocation = touchPoint->locationInView(touchPoint->view());
    

	return;
	

	/*
    CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCPoint pos = _frontbg->getMapPos();
    CCPoint pos_layer = this->getPosition();

	CCSize mapSize = _frontbg->getMapSizeV();
	float h = mapSize.height;
	float w = mapSize.width;


    _role->setEndPointByScreen(pointLocation, pos, pos_layer, h, w);
    _role->stopAnimation();
    _role->setCurrentStartPoint(pos, h, w);
    int map_h = MAX_CELLS_Y;
    int map_w = MAX_CELLS_X;

	_role->playerMove();

    
    m_needStep = true;
    return;*/
}

void BaseScene::ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCSetIterator iteratorTouch = pTouches->begin();
	CCTouch  * touchPoint = (cocos2d::CCTouch *)(* iteratorTouch);
	CCPoint pointLocation = touchPoint->locationInView(touchPoint->view());
	_cureentPoint = pointLocation;

	if (!getIsHideDetectBegin())
	{
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(BaseScene::moveFollowHideUIHandler),this,0.5f,false);
		setIsHideDetectBegin(true);
	}
	if (!getIsTouchMoveBegin())
	{
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(BaseScene::moveFollowHandler),this,0.1f,false);
		setIsTouchMoveBegin(true);
	}
}

void BaseScene::ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCSetIterator iteratorTouch = pTouches->begin();
	CCTouch  * touchPoint = (cocos2d::CCTouch *)(* iteratorTouch);
	CCPoint pointLocation = touchPoint->locationInView(touchPoint->view());
	_cureentPoint = pointLocation;

	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(BaseScene::moveFollowHideUIHandler),this);
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(BaseScene::moveFollowHandler),this);


	if (!g_pGlobalManage->isInStory && !g_pGlobalManage->_isInFight && !g_pGlobalManage->getIsInWordMap())
	{
		g_pGlobalManage->showAllUI(true);
	}

	if (getIsHideDetectBegin())
	{
		setIsHideDetectBegin(false);
	}
	if (getIsTouchMoveBegin())
	{
		setIsTouchMoveBegin(false);
	}

	clickSceneHandler(pointLocation);
}

void BaseScene::moveFollowHandler(ccTime dt)
{
	if (!g_pGlobalManage->isInStory && !g_pGlobalManage->_isInFight)
	{
		clickSceneHandler(_cureentPoint);
	}
	else
	{
		CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(BaseScene::moveFollowHandler),this);
	}
}

void BaseScene::moveFollowHideUIHandler(ccTime dt)
{
	g_pGlobalManage->showAllUI(false);

	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(BaseScene::moveFollowHideUIHandler),this);
}

void BaseScene::moveStep(ccTime dt)
{
	if(!_role)
		return;

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    
    double  deltaX = _role->getEndPoint()->x-screenSize.width/2;
    double deltaY = _role->getEndPoint()->y-screenSize.height/2;
    int length = sqrt(deltaX * deltaX +deltaY * deltaY);
    float rateX = 0.0f;
    float rateY = 0.0f;
    if(length != 0)
    {
        rateX = (float)deltaX / (float)length;
        rateY = (float)deltaY / (float)length;
    }

	if(!_frontbg)
		return;

    const CCPoint map_pos = _frontbg->getMapPos();
    
    int map_pos_x = (int)map_pos.x;
    int map_pos_y = (int)map_pos.y;
    
    CCPoint playerPosPixs;

    //playerPosPixs.x =  Map::getInstance()->getMapSprite()->getContentSizeInPixels().width/2 - Map::getInstance()->getMapSprite()->getPosition().x + screenSize.width/2;
    //playerPosPixs.y =  Map::getInstance()->getMapSprite()->getContentSizeInPixels().height/2 + Map::getInstance()->getMapSprite()->getPosition().y - screenSize.height/2;
    
	CCSize size = _frontbg->getMapSize();
	playerPosPixs.x = size.width / 2.0f - map_pos.x + screenSize.width / 2.0f;
	playerPosPixs.y = size.height / 2.0f - map_pos.y - screenSize.height / 2.0f;

    CCPoint playerPosCells;
    playerPosCells.x =  playerPosPixs.x/TILE_WIDTH;
    playerPosCells.y =  playerPosPixs.y/TILE_HEIGHT;
    
    int xPlayer = (int)playerPosCells.x;
    int yPlayer = (int)playerPosCells.y;
    int xEnd = (int)this->m_cusPointByMapCells.x;
    int yEnd = (int)this->m_cusPointByMapCells.y;
    
    
    if(((map_pos_x - int(rateX * 2.0f)) <  ((m_mapWidth / 2  - (int)(screenSize.width)) * -1 ) || (map_pos_x - int(rateX * 2.0f)) > (m_mapWidth / 2))
       && ( (map_pos_y - int(rateY * 2.0f)) < ((m_mapHeight / 2 - (int)(screenSize.height)) * -1) || (map_pos_y - int(rateY * 2.0f)) > (m_mapHeight / 2)) )
    {
        this->unschedule(schedule_selector(BaseScene::moveStep));

        return;
    }
 
    float map_dest_pos_x = 0.0f;
    float map_dest_pos_y = 0.0f;
    
    if((map_pos_x - int(rateX * 2.0f)) >  ((m_mapWidth / 2  - (int)(screenSize.width)) * -1 ) && (map_pos_x - int(rateX * 2.0f)) < (m_mapWidth / 2))
    {  
        map_dest_pos_x = (float)(_role->getStartPoint()->x) - rateX * 2.0f;
    }
    else
    {
        map_dest_pos_x = (float)(_role->getStartPoint()->x);
    }
    
    if((map_pos_y - int(rateY * 2.0f)) > ((m_mapHeight / 2 - (int)(screenSize.height)) * -1) && (map_pos_y - int(rateY * 2.0f)) < (m_mapHeight / 2))
    {
        map_dest_pos_y = (float)(_role->getStartPoint()->y) - rateY * 2.0f;
    }
    else
    { 
        map_dest_pos_y = (float)(_role->getStartPoint()->y);
    }
    
    CCLOG("********%f,%f", map_dest_pos_x, map_dest_pos_y);
    
    _frontbg->setMapPos(ccp(map_dest_pos_x, map_dest_pos_y));
    
    _role->setStartPoint(map_dest_pos_x, map_dest_pos_y);
    
    
    CCLog("=======%d,%d,%d, %d",xPlayer , yPlayer,xEnd,yEnd);
    if((xPlayer == xEnd) && (yPlayer == yEnd))
    {
        this->unschedule(schedule_selector(BaseScene::moveStep));
        return;
    }
}

void BaseScene::setCusPointByScreenPixels(float x,float y)
{
    this->m_cusPointByScreenPixels.x = x;
    this->m_cusPointByScreenPixels.y = y;
}

CCPoint * BaseScene::getCusPointByScreenPixels()
{
    return &m_cusPointByScreenPixels;
}

CCPoint * BaseScene::getCusPointByMapPixels(CCPoint *cpScreen)
{
	if(!_frontbg)
		return NULL;

    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();

    //m_cusPointByMapPixels.x = cpScreen->x + Map::getInstance()->getMapSprite()->getContentSizeInPixels().width/2 - Map::getInstance()->getMapSprite()->getPosition().x;
    //m_cusPointByMapPixels.y = Map::getInstance()->getMapSprite()->getContentSizeInPixels().height/2 + Map::getInstance()->getMapSprite()->getPosition().y - screenSize.height + cpScreen->y;
    
	CCSize size;
	CCPoint map_pos;
	if(_frontbg)
	{
		size = _frontbg->getMapSize();
		map_pos = _frontbg->getMapPos();
	}

	m_cusPointByMapPixels.x = cpScreen->x + size.width / 2.0f - map_pos.x;
	m_cusPointByMapPixels.y = size.height / 2.0f + map_pos.y - screenSize.height + cpScreen->y;
    

	return &m_cusPointByMapPixels;
}

CCPoint * BaseScene::getCusPointByMapCells(CCPoint * cpPixels,int nTileW,int nTileH)
{
	if(!cpPixels)
		return NULL;

    if((0 == nTileW)||(0 == nTileH))
    {
        return cpPixels;
    }
    m_cusPointByMapCells.x =  cpPixels->x / nTileW;
    m_cusPointByMapCells.y =  cpPixels->y / nTileH;
    return &m_cusPointByMapCells;
}

CCPoint * BaseScene::getCusPointByMapPixels()
{
    return &m_cusPointByMapPixels;
}

void BaseScene::menuCloseCallback(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//int BaseScene::getDistanceBetweenTwoSprite(CCSprite* sp1, CCSprite* sp2)
int BaseScene::getDistanceBetweenTwoSprite(CCPoint pos1, CCPoint pos2)
{
    double dis_x = (int)pos1.x - (int)pos2.x;
    double dis_y = (int)pos1.y - (int)pos2.y;
    int dis = sqrt(dis_x * dis_x + dis_y * dis_y);
    return dis;
}

void BaseScene::addMapNPC()
{
	// ADD MAP NPC
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;
	int mapId = info->playerBaseInfo._mapId;
	std::vector<int> MapVec = NPCManager::Instance()->getNpcsByMapId(mapId);

	for ( std::vector<int>::iterator itVector = MapVec.begin(); itVector != MapVec.end(); itVector++ )
	{
		int iNPCID = *itVector;

		NPCVo* pNPCVo = NPCManager::Instance()->getNPC( iNPCID );
		addNPC( pNPCVo );
	}
}

MapNPC* BaseScene::addNPC(NPCVo* pNPCVo)
{
	if(!pNPCVo)
		return NULL;

	/*std::map<int, MapNPC*>::iterator it = _MapNPCDic.find( pNPCVo->id );
	if ( it != _MapNPCDic.end() )
	{
	cocos2d::CCLog("MapLayer::addNPC twice!");
	return NULL;
	}
	*/
	MapNPC* pMapNPC = new MapNPC(pNPCVo);
	//kevine
	if(!pMapNPC)
		return NULL;
	


	char tmp[32] = {0};
	std::string s = NPC_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), pNPCVo->id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter != _elementDic.end())
	{
		removeNPC(pNPCVo->id);
	}
	_elementDic.insert(make_pair(tmp_str, pMapNPC));

	//_MapNPCDic.insert( make_pair(pNPCVo->id, pMapNPC) );

	pMapNPC->addEventListener(SceneConst::DEAD_EVENT, this, callfuncND_selector(BaseScene::npcDeadHandler));
	pMapNPC->addEventListener(SceneConst::REMOVE_NPC_DEADBODY_EVENT, this, callfuncND_selector(BaseScene::removeNPCDeadbodyHandler));
	pMapNPC->addEventListener(SceneConst::CHANGE_POSITION, this, callfuncND_selector(BaseScene::npcLayout));

	pMapNPC->loadModel(); //modify by Kenfly 20121106
	CCPoint pos_layer = _elementLayer->getPosition();
	CCSize size;
	CCPoint pos;
	if(_frontbg)
	{
		size = _frontbg->getMapSizeV();
		pos = _frontbg->getPosition();
	}
	else
	{
		size.width = m_screenWidth;
		size.height = m_screenHeight;
		pos.x = m_screenWidth / 2;
		pos.y = m_screenHeight / 2;
	}
	if(pNPCVo->_isCell)
	{
		pMapNPC->setStartPointByMapCell(ccp(pNPCVo->x, pNPCVo->y), pos, pos_layer, size.height, size.width );
	}
	else
	{
		pMapNPC->setStartPointByMap(ccp(pNPCVo->x, pNPCVo->y), pos, pos_layer, size.height, size.width );
		pMapNPC->setPosition(ccp(pNPCVo->x, pNPCVo->y + POSX(44)));//kc1019
	}
	//_movingLayer->addChild( pMapNPC );

// 	if (g_pGlobalManage&&g_pGlobalManage->isInStory)
// 	{
// 		if (pMapNPC->_iconMc)

// 		{
// 			pMapNPC->_iconMc->setIsVisible(false);

// 		}		
// 	}

	// loghui modify
	if (g_pGlobalManage->getisInFight())
	{
		addElement(pMapNPC, POSX(640)-pMapNPC->getPosition().y);//kevinchange0808 
	}
	else
	{
		addElement(pMapNPC, pNPCVo->y);
	}

	return pMapNPC;
}
//
//void BaseScene::addMapGroupMonster()
//{
//	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
//	if(!info)
//		return;
//	//int mapId = info->playerBaseInfo._mapId;
//
//	std::list<GMProgressVo*> gmProgressVo=MonsterManager::Instance()->getGroupMonsterByMapId(1054);
//
//	std::list<GMProgressVo*>::iterator gmIt;
//	for(gmIt=gmProgressVo.begin();gmIt!=gmProgressVo.end();gmIt++)
//	{
//		GMProgressVo* gmpro=*gmIt;
//		addGroupMonster(gmpro);
//	}
//
//}
//
//void BaseScene::addGroupMonster(GMProgressVo* gmpVo)
//{
//	if(!gmpVo)
//		return;
//
//	std::map<int, MapMonsters*>::iterator it = _MapMonstersDic.find(gmpVo->id);
//	if ( it != _MapMonstersDic.end() )
//	{
//		cocos2d::CCLog("MapLayer::addMonsterGroup twice!");
//		return;
//	}
//	MapMonsters* pMapMonsters=new MapMonsters(gmpVo);
//
//	if(pMapMonsters)
//	{
//		_MapMonstersDic.insert(make_pair(gmpVo->id,pMapMonsters ));
//
//		CCSprite* pCCSprite = pMapMonsters->loadMonster();
//		CCPoint pos_layer;
//		CCPoint pos_map;
//		if(_elementLayer)
//			pos_layer = _elementLayer->getPosition();
//		if(_frontbg)
//			pos_map = _frontbg->getMapPos();
//		pMapMonsters->setStartPointByMapCell( ccp(gmpVo->x, gmpVo->y), pos_map, pos_layer, m_mapHeight, m_mapWidth );
//		if(_movingLayer)
//			_movingLayer->addChild( pCCSprite );
//	}
//}
//
//void BaseScene::mapMonstersStep()
//{
//	std::map<int, MapMonsters*>::iterator it;
//	for(it=_MapMonstersDic.begin();it!=_MapMonstersDic.end();it++)
//	{
//		MapMonsters* pMapMonsteres = it->second;
//		if (pMapMonsteres && pMapMonsteres->canTalk() )
//		{
//			if ( pMapMonsteres->getTalkVisible() )
//			{
//				if (pMapMonsteres->m_TalkVisibleTimer
//					&& pMapMonsteres->m_TalkVisibleTimer->isExpired() )
//				{
//					pMapMonsteres->setTalkVisible( false );
//				}
//
//			} 
//			else
//			{
//				CCPoint pos1 = ccp(0.0f, 0.0f);
//				CCPoint pos2 = ccp(0.0f, 0.0f);
//
//				if(g_pHero)
//					pos1 = g_pHero->getPosition();
//
//				if(pMapMonsteres->getMonsterSprite())
//					pos2 = pMapMonsteres->getMonsterSprite()->getPosition();
//
//				if(  getDistanceBetweenTwoSprite(pos1, pos2) < MapMonsters::gsTalkDistance  )
//				{
//					pMapMonsteres->setTalkVisible( true );
//					//if(getDistanceBetweenTwoSprite( g_pHero->getPlayerSprite(), pMapMonsteres->getMonsterSprite() ) < 80)
//					//{
//					//	////GPH 2012.3.28
//					//	g_pBattleManager->sendBattleRequestHandler();
//					//	cocos2d::CCLog("g_pBattleManager->sendBattleRequestHandler();");
//					//}
//				}
//			}
//				
//		}
//	}
//}

 /////////////////////////////////////
/**
* @param endScenePoint
* @param ranger
* 
*/
void BaseScene::roleMove(CCPoint endScenePoint, float ranger)
{
	struct Data
	{
		CCPoint endPoint;
		float ranger;
		Data()
		{
			ranger = 0.0f;
		}
	} data;

	data.endPoint = endScenePoint;
	data.ranger = ranger;
	dispatchEvent(SceneConst::ROLE_MOVE, &data);
	//this.dispatchEvent(new ParamEvent(ROLE_MOVE,{endPoint:endScenePoint,ranger:ranger}));
}

void BaseScene::movePath(std::vector<CCPoint>& scenePath)
{
	if(scenePath.size() == 0)
		return;

	CCPoint pos = scenePath.back();


	showClickEffect(pos.x, pos.y);
	if(_role)
		_role->movePath(scenePath);
}

/**
* 
* @param e
* 
*/
void BaseScene::playerDeadHandler(CCNode* n, void* data)
{
	Player* player = (Player*)data;
	removeElement(player);
	addFaceElement(player);
}

/**
* 
* @param e
* 
*/
void BaseScene::playerLayout(CCNode* n, void* data)
{
	if(!data)
		return;

	struct Data
	{
		bool first;
		Element* player;
	};

	Data* d = (Data*)data;
	d->first = false;

	dispatchEvent(SceneConst::ELEMENT_LAYOUT, (void*)d);

}

/*************************************************************/

Player* BaseScene::addPlayerHandler(PlayerBaseVo* playerVo)
{
	if(!playerVo)
		return NULL;

	Player* player = addPlayer(playerVo);

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::CREATE_PALYER_FINISH, (void*)(&(playerVo->path)));
		//GameDispatcher.getInstance().dispatchEvent(new ParamEvent(GameDispatcher.CREATE_PALYER_FINISH, playerVo.path));
	return player;
}

Player* BaseScene::addTradePlayerHandler(PlayerBaseVo* playerVo)
{
	if(!playerVo)
		return NULL;

	Player* player = addTradePlayer(playerVo);

	//sendNotification(Facade_Command, AppFacade_SCENEPROXY_COMMAND, (char*)cmd, SceneProxyCommand::MOVE_PLAYER);
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::CREATE_TRADEPALYER_FINISH, (void*)(&(playerVo->path)));

	return player;
}

Player* BaseScene::addTradePlayer(PlayerBaseVo* playerVo)
{
	if(!playerVo)
		return NULL;

	char tmp[32] = {0};
	std::string s = TRADEPLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), playerVo->accountId);
	std::string tmp_str(tmp);
	std::map<string, IElement*>::iterator iter = _elementDic.find(tmp);
	if(iter != _elementDic.end())
	{
		if(_role && playerVo->accountId != _role->_id)
		{
			removePlayer(playerVo->accountId);
		}
	}

	Player* player = new Player();
	player->setPlayerVo(*playerVo);
	player->addEventListener(SceneConst::DEAD_EVENT, this, callfuncND_selector(BaseScene::playerDeadHandler));
	player->addEventListener(SceneConst::REMOVE_PLAYER_DEADBODY_EVENT, this, callfuncND_selector(BaseScene::removePlayerDeadbodyHandler));
	player->addEventListener(SceneConst::CHANGE_POSITION, this, callfuncND_selector(BaseScene::playerLayout));

	player->addEventListener(SceneConst::TRADE_WALK_START_NODE, this, callfuncND_selector(Scene::tradeWalkStartNodeHandler));


	_elementDic.insert(make_pair(tmp_str, player));
	CCPoint pos;
	CCPoint point;
	if(playerVo->_isCell)
	{
		pos = getElemenetPosition(playerVo->x, playerVo->y);
		point = TileUtil::Instance()->changeTileToPixs( ccp(playerVo->x, playerVo->y));
	}
	else
	{
		pos = getElemenetPositionByRealPos(playerVo->x, playerVo->y);
		pos.y += POSX(44);//kc1019
		point = ccp(playerVo->x, playerVo->y);
	}
	player->setPosition(pos);

	player->mapStartPoint(point);


	{
		addElement(player,playerVo->y); // LH0714 zOrder
	}
	
	struct Data
	{
		bool first;
		Player* player;
		Data()
		{
			first = true;
			player = NULL;
		}
	};
	Data d;
	d.first = true;
	d.player = player;

	dispatchEvent(SceneConst::ELEMENT_LAYOUT, (void*)(&d));

	if(_isHidePlayer)
	{
		player->hide();
	}
	return player;
}

Player* BaseScene::addPlayer(PlayerBaseVo* playerVo)
{
	if(!playerVo)
		return NULL;

	char tmp[32] = {0};
	std::string s = PLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), playerVo->accountId);
	std::string tmp_str(tmp);
	std::map<string, IElement*>::iterator iter = _elementDic.find(tmp);
	if(iter != _elementDic.end())
	{
		if(_role && playerVo->accountId != _role->_id)
		{
			removePlayer(playerVo->accountId);
		}
	}

	Player* player = new Player(playerVo);
	player->setPlayerVo(*playerVo);
	player->addEventListener(SceneConst::DEAD_EVENT, this, callfuncND_selector(BaseScene::playerDeadHandler));
	player->addEventListener(SceneConst::REMOVE_PLAYER_DEADBODY_EVENT, this, callfuncND_selector(BaseScene::removePlayerDeadbodyHandler));
	player->addEventListener(SceneConst::CHANGE_POSITION, this, callfuncND_selector(BaseScene::playerLayout));

	//char tmp1[32] = {0};
	//sprintf(tmp1, "%s%d", s.c_str(), playerVo->accountId);
	//std::string tmp_str1(tmp1);
	_elementDic.insert(make_pair(tmp_str, player));
	CCPoint pos;
	CCPoint point;
	if(playerVo->_isCell)
	{
		pos = getElemenetPosition(playerVo->x, playerVo->y);
		point = TileUtil::Instance()->changeTileToPixs( ccp(playerVo->x, playerVo->y));
	}
	else
	{
		pos = getElemenetPositionByRealPos(playerVo->x, playerVo->y);
		pos.y += POSX(44);//kc1019
		point = ccp(playerVo->x, playerVo->y);
	}
	player->setPosition(pos);
	
	//CCPoint point = TileUtil::Instance()->changeTileToPixs( ccp(playerVo->x, playerVo->y));
	player->mapStartPoint(point);


	// loghui modify
	if (g_pGlobalManage->getisInFight())
	{
		addElement(player, POSX(640) - playerVo->y);//kevinchange0808
	}
	else
	{
		addElement(player,playerVo->y); // LH0714 zOrder
	}

	g_pHero = _role;

	struct Data
	{
		bool first;
		Player* player;
		Data()
		{
			first = true;
			player = NULL;
		}
	};
	Data d;
	d.first = true;
	d.player = player;

	dispatchEvent(SceneConst::ELEMENT_LAYOUT, (void*)(&d));

	if(_isHidePlayer)
	{
		player->hide();
	}
	return player;
}

/**
* 
* @param playerVo
* 
*/
void BaseScene::removePlayer(int accId)
{
	//int id = accId;
	char tmp[32] = {0};
	std::string s = PLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), accId);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter == _elementDic.end())
	{
		return;
	}

	IElement* pIElement = iter->second;//jae note
	if(!pIElement)
	{
		_elementDic.erase(iter);
		return;
	}

	if(clickTarget && clickTarget->type() == PLAYER_TYPE 
		&& clickTarget->id() == pIElement->id())
		cancelClickTarget();

	Player* player = (Player*)pIElement;
	if(player)
	{
		player->removeEventListener(SceneConst::DEAD_EVENT);
		player->removeEventListener(SceneConst::REMOVE_PLAYER_DEADBODY_EVENT);
		player->removeEventListener(SceneConst::CHANGE_POSITION);
	}

	std::vector<IElement*>::iterator iterElment = _elementList.begin();//jae note
	for(; iterElment != _elementList.end(); ++iterElment)
	{
		if(*iterElment == pIElement)
		{
			_elementList.erase(iterElment);
			break;
		}
	}

	std::vector<IElement*>::iterator iterFace = _faceList.begin();
	for(; iterFace != _faceList.end(); ++iterFace)
	{
		if(*iterFace == pIElement)
		{
			_faceList.erase(iterFace);
			break;
		}
	}

	//Doyang 20120713
	pIElement->dispose();
	if(pIElement && pIElement->getParent())
		pIElement->removeFromParentAndCleanup(true);
	/*removeElement(pIElement);
	removeFaceElement(pIElement);

	player->dispose();*/
	//delete iter->second;
	_elementDic.erase(iter);

	//Doyang 20120713
	//CC_SAFE_DELETE(player);
}


void BaseScene::removeTradePlayer(int accId)
{
	//int id = accId;
	char tmp[128] = {0};
	std::string s = TRADEPLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), accId);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter == _elementDic.end())
	{
		return;
	}

	IElement* pIElement = iter->second;//jae note
	if(!pIElement)
	{
		_elementDic.erase(iter);
		return;
	}

	if(clickTarget && clickTarget->type() == TRADEPLAYER_TYPE 
		&& clickTarget->id() == pIElement->id())
		cancelClickTarget();

	Player* player = (Player*)pIElement;
	if(player)
	{
		player->removeEventListener(SceneConst::DEAD_EVENT);
		player->removeEventListener(SceneConst::REMOVE_PLAYER_DEADBODY_EVENT);
		player->removeEventListener(SceneConst::CHANGE_POSITION);

		player->removeEventListener(SceneConst::TRADE_WALK_START_NODE);
	
	}

	std::vector<IElement*>::iterator iterElment = _elementList.begin();//jae note
	for(; iterElment != _elementList.end(); ++iterElment)
	{
		if(*iterElment == pIElement)
		{
			_elementList.erase(iterElment);
			break;
		}
	}

	std::vector<IElement*>::iterator iterFace = _faceList.begin();
	for(; iterFace != _faceList.end(); ++iterFace)
	{
		if(*iterFace == pIElement)
		{
			_faceList.erase(iterFace);
			break;
		}
	}

	pIElement->dispose();
	if(pIElement && pIElement->getParent())
		pIElement->removeFromParentAndCleanup(true);
	_elementDic.erase(iter);
}

void BaseScene::playerMove(int id, std::vector<CCPoint>& path)
{
	char tmp[32] = {0};
	std::string s = PLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter == _elementDic.end())
	{
		return;
	}

	if(iter->second == NULL)
	{
		_elementDic.erase(iter);
		return;
	}
	CCLog("player start move:");
	((Player*)(iter->second))->movePath(path);
	CCLog("player move:end");
}

void BaseScene::tradeplayerMove(int id, std::vector<CCPoint>& path)
{
	char tmp[32] = {0};
	std::string s = TRADEPLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter == _elementDic.end())
	{
		return;
	}

	if(iter->second == NULL)
	{
		_elementDic.erase(iter);
		return;
	}
	CCLog("player start move:");
	((Player*)(iter->second))->movePath(path);
	CCLog("player move:end");
}

///////////////////////////

/*================================================================*/
		
void BaseScene::addElement(IElement* child, int zOrder)
{
	if(!child)
		return;

	CCPoint pos = child->getPosition();
	if(child->getParent() == NULL && _elementLayer)
	{
		_elementLayer->addChild(child, zOrder);
		child->release();
	}
	
	bool had = false;
	std::vector<IElement*>::iterator it = _elementList.begin();
	for(; it != _elementList.end(); ++it)
	{
		if(*it == child)
		{
			had = true;
			break;
		}
	}
	if(!had)
	{
		_elementList.push_back(child);
	}
	_depthChanged = true;

	//Begin Kenfly 20121025
	child->addEventListener(SceneConst::CHANGE_POSITION_Y, this, callfuncND_selector(BaseScene::playerChangePositionHandler));
	//End Kenfly 20121025
}
		
/**
	* 
	* @param displayObject
	* 
	*/		
void BaseScene::removeElement(IElement* displayObject)
{
	if(displayObject == NULL)
		return;

	if(displayObject->getParent() == _elementLayer && _elementLayer)
	{
		_elementLayer->removeChild(displayObject, true);
	}
	
	//std::vector<IElement*>::iterator iter = _elementList.begin();
	//for(; iter != _elementList.end(); ++iter)
	//{
	//	if(*iter == displayObject)
	//	{
	//		_elementList.erase(iter);
	//		break;
	//	}
	//}
}
		
		
void BaseScene::removeAllElement()
{
	if(_elementList.size() == 0)
		return;

	std::vector<IElement*>::iterator iter = _elementList.begin();
	for(; iter != _elementList.end(); ++iter)
	{
		if((*iter) != NULL && (*iter)->getParent() == _elementLayer && _elementLayer)
			_elementLayer->removeChild(*iter, false);
	}
	_elementList.clear();
}
		
/*================================================================*/

/*================================================================*/
		
/**
	*
	* 
	*/		
void BaseScene::addFaceElement(IElement* displayObject)
{
	if(!_faceLayer)
		return;
	if(displayObject->getParent() == NULL && _faceLayer)
	{
		CCPoint scalePoint;
		scalePoint.x = displayObject->getPosition().x;
		scalePoint.y = displayObject->getPosition().y;
		displayObject->setPosition(scalePoint);
		_faceLayer->addChild(displayObject);
		displayObject->release();
		_faceList.push_back(displayObject);
	}
}

void BaseScene::removeFaceElement(IElement* displayObject)
{
	if(displayObject == NULL)
		return;

	if(displayObject->getParent() == _faceLayer && _faceLayer) 
	{
		_faceLayer->removeChild(displayObject, true);
	}
	
	//std::vector<IElement*>::iterator iter = _faceList.begin();
	//for(; iter != _faceList.end(); ++iter)
	//{
	//	if(*iter == displayObject)
	//	{
	//		_faceList.erase(iter);
	//		break;
	//	}
	//}
}

void BaseScene::removeAllFaceElement()
{
	if(_faceList.size() == 0)
		return;

	std::vector<IElement*>::iterator iter = _faceList.begin();
	for(; iter != _faceList.end(); ++iter)
	{
		if((*iter) != NULL && (*iter)->getParent() == _faceLayer && _faceLayer)
			_faceLayer->removeChild(*iter, true);
	}
	_faceList.clear();
}
/*================================================================*/

/*=============================NPC===================================*/
/**
	* add npc 
	* @param npcVo
	* 
	*/
/*
MapNPC BaseScene::addNPC(npcVo* npcVo)
{
	if(_elementDic[ SceneConst.NPC_TYPE +  npcVo.id.toString()] )
	{
		removeNPC(npcVo.id);
	}

	MapNPC* npc = new MapNPC(npcVo);

	char tmp[32] = {0};
	std::string s = NPC_TYPE;
	sprintf(tmp, "%s%d", c.c_str(), npc->id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter != _elementDic.end())
		_elementDic.erase(iter);

	_elementDic.insert(make_pair(tmp_str, npc));

	CCPoint pos = npc->getElemenetPosition(npcVo->x, npcVo->y);
	npc->setPosition(pos);

	npc->addEventListener(SceneConst::DEAD_EVENT, npcDeadHandler);
	npc->addEventListener(SceneConst::REMOVE_NPC_DEADBODY_EVENT, removeNPCDeadbodyHandler);
	npc->addEventListener(SceneConst::CHANGE_POSITION, npcLayout);
	addElement(npc);
	
	struct Data
	{
		bool first;
		Npc* npc;
		Data()
		{
			first = true;
		}
	};

	Data d;
	d.first = true;
	d.npc = npc;
	dispatchEvent(ELEMENT_LAYOUT, (void*)(&d));

	return npc;
			
}
*/

void BaseScene::NPCColor(int id, cocos2d::ccColor3B color)
{
	MapNPC* p = getNPC(id);
	if (p)
	{
		p->color(color);
	}
}

void BaseScene::NPCName(int id, const char* name)
{
	MapNPC* p = getNPC(id);
	if (p)
	{
		p->name(name);
	}	
}

void BaseScene::showNPC(int id, bool val)
{
	char tmp[32] = {0};
	std::string s = NPC_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter2 = _elementDic.find(tmp_str);
	if(iter2 == _elementDic.end())
		return;

	IElement* pIElement = iter2->second;
	if(pIElement)//jae note
	{
		std::vector<IElement*>::iterator iterElment = _elementList.begin();
		for(; iterElment != _elementList.end(); ++iterElment)
		{
			if(*iterElment == pIElement)
			{
				pIElement->setIsVisible(val);
				break;
			}
		}
	}
}
/**
	*remove npc 
	* @param npcVo
	* 
	*/	
void BaseScene::removeNPC(int id)
{
	std::map<int, IElement*>::iterator iter = _findMonsterDic.find(id);
	if(iter != _findMonsterDic.end())
	{
		_findMonsterDic.erase(iter);
	}

	std::map<int, IElement*>::iterator iter1 = _findNpcDic.find(id);
	if(iter1 != _findNpcDic.end())
	{
		_findNpcDic.erase(iter1);
	}

	char tmp[32] = {0};
	std::string s = NPC_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter2 = _elementDic.find(tmp_str);
	if(iter2 == _elementDic.end())
		return;

	IElement* pIElement = iter2->second;
	if(pIElement)//jae note
	{
		pIElement->removeEventListener(SceneConst::DEAD_EVENT);
		pIElement->removeEventListener(SceneConst::REMOVE_NPC_DEADBODY_EVENT);
		pIElement->removeEventListener(SceneConst::CHANGE_POSITION);

		std::vector<IElement*>::iterator iterElment = _elementList.begin();
		for(; iterElment != _elementList.end(); ++iterElment)
		{
			if(*iterElment == pIElement)
			{
				_elementList.erase(iterElment);
				break;
			}
		}

		std::vector<IElement*>::iterator iterFace = _faceList.begin();
		for(; iterFace != _faceList.end(); ++iterFace)
		{
			if(*iterFace == pIElement)
			{
				_faceList.erase(iterFace);
				break;
			}
		}

		/*removeElement(pIElement);
		removeFaceElement(pIElement);*/
		pIElement->dispose();
		if(pIElement && pIElement->getParent())
			pIElement->removeFromParentAndCleanup(true);
	}
	_elementDic.erase(iter2);

}
		
void BaseScene::npcDeadHandler(CCNode* n, void* data)
{
	MapNPC* npc = (MapNPC*)data;
	removeElement(npc);
	addFaceElement(npc);
}

/**
	* NPC move
	* @param id
	* @param path
	* 
	*/		
void  BaseScene::npcMovePath(int id, std::vector<CCPoint>& path)
{
	char tmp[32] = {0};
	std::string s = NPC_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter =  _elementDic.find(tmp_str);
	if(iter != _elementDic.end() && iter->second)
	{
		MapNPC* npc = (MapNPC*)(iter->second);
		npc->movePath(path);
	}
}
 
void BaseScene::npcUpdateIcon(int id, int icon)
{
	char tmp[32] = {0};
	std::string s = NPC_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);
	std::map<std::string, IElement*>::iterator iter =  _elementDic.find(tmp_str);
	if(iter != _elementDic.end() && iter->second)
	{
		MapNPC* npc = (MapNPC*)(iter->second);
		if(npc)
			npc->icon( icon );
	}
}
		
void BaseScene::npcLayout(CCNode* n, void* data)
{
	MapNPC* npc = (MapNPC*)data;
	struct Data
	{
		bool first;
		MapNPC* npc;
		Data()
		{
			first = false;
		}
	};

	Data d;
	d.first = false;
	d.npc = npc;
	dispatchEvent(SceneConst::ELEMENT_LAYOUT, (void*)npc);

}
		
void BaseScene::removeNPCDeadbodyHandler(CCNode* n, void* data)
{
	if(!data)
		return;

	MapNPC* npc = (MapNPC*)data;

	if(npc)
		dispatchEvent(SceneConst::NPC_REMOVEDEADBODY, (void*)(&(npc->_id)));
}
		
void BaseScene::removePlayerDeadbodyHandler(CCNode* n, void* data)
{
	if(!data)
		return;

	Player* player =  (Player*)data;

	if(player)
		dispatchEvent(SceneConst::PLAYER_REMOVEDEADBODY, (void*)(&(player->_id)));
}
		
/*================================================================*/
		
		

/*================================================================*/
/**
	*
	* 
	*/		
void BaseScene::addExit(ExitVo* exitVo)
{
	if(exitVo == NULL)
		return;

	char tmp[32] = {0};
	std::string s = EXIT_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), exitVo->_id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter != _elementDic.end())
	{
		removeExit(exitVo->_id);
		//_elementDic.erase(iter);
	}

	Exit* sceneElement = new Exit(*exitVo);

	char tmp1[32] = {0};
	sprintf(tmp1, "%s%d", s.c_str(), sceneElement->_id);
	std::string tmp_str1(tmp1);
	//_elementDic.insert(make_pair(tmp_str1, (IElement*)&sceneElement));
	_elementDic.insert(make_pair(tmp_str1, sceneElement));
	CCPoint pos = getElemenetPosition(exitVo->x, exitVo->y);
	sceneElement->setPosition(pos);
	CCPoint point = TileUtil::Instance()->changeTileToPixs( ccp(exitVo->x, exitVo->y));
	sceneElement->mapStartPoint(point);
	addFaceElement(sceneElement);
}
/**
* 
* 
*/
void BaseScene::removeExit(int id)
{
	char tmp[32] = {0};
	std::string s = EXIT_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);

	if(iter != _elementDic.end())//jae note
	{
		IElement* pIElement = iter->second;

		if(!pIElement)
		{
			_elementDic.erase(iter);
			return;
		}
		else
		{
			std::vector<IElement*>::iterator iterFace = _faceList.begin();
			for(; iterFace != _faceList.end(); ++iterFace)
			{
				if(*iterFace == pIElement)
				{
					_faceList.erase(iterFace);
					break;
				}
			}

			pIElement->dispose();
			//removeFaceElement(pIElement);
			//Doyang 20120713
			if(pIElement && pIElement->getParent())
			{
				pIElement->removeFromParentAndCleanup(true);
			}

			_elementDic.erase(iter);
		}
	}
}


void BaseScene::setExitVo(int id, ExitVo* exitVo)
{
	if(!exitVo)
		return;

	char tmp[32] = {0};
	std::string s = EXIT_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);
	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter == _elementDic.end())
		return;

	if(iter->second)
	{
		Exit* exit = (Exit*)(iter->second);
		exit->setExitVo(*exitVo);
		_elementDic.erase(iter);

		char tmp1[32] = {0};
		sprintf(tmp1, "%s%d", s.c_str(), exitVo->_id);
		std::string tmp_str1(tmp1);
		_elementDic.insert(make_pair(tmp1, exit));
		////////////////
		//Exit* exit = new Exit();
		//*exit = *((Exit*)(iter->second));
		//exit->setExitVo(*exitVo);

		//char tmp1[32] = {0};
		//sprintf(tmp1, "%s%d", s.c_str(), exitVo->_id);
		//std::string tmp_str1(tmp1);
		//_elementDic.insert(make_pair(tmp1, exit));

		//delete iter->second;
		//_elementDic.erase(iter);
 	}
}
		
/*================================================================*/

/**
* @param element
* 
*/		
void BaseScene::roleMoveElement()
{
}

/**
* @param point
* @return 
* 
*/
IElement* BaseScene::getExitByPoint(CCPoint point)
{
	std::map<std::string, IElement*>::iterator iter = _elementDic.begin();
	for(; iter != _elementDic.end(); ++iter)
	{
		if(iter->second == NULL)
			continue;

		if(iter->second->type() == EXIT_TYPE )
		{
			if(iter->second->hitTest(point) == true)
			{

				return iter->second;
			}
		}
	}
	return NULL;
}

LiveThing* BaseScene::getPlayer(int id)
{
	char tmp[32] = {0};
	sprintf( tmp, "%d", id );
	std::string tmp_str( PLAYER_TYPE);
	tmp_str.append(tmp);

	if (!_elementDic.empty())
	{
		std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
		if(iter != _elementDic.end() && iter->second)
		{
			return (LiveThing*)(iter->second);
		}
	}
	return NULL;
}

MapNPC* BaseScene::getNPC(int id)
{
	/*std::map<int, MapNPC*>::iterator npcIt = _MapNPCDic.find(id);
	if(npcIt != _MapNPCDic.end())
	{
		return (MapNPC *)(npcIt->second);
	}
	return NULL;*/
	char tmp[32] = {0};
	std::string s = NPC_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);
	if (!_elementDic.empty())
	{
		std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
		if(iter != _elementDic.end() && iter->second)
		{
			return (MapNPC*)(iter->second);
		}
	}
	return NULL;
}

/**
	* 
	* 
	*/		

struct comp
{
	bool operator () (IElement* a, IElement* b)
	{
		if (a && b)
			return a->getPosition().y < b->getPosition().y;
		else
			return false;
	}
};
void BaseScene::sortElement()
{
	//Begin Kenfly 20121023

	std::sort(_elementList.begin(), _elementList.end(), comp());
	if (_elementLayer)
	{
		int sz = _elementList.size();
		for (int i = 0; i < sz; ++i)
		{
			if (_elementList[i] && _elementList[i]->getParent() == _elementLayer && _elementList[i]->getZOrder() != sz - i)
			{
				_elementLayer->reorderChild(_elementList[i], sz - i);
			}
		}
		_depthChanged = false;
	}

	//End Kenfly 20121023
}

void BaseScene::step()
{
	curFrame++;

	std::vector<IElement*>::iterator iter = _elementList.begin();
	for(; iter != _elementList.end(); ++iter)
	{
		if(*iter)
			(*iter)->step();
	}
	iter = _faceList.begin();
	for(; iter != _faceList.end(); ++iter)
	{
		if(*iter)
			(*iter)->step();
	}

	//int _dis = 0;
	CCPoint _tempFocusPos;
	//float tempx = 0.0f;
	//float tempy = 0.0f;

	if (_positionChanged == true)
	{
		CCPoint pos1;

		if(_movingLayer)
			pos1 = _movingLayer->getPosition();

		float disX = _focusPos.x - pos1.x;
		float disY = _focusPos.y - pos1.y;
		float dis = sqrt(disX * disX + disY * disY);
		//POSX edwardliu
		if(dis < POSX(50))
		{
			_positionChanged = false;
			return;
		}

		float x = disX / dis * POSX(8.3);
		float y = disY / dis * POSX(8.3);
		CCPoint pos2;
		pos2.x = pos1.x + x;
		pos2.y = pos1.y + y;
		if(_frontbg)
			_frontbg->load(NULL, pos2, NULL, NULL); //Kenfly 20121114

		if(_movingLayer)
			_movingLayer->setPosition(pos2);
		//_dis = 50;
		//_tempFocusPos = _focusPos;
		//CCPoint thisPos = getPosition();
		//tempx = thisPos.x;
		//tempy = thisPos.y;
		//if (tempx + _tempFocusPos.x > _dis)
		//{
		//	tempx = tempx - (tempx + _tempFocusPos.x - _dis);
		//	thisPos.x = tempx + 0.5f;
		//}
		//else if (tempx + _tempFocusPos.x < -_dis)
		//{
		//	tempx = tempx - (tempx + _tempFocusPos.x + _dis);
		//	thisPos.x = tempx + 0.5f;
		//}

		//if (tempy + _tempFocusPos.y > _dis)
		//{
		//	tempy = tempy - (tempy + _tempFocusPos.y - _dis);
		//	thisPos.y = tempy + 0.5f;
		//}
		//else if (tempy + _tempFocusPos.y < -_dis)
		//{
		//	tempy = tempy - (tempy + _tempFocusPos.y + _dis);
		//	thisPos.y = tempy + 0.5f;
		//}
		////				 
		//if (abs(tempx + _tempFocusPos.x) <= _dis && abs(tempy + _tempFocusPos.y) <= _dis)
		//{
		//	_positionChanged = false;
		//}

		//setPosition(thisPos);

	}


	//Begin Kenfly 20121025 : modify
	if(_depthChanged && curFrame % 5 == 0)
	{
		sortElement();
	}
	//End Kenfly 20121025

	std::list<int>::iterator itQue = m_removeTraderQueue.begin();
	for ( ; itQue != m_removeTraderQueue.end(); itQue++ )
	{
		removeTradePlayer(*itQue);
	}
	m_removeTraderQueue.clear();
}

/**
	*
	* 
	*/
void BaseScene::roleStop()
{
	hideClickEffect();
	if(_role)
	{ 
		_role->icon(1);
		_role->stop();
		_role->poseState->state(SceneConst::STAND);
	}
}

/**
	* 
	* @param value 
	* 
	*/	
		

void BaseScene::setLayersVisible(bool value, bool isOpe)
{
	if(!value)
		RenderManage::Instance()->remove(this);
	else
		RenderManage::Instance()->add(this);
	if(_faceLayer)
		_faceLayer->setIsVisible(value);
	if(_elementLayer)
		_elementLayer->setIsVisible(value);
	if(_frontLayer)
		_frontLayer->setIsVisible(value);
	if(_effectLayer)
		_effectLayer->setIsVisible(value);
			 
	//mouseDownChange(value, isOpe);
}


void BaseScene::showClickEffect(float tx, float ty)
{
	if(!_frontbg || !_clickEffectMc)
		return;

	CCPoint pos;
	CCSize size;
	if(_frontbg)
	{
		pos = _frontbg->getPosition();
		size = _frontbg->getMapSizeV();
	}

	CCPoint pos_layer;
	if(_elementLayer)
		pos_layer = _elementLayer->getPosition();
	

	CCPoint cp;
	cp.x = tx + pos.x + pos_layer.x - size.width / 2.0f;
	cp.y = pos.y + pos_layer.y + size.height / 2.0f - ty;
	if(_clickEffectMc)
	{
		_clickEffectMc->setPosition(cp);
		_clickEffectMc->runAction(CCRepeatForever::actionWithAction(CCAnimate::actionWithAnimation(clickEffect)));
		_clickEffectMc->setIsVisible(true);
	}
	/*if(_mouseLayer.contains(_clickEffectMc) == false)
	{
	_mouseLayer.addChild(_clickEffectMc);
	}

	_clickEffectMc.x = tx;
	_clickEffectMc.y = ty;
	_clickEffectMc.gotoAndPlay(1);*/
}


void BaseScene::hideClickEffect()
{
	if(!_clickEffectMc)
		return;

	_clickEffectMc->stopAllActions();
	_clickEffectMc->setIsVisible(false);
}

void BaseScene::clearElement()
{
	std::map<std::string, IElement*>::iterator iter = _elementDic.begin();
	for(; iter != _elementDic.end(); ++iter)
	{
		if(iter->second)
			((Element*)(iter->second))->dispose();
	}
	removeAllFaceElement();
	removeAllElement();
			
	_elementList.clear();
	_faceList.clear();
	//_elementDic = new Dictionary();
	_elementDic.clear();
}
		

void BaseScene::dispose()
{
	cancelClickTarget();
	setIsVisible(false);
	_depthChanged=true;			
	_positionChanged = false;

	/*RenderManage::Instance()->stop();
	RenderManage::Instance()->remove(this);*/

	setMoveElement(NULL);
	//DisplayObjectManager.clearChildren(_frontBGLayer);
	//DisplayObjectManager.clearChildren(_elementLayer);

	/*if(_frontbg)
	{
		_frontbg->dispose();
	}*/

	std::map<std::string, IElement*>::iterator iter = _elementDic.begin();
	for(; iter != _elementDic.end(); ++iter)
	{
		Element* pElement = (Element*)iter->second;
		if(pElement)
		{
			pElement->dispose();
			if ( pElement->getParent() )
			{
				pElement->removeFromParentAndCleanup( true );
				//jae20120821
				std::vector<IElement*>::iterator iter = _elementList.begin();
				for(; iter != _elementList.end(); ++iter)
				{
					if (*iter==pElement)
					{
						_elementList.erase(iter);
						break;
					}					
				}
			}
		}
	}
	//removeAllFaceElement();
	//removeAllElement();

	std::vector<IElement*>::iterator iterList = _elementList.begin();
	for(; iterList != _elementList.end(); ++iterList)
	{
		IElement* p = *iterList;
		if (p)
		{
			p->removeFromParentAndCleanup(true);
		}		
	}
	_elementList.clear();
	_faceList.clear();
	//_clickTimer =0;
	//_lastClickPoint = ccp(0.0f, 0.0f);
	_elementDic.clear();
	_findMonsterDic.clear();
	_findNpcDic.clear();
	//_findNpcDic = new Dictionary();
	cancelClickTarget();
	setPosition(ccp(0.0f, 0.0f));
		
	dispatchEvent(SceneConst::DISPOSE, NULL);

}

void BaseScene::setClickTarget(IElement* value)
{
	if(value != NULL && clickTarget != value)
	{
		cancelClickTarget();
		clickTarget = value;
		//clickTarget->setSelect(true);
	}
}

void BaseScene::cancelClickTarget()
{
	if(clickTarget == NULL)
		return;

	//clickTarget->setSelect(false);
	//delete clickTarget;
	clickTarget = NULL;
}


void BaseScene::setMoveElement(IElement* value, bool setOldNull)
{
	if(value == NULL)
	{
		if(_moveElement == NULL)
			return;
		//_moveElement->setGlow(false);

		//MouseCursorManage.getInstance().setState(MouseCursorManage.NORMAL);
		delete _moveElement;
		_moveElement = NULL;
	}
	else 
	{
		if(_moveElement != value && setOldNull)
		{
			setMoveElement(NULL);
		}
		else if(_moveElement == value)
		{
			return;
		}				
		_moveElement = value;
		//_moveElement->setGlow(true);
		if(_moveElement->type() ==  NPC_TYPE)
		{
			//Npc* npc = (Npc*)(_moveElement);
			//if(npc->action() == SceneConst::TALK)
			{
				//MouseCursorManage.getInstance().setState(MouseCursorManage.TALK);
			}
			//else if(npc->action() == SceneConst::FIGHT)
			{
				//MouseCursorManage.getInstance().setState(MouseCursorManage.FIGHT);
			}
		}
	}
}
