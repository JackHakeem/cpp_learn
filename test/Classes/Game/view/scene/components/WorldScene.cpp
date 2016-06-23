#include "WorldScene.h"
#include "model/player/vo/PlayerBaseVo.h"
#include "model/scene/vo/SceneVo.h"
#include "model/scene/SceneManager.h"
#include "model/player/RoleManage.h"
#include "events/GameDispatcher.h"
#include "manager/RenderManage.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "util/TileUtil.h"
#include "utils/ScaleUtil.h"
#include "model/scene/SceneProxy.h"
#include "control/AppFacade.h"
#include "manager/TouchLayerEnum.h"

WorldScene::WorldScene()
{
	_isTeamRoomPop = false;
	_childShow = false;
	radius1 = 50;
	radius2 = 36;
	_worldbg = NULL;
	_childExitCon = NULL;
	setIsTouchEnabled(true);
}

void WorldScene::addReturnButton()
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/map/res_map.plist");
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int iTagButonReturn( 256 );

	//jae 20120716
	CCMenu *buttonMenu = (CCMenu *)this->getChildByTag( iTagButonReturn );
	if ( !buttonMenu )
	{
		CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("map/return.png");
		CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("map/return.png");
		CCMenuItemSprite *_button = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite,
			this, 
			menu_selector(WorldScene::onReturnButtonDown));

		buttonMenu = CCMenu::menuWithItems(_button, NULL);
		if(buttonMenu)
		{
			buttonMenu->setPosition(CCPointZero);
			_button->setPosition(winSize.width - POSX(100), winSize.height - POSX(100));

			buttonMenu->setTag( iTagButonReturn );
			buttonMenu->setTouchLayer(TLE::WindowLayer_Map);
			addChild(buttonMenu);
		}
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/map/res_map.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/map/res_map.pvr.ccz");
}
void WorldScene::onReturnButtonDown(CCObject* pSender)
{
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(info)
	{
		int mapId = info->playerBaseInfo._mapId;
		GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::TRIGGER_EXIT, (void*)(&mapId));
	}

	if(g_pGlobalManage && LayerManager::sceneLayer)
		g_pGlobalManage->setCurFocusGID(LayerManager::sceneLayer->getMyFocusGID());

	g_pGlobalManage->setIsInWordMap(false);
	g_pGlobalManage->showAllUI(true);
}

void WorldScene::addRole(float scale)
{
	if(!_role)
		_role = new Player();
	_role->addEventListener(SceneConst::WALK_COMPLETE, this, callfuncND_selector(WorldScene::roleWalkCompleteHandler));
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	//var roleVo:PlayerBaseVo = RoleManage.getInstance().roleInfo.playerBaseInfo ;
	PlayerBaseVo roleVoClone;
	SceneVo* mapVo = SceneManager::Instance()->getSceneDic(info->playerBaseInfo._mapId);
	if(!mapVo)
		return;

	if(mapVo->pid > 0)
		mapVo = SceneManager::Instance()->getSceneDic(mapVo->pid);

	roleVoClone.x = POSX(mapVo->x);
	roleVoClone.y = POSX(mapVo->y);
	roleVoClone._hp = info->playerBaseInfo._hp;
	roleVoClone.name = "";
	roleVoClone.id = info->playerBaseInfo.id;
	roleVoClone.isRole = true;
	roleVoClone.cloth = info->playerBaseInfo.cloth;
	roleVoClone.accountId = info->playerBaseInfo.accountId;
	_role->setPlayerVo(roleVoClone, scale);
	_role->icon(0);

	char tmp[128] = {0};
	sprintf(tmp, "%s%d", _role->type().c_str(), _role->id());
	std::string tmp_str(tmp);

	_elementDic[tmp_str] = _role;

	addElement(_role);

	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	_role->setStartPointByMap(ccp(roleVoClone.x - 1, roleVoClone.y), ccp(0.0f, 0.0f), ccp(0.0f, 0.0f), screenSize.height, screenSize.width);
	//addEventListener(MouseEvent.MOUSE_DOWN,clickSceneHandler);
}

