#ifndef _VIP_GIFT_VIEW_H_
#define _VIP_GIFT_VIEW_H_
#include "LayerNode.h"
#include "utils/TipBase.h"
#include "utils/TipHelps.h"

class VipGiftView : public LayerNode, public TipBase 
{
public:
	VipGiftView(int goodsId, int count);
	~VipGiftView();

	void initGrid();
	void dispose();
	void onGoodsItemClick(CCObject *pSender);
	void timerStep();

	int _goodsId; // Goods id
	int _count;
private:
	TipHelps *_popTip;
};
#endif