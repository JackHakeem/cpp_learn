#ifndef _SCMD1B7_H_
#define _SCMD1B7_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/** 
* 新建公会响应
GMSG_COMMU_GUILD_NEW_RESP = 0x1B7 (438),		
服务端->客户端, 包结构
Short：		公会ID				
String：	公会名字
short：		人数上限 
* @author bobolive
* 
*/
class SCMD1B7 : public Packet
{
public:
	SCMD1B7() {}
	virtual ~SCMD1B7() {}
	 

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_NEW_RESP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_guildId;
	string b_guildName;
	/**公会人数上限*/
	int16 c_guildLimit;
};


class SCMD1B7Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1B7Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1B7();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_NEW_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1B7Handler 
{
public:
	static uint32 Execute(SCMD1B7* pPacket) ;
};

#endif 