void WorldScene::addElement(IElement* child, int zOder)
{
	if(child && _elementLayer && child->getParent() != _elementLayer)
	{
		_elementLayer->addChild(child);
		child->release();//jae
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
}

void WorldScene::roleWalkCompleteHandler(CCNode* n, void* data)
{
	if(!_role)
		return;

	dispatchEvent(SceneConst::WALK_COMPLETE, data);
	hideClickEffect();
	/*if(g_pGlobalManage && g_pGlobalManage->isOnMeditation())
	{
		_role->icon(13);
	}
	else
	{
		_role->icon(0);
	}*/

	_role->icon(0);

	if(!g_pGlobalManage->isRoleHidden)
	{
		_role->setIsVisible(!_role->getIsVisible());
	}

	CCPoint pos = _role->getMapStartPoint();
	IElement* exit = getExitByPoint(pos);
	if(exit != NULL)
	{
		std::vector<int>* info = exit->otherInfos();
		std::vector<int>::iterator iter = info->begin();
		if(iter != info->end())
		{
			int i = *iter;
			dispatchEvent(SceneConst::TRIGGER_EXIT,  &i);
		}
	}
}

void WorldScene::roleMoveElement(IElement* element)
{
	if(!element)
		return;

	WorldExit* exit = (WorldExit*)element;
	if(exit)
	{
		PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
		if(info)
		{
			if(info->playerBaseInfo._mapId == exit->_exitVo._id)
			{
				onReturnButtonDown(NULL);
			}
		}

		CCPoint point = ccp(POSX(exit->_exitVo.x), POSX(exit->_exitVo.y));
		BaseScene::roleMove(point);
	}
}

void WorldScene::buildScene(int width, int height, int mapRank, int offsetX, int offsetY,std::string path, CCPoint focusPos)
{
	dispose();
	CCLayerColor *pBackgroundLayer = CCLayerColor::layerWithColorWidthHeight(ccc4(0, 0, 0, 255),
		CCDirector::sharedDirector()->getWinSize().width,
		CCDirector::sharedDirector()->getWinSize().height);
	pBackgroundLayer->setAnchorPoint(CCPointZero);
	pBackgroundLayer->setPosition(CCPointZero);
	this->addChild(pBackgroundLayer, -1);
	if(_worldbg == NULL)
		_worldbg = new WorldBgBitmap;

	//if(_frontBGLayer && _worldbg->getParent() == NULL)
	//	_frontBGLayer->addChild(_worldbg);

	_worldbg->build(width, height, path, offsetX, offsetY);

	_worldbg->load(NULL, focusPos);
	if(_movingLayer)
		_movingLayer->setPosition(focusPos);

	if(_frontBGLayer && _worldbg->getParent() == NULL)
	{
		_frontBGLayer->addChild(_worldbg);
		_worldbg->release();//jae
	}

	setIsVisible(true);
	RenderManage::Instance()->add(this);
	addReturnButton();
}

void WorldScene::clickSceneHandler(CCPoint point)
{
	return;

	if (g_pGlobalManage && LayerManager::worldLayer
		&& g_pGlobalManage->getCurFocusGID() != LayerManager::worldLayer->getMyFocusGID())
	{
		return;
	}

	if(g_pGlobalManage && !g_pGlobalManage->_canMove)
		return;

	IElement* element = NULL;
	for(int k = _faceList.size() - 1 ; k >= 0; k--)
	{
		element = _faceList[k];
		if(element)
		{
			if(element->hitTest(point) && !_childShow )
			{
				if(element->type() ==  EXIT_TYPE)
				{
					showChildScene(element);
					return;
				}
			}
		}
	}
	removeChildExitCon();
}

void WorldScene::clickExit(CCNode *n, void* data)
{
	if(!data)
		return;

	IElement* exit = (IElement*)data;
	showChildScene(exit);
}
//virtual void moveSceneHandler();

void WorldScene::addExit(ExitVo* exitVo)
{
	if(exitVo == NULL)
		return;

	char tmp[128] = {0};
	std::string s = EXIT_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), exitVo->_id);
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter != _elementDic.end())
	{
		removeExit(exitVo->_id);
		//if(iter != _elementDic.end())
		//	_elementDic.erase(iter);//Jae change
	}

	// add by LH 0726
	SceneProxy * pSceneProxy = (SceneProxy *)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	if (!pSceneProxy)	{return;}
	exitVo->isOpend = pSceneProxy->isSceneOpened(exitVo->_id);

	WorldExit* sceneElement = new WorldExit(*exitVo);

	char tmp1[128] = {0};
	sprintf(tmp1, "%s%d", s.c_str(), sceneElement->_id);
	std::string tmp_str1(tmp1);
	//_elementDic.insert(make_pair(tmp_str1, (IElement*)&sceneElement));
	_elementDic.insert(make_pair(tmp_str1, sceneElement));
	CCPoint pos = getElemenetPosition(exitVo->x, exitVo->y);

	sceneElement->setPosition(pos);
	sceneElement->setAnchorPoint(CCPointZero);
	addFaceElement(sceneElement);
	sceneElement->addEventListener(SceneConst::CLICK_EXIT_IN_WORLDMAP, this, callfuncND_selector(WorldScene::clickExit));
}

