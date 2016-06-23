#ifndef _GOODS_VIEW_H_
#define _GOODS_VIEW_H_
#include "LayerNode.h"
#include "utils/TipBase.h"
#include "model/appoint/vo/GoodsVo.h"
#include "utils/TipHelps.h"

class GoodsView : public LayerNode, public TipBase 
{
public:
	GoodsView(GoodsVo *pGoodsVo, bool isAppointBlessView = false);
	~GoodsView();

	void initGrid();
	void dispose();
	void onGoodsItemClick(CCObject *pSender);
	void timerStep();
	void doubleClick();
	
	bool _isAppointBlessView;
	GoodsVo *goodsVo;				//物品值对象
private:
	//_grid:MovieClip;				//物品背景格子
	//_pic:PicLoadingContent = null;		//商人头像
	TipHelps *_popTip;				//悬停提示信息
	//_timer:Timer = null;				//双击计时器
	int _numClick;					//双击计数器
};
#endif