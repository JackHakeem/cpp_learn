#include "StoryScene.h"
#include "utils/flash/CCIEventDispatcher.h"
#include "utils/ValuesUtil.h"
#include "manager/RenderManage.h"
#include "../../../model/com/ResourceManage.h"
#include "../../../model/com/vo/ResType.h"
#include "../../../util/TileUtil.h"
#include "../../../model/dialog/DialogManager.h"
#include "../../dialog/components/DialogUtil.h"
#include "Message.h"
#include "events/GameDispatcher.h"
#include "CCUIBackground.h"
#include "../SceneListenerMediator.h"
#include "mvc/Facade.h"
#include "model/scene/StoryProxy.h"
#include "model/player/RoleManage.h"
#include "CCMenuItem.h"
#include "BaseType.h"
#include "model/scene/vo/SceneInfoVo.h"
#include "model/scene/SceneProxy.h"
#include "utils/ScaleUtil.h"
#include "manager/GlobalManage.h"
#include "BaseScene.h"
#include "NPCChat.h"
#include "manager/sound/SoundManager.h"
#include "NewEAlert.h"
#include "manager/TouchLayerEnum.h"
#include "manager/ViewManager.h"
#include "manager/SourceCacheManage.h"

StoryScene::StoryScene(Scene &scene,StoryVo &storyVo,SceneInfoVo * pInfoVo)
{
	_curNewTips = 0;

	_scene	= &scene;
	this->setIsTouchEnabled(true);
	_scene->setIsTouchEnabled(false);
	_scene->_movingLayer->setIsTouchEnabled(false);
	_scene->_mouseLayer->setIsTouchEnabled(false);
	_scene->_mouseLayer->setIsVisible(false);
	_scene->_elementLayer->setIsVisible(false);
	if(_scene->_role->poseState)
	{
		_scene->_role->poseState->state(SceneConst::STAND);
	}

	_storyProxy = (StoryProxy *)g_pFacade->retrieveProxy(AppFacade_SCENESTORY_PROXY_CHANGE);
	_sceneProxy = (SceneProxy*)g_pFacade->retrieveProxy(AppFacade_SCENE_PROXY);
	_preStoryFocusPos = _sceneProxy->_rolePos;
	_storyVo	= &storyVo;
	_sceneInfoVo = pInfoVo;
	_w		= pInfoVo->width;
	_h		= pInfoVo->height;

	_skin_left = 0;
	_skin_right = 0;
	_skin = 0;;
	_headImageContain = 0;
	_endBtn = 0;
	_container = 0;
	_storyNode = 0;		
	_element = 0; 		
	_pNewHandTipsBg = 0;
	_pUIBack = 0;
	_pEndText = 0;
	_pCurNPCChat = 0;

	if(_frontbg == NULL)
		_frontbg = new BgBitmap;
	_frontbg->build(pInfoVo->width,pInfoVo->height, pInfoVo->sceneRoot+"front/", pInfoVo->offsetX, pInfoVo->offsetY);
	_frontbg->load(NULL, _sceneProxy->_focusPos, NULL, NULL); //Kenfly 20130114
	if(_frontbg->getParent() == NULL)
		_frontBGLayer->addChild(_frontbg);

	CCPoint targetPos = ccp(_storyVo->x + 2,_storyVo->y - 1);
	CCPoint targetStoryPosPixs = TileUtil::Instance()->changeTileToPixs(targetPos);
	setFocus(targetStoryPosPixs);

	this->BaseScene::setIsVisible(true);

	addToStage(this);

	g_pGlobalManage->showAllUI(false);

	init();

	_timerManage = TimerManage::Instance();
	_dispatcher = GameDispatcher::getInstance();
	_dispatcher->addEventListener(GameDispatcher::INTO_FIGHT,this,callfuncND_selector(StoryScene::onEnterBattle));
	_dispatcher->addEventListener(GameDispatcher::OUT_STROY,this,callfuncND_selector(StoryScene::onContentComplete));
	
	_scene->addStoryScene(*this);

	_scene->_elementLayer->setIsVisible(false);


	if(storyVo.id != 1012)
	{
		CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(StoryScene::dlgStep) , this , 5.0f ,false);
	}
}

