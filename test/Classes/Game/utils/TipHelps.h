#ifndef _TIPHELPS_H_
#define _TIPHELPS_H_

#include "BaseType.h"
#include "LayerNode.h"

class TipBase;
class TipConst
{
public:
	enum
	{
		REPLACE 	= -1,		//替换（保持原来的“StringToChange”）
		NORMAL 		= 0,		//普通
		BACKPACK 	= 1,		//包裹
		BANK 		= 2,		//仓库
		EQUIPMENT 	= 3,		//装备
		STRENG 		= 4,		//强化
		MAIL		= 5,		//邮件
		SHOP		= 6,		//高店
		DIALOG		= 7,		//任务对话框
	};
};

class TipHelps
{
public:
	TipHelps();
	~TipHelps();

	void init(bool isEquip=false, int32 type =0, bool isSkill = false, bool isXH=false);
	void setToolTips(LayerNode* sprite, TipBase* tips);//, std::string tips
	void setTips(TipBase* tips = 0, TipBase* otherTips = 0);
	void timerComplete();
	void rollOverHander();
public:
	int32 _type;
	bool _isEquip;
	bool _isSkill;
	bool _isXH;
	LayerNode* _sprite;
	TipBase* _toolTips;
	bool _isTip;
};

#endif