#ifndef _SCMD1C3_H_
#define _SCMD1C3_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
	/**查看成员信息
	 GMSG_COMMU_GUILD_MEMBER_INFO = 0x1C3 (451)，			
	 服务端->客户端, 包结构
	 Short:		总页数
	 Short:		当前页码		// 如果是0，代表这是精确查找的结果，否则是模糊
	 Short:		本页人数,
		 byte:		职务,
		 Int:		玩家ID,
		 String：	名字,
		 short：		等级,
		 Int：		称号,
		 String：	状态			// 在线显示线路，离线显示时间
	 
	 */
class SCMD1C3 : public Packet
{
public:
	SCMD1C3() {}
	virtual ~SCMD1C3() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_MEMBER_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_total;
	int16 b_page;
	struct SCMD1C3Node
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
	};

	std::list<SCMD1C3Node> c_nodeArr;
};


class SCMD1C3Factory: public MessageFactory
{
public :
	
	virtual ~SCMD1C3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1C3();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_MEMBER_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1C3Handler 
{
public:
	static uint32 Execute(SCMD1C3* pPacket) ;
};

#endif 