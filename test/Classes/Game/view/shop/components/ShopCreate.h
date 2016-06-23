#ifndef _SHOPCREATE_H_
#define _SHOPCREATE_H_

#include "BaseType.h"
#include "model/shop/vo/ShopGoodsVo.h"
#include "CCUIPartialScrollView.h"

#define SHOP_ITEM_COUNT_PER_PAGE 8
#define SHOP_ITEM_PAGE_COUNT 2

class ShopGoods;
class ShopCreate:public CCUIPartialScrollView
{
public:
	ShopCreate(const CCRect& mRect);
	~ShopCreate();
	virtual void registerWithTouchDispatcher(void);
	void createGood(std::vector<ShopGoodsVo>* goods, int32 page, int32 pagesize);
	void reBuildGoods(std::vector<ShopGoodsVo>* goods, int32 page, int32 pagesize);
	ShopGoods* getCurSelectedShopGoods(CCPoint curTouchPoint);//¨ª¡§1y¡Á?¡À¨º;
public:
    static ShopCreate* shopScrollViewWithCCRect(const CCRect& mRect);
//
	//virtual int getCount();

	//virtual cocos2d::CCNode * getView( int position );

	//virtual void onItemClickListener( CCNode *itemCell, int position );
public:
	//CCUIListView *_pListView;
	//std::vector<ShopGoods*> _ListViewShopGoods;
private:
	cocos2d::CCMutableArray<cocos2d::CCObject *> *_goodsDic;
	int32 pagecount;
};
extern ShopCreate* g_pShopCreate;

#endif