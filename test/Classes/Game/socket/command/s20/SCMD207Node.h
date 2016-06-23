#ifndef _SCMD207NODE_H_
#define _SCMD207NODE_H_

#include "BaseType.h"
	/**
	 *查看黑名单列表
	GMSG_COMMU_FRIENDS_BLACK_LIST = 0x207 (),			
	服务端->客户端, 包结构
	Short：				总页数,
	Short：				当前页码,
	Short：				本页玩家数,
		Int：			玩家ID,	
		String：		玩家名字,
		Short：			水晶等级,
		Short：			玩家主角色佣兵ID,
		Byte：			在线状态		0 – 在线 / 1 – 离线  
	 * @author bobolive
	 * 
	 */	
struct SCMD207Node
{
	SCMD207Node()
	{
		a_ID = 0;
		b_name = "";
		c_mainLev = 0;
		d_hiredID = 0;
		f_offLine = 0;
	}

	int32 a_ID;
	/**好友名字*/
	std::string b_name;
	/**好友命之水晶等级*/
	int8 c_mainLev;
	int16 d_hiredID;
	int8 f_offLine;
};

#endif