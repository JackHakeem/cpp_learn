#include "view/scene/components/Scene.h"
#include "manager/RenderManage.h"
#include "util/TileUtil.h"
#include "model/scene/vo/EventType.h"
#include "model/player/RoleManage.h"
#include "model/scene/SceneProxy.h"
#include "mvc/Facade.h"
#include "control/AppFacade.h"
#include "utils/Utils.h"
#include "manager/layer/MapManage.h"
#include "events/GameDispatcher.h"
#include "manager/GlobalManage.h"
#include "manager/LayerManager.h"
#include "MapNPC.h"
#include "utils/ColorUtil.h"
#include "Message.h"
#include "manager/CDManage.h"
#include "model/scene/vo/SceneType.h"
#include "utils/ValuesUtil.h"
#include <cmath>
#include "utils/ScaleUtil.h"
#include "model/scene/NPCManager.h"
#include "manager/SourceCacheManage.h"
#include "model/task/TaskProxy.h"
#include "view/task/components/TaskStrConcat.h"
#include "model/task/vo/TaskAskType.h"
#include "model/player/vo/PlayerAniType.h"
#include "manager/ViewManager.h"
#include "view/gong/GongMediator.h"
#include "model/scene/SceneManager.h"
#include "../SceneMediator.h"

Scene::Scene()
{
	_oldDirection = 0.0f;
	_newDirection = 0.0f;
	_step = 0.0f;
	_focusChanged = false;
	_needDirPoint = false;
	setIsTouchMoveBegin(false);
	GameDispatcher::getInstance()->addEventListener(GameDispatcher::CAN_MOVE_CHANGE, this, callfuncND_selector(Scene::canMoveChange));
}

void Scene::focusPosChangeHandler(CCPoint focusPos)
{
	BaseScene::focusPosChangeHandler(focusPos);

	focusChangedHandler();
}

void Scene::buildScene(int width, int height, int mapRank, int offsetX, int offsetY,std::string path, CCPoint focusPos)
{
	BaseScene::buildScene(width, height, mapRank, offsetX, offsetY, path, focusPos);

	//jae note 20120927
	/*PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if (info)
	{
		int mapId = info->playerBaseInfo._mapId;
		if (mapId==1001)
		{
			CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_RGBA4444 );
			string _assetPath = "assets/effect/map/mapIn.plist";
			std::string _frameName = "mapIn_%02d.png";
			BitmapMovieClip* mapIn = SourceCacheManage::Instance()->loadNormal(_assetPath, _frameName, 12, 0.1f, true);

			CCPoint pos = getElemenetPosition(14,40);
			pos = ccpAdd(pos, ccp(POSX(0), POSX(155)));
			mapIn->setPosition(pos);
			_elementLayer->addChild(mapIn);
			mapIn->setTag( 648 );
			mapIn->release();
			mapIn->runActionNormal();

			CCTexture2D::setDefaultAlphaPixelFormat( kCCTexture2DPixelFormat_Default );
		}		
	}*/
	

	focusChangedHandler();
	_redProgress.clear();
	_needDirPoint = false;

	//EnterBattleController.getInstance().handler(null, null, false);

	RenderManage::Instance()->add(this);
	if(!(RenderManage::Instance()->isStart()))
		RenderManage::Instance()->start();

	//StageProxy.addListener(resize);
}

void Scene::focusChangedHandler()
{
	_focusChanged = true;
}

void Scene::rolePosChangeHandler(CCPoint rolePos)
{
	//_role->x = rolePos.x;
	//_role->y = rolePos.y;
	CCPoint pos;
	CCSize size;
	CCPoint pos_layer;

	if(_frontbg)
	{
		pos = _frontbg->getPosition();
		size = _frontbg->getMapSizeV();
	}
	
	if(_elementLayer)
		pos_layer = _elementLayer->getPosition();

	if(_role)
		_role->setStartPointByMap(rolePos, pos, pos_layer, size.height, size.width);
	//_role->setPosition(rolePos);
}

void Scene::roleIcon(int index)
{
	if(_role)
		_role->icon(index);
}

void Scene::step()
{
	BaseScene::step();

	if(autoMove && _focusChanged)
	{
		if(curFrame % 50 == 0)
		{
			processMonster();
		}
	}

	if(autoMove && curFrame % 50 == 0)
	{
		//CCLog("111111,size:%d", _findMonsterDic.size());
		std::map<int, IElement*>::iterator iter = _findMonsterDic.begin();
		for(; iter != _findMonsterDic.end(); ++iter)
		{
			int rd = rand() % 2;
			if(rd == 0)
			{
				continue;
			}

			MapNPC* npc = (MapNPC*)(iter->second);
			if(!npc)
				continue;

			std::vector<CCPoint>* path = &(npc->m_path);
			if(!path)
				return;

			/*if(npc && npc->poseState)
			{
				CCLog("222222, state:%d, timer:%d", npc->poseState->_state, npc->timer);
			}
			else
			{
				CCLog("222222, state:0, timer:%d", npc->timer);
			}*/

			if(npc->poseState && npc->poseState->_state == SceneConst::STAND && npc->timer <= 0)
			{
				//CCLog("333333, state:0, path size:%d", path->size());
				if(path->size() == 0)
				{
					*path = Utils::Instance()->randPoints(ccp(_posDic[npc->_id].x, _posDic[npc->_id].y), 2);
					//npc->m_path = path;
				}
				CCPoint point;
				std::vector<CCPoint>::iterator it = path->begin();
				if(it != path->end())
				{
					point = *it;
					path->erase(it);
				}

				if(path->size() == 0)
				{
					npc->timer =2;
				}

				CCPoint sPoint = TileUtil::Instance()->changePixsToTile(npc->getMapStartPoint());

				struct Data
				{
					int id;
					float ranger;
					CCPoint startPoint;
					CCPoint endPoint;
				};
				Data data;
				data.id = npc->_id;
				data.ranger = 0;
				data.startPoint = sPoint;
				data.endPoint = point;
				//CCLog("Npc move %d, s:[%f, %f], e:[%f, %f]", data.id, data.startPoint.x, data.startPoint.y, data.endPoint.x, data.endPoint.y);
				dispatchEvent(SceneConst::NPC_MOVE, (void*)(&data));
				//dispatchEvent(new ParamEvent(NPC_MOVE,{id:npc.id,startPoint:sPoint, point:point}));
			}				

			int rand1 = rand() % 2;
			if(npc->timer <= 0 && rand1 == 0)
			{
				bool isBoss = npc->isLeader();
				PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
				if(info)
				{
					std::string content = Utils::Instance()->getSentence(info->playerBaseInfo._mapId, npc->_id, isBoss);
					//npc->speak({style:1, content:content});
					//npc->setTalkVisible( true );

					//...............talk
					if ( npc->canTalk() )
					{
						if ( npc->getTalkVisible() )
						{
							if ( npc->m_TalkVisibleTimer->isExpired() )
							{
								npc->setTalkVisible( false );
							}
						}
						else
						{
							npc->setTalkVisible( true );
						}
					}
					//...........
				}
			}

			npc->timer--;
		}
	}
	if(_needDirPoint)
	{
		if(curFrame % 25 == 1)
		{
			updateDirection();
		}
		if(_step != 0){
			resetDirArrow();
		}
	}
}

