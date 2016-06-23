#pragma once

#include "BaseType.h"
#include "model/egg/vo/EggInfo.h"
#include "utils/TipBase.h"


class GameDispatcher;
class TipHelps;

class ShowItem:public LayerNode, public TipBase
{
public:
	ShowItem();
	~ShowItem();

	bool init(std::string picpath);
	void onTimer(CCObject* pSender);
	void setTips(int state, int type, int smallType, int quality);
	void getEggExplain(int type, int smallType, int quality);
public:
	//GameDispatcher* _dispatcher;
	//int _itemType;// 物品框的类型，区分是宝箱里的还是大奖区的（1宝箱，2大奖区）

	//int _eggId;		// 蛋蛋Id
	//std::string _eggName;	// 蛋蛋名称
	//int _type;			// 蛋蛋类型
	//int _smallType;		// 蛋蛋小类
	//int _state;		    // 蛋蛋状态
	//int _quality;		// 蛋蛋品质
	//int _num;			// 蛋蛋堆叠数
	//int _goodsId;		// 蛋蛋里的物品Id
	//int _goodsNum;		// 蛋蛋里的物品数量
	//
	//bool _isSelect;	// 是否被点击选中
	//int _clickNum;	// 鼠标点击的次数

	//CCLabelTTF* _txtNum;

	//CCMenu* _pic;
	//LayerNode* _icon;// 图片容器

	//CCSize _frameContentSize;
	TipHelps* _tips;
};