bool StoryScene::init()
{
	this->setIsTouchEnabled(true);
	_scene->setIsTouchEnabled(false);
	this->BaseScene::init();
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	_screenSize = winSize;

	this->setAnchorPoint(ccp(0,0));
	this->setIsRelativeAnchorPoint(true);
	this->setContentSize(CCSizeMake(_w,_h));
	
// 	CCUIBackground * _pUIBack = new CCUIBackground();
// 	_pUIBack->initWithSpriteFrame("ui2.png",CCPointZero,CCPointZero,CCSizeMake(_screenSize.width,_screenSize.height));
// 	_scene->addChild(_pUIBack,0,256);

	//_scene->addChild(cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,50)), 0,256);
	_scene->addChild(cocos2d::CCLayerColor::layerWithColor(ccc4(0,0,0,80)), 11,257);

	_container = new LayerNode();
	if (_container)
	{
		_container->init();
		_container->setAnchorPoint(ccp(0,0));
		_container->setIsRelativeAnchorPoint(true);
		this->addChild(_container);
		_container->release();
	}	

	_headImageContain = new ImageContain();
	
	addEndButton();

	return true;
}

void StoryScene::dlgStep(ccTime dt)
{
	clickSceneHandler(0);
}

void StoryScene::resetTimer()
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(StoryScene::dlgStep) , this);
	CCScheduler::sharedScheduler()->scheduleSelector(schedule_selector(StoryScene::dlgStep) , this , 3.0f ,false);
}

void StoryScene::setFocus(CCPoint targetPosPixs)
{
	if(_sceneInfoVo)
	{
		CCSize size = CCDirector::sharedDirector()->getWinSize();

		if(targetPosPixs.x <= size.width / 2.0f)
		{
			targetPosPixs.x = _sceneInfoVo->width / 2.0f;
		}
		else if(targetPosPixs.x >= (_sceneInfoVo->width - size.width / 2.0f))
		{
			targetPosPixs.x = - _sceneInfoVo->width / 2.0f + size.width;
		}
		else
			targetPosPixs.x = - targetPosPixs.x + _sceneInfoVo->width / 2.0f + size.width / 2.0f;


		if(targetPosPixs.y < size.height / 2.0f)
		{
			targetPosPixs.y = - _sceneInfoVo->height / 2.0f + size.height;
		}
		else if(targetPosPixs.y > (_sceneInfoVo->height - size.height / 2.0f))
		{
			targetPosPixs.y = _sceneInfoVo->height / 2.0f;
		}
		else
		{
			targetPosPixs.y = - _sceneInfoVo->height / 2.0f + size.height / 2.0f + targetPosPixs.y;
		}
		_sceneProxy->focusPos(targetPosPixs);
	}
}

void StoryScene::addEndButton()
{
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("skip0.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("skip1.png");
	CCMenuItemSprite *_pMenuImg = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite, 
		this, 
		menu_selector(StoryScene::quickEndStroy));
	_endBtn = CCMenu::menuWithItem(_pMenuImg);
	_endBtn->setScale(1);
	_endBtn->setTouchLayer(/*TLE::SceneUILayer - 5*/-5000);
	_endBtn->setPosition(ccp(_screenSize.width-POSX(120),_screenSize.height - POSX(120)));
	_scene->addChild(_endBtn , 5);

	/*
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(pNormalSprite && pPressedSprite)
	{
		CCMenuItemSprite *_pMenuImg = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite, 
			this, 
			menu_selector(StoryScene::quickEndStroy));	
		_endBtn = CCMenu::menuWithItem(_pMenuImg);
		_endBtn->setAnchorPoint(CCPointZero);
		_endBtn->setIsRelativeAnchorPoint(true);
		_endBtn->setScale(0.9);
		_endBtn->setPosition(ccp(_screenSize.width-POSX(170),POSX(30)));
		_scene->addChild(_endBtn);
		_pEndText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("STOT").c_str(),CCSizeMake(POSX(100),POSX(20)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(18));

		_pEndText->setColor(ccc3(250,215,0));
		_pEndText->setPosition(ccp(_screenSize.width-POSX(165),POSX(30)));
		_scene->addChild(_pEndText,1);
	}
	*/
}

void StoryScene::addToStage(CCObject * pSender)
{
	RenderManage::Instance()->add(this);
}

void StoryScene::setBaseCoordinate(int x, int y)
{
// 	_container.x = x;
// 	_container.y = y;
}

void StoryScene::quickEndStroy(CCObject * pSender)
{
	//e.stopPropagation();
	//clearTimeout(_si);

	if(_scene)
	{
		if (_endBtn){	_scene->removeChild(_endBtn,true);}
		if (_pEndText){_scene->removeChild(_pEndText,true);	}
		if (_pNewHandTipsBg){_scene->removeChild(_pNewHandTipsBg,true);}
		//if (_pEndText){_scene->removeChildByTag(256,true);	}
		_scene->removeChildByTag(257,true);
	}

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::OUT_STROY, 0);
}

