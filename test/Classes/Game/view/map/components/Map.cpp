#include "Map.h"
#include "manager/PopEventName.h"
#include "NPCItem.h"
#include "utils/ValuesUtil.h"
#include "model/shop/ShopManager.h"

#include "model/shop/vo/shopVo.h"
#include "util/TileUtil.h"
#include "manager/TouchLayerEnum.h"
#include "utils/ScaleUtil.h"
#include "manager/GlobalManage.h"
#include "model/player/RoleManage.h"
#include "events/GameDispatcher.h"
#include "manager/sound/SoundManager.h"
#include "manager/PopManage.h"
#include "manager/ViewManager.h"


const float MAP_X_LEN = 600.f;
const float MAP_Y_LEN = 500.f;
const float screenWidth = 0;
const float screenHeight = 0;
const float TITLE_MAP_FONT_SIZE = 20.0f;
const float NPC_MAP_FONT_SIZE = 20.0f;
Map::Map()
{
	_factorX = 0.0f;
	_factorY = 0.0f;
	_lastPoint = ccp(0,0);
	_role = 0;
	_closePointIndex = 0;
	_pContainer = 0;
}


bool Map::init()
{
	if (!LayerNode::init())
	{
		return false;
	}

	// initialization dispatcher
	//dispatcher = GameDispatcher::getInstance ();
	// initialization key
	setIsNeedClose(false); // LH20121105
	setNeedBg(NeedBg_NO);
	this->setIsRelativeAnchorPoint(true);
	this->setAnchorPoint(ccp(0,0));
	
	this->setContentSize(CCSizeMake(POSX(860), POSX(600)));
	this->setPopContentSize(this->getContentSize());

	_pContainer = new LayerNode();
	_pContainer->init();
	_pContainer->setAnchorPoint(CCPointZero);
	//_pContainer->setPosition(POS(ccp(0, 12), ScaleUtil::CENTER_TOP));
	_pContainer->setPosition(ccp(0, POSX(12)));

	
	
	key = PopEventName::MAP;
	//set
	configUI();	
	// that can be touch
//	this-> setIsTouchEnabled (true);

	this->addChild(_pContainer, -1);//为了显示出红色路径
	_pContainer->release();
	return true;
}


