#ifndef _BAGCREATE_H_
#define _BAGCREATE_H_

#include "BaseType.h"
#include "BagGoods.h"
#include "CCUIPartialScrollView.h"

#define BAGMAXGRID 36
#define BACKPACK_ITEM_COUNT_PER_PAGE 16
#define BACKPACK_ITEM_ROW 4
#define BACKPACK_ITEM_COL 4

class GoodsInfo;
class BagGoods;
class BagCreate:public CCUIPartialScrollView
{
public:
	BagCreate(const CCRect& mRect);
	~BagCreate();

	void creatGood(std::map<int32, GoodsInfo*>& goodDic, uint32 goodsNum);
	void reBuildGoods(std::map<int32, GoodsInfo*>& goodDic, uint32 goodsNum);
	BagGoods* getBagGoods(int32 index);
	void updateGoods(char* arr);
	virtual void registerWithTouchDispatcher(void);
	BagGoods* getCurSelectedBagGoods(CCPoint curTouchPoint);//Through the coordinates
	void setHeightLine(uint32 sitNum, bool value);
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
public:
    static BagCreate* bagScrollViewWithCCRect(const CCRect& mRect);

private:
	cocos2d::CCMutableArray<cocos2d::CCObject *> *_goodsDic;
};

extern BagCreate* g_pBagCreate;

#endif