/**
 *服务端返回购买结果
WMSG_WORLD_ REQ_IDENTIFY_INFO = 0x2A3 	(675)
服务端->客户端, 包结构
Uint8		格子数
Uint16		已招募俑兵数（不含解雇）
    Uint32 	俑兵唯一ID
    Uint16   俑兵模型ID
         Uint8鉴定类型（这里以格子数作为数组大小，每个俑兵都有格子数目个鉴定属性）
         Uint8鉴定等级 
 */
#ifndef _SCMD2A3_H_
#define _SCMD2A3_H_

#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD2A3 : public Packet
{
public:
	SCMD2A3() {}
	virtual ~SCMD2A3() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_REQ_IDENTIFY_INFO;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	struct SCMD2A3Node2 
	{
		uint8 a_statsType;
		uint8 b_statsLv;
	};

	struct SCMD2A3Node1 
	{
		int32 a_mercId;
		uint16 b_typeId;
		std::list<SCMD2A3Node2> c_statArr;
	};

	uint8 a_gridNum;
	std::list<SCMD2A3Node1> b_MercArr;
};


class SCMD2A3Factory: public MessageFactory
{
public :
	virtual ~SCMD2A3Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD2A3();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_REQ_IDENTIFY_INFO;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD2A3Handler 
{
public:
	static uint32 Execute(SCMD2A3* pPacket) ;
};
#endif