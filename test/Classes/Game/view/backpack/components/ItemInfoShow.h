#ifndef _ITEMINFOSHOW_H_
#define _ITEMINFOSHOW_H_

#include "BaseType.h"
#include "Alert.h"

class BagGoods;
class BagView;

class ItemInfoShow: public LayerNode
{
public:
	ItemInfoShow();
	bool initWithBagGoods(BagGoods* pBagGoods, BagView* bagView);

	void tick(ccTime dt);

	void clickhandle(CCObject* pSender);

public:
	float dieCount;
	Alert* m_alert;
	BagGoods* m_pBagGoods;
};

#endif
