#ifndef _SCMD1C6_H_
#define _SCMD1C6_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
查看科技列表
GMSG_COMMU_GUILD_TECH_LIST = 0x1C6 (454),			
服务端<-客户端, 包结构
Short：		总页数
Short：		当前页码
Short：		默认科技ID
Short：		科技数
	Short：科技ID,
	Short：科技等级,
	Int：需要银币,
	Int：已有银币
*/
class SCMD1C6 : public Packet
{
public:
	SCMD1C6() {}
	virtual ~SCMD1C6() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_TECH_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_total;
	int16 b_page;
	int16 c_defaultId;
	struct SCMD1C6Node
	{
		int16 a_scienceId;
		int16 b_scienceLevel;
		int c_requrieYB;
		int d_hasYB;
	};
	std::list<SCMD1C6Node> d_scienceArr;
};


class SCMD1C6Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1C6Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1C6();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_TECH_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1C6Handler 
{
public:
	static uint32 Execute(SCMD1C6* pPacket) ;
};

#endif 