void Map::startHandler(int32 width, int32 height, CCPoint rolePos, char* bitmapData, std::string name)
{
	if (!bitmapData) return;


	//

	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("assets/ui/map/res_map_bg.plist");
	SpriteNode* bgSprite = new SpriteNode();
	bgSprite->initWithSpriteFrameName("map/smallmapframe.png");
	bgSprite->setAnchorPoint(ccp(0,0));
	bgSprite->setPosition(CCPointZero);
	_pContainer->addChild(bgSprite, MAPZ_bgSprite-MAPZ_RoadLine, MAPTAG_bgSprite);
	bgSprite->release();
	//this->setContentSize(bgSprite->getTexture()->getContentSize());
	//setPopContentSize(this->getContentSize());	

	CCSpriteFrameCache::sharedSpriteFrameCache()->removeSpriteFramesFromFile("assets/ui/map/res_map_bg.plist");
	CCTextureCache::sharedTextureCache()->removeTextureForKey("assets/ui/map/res_map_bg.pvr.ccz");

	//
	SpriteNode* bitmapDataSprite = new SpriteNode();
	bitmapDataSprite->initWithFile(bitmapData);

	//map
	//先计算出X和Y需要放大的比例
	float factorX = POSX(MAP_X_LEN) / bitmapDataSprite->getTexture()->getContentSize().width;
	float factorY = POSX(MAP_Y_LEN) / bitmapDataSprite->getTexture()->getContentSize().height;
	bitmapDataSprite->setScaleX(factorX);
	bitmapDataSprite->setScaleY(factorY);
	//alpha
	//bitmapDataSprite->setOpacity(100);
	//AnchorPoint
	bitmapDataSprite->setAnchorPoint(ccp(0,0));

	mapWidth = bitmapDataSprite->getContentSize().width;
	mapHeight = bitmapDataSprite->getContentSize().height;
	//pos
	bitmapDataSprite->setPosition(ccp(POSX(15), (/*bgSprite->getTexture()->getContentSize().height*/POSX(594) - bitmapDataSprite->boundingBox().size.height)/2-POSX(19)));
	_pContainer->addChild(bitmapDataSprite, MAPZ_bitmapDataSprite-MAPZ_RoadLine, MAPTAG_bitmapDataSprite);
	bitmapDataSprite->release();
	//_npcLayer
	LayerNode* _npcLayer = (LayerNode*)_pContainer->getChildByTag(MAPTAG_NpcLayer);
	if (_npcLayer)
	{
		_npcLayer->setPosition(bitmapDataSprite->getPosition());
	}

	//_role
	if (!_role)
	{
		SmallMapElement* element = new SmallMapElement();

		element->createElement(5, true , (char *)RoleManage::Instance()->accountInfo()->name.c_str());

		_npcLayer->addChild(element);

		_role = element;
		element->release();
	}
	
	
	_factorX = POSX(width) / bitmapDataSprite->boundingBox().size.width;
	_factorY = POSX(height) /bitmapDataSprite->boundingBox().size.height;
	rolePos = ccp(POSX(rolePos.x) / _factorX, POSX(rolePos.y) /_factorY);
	rolePos = yConverse(rolePos);
	_role->setPosition(ccp(rolePos.x, rolePos.y));

	//title map name
	CCLabelTTF* pTitleLable = CCLabelTTF::labelWithString(name.c_str(), 
		CCSizeMake(POSX(150), POSX(TITLE_MAP_FONT_SIZE)), 
		CCTextAlignmentCenter, 
		"Arial",
		POSX(TITLE_MAP_FONT_SIZE));
	pTitleLable->setPosition(ccp(POSX(388), POSX(570)));//ccp(388, 570)
	_pContainer->addChild(pTitleLable, MAPZ_TitleLable-MAPZ_RoadLine, MAPTAG_TitleLable);
	pTitleLable->setColor(ccc3(255, 219, 96));

	//npclist name
	CCLabelTTF* pNpcListNameLable = CCLabelTTF::labelWithString(ValuesUtil::Instance()->getString("MAP001").c_str(),
		CCSizeMake(POSX(150), POSX(TITLE_MAP_FONT_SIZE)),
		CCTextAlignmentCenter,
		"Arial",
		POSX(TITLE_MAP_FONT_SIZE));
	pNpcListNameLable->setPosition(ccp(POSX(MAP_X_LEN+130), POSX(506)));//ccp(388, 570)
	_pContainer->addChild(pNpcListNameLable, MAPZ_NpcListNameLable-MAPZ_RoadLine, MAPTAG_NpcListNameLable);
	pNpcListNameLable->setColor(ccc3(255, 219, 96));

	//arrow up
	SpriteNode* arrowUp = new SpriteNode();
	arrowUp->initWithSpriteFrameName("map/arrow.png");
	arrowUp->setRotation(90.0f);
	arrowUp->setPosition(ccp(POSX(MAP_X_LEN+130), POSX(470)));
	_pContainer->addChild(arrowUp, MAPZ_ArrowUp-MAPZ_RoadLine, MAPTAG_ArrowUp);
	arrowUp->release();
	//arrow down
	SpriteNode* arrowDown = new SpriteNode();
	arrowDown->initWithSpriteFrameName("map/arrow.png");
	arrowDown->setRotation(-90.0f);
	arrowDown->setPosition(ccp(POSX(MAP_X_LEN+130), POSX(50)));
	_pContainer->addChild(arrowDown, MAPZ_ArrowDown-MAPZ_RoadLine, MAPTAG_ArrowDown);
	arrowDown->release();

	//Close button
	CCSprite *pNormalSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_normal.png");
	CCSprite *pPressedSprite = CCSprite::spriteWithSpriteFrameName("btn_close_1_pressed.png");
	CCMenuItemSprite *_btnClose = CCMenuItemSprite::itemFromNormalSprite(
		pNormalSprite,
		pPressedSprite, 
		this, 
		menu_selector(Map::clickCloseHandler) );
	_btnClose->setPosition( ccp(POSX(850), POSX(550)) );
	//CCSize winsz = CCDirector::sharedDirector()->getWinSize();
	CCMenu *buttonMenu = CCMenu::menuWithItems(_btnClose, 0);
	buttonMenu->setTouchLayer(TLE::WindowLayer_Map);
    buttonMenu->setPosition( CCPointZero );
	_pContainer->addChild(buttonMenu, MAPZ_CloseBtn-MAPZ_RoadLine, MAPTAG_CloseBtn);

	// LH20121026 world map button
	/*
	{
		CCSprite * pItemSprite1 = CCSprite::spriteWithSpriteFrameName("mapbtn/worldmap1.png");
		CCSprite * pItemSprite2 = CCSprite::spriteWithSpriteFrameName("mapbtn/worldmap2.png");
		CCMenuItemSprite * pWorldMapMenuItem = CCMenuItemSprite::itemFromNormalSprite(
			pItemSprite1,
			pItemSprite2,
			this,
			menu_selector(Map::onClickOpenWorldMap));
		CCMenu * pMenuMap = CCMenu::menuWithItem(pWorldMapMenuItem);
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pMenuMap->setPosition(ccp(size.width - POSX(280) , size.height - POSX(105)));
		pMenuMap->setTouchLayer(TLE::WindowLayer_Map);
		this->addChild(pMenuMap , MAPZ_WrdMapBtn , MAPTAG_WrdMapBtn);

		runActionFade(pMenuMap , getFadeAction());

		CCSprite * pBackSprite = new CCSprite();
		pBackSprite->initWithSpriteFrameName("mainui2/bigcircle.png");
		pBackSprite->setPosition(pMenuMap->getPosition());
		pBackSprite->setOpacity(255);
		this->addChild(pBackSprite , -1);
		pBackSprite->release();
	}
	*/

	return;
}

