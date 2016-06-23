#ifndef __STRENGGOODS_H_
#define __STRENGGOODS_H_

#include "cocos2d.h"
#include "LayerNode.h"
using namespace cocos2d;

class StrengGoodsVo;

class StrengGoods : public LayerNode
{
public:
	StrengGoods( const CCRect& rect);
	~StrengGoods();

public:
	static StrengGoods* StrengGoodsWithRect( const CCRect& rect );
	void initStrengGoodsVo( StrengGoodsVo* strengGoodsVo, int id );
	CCRect rect();

	virtual void onEnter();
	virtual void onExit();
	bool containsTouchLocation(CCTouch* touch);
	virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);

	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();
	void updateStrength( int strengthen );
	CCRect m_rect;
	int m_ItemIndex;

	CCLabelTTF* _leveEquipment;
	CCLabelTTF* _nameEquipment;
	CCSprite* _pic;

	StrengGoodsVo* _equpInfo;
};

#endif