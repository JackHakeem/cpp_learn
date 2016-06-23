#ifndef __HeritageGoods_H_
#define __HeritageGoods_H_

#include "cocos2d.h"
#include "LayerNode.h"
#include "utils/TipBase.h"
#include "utils/TipHelps.h"
using namespace cocos2d;

class StrengGoodsVo;

class HeritageGoods : public LayerNode, public TipBase
{ 
public:
	HeritageGoods( const CCRect& rect);
	~HeritageGoods();

public:
	static HeritageGoods* StrengGoodsWithRect( const CCRect& rect );
	void initStrengGoodsVo( StrengGoodsVo* heritageGoodsVo, int id );
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
	void resetPic();
	void updateTip();
	void onRollOverHandler();

	CCRect m_rect;
	int m_ItemIndex;

	CCLabelTTF* _leveEquipment;
	CCLabelTTF* _nameEquipment;
	CCSprite* _pic;
	CCSprite* _picClone;
	CCPoint m_initPoint;	// 

	StrengGoodsVo* _equpInfo;
	bool _isMove;
	TipHelps* myTip;
};

#endif