void Map::runActionFade(CCNode * pNode , CCAction * pAction)
{
	if (pNode && pAction)
	{
		pNode->runAction(pAction);
	}
}

CCAction * Map::getFadeAction()
{
	CCFiniteTimeAction * pFadeOut = CCFadeTo::actionWithDuration (0.8f , 128);
	CCFiniteTimeAction * pFadeIn = CCFadeTo::actionWithDuration (0.8f , 255);
	CCAction * pAction = CCRepeatForever::actionWithAction(CCSequence::actionOneTwo(pFadeOut , pFadeIn));
	return pAction;
}

void Map::onClickOpenWorldMap(CCObject * pSender)
{
	if(!g_pGlobalManage->_canMove)
	{
		return;
	}

	clickCloseHandler(0);

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::WALK_COMPLETE,0);
	Scene *pScene = ViewManager::getInstance()->_scene;
	if(pScene && pScene->_role && pScene->_role->poseState)
	{
		pScene->_role->poseState->state(SceneConst::STAND);
	}

	GameDispatcher::getInstance()->dispatchEvent(GameDispatcher::SHOW_UI_MAP, NULL);

	g_pGlobalManage->setIsInWordMap(true);
	g_pGlobalManage->showAllUI(false);
	SoundManager::Instance()->playPopContainerEffectSound();
}