void StoryScene::clickSceneHandler(CCObject * pSender) 
{
	if (_pCurNPCChat)
	{
		_pCurNPCChat->setIsVisible(false);
	}
	
	skipNext();
}

/**
*  show next StoryScript 
*/	
void StoryScene::showNext(StoryScript &storyNode)
{
	_storyNode = &storyNode;
	int type = _storyVo->elemenet[_storyNode->index].type;
	switch (type)
	{
	case 0:
		_storyNode->type = PLAYER_TYPE;
		break;
	case 1:
		_storyNode->type = NPC_TYPE;// or MONSTER_TYPE
		break;
	case 3:
		_storyNode->type = ITEM_TYPE;
		break;
	}

	if(!(StoryScript*)&_storyNode)
	{
		skipNext();
		return;
	}

	clear();

	hideDialogs();

	_element = getElement(*_storyNode);
	if(!_element)
	{
		skipNext();  
		return;
	}

// 	if(storyNode.duration>0){   
// 		if(_si>0){
// 			clearTimeout(_si);
// 			_si = 0;
// 		}
// 		_si = setTimeout(skipNext, storyNode.duration);
// 	}

	if(_storyNode->isNew)
	{   // 
		_element->setIsVisible(true);
	}
	// 
	if(((_storyNode->type == PLAYER_TYPE)||(_storyNode->type == NPC_TYPE)||(_storyNode->type == MONSTER_TYPE)) && !_storyNode->resid)
	{
		BitmapMovieClip *effectMC = 0;
		//var callback:Function = null;
		LiveThing *alive = (LiveThing*)&_element;

		int vx,vy;
		if(_storyNode->resid>1000)
		{
// 			callback = function():void
// 			{
// 				effectMC.gotoAndPlay1(1, true);
// 			};
			std::string mcName = getMcNameByResId(_storyNode->resid);
			effectMC = new BitmapMovieClip;
			//effectMC.translate(mcName, BitmapMovieClip.MC_TYPE,callback, LoadLevel.MIDDILE);

			vx = 100;
			vy = -45;  // -25
			alive->addMC(_storyNode->resid, effectMC, vx, vy);
		}
		else if(_storyNode->resid>0)
		{
			//					addMC(type:int,effectMC:BitmapMovieClip,vx:int=0,vy:int=0)
			ResourceVo * resourceVo = ResourceManage::Instance()->getRes(ResType::SKILL_TYPE, _storyNode->resid);
			effectMC = new BitmapMovieClip;
			//effectMC->delay = resourceVo.timer;
			//effectMC.translate(resourceVo.skillUrl, BitmapMovieClip.URL_TYPE, callback, LoadLevel.MIDDILE);

			vy = resourceVo->offsety;
			alive->addMC(_storyNode->resid, effectMC, vx, vy);
		}
		else if(_storyNode->resid==-1)
		{
			alive->removeAllMC();
		}
	}

	if(_storyNode->move)
	{  
		int tox = _storyNode->_tox>0? _storyNode->_tox:(-_storyNode->_tox);
		int toy = _storyNode->_toy>0? _storyNode->_toy:(-_storyNode->_toy);
		bool syncRole = false;
		if(_storyNode->_tox<0 && _storyNode->_toy<0)
		{
			syncRole = true;
		}

		CCPoint point(tox,toy);
		CCPoint newPoint = TileUtil::Instance()->changeTileToPixs(point);
		std::vector<CCPoint> path;

		path.push_back(newPoint);

		if(_storyNode->type == PLAYER_TYPE)
		{
			playerMove(/*_storyNode->id*/RoleManage::Instance()->roleInfo()->playerBaseInfo.accountId, path);
			doDialog();
		}
		else if (_storyNode->type == NPC_TYPE)
		{
			npcMovePath(_storyNode->id, path);
			doDialog();
		}
		else if (_storyNode->type == MONSTER_TYPE)
		{
			npcMovePath(_storyNode->id, path);
			doDialog();
		}

		if(syncRole)
		{
			RenderManage::Instance()->add((IRender *)&_scene);

			//					_dispatcher.dispatchEvent(new ParamEvent(GameDispatcher.ROLE_MOVE_SYNC, [newPoint]));

			_scene->movePath(path);
		}

	}
	else
	{
		doDialog();
	}
}

