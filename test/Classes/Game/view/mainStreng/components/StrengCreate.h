/**
 * build streng goods
 */
#ifndef _STRENGCREATE_H_
#define _STRENGCREATE_H_

#include "BaseType.h"
#include "cocos2d.h"
#include "utils/Singleton.h"
#include "utils/ScaleUtil.h"
using namespace cocos2d;

#define STRENG_CREATE_W POSX(538)
#define STRENG_CREATE_H POSX(428)

class StrengGoodsVo;
class StrengGoods;

class StrengCreate : public CCLayer, public Singleton<StrengCreate>
{
public:
	StrengCreate();
	~StrengCreate(){};

public:

	bool init();
	LAYER_NODE_FUNC(StrengCreate);
	void createGood( StrengGoodsVo* strengGoodsVo,int sitNum );
	void removeSkinChild();
	void updateTip( int id );
	StrengGoods* getStrengGoods( int id );
	CCNode *getNewHandItem(int eqSitNum);

	//int getDefaultGoodIndex() const { return i; }
	void setDefaultGoodIndex(int val) { i = val; }
	void registerWithTouchDispatcher();
	void ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent );
	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	CCRect rect();
	bool containsTouchLocation(CCTouch* touch);
private:
	std::map<int, StrengGoods*> _goodsDic;
	int i;
};

#endif