void Map::startListViewHandler()
{
	//　Has connected a task list
	_pListView = CCUIListView::listViewWithCCRect(CCRectMake(POSX(30+MAP_X_LEN), POSX(60), POSX(260), POSX(400)), false);
	_pListView->setIsRelativeAnchorPoint(true);
    _pListView->setAnchorPoint(ccp(0,0));
	//_pListView->setAnchorPoint(CCPointZero);
	_pListView->setSpacingVertical(POSX(15));

	//_pListView->setClipLayerRect(CCRectMake(30+MAP_X_LEN, this->getPosition().y+90, 200+this->getPosition().x, 360));
	_pListView->setWorldSpaceLeftBottomPoint(ccp(_pListView->getPosition().x + _pContainer->getPosition().x + this->getPosition().x,  
		_pListView->getPosition().y + _pContainer->getPosition().y + this->getPosition().y));
	_pListView->setOnItemActionListener(this);
	_pContainer->addChild(_pListView, MAPZ_ListView-MAPZ_RoadLine, MAPTAG_ListView);
	_pListView->release();//Kenfly 20130125
	//_pListView->setAdapter(this);
	
}
/*
//CC_PROPERTY(CCRect, _mapArea, MapArea)
CCRect* Map::getMapScreenArea()
{
	CCNode* bitmapDataSprite = this->getChildByTag(MAPTAG_bitmapDataSprite);
	if (!bitmapDataSprite)
		return 0;
	else
	{
		CCPoint pos = getScreenPos(bitmapDataSprite);
        CCRect rect = bitmapDataSprite->boundingBox();
		return &rect;
		//return CCRectMake(pos.x, pos.y, bitmapDataSprite->getContentSize().width, bitmapDataSprite->getContentSize().height);
	}
}
*/
void Map::setMapLocalArea(CCRect var)
{

}

void Map::configUI()
{
	LayerNode* npcLayer = new LayerNode();
	_pContainer->addChild(npcLayer, MAPZ_NpcLayer-MAPZ_RoadLine, MAPTAG_NpcLayer);
	npcLayer->release(); //Kenfly 20130123
}

//touch begin

void Map::registerWithTouchDispatcher()
{
  //  CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, -10, true);
}

void Map::onEnter()
{
	this-> setIsTouchEnabled (true);
	CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, TLE::WindowLayer_Map, true);
	CCLayer::onEnter();
}

void Map::onExit()
{
	this-> setIsTouchEnabled (false);
	CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	CCLayer::onExit();

	//g_pGlobalManage->showAllUI(true);
}	

bool Map::containsTouchLocation(CCPoint touchPoint)
{
	CCRect contentLayerRect = CCRectZero;
	contentLayerRect.origin = this->getPosition();
	contentLayerRect.size = this->getContentSize();
	return CCRect::CCRectContainsPoint(contentLayerRect, touchPoint);
	////return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
	//CCPoint nodeSpaceLocation = this->convertTouchToNodeSpace(touch);

 //   CCRect contentLayerRect = CCRectZero;
 //   contentLayerRect.origin = CCPointZero;
 //   contentLayerRect.size = m_viewSize;//contentLayer->getContentSize();

 //   return CCRect::CCRectContainsPoint(contentLayerRect, nodeSpaceLocation);
}

bool Map::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	//
	CCPoint locationInView = touch->locationInView(touch->view());
    preTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	mapClickedHandle(preTouchPoint);

	/*
	if (!containsTouchLocation(preTouchPoint))
	{
		clickCloseHandler(0);
		return false;
	}
	*/

	//TIPS?????
	//LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	////
	//if (g_pGlobalManage->getCurFocusGID() != LayerManager::windowLayer->getMyFocusGID())//The current need windowLayer focus
	//{
	//	//LayerManager::tipsLayer->setLastItemGID(NONEINT);
	//	LayerManager::tipsLayer->setLastItemGID(NONEINT);
	//	return false;
	//}

	
	return false;
}

void Map::ccTouchMoved(CCTouch* touch, CCEvent* event)
{	
	//setSelectFrameShow(false);
	//
	CCPoint locationInView = touch->locationInView(touch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);
	////XCoordinate crane tower limit, too small think didn't move
	//int diaotaX = abs(currentTouchPoint.x - preTouchPoint.x);
	////



	//	else if (getTouchState() == TouchState_5)
	//	{
	//		CCPoint dstp = currentTouchPoint;
	//		dstp = ccp(currentTouchPoint.x, currentTouchPoint.y);
	//		
	//		if (m_pCurSelectedBagGoods)
	//		{
	//			CCPoint p = currentTouchPoint;
	//			//CCPoint __containerPosition = __container->getPosition();
	//			//p = ccp(p.x-__containerPosition.x, p.y-__containerPosition.y);
	//			m_pCurSelectedBagGoods->onMouseMoveHnadler(ccp(currentTouchPoint.x - preTouchPoint.x, currentTouchPoint.y - preTouchPoint.y));
	//		}
	//	}
	//}

	////
	//preTouchPoint = currentTouchPoint;
}

