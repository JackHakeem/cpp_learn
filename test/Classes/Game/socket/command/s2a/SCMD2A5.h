/**
 *服务端返回购买结果
WMSG_WORLD_ MOD_IDENTIFY_INFO = 0x2A5	(677)
Uint32 	俑兵唯一ID
Uint16       俑兵模型ID
Uint16 		鉴定属性个数
    Uint8 	鉴定类型
    Uint8    鉴定等级 
 */

#ifndef _SCMD2A5_H_
#define _SCMD2A5_H_

#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD2A5 : public Packet
{
public:
	SCMD2A5() {}
	virtual ~SCMD2A5() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_MOD_IDENTIFY_INFO;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	struct  SCMD2A5Node
	{
		uint8 a_statsType;
		uint8 b_statsLv;
	};

	int32 a_mercId;
	uint16 b_mercModId;
	std::list<SCMD2A5Node> c_statsArr;
};


class SCMD2A5Factory: public MessageFactory
{
public :
	virtual ~SCMD2A5Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD2A5();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_MOD_IDENTIFY_INFO;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD2A5Handler 
{
public:
	static uint32 Execute(SCMD2A5* pPacket) ;
};
#endif