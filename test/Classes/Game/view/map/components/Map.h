#ifndef _MAP_H_
#define _MAP_H_

#include "PopContainer.h"
#include "LayerNode.h"
#include "UIListView/CCUIListView.h"
#include "SmallMapElement.h"

USING_NS_CC;

class NPCVo;
class Map:public PopContainer, CCUIListViewAdapter, CCUIListViewItemActionListener
{
public:
	enum
	{
		MAPZ_bgSprite,
		MAPZ_bitmapDataSprite,
		MAPZ_TitleLable,
		MAPZ_ListView,
		MAPZ_NpcListNameLable,
		MAPZ_ArrowUp,
		MAPZ_ArrowDown,
		MAPZ_CloseBtn,
		MAPZ_RoadLine,
		MAPZ_NpcLayer,
		MAPZ_WrdMapBtn,
	};

	enum
	{
		MAPTAG_bgSprite,
		MAPTAG_bitmapDataSprite,
		MAPTAG_TitleLable,
		MAPTAG_ListView,
		MAPTAG_NpcListNameLable,
		MAPTAG_ArrowUp,
		MAPTAG_ArrowDown,
		MAPTAG_CloseBtn,
		MAPTAG_NpcLayer,
		MAPTAG_WrdMapBtn,
	};

	Map();
	~Map();
public:
	virtual void removeDataObjectChild();
	void startHandler(int32 width, int32 height, CCPoint rolePos, char* bitmapData, std::string name);
	void startListViewHandler();
	bool init();
	void configUI();
	void addNPCHandler(NPCVo* vo);

	void updateNpcRes();
	virtual int getCount();
	virtual LayerNode * getView( int position );
	virtual void onItemClickListener( LayerNode *itemCell, int position );


	void rolePosChangeHandler(CCPoint _rolePos);
	void changePath();
	void clearClosePoint();
	void drawPath(std::vector<CCPoint> apath, int id=0);
	float getDistanceToRole(CCPoint po, bool resize=true);
	void roleMoveHandler(vector<CCPoint>& _array);
	void draw();
	CCPoint yConverse(CCPoint src);

	void onEnter();
	void onExit();

	// LH20121026 world map button handler
	void onClickOpenWorldMap(CCObject * pSender);

	//LH20121114
	void mapClickedHandle(CCPoint clickPoint);
public:
//触控begin

	bool containsTouchLocation(CCPoint touchPoint);

    virtual void registerWithTouchDispatcher(void);
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent){};

//	void step(ccTime dt);//触控计时

	enum TouchStateEnum
	{
		TouchState_0 = 0,//No state, is not inspire the touch module
	};
	/*
		 0
	   /   \
	   1   2
	  /     \
	 3       4
	*/

	//CC_PROPERTY(int32, _TouchState, TouchState)	


	CCPoint preTouchPoint;
    CCPoint currentTouchPoint;


//touch end
public:
	std::vector<LayerNode*> m_vNpcList;
public:
	CCUIListView *_pListView;

	void setMapLocalArea(CCRect var);
	//CCRect* getMapScreenArea();
	void runActionFade(CCNode * pNode , CCAction * pAction);
	CCAction * getFadeAction();

	float _factorX;
	float _factorY;
	float mapWidth;
	float mapHeight;
	std::map<int, SmallMapElement*> _NPCDic;
	std::vector<CCPoint> _roleMovePoints;
	void setroleMovePoints(std::vector<CCPoint> pathArr);

	CC_PROPERTY(int, _closePointIndex, closePointIndex)
	CCPoint _lastPoint;

	SmallMapElement* _role;

	CCLayer *_pContainer;

	CCPoint getScenePosByScreenPoint(CCPoint & pos);

//Begin Kenfly 20130125 : memory leak
	void removeNpcList();
//End Kenfly 20130125

};


#endif