void Map::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
	//setSelectFrameShow(false);

	CCPoint locationInView = touch->locationInView(touch->view());
    currentTouchPoint = CCDirector::sharedDirector()->convertToGL(locationInView);

	//if (_pBagCreate)// && _pBagCreate->getIsScrolling()
	//{
	//	if (getTouchState() == TouchState_1)
	//	{//
	//		setTouchState(TouchState_6);
	//		//Detection met which backpack BagGood grid
	//		BagGoods* bagGoods = 0;
	//		bagGoods = getCurSelectedBagGoods(currentTouchPoint);//touchbegan Inside the preTouchPoint set
	//		//Display props information box
	//		if (bagGoods)
	//		{
	//			if (!bagGoods->_lock)
	//			{//???????
	//				if (bagGoods->myInfo->id > 0)
	//				{//??????
	//					if (LayerManager::tipsLayer->getLastItemGID() == bagGoods->getTag())
	//					{
	//						LayerManager::tipsLayer->setLastItemGID(NONEINT);
	//					}//LayerManager::tipsLayer->removeChildByTag(TipsLayer::TipsLayerTAG_itemInfoShow, true);
	//					else
	//					{
	//						bagGoods->myTip->rollOverHander();	
	//						LayerManager::tipsLayer->setLastItemGID(bagGoods->getMyFocusGID());
	//					}
	//					//setSelectFrameShow(true);
	//				}
	//			}
	//			else
	//			{//閫変腑閿佹锛屾槸鍚︿粯璐规墦寮�妗?	//				onClickHandler(bagGoods);
	//				//Confirm* pConfirm = new Confirm();
	//				//pConfirm->initWithParam("浣犱斧", this, menu_selector(BagView::handleBuyCell));
	//				//LayerManager::windowLayer->addChild(pConfirm,109);
	//			}
	//		}
	//	}
	//	if (getTouchState() == TouchState_3)
	//	{
	//		_pBagCreate->ccTouchEnded(touch, event);
	//	}
	//	else if (getTouchState() == TouchState_5)
	//	{
	//		if (m_pCurSelectedBagGoods)
	//				m_pCurSelectedBagGoods->onMouseUpHnadler(currentTouchPoint);
	//	}
	//}
	//

	////Change to return without state
	//setTouchState(TouchState_0);
} 

int Map::getCount()
{
	return m_vNpcList.size();
}

LayerNode* Map::getView(int position)
{
	if ((uint32)position >= m_vNpcList.size())
		return 0;
	else
	{
		m_vNpcList[position]->setvisibleSize(CCSizeMake(POSX(200), POSX(NPC_MAP_FONT_SIZE)));
		m_vNpcList[position]->setContentSize(CCSizeMake(POSX(200), POSX(NPC_MAP_FONT_SIZE)));
		return m_vNpcList[position];
	}
	/*
	static int a = 50;
	LayerNode* newl = new LayerNode();
	newl->addChild(CCLayerColor::layerWithColorWidthHeight(ccc4( 120,255-a,120-a,100), 200, NPC_MAP_FONT_SIZE+10));
	newl->setvisibleSize(CCSizeMake(200, NPC_MAP_FONT_SIZE+10));
	newl->setContentSize(CCSizeMake(200, NPC_MAP_FONT_SIZE+10));


	//newl->addChild(CCSprite::spriteWithFile("assets/ui/pack/lock.png"));
	a+=20;
	return newl;
	*/
}

void Map::onItemClickListener( LayerNode *itemCell, int position )
{
	CCLog("click...position=%d", position);

	if (!itemCell)
		return;

	int len = m_vNpcList.size();
	for (int pos = 0 ; pos < len ; pos++)
	{
		if (m_vNpcList[pos])
		{
			CCLabelTTF * pLab = (CCLabelTTF *)m_vNpcList[pos]->getChildByTag(0);
			if (pLab)
			{
				if (position == pos)
				{
					pLab->setColor(ccc3(40,233,25));
				}
				else
				{
					pLab->setColor(ccc3(255,255,255));
				}				
			}
		}		
	}
	updateNpcRes();

	NPCItem* tmpitemCell = (NPCItem*)itemCell;
	tmpitemCell->findNpc();
	//this.dispatchEvent(new ParamEvent(GO_TO_NPC,_vo.id))

}

