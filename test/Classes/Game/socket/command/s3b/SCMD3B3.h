#ifndef _SCMD3B3_H_
#define _SCMD3B3_H_

/**
	服务端返回打开幻龙塔面板信息
	WMSG_WORLD_ENTER_TOWER_GATE	= 0X3B3,			
	服务端->客户端, 包结构
	Uint8		免费进入剩余次数
	Uint8		本日进入次数（除免费次数外）
	Uint8		上次闯塔楼层（初始为0层）
	Uint8		历史最高闯塔楼层
	Uint8		爬塔留名（返回0则是100+）
	Uint16		在玩家留名层最近留名挑战的玩家个数（三个）
		String	名字
		Uint32 	时间
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"

class SCMD3B3 : public Packet
{
public:
	SCMD3B3()
	{
		a_numFree = 0; 
		b_numPay = 0;
		c_lastFloor = 0;
		d_maxFloor = 0;
		e_myRank = 0;
	}
	~SCMD3B3()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_ENTER_TOWER_GATE;}

public:
	int8 a_numFree; 
	int8 b_numPay;
	int8 c_lastFloor;
	int8 d_maxFloor;
	int8 e_myRank;

	struct SCMD3B3Node
	{
		string a_name;
		int b_time;
		SCMD3B3Node()
		{
			a_name = "";
			b_time = 0;
		}
	};
	std::list<SCMD3B3Node> f_topRank;
};


class SCMD3B3Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3B3();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_ENTER_TOWER_GATE;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3B3Handler 
{
public:
	static uint32 Execute(SCMD3B3 *pPacket) ;
};

#endif
