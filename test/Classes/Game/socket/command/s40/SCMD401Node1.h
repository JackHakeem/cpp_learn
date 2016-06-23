#pragma once

#include "BaseType.h"
/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 服务端返回-获蛋历史记录
WMSG_EGG_HISTORY = 0x401
服务端 -> 客户端, 包结构:
Uint8		许愿币个数
Uint16		个人记录数
	Uint8	蛋类(1装备蛋/2佣兵蛋/3资源蛋)
	Uint8	品质(1小/2大/3蓝色/4紫色/5橙色/6红色)
	Uint8	状态(1已开/2未开)
	Uint32	内容ID(比如装备ID,佣兵ID,物品ID)
	Uint32	内容数量(装备数量,佣兵数量,物品数量)
	Uint32	蛋数
Uint16		其他玩家记录数
	String	玩家名字
	Uint8	蛋类(1装备蛋/2佣兵蛋/3资源蛋)
	Uint8	品质(1小/2大/3蓝色/4紫色/5橙色/6红色)
	Uint8	状态(1已开/2未开)
	Uint32	内容ID(比如装备ID,佣兵ID,物品ID)
	Uint32	内容数量(装备数量,佣兵数量,物品数量)
	Uint32	蛋数

 * @data 2012-3-26 下午03:25:47 
 * 
 */ 

struct SCMD401Node1
{
	SCMD401Node1()
	{
		memset(this, 0, sizeof(SCMD401Node1));
	}

	int8 a_type;
	int8 b_quality;
	int8 c_state;
	int32 d_goodsId;
	int32 e_goodsNum;
	int32 f_num;
};