void Map::updateNpcRes()
{
	//Doyang 20120711
	/*
	CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin();
		it != listChilds->end();
		++ it)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		pChildLayer->removeFromParentAndCleanup(true);
		pChildLayer->release();
	}
	*/
	CCMutableArray<LayerNode *>* listChilds = _pListView->getChilds();
	CCMutableArray<LayerNode *>::CCMutableArrayIterator it;
	for(it = listChilds->begin();
		it != listChilds->end();
		++ it)
	{
		LayerNode *pChildLayer = (LayerNode *) *it;
		if(!pChildLayer)
			continue;

		pChildLayer->removeFromParentAndCleanup(true);
		//pChildLayer->release();
	}


	_pListView->setAdapter(this);
}

void Map::addNPCHandler(NPCVo* vo)
{
	LayerNode* _npcLayer = (LayerNode*)_pContainer->getChildByTag(MAPTAG_NpcLayer);
	if (!_npcLayer) return;
	ShopVo* pShopVo = ShopManager::Instance()->getShopsByNPCId(vo->id);
	std::string name = vo->name;
	if(pShopVo) 
	{
		name.append("(");
		name.append(pShopVo->name);
		name.append(")");
	}

	SmallMapElement* element = new SmallMapElement();
	element->createElement(vo->icon, false, (char *)name.c_str() ,vo);//createElement(vo, 0xffffff, 6,vo.icon,false,_name);
	float x = POSX(vo->x) * TileUtil::Instance()->getTileWidth() / _factorX;//*_fullScreenX;
	float y = POSX(vo->y) * TileUtil::Instance()->getTileHeight() / _factorY;//*_fullScreenY;


	CCPoint dstp = ccp(x, y);
	dstp = yConverse(dstp);

	element->setPosition(dstp);//-disY
	_npcLayer->addChild(element);

	_NPCDic[vo->id] = element;
	element->release(); //Kenfly 20130123
}

CCPoint Map::yConverse(CCPoint src)
{
	float centerY = POSX(250);
	float disY = src.y-centerY;
	src.y = src.y-disY*2;
	return src;
}

/**
		 * 玩家位置改变处理函数
		 * @param e
		 *
		 */
void Map::rolePosChangeHandler(CCPoint _rolePos)
{

	CCPoint rolePos = ccp(_rolePos.x/_factorX, _rolePos.y/_factorY);
	CCPoint pos = ccp(0, 0);
	if (rolePos.x < (screenWidth/2))
	{
		pos.x = 0;
	}
	else if (rolePos.x > mapWidth - (screenWidth/2))
	{
		pos.x= mapWidth - (screenWidth);
	}
	else
	{
		pos.x=(rolePos.x - (screenWidth /2));
	}

	if (rolePos.y < (screenHeight /2))
	{
		pos.y=0;
	}
	else if (rolePos.y > mapHeight - (screenHeight /2))
	{
		pos.y = mapHeight - (screenHeight);
	}
	else
	{
		pos.y = (rolePos.y - (screenHeight /2));
	}
	CCPoint point = ccp(POSX(rolePos.x), POSX(rolePos.y));
	point = yConverse(point);
	_role->setPosition(point);
	changePath();

}

void Map::clearClosePoint()
{
	if (getclosePointIndex() != -1)
	{
		if (_roleMovePoints.size())
		{
			std::vector<CCPoint>::iterator it = _roleMovePoints.begin();
			_roleMovePoints.erase(it);
		}
	}
}