void StoryScene::doDialog()
{
	if (	_storyNode->index > 1000 ||	_storyNode->index<0)
	{
		return;
	}
	if(_storyNode->dialog>0)
	{
		std::string content("");
		std::string halfBodyUrl("");

		if(/*_storyNode->type == ITEM_TYPE*/0)
		{
			content = DialogUtil::replaceContentWithName( DialogManager::Instance()->getDialogs(_storyNode->dialog)->content,ccc3(122,122,0));
			halfBodyUrl = (ResourceVo *)&_element->_res ? _element->_res.gethalfBodyUrl() : "";

			showDialog(content, _element->_eleName, halfBodyUrl);


			//
// 			if(!this->hasEventListener(MouseEvent.MOUSE_DOWN))
// 			{
// 				this->addEventListener(MouseEvent.MOUSE_DOWN,clickSceneHandler);
// 			}

		}
		else
		{
			//content = DialogUtil::replaceContentWithName( DialogManager::Instance()->getDialogs(_storyNode->dialog)->content,ccc3(122,122,0));
			if (DialogManager::Instance()->getDialogs(_storyNode->dialog))
			{
				content = DialogManager::Instance()->getDialogs(_storyNode->dialog)->content;
			}
			if(_storyNode->dir >= 2)
			{   
				if((ResourceVo *)&_element->_res)
				{
					LiveThing * liveThing = (LiveThing *)_element;
					//_VOICE_ *_voice = new _VOICE_();
					struct _VOICE_ _voice;
					_voice.content = content;
					_voice.name = _element->_eleName;
					_voice.id = liveThing->_res.id/*_element->getResource().id*/;
					_voice.style = _storyNode->dir;

					speak(liveThing,(struct _VOICE_ *)&_voice);

					_pCurNPCChat = liveThing->_npcChat;
				}
			}
			else
			{  
				/*
				LiveThing * liveThing = (LiveThing *)_element;
				//_VOICE_ *_voice = new _VOICE_();
				struct _VOICE_ _voice;
				_voice.content = content;
				_voice.name = _element->_eleName;
				_voice.id = liveThing->_res.id;
				_voice.style = _storyNode->dir;

				liveThing->speak((struct _VOICE_ *)&_voice);

				_pCurNPCChat = liveThing->_npcChat;
				*/
				
				// _storyNode->dir = 0 or 1
                ResourceVo temp = _element->getResource();
                ResourceVo * pTemp = (ResourceVo *) &temp;
				halfBodyUrl = pTemp ? _element->getResource().gethalfBodyUrl() : "";
				showDialog(content, _element->_eleName, halfBodyUrl);

				//
// 				if(!this.hasEventListener(MouseEvent.MOUSE_DOWN))
// 				{
// 					this.addEventListener(MouseEvent.MOUSE_DOWN,clickSceneHandler);
// 				}
				
			}
		}
		content = "";
		halfBodyUrl = "";
	}
	else if(_storyNode->dialog<0)
	{
		int disType = (_storyNode->dialog==-1) ? 0 : 1;
		//disappear(_element, disType);
		switch(disType)
		{
		case 0:// disappear fast
			_element->setIsVisible(false);
			break;
		case 1:// disappear slowly
			_element->setIsVisible(false);
			break;
		default:
			_element->setIsVisible(false);
			break;
		}
		skipNext();
	}
	else
	{
		
		// _storyNode->dialog == 0 
		// 
// 		if(!this.hasEventListener(MouseEvent.MOUSE_DOWN))
// 		{
// 			this.addEventListener(MouseEvent.MOUSE_DOWN,clickSceneHandler);
// 		}
	}
}

void StoryScene::speak(LiveThing * thing , _VOICE_ *_voice)
{
	if (thing && _voice)
	{
		this->setIsTouchEnabled(false);
		thing->speak(_voice);
	}
	
}

void StoryScene::walkCompleteHandler(CCNode * pSender,void *)
{
	doDialog();
}

