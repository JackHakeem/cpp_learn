	/**
	 * GMSG_COMMU_FRIENDS_LIST = 0x201 (),			
	 服务端->客户端, 包结构
	 Short：				总页数,
	 Short：				当前页码,
	 Short：				本页玩家数,
		 Int：			玩家ID,
		 Short：			玩家主角色佣兵ID,
		 String：		玩家名字,
		 Byte：			命之水晶等级,
		 Byte：			在线状态		0 – 在线 / 1 – 离线 
		 Byte：			能否祝福标志	0 – 可以 / 1 – 不可 
	 * @author bobolive
	 * 
	 */		

#ifndef _SCMD205_H_
#define _SCMD205_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD205Node.h"

class SCMD205 : public Packet
{
public:
	SCMD205() {}
	virtual ~SCMD205() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_FRIENDS_SAME_LEVEL;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**总页数*/
	int16 a_total;
	/**当前页码*/
	int16 b_page;
	/**总页数*/
	std::list<SCMD205Node> c_nodeArr;
};


class SCMD205Factory: public MessageFactory
{
public :
	
	virtual ~SCMD205Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD205();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_FRIENDS_SAME_LEVEL;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD205Handler 
{
public:
	static uint32 Execute(SCMD205* pPacket) ;
};

#endif 