//CC_PROPERTY(int, _closePointIndex, closePointIndex)
int32 Map::getclosePointIndex()
{			
	if (_roleMovePoints.size())
	for (int i = 0; i < _roleMovePoints.size(); i++)
	{
		float disToClose = getDistanceToRole(_roleMovePoints[i]);
		if (disToClose < 1)
			return i;
		
	}
	return -1;
	/*
	for (var i:int = 0; i < _roleMovePoints.length; i++){
				var disToClose:Number = getDistanceToRole(_roleMovePoints[i] as Point);
				if(disToClose < 1)
					return i;
			}
			return -1;
			*/
	//return _closePointIndex;
}

void Map::setclosePointIndex(int32 var)
{
	//_closePointIndex = var;
}

void Map::changePath()
{
	if (_roleMovePoints.size() <= 0 )//
	{
		return;
	}
	clearClosePoint();

	if (_roleMovePoints.size() > 0)
	{
		CCPoint closePoint = _roleMovePoints[0];
		closePoint = ccp(POSX(closePoint.x)/_factorX, POSX(closePoint.y)/_factorY);
		closePoint = yConverse(closePoint);

		drawPath(_roleMovePoints);
			//_debugSprite.graphics.moveTo(_role.x, _role.y );
			//_debugSprite.graphics.lineTo(closePoint.x / _factorX*_fullScreenX, closePoint.y / _factorY*_fullScreenY);
		float x = closePoint.x-_role->getPosition().x;
		float y = closePoint.y-_role->getPosition().y;
		float dis = cocos2d::ccpDistance(closePoint, _role->getPosition());
		float rot = asin(y/dis)*180/3.1415f;//atan2(closePoint.x-_role->getPosition().x,closePoint.y-_role->getPosition().y)*180/3.1415f;

		if (x >= 0 && y >= 0)
		{
			rot = -rot;
		}
		else if (x <= 0 && y >= 0)
		{
			rot = rot+180;
		}
		else if (x <= 0 && y <= 0)
		{
			rot = 180 + rot;
		}
		else if (x >= 0 && y <= 0)
		{
			rot = -rot;
		}
		/*
		else if (x <= 0 && y >= 0)
		{
			rot += 180;
		}
		else if (x <= 0 && y <= 0)
		{
			rot = 180 - rot;
		}
		else if (x >= 0 && y <= 0)
		{
			rot = -rot;
		}
		*/

		//	float rot = -(atan2(closePoint.x-_role->getPosition().x,closePoint.y-_role->getPosition().y))*180/3.1415f+90;+90
		//CCActionInterval *rotateTo = CCRotateTo::actionWithDuration(2, 61.0f);
		_role->iconSetRotation(rot);
			//_role._icon.rotation=-(Math.atan2(closePoint.x / _factorX*_fullScreenX-_role.x,closePoint.y / _factorY*_fullScreenY-_role.y))*180/Math.PI+90;
	}
	

	float disTolast = getDistanceToRole(_lastPoint);
	if (disTolast < 0.8f)
	{
		_roleMovePoints.clear();
		//_debugSprite.graphics.clear();
	}
}

float Map::getDistanceToRole(CCPoint po, bool resize)
{
	float scanX;
	float scanY;
	if (resize)
	{
		scanX = _factorX;
		scanY = _factorY;
	}
	else
	{
		scanX = 1;
		scanY = 1;		
	}

	CCPoint ppo = ccp(POSX(po.x) / scanX,  POSX(po.y) /scanY);
	ppo = yConverse(ppo);
	float dis = cocos2d::ccpDistance(ppo, _role->getPosition());


//	double s = x2+y2;
	return dis;
}

void Map::drawPath(std::vector<CCPoint> apath, int id)
{
	std::vector<CCPoint> path = apath;
	/*
	if (_debugSprite == null)
	{
		_debugSprite = new Sprite();
		_skin["_mapContainer"].addChildAt(_debugSprite,_skin["_mapContainer"].getChildIndex(_role));
	}
	*/

	CCPoint spoint = path[0];
	//spoint是startpoint
	uint32 i = 1;
	while (i < path.size())
	{
		spoint = path[i];
		//spoint连接startpoint
		i++;
	}

	setroleMovePoints(path);
}