void StoryScene::showDialog(std::string content,std::string elemName,std::string halfBodyUrl)
{
	
// 	if(!_skin_left)
// 	{
// 		try
// 		{
// 			_skin_left = Reflection.createInstance("ui_leftDialog");
// 		}
// 		catch(exception e)
// 		{
// 			skipNext();
// 			return;
// 		}
// 	}
// 	if(_skin_left)
// 	{
// 		_skin = _skin_left;
// 		_container.addChild(_skin_left);
// 		_skin_left.visible = false;
// 		_skin_left.x = 0;                   // _focusPoint.x; // StageProxy.width; 
// 		_skin_left.y =  StageProxy.height-50; // + _focusPoint.y;
// 	}
// 	if(!_skin_right)
// 	{
// 		try
// 		{
// 			_skin_right = Reflection.createInstance("ui_rightDialog");
// 		}
// 		catch(e:Error){
// 			skipNext();
// 			return;
// 		}
// 	}
// 	if(_skin_right)
// 	{
// 		_container.addChild(_skin_right);
// 		_skin_right.visible = false;
// 		_skin_right.x = StageProxy.width; // + _focusPoint.x; // StageProxy.width;
// 		_skin_right.y = StageProxy.height-50; // + _focusPoint.y; // StageProxy.height;
// 	}
// 
// 	if(_storyNode.dir == 0)
// 	{
// 		_skin_left.visible = true;
// 		_skin = _skin_left;
// 		_headImageContain.scaleX = 1;
// 	}
// 	else if(_storyNode.dir == 1)
// 	{
// 		_skin_right.visible = true;
// 		_skin = _skin_right;
// 		_headImageContain.scaleX = -1;
// 	}
// 
// 	_skin["_txtName"].text = eleName + ":";
// 
// 	_content = DialogUtil.replaceColor(content);
// 	//			_skin["_txtDescription"].htmlText = 
// 	fillContent();
// 
// 	if(halfBodyUrl && halfBodyUrl!=""){
// 		_headImageContain.url = rURL(halfBodyUrl) ;
// 	}
// 	_skin["_pngContainer"].addChild(_headImageContain);
// 
// 	if(!this.hasEventListener(MouseEvent.MOUSE_DOWN)){
// 		this.addEventListener(MouseEvent.MOUSE_DOWN,clickSceneHandler);
// 	}
}

Element *StoryScene::getElement(StoryScript &storyNode)
{
	Element *element = 0;
	if (storyNode.type == PLAYER_TYPE)
	{
		//element = getPlayer(storyNode.id);
		int id = RoleManage::Instance()->roleInfo()->playerBaseInfo.accountId;
		element = getPlayer(id);
	}
	else if (storyNode.type == NPC_TYPE)
	{
		element = getNPC(storyNode.id);
	}
	else if (storyNode.type == MONSTER_TYPE)
	{
		element = getNPC(storyNode.id);
	}
	else if (storyNode.type == ITEM_TYPE)
	{
		element = getItem(storyNode.id);
	}
	return element;
}

void StoryScene::hideDialogs()
{
	std::map<std::string, IElement*>::iterator iter = _elementDic.begin();
	for(;iter != _elementDic.end();iter++)
	{
		if((iter->second->type() == PLAYER_TYPE)||(iter->second->type() == NPC_TYPE))
		{
			LiveThing * live = (LiveThing *)iter->second;
			live->shutup();
		}
	}
}

void StoryScene::onEnterBattle(CCNode * pSender,void *)
{
	_dispatcher->removeEventListener(GameDispatcher::INTO_FIGHT);

	if(_si > 0)
	{
		//clearTimeout(_si);
		//_si = 0;
	}

	_dispatcher->dispatchEvent(GameDispatcher::OUT_STROY, (void *)1);

	// 
	if(_scene)
	{
		_scene->setLayersVisible(false);
	}
}

void StoryScene::onContentComplete(CCNode * pSender,void *)
{
	// add touch event
}

void StoryScene::skipNext()
{
	if(_si>0)
	{
		//clearInterval(_si);
		//_si = 0;
	}
	this->dispatchEvent(StoryScene::SHOW_NEXT,0);
}

void StoryScene::clear()
{
	
// 	if(_skin)
// 	{
// 		_skin.visible = false;
// 		_skin["_txtName"].text ="";
// 		_skin["_txtDescription"].text ="";
// 	}
// 	if(_skin_left)
// 	{
// 		_skin_left.visible = false;
// 	}
// 	if(_skin_right)
// 	{
// 		_skin_right.visible = false;
// 	}
	_headImageContain->clear();
}