void Scene::processMonster()
{
	std::map<int, IElement*> newDic;
	
	std::map<std::string, IElement*>::iterator iter = _elementDic.begin();
	for(; iter != _elementDic.end(); ++iter)
	{
		if(iter->second == NULL)
			continue;

		//CCSize mapSize = _frontbg->getMapSizeV();
		//Element* i = (Element*)(iter->second);
		//if(!i)
		//	continue;
		//CCPoint pos = i->getMapStartPoint();
		//int tmpx = pos.x - mapSize.width / 2 - _focusPos.x;
		//int tmpy = pos.y - mapSize.height / 2 + m_screenHeight + _focusPos.y;
		//bool inView = (tmpx >= 0 && tmpx <= m_screenWidth
		//			&& tmpy >= 0 && tmpy <= m_screenHeight);
		//if(iter->second->type() == NPC_TYPE && inView)
		if(iter->second->type() == NPC_TYPE)
		{
			MapNPC* npc = (MapNPC*)(iter->second);
			if(npc->action() == SceneConst::FIGHT || npc->action() == SceneConst::WANDER)
			{
				newDic.insert(make_pair(npc->id(), npc));
			}
		}
	}
	std::map<int, IElement*> remove;

	std::map<int, IElement*>::iterator iter1 =  _findMonsterDic.begin();

	for(; iter1 != _findMonsterDic.end(); ++iter1)
	{
		if(newDic.find(iter1->first) != newDic.end())
		{
			if(iter1->second == NULL)
				continue;

			MapNPC* _npc = (MapNPC*)(iter1->second);
			if(_npc->poseState)
				_npc->poseState->state(SceneConst::STAND);

			std::map<int, CCPoint>::iterator it = _posDic.find(_npc->id());
			if(it == _posDic.end())
				continue;

			//set the pos to the original pos
			CCPoint pos = getElemenetPosition(it->second.x, it->second.y);
			_npc->setPosition(pos);
			CCPoint startPoint = TileUtil::Instance()->changeTileToPixs(ccp(it->second.x, it->second.y));
			_npc->mapStartPoint(startPoint);
			
			remove.insert(make_pair(iter1->first, _npc));
		}
	}

	std::map<int, IElement*>::iterator iter2 = remove.begin();
	for(; iter2 != remove.end(); ++iter2)
	{
		std::map<int, IElement*>::iterator it = _findMonsterDic.find(iter2->first);
		if(it != _findMonsterDic.end())
			_findMonsterDic.erase(it);
	}

	std::map<int, IElement*>::iterator iter3 = newDic.begin();
	for(; iter3 != newDic.end(); ++iter3)
	{
		if(iter3 != newDic.end() && iter3->second)
			_findMonsterDic.insert(make_pair(iter3->first, iter3->second));
	}

	_focusChanged = false;

}
 
void Scene::addRole(int scale)
{
	if(_role == NULL)
		_role = new Player();

	//CCSprite * playerSprite = _role->loadPlayer();
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	CCPoint cp = ccp(info->playerBaseInfo.x, info->playerBaseInfo.y);

	//CCPoint pos = _frontbg->getMapPos();
	//CCSize size = _frontbg->getMapSizeV();

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
	

	_role->setStartPointByMapCell(cp, pos, pos_layer, size.height, size.width);

	//SceneProxy* sp = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	//if((!sp) || (!sp->_sceneInfoVo))
	//	return;

	//int map_w = int(ceil((sp->_sceneInfoVo->width) / 60.0f));
	//int map_h = int(ceil((sp->_sceneInfoVo->height) / 30.0f));

	//_role->setFindPath8((char**)(sp->_sceneInfoVo->mapData), map_h, map_w);


	_role->setPlayerVo(info->playerBaseInfo, scale);
	addElement(_role, 100);
	g_pHero = _role;

	if(g_pGlobalManage && g_pGlobalManage->isOnMeditation())
	{
		_role->icon(13);
	}
	else
	{
		_role->icon(0);
	}

	//add from flash
	_role->addEventListener(SceneConst::WALK_COMPLETE, this, callfuncND_selector(Scene::roleWalkCompleteHandler));

	_role->addEventListener(SceneConst::WALK_PATH_CHANGE, this, callfuncND_selector(Scene::roleWalkPathChangeHandler));

	_role->addEventListener(SceneConst::CHANGE_POSITION, this, callfuncND_selector(Scene::roleChangePositionHandler));

	_role->addEventListener(SceneConst::WALK_START_NODE, this, callfuncND_selector(Scene::roleWalkStartNodeHandler));

	_role->addEventListener(SceneConst::DEAD_EVENT, this, callfuncND_selector(Scene::roleDeadHandler));

	_role->addEventListener(SceneConst::WALK_START, this, callfuncND_selector(Scene::roleWalkStartHandler));

	//if(_role->poseState)
	//	_role->poseState->addEventListener(SceneConst::CHANGE1, this, callfuncND_selector(Scene::roleStateChangeHandler));

	_role->icon(0);

	char tmp[32] = {0};
	sprintf(tmp, "%s%d", _role->type().c_str(), _role->id());
	std::string tmp_str(tmp);

	_elementDic.insert(make_pair(tmp_str, _role));
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
	d.player = _role;
	dispatchEvent(SceneConst::PLAYER_LAYOUT, (void*)(&d));
	//dispatchEvent(new ParamEvent(ELEMENT_LAYOUT,{first:true,value:_role}));
}

