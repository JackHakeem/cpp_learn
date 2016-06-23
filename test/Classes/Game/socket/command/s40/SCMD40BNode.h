#pragma once

#include "BaseType.h"
/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description 服务端返回-仓库
WMSG_EGG_DEPOT = 0x40B
服务端 ->客户端, 包结构:
Uint16		蛋数
	Uint8	蛋类(1装备蛋/2佣兵蛋/3资源蛋)
	Uint8	品质(1小/2大/3蓝色/4紫色/5橙色/6红色)
	Uint8	状态(1已开/2未开)
	Uint32	内容ID(比如装备ID,佣兵ID,物品ID)
	Uint32	内容数量(装备数量,佣兵数量,物品数量)
	Uint32	堆叠数

 * @data 2012-3-26 下午03:46:12 
 * 
 */ 

struct SCMD40BNode
{
	SCMD40BNode()
	{
		memset(this, 0, sizeof(SCMD40BNode));
	}

	int8 a_type;
	int8 b_quailty;
	int8 c_state;
	int32 d_goodsId;
	int32 e_goodsNum;
	int32 f_num;
};