Player *StoryScene::addPlayerHandler(char * data)
{
	/*
	Player *player = _scene->addPlayerHandler((PlayerBaseVo *)data);
	PlayerBaseVo *playerVo = (PlayerBaseVo*)data;
	CCPoint pos = getElemenetPosition(playerVo->x, playerVo->y);
	player->setPosition(pos);
	CCPoint point = TileUtil::Instance()->changeTileToPixs( ccp(playerVo->x, playerVo->y));
	player->mapStartPoint(point);

	std::vector<CCPoint> path;
	movePath(path);
	path.push_back(point);
	path.push_back(ccp(1290,1455));
	player->movePath(path);
	return player;
//	return _scene->addPlayerHandler((PlayerBaseVo *)data);
	*/

	
	PlayerBaseVo *playerVo = (PlayerBaseVo*)data;
	Player  *player = new Player();

	player->setPlayerVo(*playerVo);

	//player->addEventListener(SceneConst::CHANGE_POSITION, this, callfuncND_selector(BaseScene::playerLayout));
	player->addEventListener(SceneConst::WALK_COMPLETE,this,callfuncND_selector(StoryScene::walkCompleteHandler));

	char tmp[32];
	std::string s = PLAYER_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), playerVo->accountId);
	std::string tmp_str(tmp);
	_elementDic[tmp_str] = player;

	CCPoint pos = getElemenetPosition(playerVo->x, playerVo->y);
	player->setPosition(pos);
	CCPoint point = TileUtil::Instance()->changeTileToPixs( ccp(playerVo->x, playerVo->y));
	player->mapStartPoint(point);

	std::vector<CCPoint> path;
	movePath(path);
	path.push_back(point);
	path.push_back(ccp(1290,1455));
	//setElemenetPosition(playerVo.x,playerVo.y,player);
	setCusPointByScreenPixels(playerVo->x,playerVo->y);

	addElement(player,playerVo->y);

//	player->movePath(path);

	return player;
	
	
}

MapNPC *StoryScene::addNPC(char * data)
{
	/*
	NPCVo* pNPCVo = (NPCVo* )data;
	if(!pNPCVo)
		return NULL;
	MapNPC* pMapNPC = new MapNPC(pNPCVo);

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

// 	pMapNPC->addEventListener(SceneConst::DEAD_EVENT, this, callfuncND_selector(BaseScene::npcDeadHandler));
// 	pMapNPC->addEventListener(SceneConst::REMOVE_NPC_DEADBODY_EVENT, this, callfuncND_selector(BaseScene::removeNPCDeadbodyHandler));
// 	pMapNPC->addEventListener(SceneConst::CHANGE_POSITION, this, callfuncND_selector(BaseScene::npcLayout);
	pMapNPC->addEventListener(SceneConst::WALK_COMPLETE,this,callfuncND_selector(StoryScene::walkCompleteHandler));
	CCSprite* pCCSprite = pMapNPC->loadNpc();
	CCPoint pos_layer = _elementLayer->getPosition();
	CCSize size;
	CCPoint pos;
	if(_frontbg)
	{
		size = _frontbg->getMapSizeV();
		pos = _frontbg->getPosition();
	}
	pMapNPC->setStartPointByMapCell(ccp(pNPCVo->x, pNPCVo->y), pos, pos_layer, size.height, size.width );
	addElement(pMapNPC);
	return pMapNPC;
	*/
	NPCVo* pNPCVo = (NPCVo*)data;
	return BaseScene::addNPC(pNPCVo);	
}

Item *StoryScene::addItem(char * data)
{
	ItemVo *itemVo = (ItemVo *)data;

	char tmp[32];
	std::string s = ITEM_TYPE;
	sprintf(tmp, "%s%d", s.c_str(), itemVo->getID());
	std::string tmp_str(tmp);

	std::map<std::string, IElement*>::iterator iter = _elementDic.find(tmp_str);
	if(iter != _elementDic.end())
	{
		removeItem(itemVo->getID());
	}
	Item *item = new Item(*itemVo);
	memset(tmp,0,sizeof(tmp));
	sprintf(tmp,"%s%d",s.c_str(),item->_id);
	tmp_str.clear();
	tmp_str.assign(tmp);
	_elementDic.insert(make_pair(tmp_str, item));
	//setElemenetPosition(itemVo.x, itemVo.y, item);
	setCusPointByScreenPixels(itemVo->x,itemVo->y);

	addElement(item,itemVo->y);

	addFaceElement(item);
	return item;
}

void StoryScene::removeItem(int id)
{
	char path[32];
	std::string s = ITEM_TYPE;
	sprintf(path,"%s%d",s.c_str(),id);
	std::string tmp_str(path);

	std::map<std::string, IElement*>::iterator it = _elementDic.find(tmp_str);//jae note
	if ( it != _elementDic.end() )
	{
		Item *item = (Item *)it->second;
		if(!item)
			return;

		item->dispose();

		std::vector<IElement*>::iterator iter = _faceList.begin();
		for(; iter != _faceList.end(); ++iter)
		{
			if(*iter == item)
			{
				_faceList.erase(iter);
				break;
			}
		}

		removeFaceElement(item);

		_elementDic.erase(it);
	}
	
}

Item *StoryScene::getItem(int id)
{
	char path[32];
	std::string s = ITEM_TYPE;
	sprintf(path,"%s%d",s.c_str(),id);
	if(_elementDic[path])
	{	 
		return ((Item *)_elementDic[path]);
	}
	return 0;
}