void Scene::roleStateChangeHandler(CCNode* n, void* data)
{
	if(!data)
		return;

	PoseState* p = (PoseState*)data;
	if(p->state() == SceneConst::STAND)
	{
		if(clickTarget && clickTarget->type() == NPC_TYPE)
		{
			MapNPC* npc = (MapNPC*)(clickTarget);
			if(!npc)
				return;
			if(npc->action() == SceneConst::TALK)
			{
				roleDialogNPC(npc);
			}
			else if(npc->action() == SceneConst::FIGHT)
			{
				roleAttackMonster((MapNPC*)npc);
			}
		}
	}
}

MapNPC* Scene::addNPC(NPCVo* pNPCVo)
{
	if(!pNPCVo)
		return NULL;

	CCPoint p = ccp(pNPCVo->x, pNPCVo->y);
	std::map<int, CCPoint>::iterator iter = _posDic.find(pNPCVo->id);
	if(iter != _posDic.end())
	{
		iter->second = p;
	}
	else
	{
		_posDic.insert(make_pair(pNPCVo->id, p));
	}

	return BaseScene::addNPC(pNPCVo);
}

void Scene::roleWalkPathChangeHandler(CCNode* n, void* data)
{
	dispatchEvent(SceneConst::WALK_PATH_CHANGE, data);
	//dispatchEvent(new ParamEvent(SceneConst.WALK_PATH_CHANGE,evt.param));
}


void Scene::roleChangePositionHandler(CCNode* n, void* data)
{
	if(!data || !_role)
		return;

	struct Data1
	{
		bool first;
		Player* role;
	};
	Data1 d1;
	d1.first = false;
	d1.role = _role;
	//set the alpha of player
	dispatchEvent(SceneConst::ELEMENT_LAYOUT, (void*)(&d1));
	//this.dispatchEvent(new ParamEvent(ELEMENT_LAYOUT,{first:false,value:_role}));

	//CCPoint pos = _role->getPosition();
	CCPoint pos = _role->getMapStartPoint();
	dispatchEvent(SceneConst::ROLE_POS_CHANGED, (void*)(&pos));
	//this.dispatchEvent(new ParamEvent(ROLE_POS_CHANGED,{x:_role.x,y:_role.y} ));
	dispatchEvent(BaseScene::ROLE_POS_CHANGED, (void*)(&pos));//小地图系统要用
	
}
		

void Scene::roleWalkStartHandler(CCNode* n, void* data)
{
	dispatchEvent(SceneConst::WALK_START, data);//data = vector<CCPoint>* _path;
	dispatchEvent(SceneConst::WALK_START_1, data);
	//this.dispatchEvent(new ParamEvent(SceneConst.WALK_START,evt.param));
	
}
		
		
void Scene::roleWalkStartNodeHandler(CCNode* n, void* data)
{
	dispatchEvent(SceneConst::WALK_START_NODE, data);
	//this.dispatchEvent(new ParamEvent(SceneConst.WALK_START_NODE,evt.param));
}


void Scene::showNPC(int id, bool val)
{
	BaseScene::showNPC(id, val);
}

void Scene::NPCName(int id, const char* name)
{
	BaseScene::NPCName(id, name);
}

void Scene::NPCColor(int id, cocos2d::ccColor3B color)
{
	BaseScene::NPCColor(id, color);
}



void Scene::tradeWalkStartNodeHandler(CCNode* n, void* data)
{
	dispatchEvent(SceneConst::TRADE_WALK_START_NODE, data);
}



void Scene::removeNPC(int id)
{
	BaseScene::removeNPC(id);
	int index = 0;
	std::vector<int>::iterator iter = _redProgress.begin();
	for(; iter != _redProgress.end(); ++iter)
	{
		if(*iter == id)
		{
			index++;
			break;
		}
	}
	if(index != 0)
	{
		_redProgress.erase(iter);
		if(_redProgress.size() == 0)
		{
			_needDirPoint = false;
			_oldDirection = 0.0f;
			_newDirection = 0.0f;
			_step = 0.0;
			if(_role)
			{
				_role->removeDirArrow();
			} 
		}
	}
}


void Scene::levUpEffect(int accountId)
{
	char tmp[32] = {0};
	std::string s = PLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), accountId);
	std::string tmp_str(tmp);
	std::map<string, IElement*>::iterator iter = _elementDic.find(tmp);

	if( iter == _elementDic.end() )
		return;

	Player* player = (Player*)(iter->second);
	if(!player)
		return;

	//var effect:Effect1 = new Effect1();
	//effect.showEffect(rURL("assets/mapassets/effect/levelUp.swf"),  0, -20, player, null, BlendMode.ADD );
}

