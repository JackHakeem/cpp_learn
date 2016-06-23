#pragma once

#include "BaseType.h"
#include "cocos2d.h"
#include "model/tower/vo/TowerRankItemVo.h"
using namespace cocos2d;

class TowerRankItem:public LayerNode
{
public:
	enum
	{
		TowerRankItemZ_bg1,
	};
	enum
	{
		TowerRankItemTAG_bg1,
	};
	TowerRankItem();
	~TowerRankItem();

	bool init(TowerRankItemVo* rankVo);
	void initView();

	//CCRect rect();
	//virtual void onEnter();
	//virtual void onExit();
	//bool containsTouchLocation(CCTouch* touch);
	//virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	//virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	//virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
public:
	TowerRankItemVo* itemVo;
};