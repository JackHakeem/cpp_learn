#ifndef HLQS_EquiptmentItem_H_
#define HLQS_EquiptmentItem_H_
#include "LayerNode.h"
#include "model/backpack/vo/GoodsInfo.h"
#include "utils/TipBase.h"

USING_NS_CC;
class ValuesUtil;
class TipHelps;

class EquiptmentItem: public LayerNode,public TipBase
{
public:
	EquiptmentItem();
	~EquiptmentItem();
	bool init();
	EquiptmentItem(GoodsInfo* info, int sitNum, int page);
	void initEquiptmentItem(GoodsInfo* info, int sitNum, int page);
	void closeEquiptmentItem();
	void onMouseDownHandler(CCPoint curTouchPoint);
	void onMouseMoveHnadler(CCPoint curTouchPoint);
	void onMouseUpHnadler(CCPoint curTouchPoint);

	void setHighLight(bool isHighLight);
	CCAction * getAction();
public:
	GoodsInfo *_info;
	int _sitNum;
	int _page;
	TipHelps * _eqTip;
};

#endif