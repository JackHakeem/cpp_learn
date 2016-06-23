#ifndef __MELTINGBAGGOODS_H_
#define __MELTINGBAGGOODS_H_

#include "cocos2d.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "LayerNode.h"
using namespace cocos2d;

class MeltingBagGoods : public LayerNode
{
public:
	MeltingBagGoods( const CCRect& rect);
	~MeltingBagGoods();

public:
	static MeltingBagGoods* MeltingBagGoodsWithRect( const CCRect& rect );
	void initMeltingBagGoodsVo( GoodsInfo* goodsInfo, int id );
	CCRect rect();

	virtual void onEnter();
	//virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
	void updateStrength( int strengthen );
	void setIcon( bool boolean );
	void setNum( int cnt );
	CCRect m_rect;
	//int m_ItemIndex;

	CCLabelTTF* _leveEquipment;
	CCLabelTTF* _nameEquipment;
	CCLabelTTF* _EquipCnt;

	CCSprite* _pic;
	CCSprite* _picClone;

	GoodsInfo* _myInfo;
	int _myStage;
	int _clickNum;
	int _page;
	uint _mySitNum;
	bool _isMove;

	CCPoint m_initPoint;	// 
};

#endif