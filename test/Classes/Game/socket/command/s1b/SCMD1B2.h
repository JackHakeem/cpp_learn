#ifndef _SCMD1B2_H_
#define _SCMD1B2_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
	/**
	 查看公会列表（分页）
	 GMSG_COMMU_GUILD_GET_LIST = 0x1B2 (434)，			 
	 服务端->客户端, 包结构
	 Short：		总页数,
	 Short:		当前页码,
	 Short：		本页公会数,
		 * Short：		排名，
		 * String：	公会名字，
		 * String：	会长名字，
		 * Short：		公会等级，
		 * Short：		成员数，
		 * Short：		成员数上限
		 * String:      公会介绍 
		 * Byte：		申请标志		// 0 – 未申请 / 1 – 已申请
	 */
class SCMD1B2 : public Packet
{
public:
	SCMD1B2() {}
	virtual ~SCMD1B2() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_GET_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_total;
	int16 b_page;
	struct SCMD1B2Node
	{
		/**公会排名*/
		int16 a_rank;
		string b_guildName;
		string c_leadName;
		int16 d_emblemLevel;
		/**公会成员数*/
		int16 e_memberNum;
		/**公会成员上限*/
		int16 f_memberLimit;
		/**公会介绍*/
		string g_guildIntr;
		/**申请标志,0未申请,1已申请*/
		int8 h_flag;
	};

	std::list<SCMD1B2Node> e_guildArr;
};


class SCMD1B2Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1B2Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1B2();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_GET_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1B2Handler 
{
public:
	static uint32 Execute(SCMD1B2* pPacket) ;
};

#endif 