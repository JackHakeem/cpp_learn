#ifndef _SCMD1BF_H_
#define _SCMD1BF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

/**
查看公会信息
GMSG_COMMU_GUILD_INFO = 0x1BF (447)，			 
服务端->客户端, 包结构
String:		公会名字，
String：	    会长名字,
Short：		军徽等级，
Short：		公会等级，
Short：		公会排名，
Short：		成员数，
Short：		成员上限，
String：	创建时间，
String：	QQ群，
String：	公告
byte:   状态 1为解散中
*/
class SCMD1BF : public Packet
{
public:
	SCMD1BF() {}
	virtual ~SCMD1BF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_GUILD_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	/**公会名字*/
	string a_guildName;
	string b_leaderName;
	/**军徽等级*/
	int16 c_emblemLevel;
	int16 d_guildLevel;
	int16 e_guildRank;
	int16 f_memberNum;
	int16 g_memberLimit;
	string h_createDate;
	string i_qqGN;
	string j_notice;
	string l_intro;
	int8 m_state;
	int n_abortTime;
};


class SCMD1BFFactory: public MessageFactory
{
public :

	virtual ~SCMD1BFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1BF();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_GUILD_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1BFHandler 
{
public:
	static uint32 Execute(SCMD1BF* pPacket) ;
};

#endif 