void Scene::playerHonor(int honorId, int last, int total)
{
	//DisplayObjectManager.playHonorEfc(honorId,last,total);
}

void Scene::doubleReward()
{
	/*doubleEffect = Reflection.createInstance("Shaut") as MovieClip;
	doubleEffect.x=600;
	doubleEffect.y=50;
	addChild(doubleEffect);
	mcPlayOnce(doubleEffect);*/
}

void Scene::missionComplete(std::string name, std::string desc)
{
	//DisplayObjectManager.missionComplete(name,desc);
}

void Scene::playOnce()
{
	/*var mc:MovieClip = e.target as MovieClip;
	if(mc.currentFrame==mc.totalFrames)
	{
	mc.stop();
	mc.removeEventListener(Event.ENTER_FRAME, playOnce);
	}
	mc = null;*/
}

void Scene::mcPlayOnce()
{
	//mc.addEventListener(Event.ENTER_FRAME,playOnce);
}

void Scene::roleStopMove()
{
	dispatchEvent(SceneConst::WALK_COMPLETE, 0);
	BaseScene::roleStop();
}

void Scene::roleWalkCompleteHandler(CCNode* n, void* data)
{
	dispatchEvent(SceneConst::WALK_COMPLETE, data);

	hideClickEffect();
	if(g_pGlobalManage && g_pGlobalManage->isOnMeditation())
	{
		_role->icon(13);
	}
	else
	{
		_role->icon(0);
	}

	if(!(g_pGlobalManage && g_pGlobalManage->isRoleHidden))
	{
		_role->setIsVisible(true);
		//_role.visible != _role.visible;
	}

	CCPoint pos;
	if(_role)
		pos = _role->getMapStartPoint();

	IElement* exit = getExitByPoint(pos);
	if(exit != NULL)
	{
		std::vector<int>* info = exit->otherInfos();
		if(info)
		{
			std::vector<int>::iterator iter = info->begin();
			if(iter != info->end())
			{
				int i = *iter;
				dispatchEvent(SceneConst::TRIGGER_EXIT,  &i);
			}
		}
	}
	else if(clickTarget && clickTarget->type() == NPC_TYPE)
	{
		MapNPC* npc = (MapNPC*)clickTarget;

		if(!npc)
			return;

		if(npc->action() == SceneConst::TALK)
		{
			roleDialogNPC(npc);
		}
		else if(npc->action() == SceneConst::FIGHT)
		{
			roleAttackMonster((MapNPC*)npc);
		}
		else if(npc->action() == SceneConst::WANDER)
		{
			roleAttackMonster((MapNPC*)npc);
		}
	}
}

void Scene::roleReDress()
{
	char tmp[128] = {0};
	std::string s = TRADEPLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), RoleManage::Instance()->accountInfo()->accountId);
	std::map<string, IElement*>::iterator iter = _elementDic.find(tmp);
	IElement* pIElement = 0;//jae note
	if(iter != _elementDic.end())
	{
		pIElement = iter->second;
		_elementDic.erase(iter);
	}
	if (!pIElement)
	{
		return;
	}
	
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

	pIElement->dispose();
	if(pIElement && pIElement->getParent())
		pIElement->removeFromParentAndCleanup(true);
}

void Scene::canMoveChange(CCNode* n, void* data)
{
	/*bool canMove;
	if(g_pGlobalManage)
		 canMove = g_pGlobalManage->canMove();*/
	//mouseDownChange(canMove);
}

void Scene::roleToExit(int id)
{
	char tmp[32] = {0};
	std::string s = EXIT_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);
	std::map<string, IElement*>::iterator iter = _elementDic.find(tmp);

	if ( iter == _elementDic.end() )
	{
		return;
	}
	
	Exit* exit = (Exit*)(iter->second);

	if(!_role)
		return;

	if(exit == NULL)
	{
		_role->icon(0);
		return;
	}

	setClickTarget(exit);
	if(_role->poseState && _role->poseState->_state == SceneConst::ATTACK)
		return;

	CCPoint ePos = exit->getMapStartPoint();
	CCPoint rPos = _role->getMapStartPoint();
	//float angle = atan2(ePos.y - rPos.y, ePos.x - rPos.x);
	float ranger = TileUtil::Instance()->getTileHeight() >> 1;
	
	float dis = sqrt((ePos.x - rPos.x) * (ePos.x - rPos.x) + (ePos.y - rPos.y) * (ePos.y - rPos.y));
	if(dis > ranger)
	{
		roleMove(ePos, ranger);
	}	
}

void Scene::roleToNPC(int id)
{
	if(_role)
	{
		if(g_pGlobalManage->isOnBusiness())
		{
			_role->icon(12);
		}
		else
		{
			_role->icon(11);
		}
	}

	char tmp[32] = {0};
	std::string s = NPC_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), id);
	std::string tmp_str(tmp);
	std::map<string, IElement*>::iterator iter = _elementDic.find(tmp);
	MapNPC* npc = NULL;
	if(iter != _elementDic.end())
		npc = (MapNPC*)(iter->second);
	/*std::map<int, MapNPC*>::iterator iter = _MapNPCDic.find(id);
	MapNPC* npc = iter->second;*/
	if(npc == NULL)
	{
		if(_role)
			_role->icon(0);
		return;
	}
	
	// new hand
	if (SceneManager::Instance()->getCurMapType() == SceneType::CITY)
	{
		int count = changeSceneTipsPopCallBack();
		if (count > 0)
		{
			roleStopMove();
			return;
		}
	}

	if(npc->action() == SceneConst::TALK)
	{
		roleDialogNPC(npc);
	}
	else if(npc->action() == SceneConst::FIGHT)
	{
		roleAttackMonster(npc);
	}
	else if(npc->action() == SceneConst::WANDER)
	{
		roleAttackMonster(npc);
	}
}

