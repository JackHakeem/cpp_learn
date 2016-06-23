#include "MapMediator.h"
#include "components/Map.h"
#include "components/NPCItem.h"

#include "model/player/RoleManage.h"
#include "model/player/vo/PlayerInfoVo.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/SceneManager.h"
#include "manager/ViewManager.h"
#include "model/scene/SceneProxy.h"
#include "model/scene/vo/SceneInfoVo.h"
#include "model/scene/NPCManager.h"
#include "manager/ViewManager.h"
#include "manager/PopEventName.h"
#include "events/GameDispatcher.h"
#include "view/scene/SceneMediator.h"
#include "manager/GlobalManage.h"
#include "model/shop/ShopManager.h"
#include "model/shop/vo/shopVo.h"
#include "util/TileUtil.h"

MapMediator::MapMediator()
{
	_map = 0;
	_isStart = true;
	_dispatcher = 0;
	_sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);

	_dispatcher = GameDispatcher::getInstance();
	_dispatcher->addEventListener(PopEventName::SHOW_UI_MAP, this, callfuncND_selector(MapMediator::startupSmallmapUI));
}

void MapMediator::startupSmallmapUI(CCNode* n, void* data)
{
	openMapView();
}

void MapMediator::openMapView()
{
	if (_map && _map->_pContainer)
	{
		if (_map->_pContainer->getParent())
		{
			_map->_pContainer->removeFromParentAndCleanup(true);
			_map->release();
			_map = 0;
			ViewManager::getInstance()->mapView = 0;				
		}
	}


	if(_map)
	{
		_map->setisPop(!_map->getisPop());	
		return;
	}

	//g_pGlobalManage->showAllUI(false);
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/map/res_map.plist");

	PlayerInfoVo* playInfo = RoleManage::Instance()->roleInfo();
	if (!playInfo) return;
	int32 mapId = playInfo->playerBaseInfo._mapId;
	mapId = mapId<=0?1:mapId;
	SceneVo* scene = SceneManager::Instance()->getSceneDic(mapId);
	if (!scene) return;
	_rolePos = ccp(playInfo->playerBaseInfo.x, playInfo->playerBaseInfo.y);
	_rolePos = TileUtil::Instance()->changeTileToPixs(_rolePos);

	_map = new Map();
	_map->init();
	
	//if (ViewManager::getInstance()->scene.smallMap){
		char resMapRoad[100];
		sprintf(resMapRoad, "assets/mapassets/scene/%d/front/small.jpg", scene->mapResId);
		_map->startHandler(_sceneProxy->_sceneInfoVo->width, _sceneProxy->_sceneInfoVo->height,
			_rolePos,resMapRoad/*ViewManager::getInstance().scene.smallMap*/,_sceneProxy->_sceneInfoVo->name);
		
		_isStart= true;
	
	//}
	_map->setisPop(true);
	_map->startListViewHandler();

	std::vector<int> npcs = NPCManager::Instance()->getNpcsByMapId(mapId);
	addNPCHandler(npcs);
	//if(_pathArr){
	//	_map.roleMoveHandler(_pathArr);
	//}
	startListener();
	ViewManager::getInstance()->mapView = _map;

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/map/res_map.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/map/res_map.pvr.ccz");
}


void MapMediator::startListener()
{
	ViewManager::getInstance()->scene()->addEventListener(BaseScene::ROLE_POS_CHANGED, this, callfuncND_selector(MapMediator::rolePosChangeHandler));
	ViewManager::getInstance()->scene()->addEventListener(SceneConst::WALK_START_1, this, callfuncND_selector(MapMediator::roleMoveHandler));

/*			ViewManager.getInstance().scene.addEventListener(BaseScene.SMLMAP_BG_INIT, getProcess);
			ViewManager.getInstance().scene.addEventListener(SceneConst.WALK_START, roleMoveHandler);
			
			_map.addEventListener(Map.ROLE_MOVE,roleMove);
			_map.addEventListener(Map.ROLE_TO_NPC,roleToNpc);
			_map.addEventListener(NPCItem.GO_TO_NPC,roleToNpc);
			_map.addEventListener(Map.MAP_CLOSE,onCloseHandler);
			_map.addEventListener(Map.MOUSE_LIMIT,onLimitHandler);
*/
}

void MapMediator::rolePosChangeHandler( CCNode* n, void* data )
{
	if (_map && data)
	{
		CCPoint objpos = *(CCPoint*)data;
		//CCPoint _rolePos = obj->getPosition();
		_map->rolePosChangeHandler(objpos);
		return;
	}
}

void MapMediator::roleMoveHandler( CCNode* n, void* data )
{
	if (!data || !_map) return;
	_pathArr.clear();

	vector<CCPoint>* _array = (vector<CCPoint>*)data;

	CCLog("--------------------------size=%d", _array->size());
	_map->roleMoveHandler(*_array);

	_pathArr = *_array;
}


void MapMediator::addNPCHandler(std::vector<int>& arr)
{
	std::vector<int>::iterator it;

	//Begin Kenfly 20130125 : memory leak
	//_map->m_vNpcList.clear();
	_map->removeNpcList();
	//End Kenfly 20130125
	//int count  = arr.size();
	for (it = arr.begin(); it != arr.end(); it++)
	{
		int id = *it;
		NPCVo* vo = NPCManager::Instance()->getNPC(id);
		if (!vo)  continue;
		if(vo->action == !SceneConst::FIGHT)
		{
			NPCItem* item = new NPCItem();
			item->init();
			item->_vo = *vo;
			
			item->setIsRelativeAnchorPoint(true);
			item->setAnchorPoint(ccp(0,0));

			char showname[50];
			ShopVo* pShopVo = ShopManager::Instance()->getShopsByNPCId(item->_vo.id);
			if(!pShopVo) 
			{
				sprintf(showname, "%s", vo->name.c_str());
			}
			else
			{
				sprintf(showname, "%s(%s)", vo->name.c_str(), pShopVo->name.c_str());
			}
			
			CCLabelTTF* pNpcLable = CCLabelTTF::labelWithString(showname, CCSizeMake(POSX(250),POSX(20)), CCTextAlignmentLeft, "Arial", POSX(20));
			pNpcLable->setAnchorPoint(ccp(0,0));
			pNpcLable->setPosition(ccp(0,0));
			pNpcLable->setColor(ccc3(255, 255, 255));
			item->addChild(pNpcLable, 0, 0);
			_map->m_vNpcList.push_back(item);
			//newNpcCell->release();
			
			_map->addNPCHandler(vo);//小地图里面NPC标记

			item->addEventListener(NPCItem::GO_TO_NPC, this, callfuncND_selector(MapMediator::roleToNpc));//右边NPC列表点了寻路反应
		}
	}
	/*
	_map.scrollPane.update();
	if (_map.scrollCotent.height > _map.scrollPane.height)
		_map.scrollPane.verticalScrollBar.visible=true;
	else
		_map.scrollPane.verticalScrollBar.visible=false;
	*/

	_map->updateNpcRes();//右边NPC列表
}

void MapMediator::roleToNpc(CCNode* n, void* data)
{
	if(!g_pGlobalManage->canMove())
	{
		//Alert.show("当前状态不能进行寻路");
		return;
	}
	sendNotification(Facade_Mediator, AppFacade_SCENE_MEDIATOR, (char*)(data), SceneMediator::ROLE_TO_NPC);
}
