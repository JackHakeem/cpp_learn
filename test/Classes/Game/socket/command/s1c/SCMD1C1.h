#ifndef _SCMD1C1_H_
#define _SCMD1C1_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
	/**
	 * GMSG_COMMU_GUILD_MEMBER_LIST = 0x1C1 (449)，			
	 服务端->客户端, 包结构
	 Short:		总页数
	 Short:		当前页码
	 Short:		本页人数,
		 int8:		职务,
		 Int：		玩家ID,
		 String：	名字,
		 short：		等级,
		 Int：		称号,
		 String：	状态		// -1 在线   0 离线  else 离线X天
		 Int:		贡献度
	 */	
class SCMD1C1 : public Packet
{
public:
	SCMD1C1() {}
	virtual ~SCMD1C1() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_MEMBER_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_total;
	int16 b_page;
	struct SCMD1C1Node
	{
		/**职务*/
		int8 a_position;
		int b_pID;
		string c_pName;
		int16 d_pLevel;
		/**称号*/
		int e_emblem;
		/**状态*/
		string g_pState;
		/**贡献度*/
		int h_con;
	};

	std::list<SCMD1C1Node> c_pArr;
};


class SCMD1C1Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1C1Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1C1();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_MEMBER_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1C1Handler 
{
public:
	static uint32 Execute(SCMD1C1* pPacket) ;
};

#endif 