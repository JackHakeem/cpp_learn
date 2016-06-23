#ifndef _SCMD205NODE_H_
#define _SCMD205NODE_H_

#include "BaseType.h"
/**
	 *查看推荐好友列表
	GMSG_COMMU_FRIENDS_SAME_LEVEL = 0x205 (),			
	服务端->客户端, 包结构
	Short：				总页数，
	Short：				当前页码，
	Short：				玩家数,
		Int：			玩家ID,	
	    Short：			玩家主角色佣兵ID,
		String：		玩家名字,
		byte：			水晶等级, 
	 * @author bobolive
	 * 
	 */	
struct SCMD205Node
{
	SCMD205Node()
	{
		a_ID = 0;
		b_hiredID = 0;
		c_name = "";
		d_mainLev = 0;
	}
	int32 a_ID;
	int16 b_hiredID;
	std::string c_name;
	/**命之水晶等级*/
	int8 d_mainLev;
};

#endif