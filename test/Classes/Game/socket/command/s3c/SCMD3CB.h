#ifndef _SCMD3CB_H_
#define _SCMD3CB_H_

/**
	服务端返回请求幻龙塔排位信息
	WMSG_WORLD_REQ_RANKLIST_BY_PAGE	= 0X3CB			
	服务端->客户端, 包结构
	Uint16		第几页（1-10,如果超过范围则返回第一页数据）
	Uint8		玩家历史最高闯塔楼层
	Uint8		玩家当前所在楼层
	Uint8		玩家排名(0为100+名)
	Uint16		每页人数（每页10人）
		Uint8	排名
		Uint8	楼层
		String	角色名/怪物组合名
		String	公会名（若怪物占领则为空）
		Uint8	命之水晶等级（若怪物占领则组合等级）
		Uint32	留名时间(若怪物占领则为０)
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"

class SCMD3CB : public Packet
{
public:
	SCMD3CB()
	{
		a_page = 0;
		b_maxFloor = 0;
		c_curFloor = 0;
		c_curFloor = 0;
	}
	~SCMD3CB()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_REQ_RANKLIST_BY_PAGE;}

public:
	int16 a_page;
	int8 b_maxFloor;
	int8 c_curFloor;
	int8 d_myRank;
	int8 d_nRestCount;
	int8 d_oLastRank;

	struct SCMD3CBNode
	{
		int8 a_rank;
		int8 b_floor;
		string c_name;
		string d_guild;
		int8 e_lev;
		int f_date;
		SCMD3CBNode()
		{
			a_rank = 0;
			b_floor = 0;
			c_name = "";
			d_guild = "";
			e_lev = 0;
			f_date = 0;
		}
	};
	std::list<SCMD3CBNode> e_rankList;
};


class SCMD3CBFactory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3CB();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_REQ_RANKLIST_BY_PAGE;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3CBHandler 
{
public:
	static uint32 Execute(SCMD3CB *pPacket) ;
};

#endif