int Scene::changeSceneTipsPopCallBack()
{
	SceneMediator * pSceneMediator = (SceneMediator *)g_pFacade->retrieveMediator(AppFacade_SCENE_MEDIATOR);
	if (pSceneMediator)
	{
		return pSceneMediator->changeSceneTipsPopCallBack();
	}
	return 0;
}

void Scene::addStoryScene(StoryScene &storyScene)
{
	hideClickEffect();
	//storyScene.setBaseCoordinate(0,0);
	if (_storyLayer->getChildByTag(1))
	{
		_storyLayer->removeChildByTag(1,true);
	}	
	_storyLayer->addChild(&storyScene,0,1);
}
		
	
void Scene::rmFightScene()
{
	monsterAutoMoveStart();
	//DisplayObjectManager.clearChildren(_fightLayer);
}

void Scene::roleStopAndNPCMove(int id, int type)
{
	//mouseDownChange(false);
	roleStop();
	if(g_pGlobalManage)
	{
		if(g_pGlobalManage->bFollowerId)
		{
			std::vector<CCPoint> path;
			playerMove(g_pGlobalManage->bFollowerId, path);
		}
		else if(g_pGlobalManage->followerId)
		{
			std::vector<CCPoint> path;
			playerMove(g_pGlobalManage->followerId, path);
		}
	}
	//switch(type)
	//{
	//case EventType::ANIMATION:
	//		break;
	//case EventType::PVE:
	//	{
	//		LiveThing* npc = (LiveThing*)getNPC(id) ;
	//		if(clickTarget != NULL)
	//		{
	//			cancelClickTarget();
	//		}
	//		else if(npc != NULL)
	//		{
	//			monsterAutoMoveStop();
	//			npcMove(npc);
	//		}
	//		break;
	//	}
	//case EventType::PVP:
	//		break;
	//}
	//		
	//dispatchEvent(SceneConst::STOP_AND_ATTACK_COMPLETE, NULL); 

	MapNPC* npc = getNPC(id) ;
	if(clickTarget != NULL)
	{
		cancelClickTarget();
	}
	else if(npc != NULL)
	{
		CCPoint sPoint = TileUtil::Instance()->changePixsToTile(ccp(npc->_x, npc->_y));
		monsterAutoMoveStop();
		npcMove(npc);
	}
}
	
void Scene::monsterAutoMoveStop()
{
	autoMove = false;
	if(_findMonsterDic.size() == 0)
		return;

	std::map<int, IElement*>::iterator iter = _findMonsterDic.begin();
	for(; iter != _findMonsterDic.end(); ++iter)
	{
		if(iter->second != NULL)
		{
			Npc* npc = (Npc*)(iter->second);
			npc->stop();
		}
	}
}

void Scene::npcMove(LiveThing* npc)
{
	if(!npc)
		return;

	int ranger = 80;
	CCPoint startPoint = npc->getPosition();
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;

	CCPoint endPoint = getElemenetPosition(info->playerBaseInfo.x, info->playerBaseInfo.y);

	float angle = atan2(endPoint.y - startPoint.y , endPoint.x - startPoint.x);
			
	int dir = Utils::Instance()->getDir(startPoint.x, startPoint.y, endPoint.x, endPoint.y);
	if(dir % 3 ==0)
	{
		npc->dirState->state(3);
	}
	else
	{
		npc->dirState->state(1);
	}
			
	CCPoint point = startPoint;
	float dis = sqrt((endPoint.y - startPoint.y) * (endPoint.y - startPoint.y) + (endPoint.x - startPoint.x) * (endPoint.x - startPoint.x));
	if(dis > ranger)
	{
		point = ccp(endPoint.x - ranger * cos(angle), endPoint.y - ranger * sin(angle));
		//TweenLite.to(npc,0.5,{x:point.x,y:point.y ,onComplete:onFinishTween,onCompleteParams:[npc]});
	}
	else
	{
		onFinishTween(npc);
	}
}

void Scene::onFinishTween(LiveThing* npc)
{
	if(!npc)
		return;

	//addEventListener(SceneConst::ATTACK_COMPLETE, this, callfuncND_selector(Scene::attactComplete));
	npc->toAttack();
	
	if(npc->dirState)
	{
		if(npc->dirState->_state == 3)
		{
			_role->dirState->state(7);
		}
		else
		{
			_role->dirState->state(9);
		}
	}
}
			
void Scene::attactComplete(CCNode* n, void* data)
{
	removeEventListener(SceneConst::ATTACK_COMPLETE);
	//npc.removeEventListener(SceneConst.ATTACK_COMPLETE,attactComplete);
}

		
void Scene::monsterAutoMoveStart()
{
	autoMove = true;
}

bool Scene::getIsCanDialogPop(int npcId)
{
	//CCPoint point = monster->getMapStartPoint();
	std::map<int, CCPoint>::iterator iter = _posDic.find(npcId);
	if (iter == _posDic.end())
	{
		return false;
	}
	if (!_role)
	{
		return false;
	}
	
	CCPoint point1 = iter->second;
	CCPoint point = TileUtil::Instance()->changeTileToPixs(point1);
	CCPoint rPoint = _role->getMapStartPoint();
	//float angle = atan2(point.y - rPoint.y, point.x - rPoint.x);
	float ranger = _role->range() * TileUtil::Instance()->getTileWidth();

	float dis = sqrt((point.y - rPoint.y) * (point.y - rPoint.y) + (point.x - rPoint.x) * (point.x - rPoint.x));
	if(dis > (ranger + 10))
	{
		return false;
	}
	return true;
}

/**
	* role attack monster
	* @return 
	*/		
