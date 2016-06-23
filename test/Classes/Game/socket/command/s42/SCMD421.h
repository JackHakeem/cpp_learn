/**
WMSG_WORLD_DAILY_TASK_INFO = 0x411,	
uint8 remainFreeCount
uint8 remainTaskCount
uint8	taskCount
	uint8	taskid
	uint8	quality
	uint8	count
	uint8	finishCount
	uint8	tasktype
	uint32	monstergroup
	uint8	hasAccepted
	
	uint8 awardSize
		uint32	goodsId
		uint32	goodsNum
 */

#ifndef _SCMD421_H_
#define _SCMD421_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD421 : public Packet
{
public:

	struct SCMD421Node2
	{
		uint32 a_goodsId;
		uint32 b_goodsNum;
	};

	struct SCMD421Node
	{
		uint8 a_taskId;
		uint8 b_quality;
		uint8 c_count;
		uint8 d_finishCount;
		uint8 e_taskType;
		uint32 f_monsterGroup;
		uint8 g_hasAccepted;
		std::vector<SCMD421Node2> h_awardList;
	};

	SCMD421()
	{
		a_remainTaskCount = 0;
		b_remainFreeCount = 0;
		c_taskCount = 0;
	}

	virtual ~SCMD421() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DAILY_TASK_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_remainTaskCount;
	int8 b_remainFreeCount;
	int16 c_taskCount;
	std::vector<SCMD421Node> d_nodeList;
};


class SCMD421Factory: public MessageFactory
{
public :
	
	virtual ~SCMD421Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD421();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DAILY_TASK_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD421Handler 
{
public:
	static uint32 Execute(SCMD421* pPacket) ;
};

#endif