void Map::setroleMovePoints(std::vector<CCPoint> pathArr)
{
	_roleMovePoints = pathArr;
	CCLog("--------------------------------count=%d", _roleMovePoints.size());
	if (_roleMovePoints.size() >= 1)
	{
		_lastPoint = _roleMovePoints[_roleMovePoints.size() - 1];
	}
}

/**
	* 玩家移动
	* @param e
	*
	*/
void Map::roleMoveHandler(vector<CCPoint>& _array)
{
	drawPath(_array);
}

void Map::draw()
{
	PopContainer::draw();

	int size = _roleMovePoints.size();
	if (size < 2) return;


	//draw road point lines
	float yOffset = POSX(40.0f);
	float xOffset = POSX(14.0f);
	for (int i = 1; i < size; i++)
	{
		glDisable(GL_LINE_SMOOTH);
		glLineWidth( POSX(2.0f) );
		/*glColor4ub(255,0,0,255);*/
		glColor4f(1.0, 0.0, 0.0, 1.0);
		CCPoint fstp = _roleMovePoints[i-1];
		fstp = ccp(POSX(fstp.x) / _factorX, POSX(fstp.y) / _factorY);
		CCPoint secp = _roleMovePoints[i];
		secp = ccp(POSX(secp.x) / _factorX, POSX(secp.y) / _factorY);

		fstp = yConverse(fstp);
		fstp = ccp(fstp.x+xOffset, fstp.y+yOffset);
		secp = yConverse(secp);
		secp = ccp(secp.x+xOffset, secp.y+yOffset);
		ccDrawLine( fstp, secp );
	}
	
	//draw role to _roleMovePoints[0](closing point)
	glDisable(GL_LINE_SMOOTH);
	glLineWidth( POSX(2.0f) );
	/*glColor4ub(255,0,0,255);*/
	glColor4f(1.0, 0.0, 0.0, 1.0);
	CCPoint fstp = _roleMovePoints[0];
	fstp = ccp(POSX(fstp.x) / _factorX, POSX(fstp.y) / _factorY);
	

	//secp = ccp(secp.x/_factorX, secp.y/_factorY);

	fstp = yConverse(fstp);
	fstp = ccp(fstp.x + xOffset, fstp.y + yOffset);

	CCPoint secp = ccp(_role->getPosition().x + xOffset, _role->getPosition().y + yOffset);
	//secp = yConverse(secp);
	ccDrawLine( fstp, secp );
}

void Map::mapClickedHandle(CCPoint clickPoint)
{
	if (!_pContainer)
	{
		return;
	}	
	SpriteNode * pMapSprite = (SpriteNode * )_pContainer->getChildByTag(MAPTAG_bitmapDataSprite);
	if (pMapSprite)
	{
		CCPoint pos = getScreenPos(pMapSprite);
		float scaleX = pMapSprite->getScaleX();
		float scaleY = pMapSprite->getScaleY();
		if (CCRect::CCRectContainsPoint(CCRectMake(pos.x , pos.y , mapWidth * scaleX , mapHeight * scaleY) , preTouchPoint))
		{
			Scene * pScene = ViewManager::getInstance()->_scene;
			if (pScene)
			{
				CCSize mapRealSize = pScene->getMapSizePixels();
				float rateX = mapRealSize.width / ( mapWidth * scaleX );
				float rateY = mapRealSize.height / ( mapHeight * scaleY );

				float disX = ( preTouchPoint.x - pos.x ) * rateX;
				float disY = mapRealSize.height - ( preTouchPoint.y - pos.y ) * rateY;

				CCPoint scenePos = ccp(disX , disY);
			
				pScene->roleMove(scenePos);

				//setTargetEffect();
			}
		}	
	}
}

Map::~Map()
{

}

void Map::removeDataObjectChild()
{
	removeNpcList();
	_NPCDic.clear();
}

void Map::removeNpcList()
{
	std::vector<LayerNode*>::iterator ix = m_vNpcList.begin();
	while (ix != m_vNpcList.end())
	{
		(*ix)->release();
		++ix;
	}
	m_vNpcList.clear();
}