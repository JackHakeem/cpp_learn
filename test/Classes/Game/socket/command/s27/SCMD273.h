/**
团战副本战队列表信息
CMSG_WORLD_GROUPINFO = 0x273 
服务端->客户端, 包结构
Uint16		副本ID
Uint32		战队ID
Int8		自动开战人数（-1为手动开战）
uint32      队长ID
战队玩家信息数组：
Uint8		玩家位置（0~7）
Uint32		玩家ID
String		玩家名字
Uint8		命之水晶等级
string		公会名
*/

#ifndef _SCMD273_H_
#define _SCMD273_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD273 : public Packet
{
public:
	SCMD273() {}
	virtual ~SCMD273() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD273Node
	{
		uint8 a_sitNum;
		int32 b_playerId;
		uint16 c_mercId;  
		std::string d_playerName;
		uint8 e_cryLev;
		std::string f_guildName;
	};

	uint16 a_fbId;
	uint16 b_teamId;
	int8 c_auto;
	int32 d_captainId;
	std::list<SCMD273Node> e_members;
};


class SCMD273Factory: public MessageFactory
{
public :

	virtual ~SCMD273Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD273();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD273Handler 
{
public:
	static uint32 Execute(SCMD273* pPacket) ;
};

#endif