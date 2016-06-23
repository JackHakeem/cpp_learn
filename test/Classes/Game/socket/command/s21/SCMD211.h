	/**
	 * 从当前列表删除  // 用于黑名单列表
	GMSG_COMMU_FRIENDS_DEL_FROM_LIST = 0x211 (),			
	服务端->客户端, 包结构
	Int：				被删玩家ID,
	String：			被删玩家名字
	 * @author bobolive
	 * 
	 */	

#ifndef _SCMD211_H_
#define _SCMD211_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD211 : public Packet
{
public:
	SCMD211() {}
	virtual ~SCMD211() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_DEL_FROM_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_ID;
	std::string b_name;

};


class SCMD211Factory: public MessageFactory
{
public :
	
	virtual ~SCMD211Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD211();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_DEL_FROM_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD211Handler 
{
public:
	static uint32 Execute(SCMD211* pPacket) ;
};

#endif 