void Scene::roleAttackMonster(MapNPC* monster)
{
	g_pGlobalManage->g_isRedMonster = false;

	if(!monster || !_role)
		return;

	setClickTarget(monster);
	if(_role->poseState && _role->poseState->_state == SceneConst::ATTACK)
		return;

	CCPoint point = monster->getMapStartPoint();
	CCPoint rPoint = _role->getMapStartPoint();
	//float angle = atan2(point.y - rPoint.y, point.x - rPoint.x);
	float ranger = _role->range() * TileUtil::Instance()->getTileWidth();

	float dis = sqrt((point.y - rPoint.y) * (point.y - rPoint.y) + (point.x - rPoint.x) * (point.x - rPoint.x));
	if(dis > (ranger + 10))
	{
		roleMove(point,ranger);
	}	
	else
	{
		//Doyang 20120814
		//bool canFight = true;
		//SceneProxy *pSceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
		////Fix monster in city can be fight.
		//if(pSceneProxy->sceneInfoVo()->type == SceneType::CITY)
		//{
		//	bool red = this->isTaskCityMonster(monster);
		//	if(!red)
		//	{
		//		canFight = false;
		//	}
		//}
		if (!getIsTouchMoveBegin())
		{
			bool canFight = checkFightCD();
			if(canFight)
			{
				//ccColor3B cl1 = monster->color();
				//ccColor3B cl2 = ColorUtil::getGoodColor(6);
				//if(cl1.r == cl2.r && cl1.g == cl2.g && cl1.b == cl2.b)
				//{
				//	roleMove(ccp(point.x - TileUtil::Instance()->getTileWidth(), point.y - TileUtil::Instance()->getTileHeight()), ranger);
				//}

				//else
				{
					_role->icon(1);
					MapManage::Instance()->cancelAutoPath();

					//Doyang 20120811
					bool isRedMonster = false;
					std::vector<int>::iterator it;
					for(it = _redProgress.begin(); it != _redProgress.end(); ++ it)
					{
						MapNPC* pNpc = NULL;
						int redId = *it;
						char tempStr[20];
						sprintf(tempStr, "npc%d", redId);
						std::map<std::string, IElement*>::iterator iter;
						if((iter = _elementDic.find(tempStr)) != _elementDic.end())
						{
							pNpc = (MapNPC *) iter->second;
							if(pNpc->id() == monster->id())
							{
								isRedMonster = true;
								break;
							}
						}
					}
					if(monster->action() == SceneConst::FIGHT)
					{
						//	g_pGlobalManage->g_isRedMonster = isRedMonster;
						g_pGlobalManage->setIsShowEndFightButton( !isRedMonster );
					}
					if (monster->_npcVo->id > 9000)
					{
						g_pGlobalManage->setIsShowEndFightButton( false );
					}
					//else
					g_pGlobalManage->g_isRedMonster = isRedMonster;

					dispatchEvent(SceneConst::ATTACKMONSTER, (void*)(&(monster->_id)));
				}
			}
			else
			{
				MapManage::Instance()->cancelAutoPath();
			}
		}		
	}
}

bool Scene::checkFightCD()
{
	AccountInfoVo* info = RoleManage::Instance()->accountInfo();
	if(!info)
		return false;

	int energy = info->energy();
	int type = CDManage::Instance()->getLockBytype(CDManage::FIGHT);
	int token = 0;
	//int token = TokenManager::getInstance().getNum(TokenManager.TOKEN_FIGHT);
	if(_mapRank == SceneType::COPY|| _mapRank == SceneType::WORLD_BOSS)
	{
		return true;
	}
	if(energy + token <= 0)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("FT003"));
		return false;
	}
	else if(type == 1)
	{
		Message::Instance()->show(ValuesUtil::Instance()->getString("FT004"));
		//Alert.show("CD cooling，can not fight","",0);
		return false;
	}
	return true;
}

void Scene::roleDialogNPC(MapNPC* npc)
{
	if(!npc || !_role)
		return;

	setClickTarget(npc);
	if(_role->poseState && _role->poseState->_state == SceneConst::ATTACK)
		return;

	CCPoint nPos = npc->getMapStartPoint();
	CCPoint rPos = _role->getMapStartPoint();

	//float angle = atan2(nPos.y - rPos.y, nPos.x - rPos.x);

	float ranger = _role->_range * TileUtil::Instance()->getTileWidth();
	float dis = sqrt((nPos.x - rPos.x) * (nPos.x - rPos.x) + (nPos.y - rPos.y) * (nPos.y - rPos.y));
	if(dis > (ranger + 10.0f))
	{
		roleMove(nPos, ranger);
	}
	else
	{
		if (!getIsTouchMoveBegin())
		{
			_role->icon(1);
			MapManage::Instance()->cancelAutoPath();
			int id = npc->id();
			if (id == 9999)
			{//npc9999
				GongMediator* p = (GongMediator*)g_pFacade->retrieveMediator(AppFacade_GONG);
				if (p)
					p->openMBView();
			}	
			else
				dispatchEvent(SceneConst::DIALOG_NPC, (void*)(&id));
		}
	}
}	

void Scene::roleDialogTrader(Player* pPlayer)
{
	if(!pPlayer || !_role)
		return;

	//setClickTarget(pPlayer);
	if(_role->poseState && _role->poseState->_state == SceneConst::ATTACK)
		return; 

	CCPoint nPos = pPlayer->getMapStartPoint();
	CCPoint rPos = _role->getMapStartPoint();
	
	float ranger = _role->_range * TileUtil::Instance()->getTileWidth();
	float dis = sqrt((nPos.x - rPos.x) * (nPos.x - rPos.x) + (nPos.y - rPos.y) * (nPos.y - rPos.y));
	if(dis > (ranger + 10.0f))
	{
		roleMove(nPos, ranger);
	}
	else
	{
		do 
		{
			CC_BREAK_IF(!pPlayer);

			pPlayer->playSelectedEffect();

			struct StructTemp
			{
				int id;
				string name;
				int lv;
				int type;
			} param;

			param.id = pPlayer->_playerVo.accountId;
			param.name = pPlayer->_playerVo.name;
			param.lv = pPlayer->_playerVo.lev();
			if (param.id==RoleManage::Instance()->accountInfo()->accountId)
			{
				param.type = 3;
			} 
			else
			{
				param.type = 2;
			}
			GameDispatcher::getInstance()->dispatchEvent( GameDispatcher::SHOW_ROB_INFO, &param );

		} while (0);
	}
}

