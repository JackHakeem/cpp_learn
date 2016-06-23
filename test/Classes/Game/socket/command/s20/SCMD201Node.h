#ifndef _SCMD201NODE_H_
#define _SCMD201NODE_H_

#include "BaseType.h"
	/**
	 * GMSG_COMMU_FRIENDS_LIST = 0x201 (),			
	 服务端->客户端, 包结构
	 Short：				总页数,
	 Short：				当前页码,
	 Short：				本页玩家数,
		 Int：			玩家ID,
		 Short：			玩家主角色佣兵ID,
		 String：		玩家名字,
		 Byte：			命之水晶等级,
		 Byte：			在线状态		0 – 在线 / 1 – 离线 
		 Byte：			能否祝福标志	0 – 可以 / 1 – 不可
	 * @author bobolive
	 * 
	 */	
struct SCMD201Node
{
	SCMD201Node()
	{
		a_ID = 0;
		b_hiredID = 0;
		c_name = "";
		d_mainLev = 0;
		e_offLine = 0;
		f_fCrystal = 0;
	}

	int32 a_ID;
	int16 b_hiredID;
	/**好友名字*/
	std::string c_name;
	/**好友命之水晶等级*/
	int8 d_mainLev;
	int8 e_offLine;
	/**友之水晶等级是否达到祝福要求*/
	int8 f_fCrystal;
};

#endif