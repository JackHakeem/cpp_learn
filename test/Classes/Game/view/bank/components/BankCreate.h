#ifndef _BANKCREATE_H_
#define _BANKCREATE_H_

#include "BaseType.h"
#include "BankGoods.h"
#include "CCUIPartialScrollView.h"

#define BANKMAXGRID 60
#define BANK_ITEM_COUNT_PER_PAGE 16
#define BANK_ITEM_ROW 4
#define BANK_ITEM_COL 4

class GoodsInfo;
class BankGoods;
class BankCreate:public CCUIPartialScrollView
{
public:
	BankCreate(const CCRect& mRect);
	~BankCreate();

	void creatGood(std::map<int32, GoodsInfo*>& goodDic, uint32 goodsNum);
	void reBuildGoods(std::map<int32, GoodsInfo*>& goodDic, uint32 goodsNum);
	BankGoods* getBankGoods(int32 index);
	void updateGoods(char* arr);
	virtual void registerWithTouchDispatcher(void);
	BankGoods* getCurSelectedBankGoods(CCPoint curTouchPoint);//Through the coordinates
	void setHeightLine(uint32 sitNum, bool value);
	//virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
public:
    static BankCreate* bankScrollViewWithCCRect(const CCRect& mRect);

private:
	cocos2d::CCMutableArray<cocos2d::CCObject *> *_goodsDic;
};

extern BankCreate* g_pBankCreate;

#endif