CCPoint WorldScene::getElemenetPosition(float vx, float vy)
{
	//CCPoint point = TileUtil::Instance()->changeTileToPixs(ccp(vx, vy));
	CCPoint point = ccp(vx, vy);
	CCPoint pos = ccp(0.0f, 0.0f);
	CCSize bgSize = CCSizeMake(0, 0);
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
	if(_worldbg)
	{
		pos = _worldbg->getPosition();
		bgSize = _worldbg->getContentSize();
	}
	//CCSize size = CCDirector::sharedDirector()->getWinSize();
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
//
//	float scaleFactor = 1;
//
//#else
//	float scaleFactor = CCDirector::sharedDirector()->getContentScaleFactor();
//
//#endif
//	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
//	float EXPAND_WIDTH = abs(winSize.width -  WIDTH / scaleFactor);
//	float EXPAND_HEIGHT = abs(winSize.height - HEIGHT / scaleFactor);
	// 20120724
	CCPoint cp;
	// 20120707
	//Doyang
	cp.x = POSX(point.x + pos.x - 480);
	cp.y = POSX(pos.y + 320 - point.y);
	/*cp.x = pos.x - bgSize.width / 2 + POSX(vx) + EXPAND_WIDTH / 2;
	cp.y = pos.y - bgSize.height / 2  + POSX(vy) + EXPAND_HEIGHT / 2;*/
	return cp;
}

WorldExit* WorldScene::getExit(int id)
{
	char tmp1[128] = {0};
	std::string s = EXIT_TYPE;
	sprintf(tmp1, "%s%d", s.c_str(), id);
	std::string tmp_str1(tmp1);
	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str1);
	if(iter != _elementDic.end() && iter->second != NULL)
	{
		return (WorldExit*)(iter->second);
	}
    return 0;
}
//virtual void setElemenetPosition(int vx, int vy, dis:DisplayObject);
void WorldScene::showChildScene(IElement* element)
{
	removeChildExitCon();
	_childShow = true;
	struct Data
	{
		bool auto1;
		IElement* element;
		Data()
		{
			auto1 = false;
			element = NULL;
		};
	};

	Data data;
	data.element = element;
	dispatchEvent(SceneConst::SHOW_CHILD_SCENE, &data);
}

void WorldScene::showChildSceneHandle(std::vector<WorldExitData>& array, IElement& currElement)
{
	_childShow = true;
	if(_childExitCon == NULL)
	{
		_childExitCon = new ChildExitContainer();
	}

	CCPoint pos = currElement.getPosition();
	_childExitCon->setPosition(pos);
	_childExitCon->data(array);
	//if(_childExitCon->getParent() != this)
	//	addChild(_childExitCon);
	addFaceElement((IElement*)_childExitCon);
}

