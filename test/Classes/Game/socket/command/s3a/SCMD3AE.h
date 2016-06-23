#ifndef _SCMD3AE_H_
#define _SCMD3AE_H_

/**
	服务端返回鼓舞结果
	WMSG_WORLD_TOWER_INSPIRE	= 0X3AE
	服务端->客户端, 包结构
	Uint8		鼓舞结果：０，失败；１，成功；２，不变（请求鼓舞信息）
	Uint8		鼓舞百分比(整数)
	Uint32		下次历练鼓舞所需历练值
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"

class SCMD3AE : public Packet
{
public:
	SCMD3AE()
	{
		a_result = 0;
		b_inspire = 0;
		c_nextPrac = 0;
	}
	~SCMD3AE()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_TOWER_INSPIRE;}

public:
	int8 a_result;
	int8 b_inspire;
	int c_nextPrac;
};


class SCMD3AEFactory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3AE();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_TOWER_INSPIRE;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3AEHandler 
{
public:
	static uint32 Execute(SCMD3AE *pPacket) ;
};

#endif