void Scene::rmStoryScene()
{
	//DisplayObjectManager.clearChildren(_storyLayer);
	_storyLayer->removeAllChildrenWithCleanup(true);
}

void Scene::dispose()
{
	RenderManage::Instance()->stop();
	RenderManage::Instance()->remove(this);

	if(_role != NULL)
	{
		_role->removeEventListener(SceneConst::WALK_COMPLETE);
		_role->removeEventListener(SceneConst::WALK_PATH_CHANGE);
		_role->removeEventListener(SceneConst::CHANGE_POSITION);
		_role->removeEventListener(SceneConst::WALK_START_NODE);
		_role->removeEventListener(SceneConst::DEAD_EVENT);
		_role->removeEventListener(SceneConst::WALK_START);
		//_role->release();
		//delete _role;
		_role = NULL;
	}


//#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)
	//jae: get npc and monster resid.
	std::vector<int> array;
	std::map<std::string, IElement*>::iterator iter = _elementDic.begin();
	for(; iter != _elementDic.end(); ++iter)
	{
		LiveThing* pElement = (LiveThing*)iter->second;
		string tmp = iter->first;
		if ( strncmp( tmp.c_str(), NPC_TYPE.c_str(), 3 )==0 )
		{
			array.push_back( pElement->_res.id );
		}
		if ( strncmp( tmp.c_str(), MONSTER_TYPE.c_str(), 6 )==0 )
		{
			array.push_back( pElement->_res.id );
		}
		
	}

//#endif
	if (_elementLayer)
	{
		CCNode* mapIn = _elementLayer->getChildByTag(648);
		if (mapIn)
		{
			mapIn->removeFromParentAndCleanup(true);
		}		
	}	

	BaseScene::dispose();

	if(_frontbg != NULL)
	{
		if(_frontbg->getParent() == _frontBGLayer)
		{
			_frontBGLayer->removeChild(_frontbg, true);
		}
		_frontbg->dispose();
		_frontbg->release();
		_frontbg = NULL;
	}


	//StageProxy.removeListener(resize);

//#if (CC_TARGET_PLATFORM != CC_PLATFORM_ANDROID)

	//jae: remove spriteFrame & animation & texture.
	PlayerInfoVo* info = RoleManage::Instance()->roleInfo();
	if(!info)
		return;
	char _assetURL[128];
	for(std::vector<int>::iterator iter = array.begin();
		iter != array.end(); ++iter)
	{
		int resid = *iter;

		sprintf( _assetURL, "assets/res/%d/model-%d.plist", resid, resid );
		if ( !BitmapMovieClip::isFileExist( _assetURL ) )
		{
			continue;
		}		

		char path[128] = {0};
		int direction[5] = {1, 2, 4, 7, 8};
		std::string frameName;
		// stand 
		for ( int i = 0; i < 5; i++ )
		{
			sprintf( path, "%d/stand-%d", resid, direction[i] );	// 1/stand-8-9.png
			frameName = std::string(path) + "-%d.png";
			CCAnimationCache::sharedAnimationCache()->removeAnimationByName( frameName.c_str() );
		}

		// walk 
		for ( int i = 0; i < 5; i++ )
		{
			sprintf( path, "%d/walk-%d", resid, direction[i] );	//..	/1/walk-4-1.png
			frameName = std::string(path) + "-%d.png";
			CCAnimationCache::sharedAnimationCache()->removeAnimationByName( frameName.c_str() );
		}

		// hit 
		for ( int i = 0; i < 5; i++ )
		{
			sprintf( path, "%d/hit-%d", resid, direction[i] );	//..	/1/hit-4-1.png
			frameName = std::string(path) + "-%d.png";
			CCAnimationCache::sharedAnimationCache()->removeAnimationByName( frameName.c_str() );
		}

		// attack 
		for ( int i = 0; i < 5; i++ )
		{
			sprintf( path, "%d/attack-%d", resid, direction[i] );	//..	/1/attack-4-1.png
			frameName = std::string(path) + "-%d.png";
			CCAnimationCache::sharedAnimationCache()->removeAnimationByName( frameName.c_str() );
		}

		CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile( _assetURL );

		sprintf( _assetURL, "assets/res/%d/model-%d.pvr.ccz", resid, resid );
		std::string pathKey = _assetURL;
		CCFileUtils::removeSuffixFromFile(pathKey);
		pathKey = CCFileUtils::fullPathFromRelativePath(pathKey.c_str());
		CCTextureCache::sharedTextureCache()->removeTextureForKey(pathKey.c_str());

		sprintf( _assetURL, "assets/res/%d", resid );
		SourceCacheManage::Instance()->remove( _assetURL, true );
	}
	//Begin Kenfly 20121109
	SourceCacheManage::Instance()->dispose();
	//End Kenfly 20121109
//#endif  // CC_PLATFORM_ANDROID
}

//void Scene::setClickTarget(IElement* value)
//{
//	if(value != NULL && clickTarget != value)
//	{
//		cancelClickTarget();
//		clickTarget = value;
//		clickTarget->setSelect(true);
//	}
//}

//void Scene::cancelClickTarget()
//{
//	if(clickTarget == NULL)
//		return;
//
//	clickTarget.setSelect(false);
//	clickTarget = NULL;
//}

