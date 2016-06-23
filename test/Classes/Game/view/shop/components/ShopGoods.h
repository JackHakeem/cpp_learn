#ifndef _SHOPGOODS_H_
#define _SHOPGOODS_H_

#include "BaseType.h"
#include "utils/TipBase.h"
#include "model/shop/vo/ShopGoodsVo.h"

class ShopGoodsVo;
class GameDispatcher;
class TipHelps;
class ShopGoods:public LayerNode, public TipBase
{
public:
	enum
	{
		RENDERZ_bg = 0,  // gray background
		RENDERZ_itembg, // items background
		RENDERZ_item, // items
		RENDERZ_ttfname, // name
		RENDERZ_ttfmoney, // money
		RENDERZ_buttonmenu, // button
	};
	enum
	{
		RENDERTAG_bg = 0,  // gray background
		RENDERTAG_itembg, // items background
		RENDERTAG_item, // items
		RENDERTAG_ttfname, // name
		RENDERTAG_ttfmoney, // money
		RENDERTAG_buttonmenu, // button
	};

	ShopGoods();
	~ShopGoods();

	bool initWithParam(ShopGoodsVo* info, int32 sitNum, int32 pageNum);
	void buy(CCObject* pSender);
	CCPoint getBgPos();
	CCPoint getItemBgPos();
	virtual CCSize getSrcContentSize();

public:
	ShopGoodsVo _myInfo;
	int32 _mySitNum;
	int32 m_page;
	GameDispatcher* dispatcher;

	TipHelps* myTip;
};

#endif