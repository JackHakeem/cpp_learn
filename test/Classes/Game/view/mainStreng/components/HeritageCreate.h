/**
 * build streng goods
 */
#ifndef _HeritageCreate_H_
#define _HeritageCreate_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "utils/ScaleUtil.h"
#include "CCUIPartialScrollView.h"
#include "HeritageGoods.h"
#include "model/backpack/vo/GoodsInfo.h"
using namespace cocos2d;

class StrengGoodsVo;
class StrengGoods;

class HeritageCreate : public CCUIPartialScrollView
{
public:
	HeritageCreate(const CCRect& mRect);
	~HeritageCreate();

public:
	static HeritageCreate* HeritageCreateWithCCRect(const CCRect& mRect);

	bool init();
	void createGood( StrengGoodsVo* strengGoodsVo,int sitNum );
	void removeSkinChild();
	HeritageGoods* getStrengGoods( int id );

	void setDefaultGoodIndex(int val) { i = val; }

	virtual void registerWithTouchDispatcher();
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void update( ccTime dt );
	HeritageGoods* getGoods( int index );
	void updateGoods( GoodsInfo* _goodsInfo1, int param2 );
	void updateTip( uint32 id );

	int pages;
	int i;
private:
	std::map<int, HeritageGoods*> _goodsDic;
	int m_iTouchState;

	float m_fStep;
	int m_state;
	bool m_bDraded;
	HeritageGoods* m_pClickGood;
	CCTouch *m_pTouch;
	CCEvent *m_pEvent;
	float m_fYMove;
	CCPoint preTouchPoint;
};

#endif