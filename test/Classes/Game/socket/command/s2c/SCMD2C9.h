/**
	世界BOSS活动BOSS信息
	WMSG_WORLDBOSS_BOSSINFO = 0X2C9			
	服务端->客户端, 包结构
	int32			当前BOSS血量（-1：表示在前20分钟内显示？号，0：表示被杀，大于零表示当前血量）
	int32			最大血量
	当前活动伤害排名数组（前十名）
	Uint8		名次（0~9）		
	string		玩家名字
	int32		伤害量
	uint8		伤害比（0～100）
*/

#ifndef _SCMD2C9_H_
#define _SCMD2C9_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2C9 : public Packet
{
public:
	SCMD2C9() {}
	virtual ~SCMD2C9() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLDBOSS_BOSSINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD2C9Node 
	{
		uint8 a_rank;		// 名次（0~9）	
		std::string b_name;	// 玩家名字
		uint32 c_damage;	// 伤害量
		//public var d_damagePercent:uint;	// 伤害比（0～100）
		SCMD2C9Node()
		{
			a_rank = 0;
			b_name = "";
			c_damage = 0;
		}
	};

	uint32 a_currentHP;		// 当前BOSS血量（-1：表示在前20分钟内显示？号，0：表示被杀，大于零表示当前血量）
	uint32 b_maxHP;			// 最大血量
	uint32 c_totalDamage_low;	// 总伤害量-低位
	uint32 c_totalDamage_high;// 总伤害量-高位
	std::list<SCMD2C9Node> d_damageRankList;	// 当前活动伤害排名数组（前十名）
};


class SCMD2C9Factory: public MessageFactory
{
public :

	virtual ~SCMD2C9Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2C9();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLDBOSS_BOSSINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2C9Handler 
{
public:
	static uint32 Execute(SCMD2C9* pPacket) ;
};

#endif