void StoryScene::clickNewHandTips(CCObject *)
{
	_isNewhandLeader = false;
	if (_pNewHandTipsBg)
	{
		_pNewHandTipsBg->removeAllChildrenWithCleanup(true);
		//if (_pNewHandTipsBg->getParent())
		//{
		//	_pNewHandTipsBg->removeFromParentAndCleanup(true);
		//}
		//_pNewHandTipsBg->release();
	}

	SoundManager::Instance()->playButtonEffectSound();
}

void StoryScene::showNewhandLeader()
{
	_isNewhandLeader = true;

	if (_endBtn)
	{
		_endBtn->setIsVisible(false);
	}	

	
	if (!_pNewHandTipsBg)
	{
		
		_pNewHandTipsBg = new CCUIBackground();
		_pNewHandTipsBg->initWithSpriteFrame("ui.png" , ccp(0,0) ,  ccp(0,0)  , CCSizeMake(_screenSize.width , POSX(400)));
		_pNewHandTipsBg->setPosition(ccp(POSX(0) , _screenSize.height/2 - POSX(200)));
		//this->addChild(_pNewHandTipsBg);
		//_pNewHandTipsBg->release();
	}

	CCUIBackground * pContentBack = new CCUIBackground();
	pContentBack->initWithSpriteFrame("ui2.png" , ccp(0,0) ,  ccp(0,0)  , CCSizeMake(_screenSize.width/2 , POSX(260)));
	pContentBack->setPosition(ccp(POSX(360) , _screenSize.height/2 - POSX(240)));
	_pNewHandTipsBg->addChild(pContentBack,1);
	pContentBack->release();

//	char path[32];
//	sprintf(path,"assets/res/%d/halfbody.png",109);
	CCSprite * pHeadSprite = CCSprite::spriteWithSpriteFrameName("loading/girl.png");
	if (!pHeadSprite)
	{
		CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/loading/res_loading.plist");
		pHeadSprite = CCSprite::spriteWithSpriteFrameName("loading/girl.png");
	}
	
	if (pHeadSprite)
	{
		pHeadSprite->setFlipX(true);
		pHeadSprite->setScale(0.9);
		pHeadSprite->setAnchorPoint(CCPointZero);
		pHeadSprite->setIsRelativeAnchorPoint(true);
		pHeadSprite->setPosition(ccp(POSX(0),POSX(10)));		
		_pNewHandTipsBg->addChild(pHeadSprite);
	}

	std::string szNewHandContent = ValuesUtil::Instance()->getString("STCT");
	CCLabelTTF * _pContentText = CCLabelTTF::labelWithString(szNewHandContent.c_str(),CCSizeMake(POSX(500),POSX(240)),CCTextAlignmentLeft,g_sSimHeiFont,POSX(30));
	_pContentText->setAnchorPoint(CCPointZero);
	_pContentText->setIsRelativeAnchorPoint(true);
	_pContentText->setColor(ccc3(250,250,0));
	_pContentText->setPosition(ccp(POSX(380) , _screenSize.height/2 - POSX(220)));
	_pNewHandTipsBg->addChild(_pContentText , 2);
	
	
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("button.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("button1.png");
	if(pNormalSprite && pPressedSprite)
	{
		CCMenuItemSprite *pMenuNewHandItem = CCMenuItemSprite::itemFromNormalSprite(
			pNormalSprite,
			pPressedSprite, 
			this,
			menu_selector(StoryScene::clickNewHandTips));
		//pMenuNewHandItem->setAnchorPoint(CCPointZero);
		//pMenuNewHandItem->setIsRelativeAnchorPoint(true);
		pMenuNewHandItem->setScale(1.0);

		CCMenu * pMenuNewHand = CCMenu::menuWithItem(pMenuNewHandItem);
		pMenuNewHand->setAnchorPoint(CCPointZero);
		pMenuNewHand->setIsRelativeAnchorPoint(true);

		CCPoint pos = ccp(_pNewHandTipsBg->getContentSize().width-pMenuNewHandItem->getContentSize().width-POSX(260),POSX(40));
		pMenuNewHand->setPosition(pos);

		CCLabelTTF * _pOKText = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("STOK").c_str(),CCSizeMake(POSX(200),POSX(30)),CCTextAlignmentCenter,g_sSimHeiFont,POSX(24));
		//_pOKText->setAnchorPoint(CCPointZero);
		//_pOKText->setIsRelativeAnchorPoint(true);
		_pOKText->setColor(ccc3(250,215,0));
		_pOKText->setPosition(ccp(pos.x,pos.y));
		_pNewHandTipsBg->addChild(_pOKText,1);

		_pNewHandTipsBg->addChild(pMenuNewHand);
		_scene->addChild(_pNewHandTipsBg,1);
		//Doyang 20120712
		_pNewHandTipsBg->release();
	}

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/loading/res_loading.plist");
}

