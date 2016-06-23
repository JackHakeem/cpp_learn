#ifndef _SCMD1CB_H_
#define _SCMD1CB_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**入会申请审批
 * GMSG_COMMU_GUILD_APPLY_HANDLE = 0x1CB (459)
 * 服务端->客户端, 包结构	
 * Int16：	公会ID
 * byte:		审批结果   0-操作成功 / 1-公会人数满 / 2-对方已加入其他公会
 * String:	被审批者名字
 * */ 
class SCMD1CB : public Packet
{
public:
	SCMD1CB() {}
	virtual ~SCMD1CB() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_APPLY_HANDLE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_guildId;
	int8 b_retNum;
	string c_name;
};


class SCMD1CBFactory: public MessageFactory
{
public :
	
	virtual ~SCMD1CBFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1CB();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_APPLY_HANDLE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1CBHandler 
{
public:
	static uint32 Execute(SCMD1CB* pPacket) ;
};

#endif 