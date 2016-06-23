//
//  BaseScene.h
//  HLQS
//
//  Created by edward liu on 12-2-23.
//  Copyright (c) 2012 4399. All rights reserved.
//

#ifndef HLQS_BaseScene_h
#define HLQS_BaseScene_h
#include "cocos2d.h"
#include "BaseType.h"
#include "view/scene/components/BgBitmap.h"
#include "view/scene/components/Player.h"
#include "model/scene/vo/NPCVo.h"
#include "../components/MapNPC.h"
#include "model/scene/vo/GMProgessVo.h"
//#include "MapMonsters.h"
#include "LayerNode.h"
#include "model/scene/vo/ExitVo.h"
#include "view/interfaces/IRender.h"
#include "view/interfaces/IElement.h"
#include "Exit.h"
#include "utils/flash/CCIEventDispatcher.h"

using namespace cocos2d;

class BaseScene : public LayerNode, public IRender
{

public:
	enum
	{
		ROLE_POS_CHANGED = 10000,
		/*MAP_BG_INIT = 0,
		SMLMAP_BG_INIT,
		TRIGGER_EXIT,
		ROLE_MOVE,
		ROLE_POS_CHANGED,
		NPC_REMOVEDEADBODY,
		PLAYER_REMOVEDEADBODY,
		ATTACKMONSTER,
		DIALOG_NPC,
		ELEMENT_LAYOUT,
		NPC_MOVE,
		DISPOSE,
		BUILD,*/
	};

	BgBitmap* _frontbg;
	float m_mapWidth;
    float m_mapHeight;
    
    float m_screenWidth;
    float m_screenHeight;
    
    CCPoint m_map_pos_start;
    float m_distance_x;
    float m_distance_y;

	CCPoint m_cusPointByScreenPixels;
    CCPoint m_cusPointByMapPixels;
    CCPoint m_cusPointByMapCells;

	Player* _role;

	bool m_needStep;

	//from flash
	LayerNode* _movingLayer;  
	LayerNode* _frontBGLayer; 

	LayerNode* _faceLayer;		
	LayerNode* _elementLayer;		
	LayerNode* _frontLayer;		
	LayerNode* _effectLayer; 		
	LayerNode* _fightLayer;		
	LayerNode* _storyLayer;		
	LayerNode* _mouseLayer;		

	CCSprite* _clickEffectMc;
	CCAnimation* clickEffect;

	std::vector<IElement*> _elementList;		
	std::vector<IElement*> _faceList;			

	CCPoint _focusPos;
	CCPoint _oldPos;

	bool _depthChanged;
	bool _positionChanged;
	IElement* _moveElement;
	CCPoint _lastClickPoint;
	bool _isHidePlayer;
	IElement* clickTarget;
	std::map<std::string, IElement*> _elementDic;
	bool autoMove;
	int curFrame;

	std::map<int, IElement*> _findMonsterDic;
	std::map<int, IElement*> _findNpcDic;
	int _mapRank;

	CCPoint _cureentPoint;
	CC_SYNTHESIZE(bool,isHideDetectBegin,IsHideDetectBegin)
	CC_SYNTHESIZE(bool,isTouchMoveBegin,IsTouchMoveBegin)

	std::list<int> m_removeTraderQueue;
	void addRemoveEliment( int accId ) { m_removeTraderQueue.push_back(accId); }
public:
    BaseScene();

    virtual ~BaseScene();
    virtual bool init();

	void startListener();
	void playerChangePositionHandler(CCNode* n, void* data);

	virtual void buildScene(int width, int height, int mapRank, int offsetX, int offsetY,std::string path, CCPoint focusPos);

	//void addRole();

	void step_old(ccTime dt);
	void moveStep(ccTime dt);
    
    void setCusPointByScreenPixels(float x,float y);
    CCPoint * getCusPointByScreenPixels();
    
    CCPoint * getCusPointByMapPixels(CCPoint *cpScreen);
    CCPoint * getCusPointByMapCells(CCPoint *cpPixels,int nTileW,int nTileH);
    CCPoint * getCusPointByMapPixels();
    CCPoint * pixelsToCells(CCPoint *cpPixels);
    static int getDistanceBetweenTwoSprite(CCPoint pos1, CCPoint pos2);
    virtual CCPoint getElemenetPosition(float vx, float vy);
	virtual void focusPosChangeHandler(CCPoint focusPos);

    void setPlayerCenter();
    
    virtual void menuCloseCallback(CCObject* pSender);

    virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

	void roleMove(CCPoint endScenePoint, float ranger = 0.0f);
	void movePath(std::vector<CCPoint>& scenePath);
	void playerDeadHandler(CCNode* n, void* data);
	void playerLayout(CCNode* n, void* data);
	Player* addPlayerHandler(PlayerBaseVo* playerVo);
	Player* addPlayer(PlayerBaseVo* playerVo);
	void removePlayer(int accId);

	void removeTradePlayer(int accId);
	Player*  addTradePlayer(PlayerBaseVo* playerVo);
	
	void playerMove(int id, std::vector<CCPoint>& path);
	virtual void addElement(IElement* child, int zOrder = 0);
	void removeElement(IElement* displayObject);
	void removeAllElement();
	void addFaceElement(IElement* displayObject);
	void removeFaceElement(IElement* displayObject);
	void removeAllFaceElement();
	void addExit(ExitVo* exitVo);
	void removeExit(int id);
	void setExitVo(int id, ExitVo* exitVo);
	virtual void roleMoveElement();
	IElement* getExitByPoint(CCPoint point);
	LiveThing* getPlayer(int id);
	MapNPC* getNPC(int id);
	void sortElement();
	virtual void step();
	void roleStop();
	void setLayersVisible(bool value, bool isOpe = true);
	void showClickEffect(float tx, float ty);
	void hideClickEffect();
	void clearElement();
	virtual void dispose();
	virtual void removeNPC(int id);
	void showNPC(int id, bool val);
	void NPCName(int id, const char* name);
	void NPCColor(int id, cocos2d::ccColor3B color);
	void setClickTarget(IElement* value);
	virtual void cancelClickTarget();
	void setMoveElement(IElement* value, bool setOldNull = false);
	virtual void clickSceneHandler(CCPoint point);
	virtual MapNPC* addNPC(NPCVo* npcVo);
	void npcDeadHandler(CCNode* n, void* data);
	void npcMovePath(int id, std::vector<CCPoint>& path);
	void npcUpdateIcon(int id, int icon);
	void npcLayout(CCNode* n, void* data);
	void removeNPCDeadbodyHandler(CCNode* n, void* data);
	void removePlayerDeadbodyHandler(CCNode* n, void* data);
	CCPoint getElemenetPositionByRealPos(float vx, float vy);

	void moveFollowHandler(ccTime dt);
	void moveFollowHideUIHandler(ccTime dt);

	Player* addTradePlayerHandler(PlayerBaseVo* playerVo);
	void tradeplayerMove(int id, std::vector<CCPoint>& path);

protected:
	//std::map<int, MapNPC*> _MapNPCDic;

	// add NPC
	void addMapNPC();

	void mapNPCStep();

	//GPH 2012.3.27 add GroupMonster
	//void addMapGroupMonster();
	//void addGroupMonster( GMProgressVo* gmpVo );
	//std::map<int, MapMonsters*> _MapMonstersDic;
	//void mapMonstersStep();
};

extern Player* g_pHero;

#endif