void StoryScene::dispose()
{
	CCScheduler::sharedScheduler()->unscheduleSelector(schedule_selector(StoryScene::dlgStep) , this);

	setFocus(_preStoryFocusPos);
// 	if (g_pHero)
// 	{
// 		g_pHero->setRoleSpeed(g_pGlobalManage->getRoleSpeed());
// 	}

	RenderManage::Instance()->remove(this);

	BaseScene::dispose();

	setFocus(_preStoryFocusPos);

	clickNewHandTips(0);

	if (_scene)
	{
		if (_endBtn){	_scene->removeChild(_endBtn,true);}
		if (_pEndText){_scene->removeChild(_pEndText,true);	}
		if (_pNewHandTipsBg){_scene->removeChild(_pNewHandTipsBg,true);}
		//if (_pEndText){_scene->removeChildByTag(256,true);	}
		_scene->rmStoryScene();
		//_scene->removeChildByTag(256,true);
		_scene->removeChildByTag(257,true);

		if (!g_pGlobalManage->getisInFight())
		{
			_scene->_movingLayer->setIsTouchEnabled(true);
			_scene->_mouseLayer->setIsTouchEnabled(true);
			_scene->_mouseLayer->setIsVisible(true);
			_scene->_elementLayer->setIsVisible(true);
		}		
		_scene->_storyLayer->removeAllChildrenWithCleanup(true);
		_scene->setIsTouchEnabled(true);
		_elementList.clear();

		_scene->rmStoryScene();

	}

	//BaseScene::dispose();
	//_timerManage.remove(dd);
	_dispatcher->removeEventListener(GameDispatcher::INTO_FIGHT);
	_dispatcher->removeEventListener(GameDispatcher::CONTENT_COMPLETE);
	RenderManage::Instance()->remove(this);

	if(_isNewhandLeader)
	{
		_isNewhandLeader = false;
		//LeaderAlert.close();
	}	

	g_pGlobalManage->isInStory = false;
	if (!g_pGlobalManage->_isInFight)
	{
		g_pGlobalManage->showAllUI(true);
	}

	// reset role speed
	if (_scene && _scene->_role)
	{
		_scene->_role->setRoleSpeed(g_pGlobalManage->getRoleSpeed());
	}

	//Begin Kenfly 20130114
	if (_frontbg)
	{
		_frontbg->dispose();
	}
	//End Kenfly 20130114

	// callback
	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::STORY_FOLLOW_CALLBACK,0);
	GameDispatcher::getInstance()->removeEventListener(GameDispatcher::STORY_FOLLOW_CALLBACK);
	
	SourceCacheManage::Instance()->disposeModel();
}

//void StoryScene::disappear(target:DisplayObject, disType:int=0);

void StoryScene::fillContent()
{

}

void StoryScene::dd()
{

}

std::string StoryScene::getMcNameByResId(int resId)
{
	std::string mc("");
	switch(resId)
	{
	case 1001:
		mc = "stun";  // 
		break;
	case 1002:
		mc = "star";  // 
		break;
	case 1003:   // 
		mc = "heart";
		break;
	case 1004:  // 
		mc = "question";
		break;
	case 1005:  // 
		mc = "ellipsis";
		break;
	case 1006:   // 
		mc = "chaos";
		break;
	case 1007:  // 
		mc = "happy";
		break;
	case 1008:  // 
		mc = "exclamation";
		break;
	case 1009:  // 
		mc = "anxiety";
		break;
	case 1010:  // 
		mc = "blackline";
		break;
	case 1011:  // 
		mc = "sweat";
		break;
	case 1012:  // 
		mc = "anger";
		break;
	case 1013:  // 
		mc = "lamp";
		break;
	case 1014:  // ZZZ
		mc = "sleeping";
		break;
	default:
		mc = "ellipsis";
		break;
	}
	return mc;
}

// void StoryScene::registerWithTouchDispatcher()
// {
// 	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -2000, true);
// }

void StoryScene::ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent)
{
	CCSetIterator iteratorTouch = pTouches->begin();
	CCTouch  * touchPoint = (cocos2d::CCTouch *)(* iteratorTouch);
	CCPoint pointLocation = touchPoint->locationInView(touchPoint->view());

	clickSceneHandler(0);

	return;
}