void Scene::clickSceneHandler(CCPoint point)
{
	if (g_pGlobalManage && LayerManager::sceneLayer
		&& g_pGlobalManage->getCurFocusGID() != LayerManager::sceneLayer->getMyFocusGID())
	{
		return;
	}

	if(g_pGlobalManage && (!g_pGlobalManage->canMove()))
		return;

	if(!_role)
		return;

	_role->icon(1);
	
	///////////////////////////////////////
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCPoint pos;
	CCSize mapSize;
	if(_frontbg)
	{
		pos = _frontbg->getPosition();
		mapSize = _frontbg->getMapSizeV();
	}
	CCPoint pos_layer;
	if(_movingLayer)
		pos_layer = _movingLayer->getPosition();

	

	float h = mapSize.height;
	float w = mapSize.width;

	CCPoint clickScenePoint = _role->setEndPointByScreen(point, pos, pos_layer, h, w);
	_lastClickPoint = clickScenePoint;
	///////////////////////////////////////


	for(int j= _elementList.size() - 1; j >= 0; j--)
	{
		IElement* element = _elementList[j];
		if(element && element->isInteractive() == true && element->getIsVisible() == true)
		{
			if(element->isHit(clickScenePoint) == true)
			{
				hideClickEffect();
				if(element->type() == NPC_TYPE)
				{
					MapNPC* npc = (MapNPC*)element;

					//Begin Kenfly 20121026
					npc->playSelectedEffect();
					//End Kenfly 20121026

					if(npc->action() == SceneConst::TALK)
					{
						roleDialogNPC(npc);
					}
					else if(npc->action() == SceneConst::FIGHT)
					{
						roleAttackMonster(npc);
					}
					return;
				}
				else if(element->type() == TRADEPLAYER_TYPE)
				{
					Player* pPlayer = (Player*)element;
					roleDialogTrader(pPlayer);
					return;
				}
				else if(element->type() == PLAYER_TYPE)
				{
					setClickTarget(element);
					return;
				}
			}
		}
	}
	cancelClickTarget();
	hideClickEffect();
	MapManage::Instance()->cancelAutoPath();

	roleMove(clickScenePoint);

	// LH20121114
	if((ViewManager::getInstance()->mainNavigate)
		&& (ViewManager::getInstance()->mainNavigate->getisMainBtnOpen()))
	{
		ViewManager::getInstance()->mainNavigate->setisMainBtnOpen(false);
	}

	// LH20120128
	if(ViewManager::getInstance()->_pVScrollUI)
	{
		ViewManager::getInstance()->_pVScrollUI->showUI(false);
	}
}


void Scene::roleDeadHandler(CCNode* n, void* data)
{
}

// Doyang 20120710
void Scene::initRedProgress( char *data )
{
	_redProgress.clear();
	_redProgress = *(std::vector<int> *) data;
	//_redProgress.sort(Array.NUMERIC);
	_needDirPoint = true;
	if(_role){
		_role->initDirArrow();//主角比怪物先初始化，如果这时真的没有主角，那是百万分之一的概率
		updateDirection();
		//立即调整箭头到第一只怪的方向
		_oldDirection = _newDirection;
		_step = 0;
		_role->resetDirArrow(_oldDirection);
	} 
}

void Scene::updateDirection()
{
	int firstRed = getFirstRedProgress();

	MapNPC* pNpc = NULL;

	char tempStr[20];
	sprintf(tempStr, "npc%d", firstRed);
	std::map<std::string, IElement*>::iterator iter;
	if((iter = _elementDic.find(tempStr)) != _elementDic.end())
	{
		pNpc = (MapNPC *) iter->second;
	}
	_role->retain();
	if(pNpc){
		int subY = pNpc->getPosition().y - _role->getPosition().y;
		int subX = pNpc->getPosition().x - _role->getPosition().x;
		int sub = subY * subY + subX * subX;
		float dis = sqrt((float)sub);
		_role->goVisible(dis > POSX(150));
		_role->dirArrowVisible(dis > POSX(100));
		float dir = atan2(_role->getPosition().y - pNpc->getPosition().y, pNpc->getPosition().x - _role->getPosition().x) * 57.3;// 180/Math.PI == 57.3
		float diff = dir - _oldDirection;
		if(diff >= 180)
		{
			diff = diff - 360;
		}
		else if(diff < -180)
		{
			diff = diff + 360;
		}
		_newDirection = diff + _oldDirection;
		_step = diff / 20;
	}
}

//取得第一个红色怪进度
int Scene::getFirstRedProgress()
{
	if(!_redProgress.empty())
	{
		return _redProgress[0];
	}
	return 0;
}

void Scene::resetDirArrow()
{
	if(abs(_newDirection - _oldDirection) < abs(_step))
	{
		_oldDirection = _newDirection;
		_step = 0;
	}
	else
	{
		_oldDirection += _step;
	}
	_role->resetDirArrow(_oldDirection);
}

bool Scene::isTaskCityMonster(MapNPC *pMonster)
{
    TaskProxy *pTaskProxy = (TaskProxy *)g_pFacade->retrieveProxy(AppFacade_TASK_PROXY);
    if(!pTaskProxy)
    {
        return false;
    }
    
    std::vector<TaskVo *> &recList = pTaskProxy->_receivedTaskList;
    std::vector<TaskVo *>::iterator it;
    for(it = recList.begin(); it != recList.end(); ++it)
    {
        TaskVo *pTask = *it;
        if(!pTask) 
        {
            continue;
        }
        
        if(pTask->_taskTip->_type == TaskAskType::TASK_ASK_TYPE_KILL_MONSTER)
        {
			if(!TaskStrConcat::checkTaskFinish(pTask->_taskTip))
			{
				if(pTask->_taskTip->_progress == pMonster->id())
				{
					return true;
				}
			}
        }
           
    }
    return false;
}

CCSize Scene::getMapSizePixels()
{
	return _frontbg->getMapSizeV();
}

Scene::~Scene()
{

}
