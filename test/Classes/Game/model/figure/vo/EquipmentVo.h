#ifndef HLQS_EquipmentVo_H_
#define HLQS_EquipmentVo_H_

#include "model/backpack/vo/GoodsInfo.h"

class EquipmentVo
{
public:
	std::map<int, GoodsInfo> m_equipments;

public:
	~EquipmentVo();
	int setIndex(int index, GoodsInfo goodsInfo);
	GoodsInfo* getIndex(int index);
	std::map<int, GoodsInfo>* getAll();
};

#endif