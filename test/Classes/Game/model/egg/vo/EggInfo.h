#pragma once

#include "BaseType.h"

struct EggInfo
{
	EggInfo()
	{
		eggId = 0;
		type = 0;
		quality = 0;
		state = 0;
		goodsId = 0;
		goodsNum = 0;
		num = 0;
		name = "";
	}

	int32 eggId;			// 蛋蛋Id（涛涛说：客户端要自己根据服务端传过来的数组索引作为蛋蛋的Id）
	int32 type;			// 蛋蛋类型（1装备蛋/2佣兵蛋/3资源蛋）
	int32 quality;		// 蛋蛋品质（1小/2大/3蓝色/4紫色/5橙色/6红色）
	int32 state;			// 蛋蛋状态（1已开/2未开）
	int32 goodsId;		// 物品原型Id
	int32 goodsNum;		// 物品数量
	int32 num;			// 物品堆叠数
	std::string name;	// 玩家姓名（初始化其他玩家历史奖励信息的时候用到）	
};