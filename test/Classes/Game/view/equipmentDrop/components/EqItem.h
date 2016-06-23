#pragma once

#include "BaseType.h"
#include "utils/TipBase.h"

class GoodsBasic;
class TipHelps;

class EqItem:public LayerNode, public TipBase
{
public:
	enum
	{
		EqItemZ_bg1,
	};

	enum
	{
		EqItemTAG_bg1,
	};
public:
	EqItem();
	~EqItem();

	bool init(GoodsBasic* goods);
	void setDropInfo();
	CCSize getSrcContentSize();
public:
	GoodsBasic* _goods;
	CCLabelTTF* _txtName;
	CCLabelTTF* _txtFrom;
	CCLabelTTF* _txtMonster;
	int _type;
	char _dropInfo[100];
	TipHelps* myTip;
};