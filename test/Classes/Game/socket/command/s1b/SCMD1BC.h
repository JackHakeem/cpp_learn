#ifndef _SCMD1BC_H_
#define _SCMD1BC_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
查看入会申请列表
GMSG_COMMU_GUILD_APPLY_LIST = 0x1BC (444),			    
服务端->客户端, 包结构
Short：		总页数,
Short:      页码
Short：		申请人数,
	String：名字,
	Short：等级,
	 Int：称号,
	String：申请日期
*/
class SCMD1BC : public Packet
{
public:
	SCMD1BC() {}
	virtual ~SCMD1BC() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_APPLY_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_total;
	int16 b_page;
	struct SCMD1BCNode
	{
		string a_pName;
		int16 b_pLevel;
		int c_prestige;
		string d_applyDate;
	};

	std::list<SCMD1BCNode> c_applyArr;
};


class SCMD1BCFactory: public MessageFactory
{
public :

	virtual ~SCMD1BCFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1BC();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_APPLY_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1BCHandler 
{
public:
	static uint32 Execute(SCMD1BC* pPacket) ;
};

#endif 