void WorldScene::removeChildExitCon()
{
	_childShow = false;
	if(_childExitCon && _childExitCon->getParent() == this)
	{
		_childExitCon->dispose();
	}
}
void WorldScene::showChildSceneAutoFindPath(int id)
{
	char tmp1[128] = {0};
	std::string s = EXIT_TYPE;
	sprintf(tmp1, "%s%d", s.c_str(), id);
	std::string tmp_str1(tmp1);
	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str1);

	if(iter != _elementDic.end())
	{
		/*struct Data
		{
			int auto1;
			IElement* element;
		};
		Data d;
		d.auto1 = true;
		d.element = iter->second;
		dispatchEvent(SceneConst::SHOW_CHILD_SCENE, (void*)(&d));*/
		roleMoveElement(iter->second);
	}
}
void WorldScene::isTeamRoomPop(bool value)
{
	_isTeamRoomPop = value;
	if(_isTeamRoomPop)
	{
		//removeEventListener(MouseEvent.MOUSE_DOWN,clickSceneHandler);
		//_childShow = true;
	}
	else
	{
		//addEventListener(MouseEvent.MOUSE_DOWN,clickSceneHandler);
		//_childShow = false;
	}
}

bool WorldScene::isTeamRoomPop()
{
	return _isTeamRoomPop;
}

CCNode* WorldScene::getNewHandItem(int id, bool isPid)
{
	if(isPid)
	{
		char tmp1[128] = {0};
		std::string s = EXIT_TYPE;
		sprintf(tmp1, "%s%d", s.c_str(), id);
		std::string tmp_str1(tmp1);
		std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str1);

		if(iter != _elementDic.end() && iter->second)
			return iter->second;
	}
	else if(_childExitCon)
	{
		CCArray * pArray = _childExitCon->getChildren();
		CCObject* pObject = NULL;
		IElement* child = NULL;
		CCARRAY_FOREACH(pArray, pObject)
		{
			if(pObject == NULL)
				continue;

			child = (IElement*)pObject;
			if(child->id() == id)
				return child;
		}

		/*for(var i:int = 0; i<_childExitCon.numChildren; i++)
		{
			CCArray* array = _childExitCon->getChildren();
			
			var ob:Object = _childExitCon.getChildAt(i);
			if(ob is ChildExit && ob.id == id){
				return ob;
			}
		}*/
	}
	return NULL;
}

//void WorldScene::setChildExitStarLev(int childId, int starLev)
//{
//	if(_childExitCon)
//	{
//		_childExitCon->setChildExitStarLev(childId, starLev);
//	}
//}

void WorldScene::dispose()
{
	if(isTeamRoomPop())
	{
		isTeamRoomPop(false);
	}
	RenderManage::Instance()->remove(this);

	BaseScene::dispose();

	//if(_btnReturn)
	//{
	//	_btnReturn.removeEventListener(MouseEvent.MOUSE_DOWN, onReturnButtonDown);
	//	removeChild(_btnReturn);
	//	_btnReturn = NULL;
	//}

	//jae 20120706
	if(_worldbg)
	{
		_worldbg->dispose();

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
		string tmp = std::string ( _worldbg->_rootPath.c_str() );
#endif

		if(_worldbg->getParent() == _frontBGLayer)
			_frontBGLayer->removeChild(_worldbg, true);

		//_worldbg->release();
		_worldbg = NULL;

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
		CCTextureCache::sharedTextureCache()->removeTextureForKey( tmp.c_str() );
#endif
	}

	//if(_role)
	//{
	//	//_role->dispose();
	//	//delete _role;
	//}
	_role = NULL;
	

#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	//jae 20120716: remove texture of city pic
	char tmp1[128] = {0};
	std::vector<SceneVo*> array = SceneManager::Instance()->getWorldSceneDic();
	for(std::vector<SceneVo*>::iterator iter = array.begin();
		iter != array.end(); ++iter)
	{
		//CCLog("-----------map id:%d, resId:%s, x:%d, y:%d", (*iter)->id, (*iter)->resid.c_str(), (*iter)->x, (*iter)->y);
		SceneVo* pSceneVo = *iter;
		if( !pSceneVo )
			continue;

		std::string _textPath = "assets/mapassets/exit/%s_txt.png";
		sprintf( tmp1, _textPath.c_str(), pSceneVo->resid.c_str() );
		CCTextureCache::sharedTextureCache()->removeTextureForKey(tmp1);
	}
#endif  // CC_PLATFORM_ANDROID

}
