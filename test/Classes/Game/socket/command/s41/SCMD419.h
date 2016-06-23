#ifndef _SCMD419_H_
#define _SCMD419_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD419 : public Packet
{
public:
	SCMD419() {}
	virtual ~SCMD419() {}


	virtual bool	Read();
public :
	virtual int32 	Execute(); 

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_GUA_REWARD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD419Node
	{
		int _goodsId;
		int _goodsNum;
	};

	struct SCMD419Node2
	{
		int _id;
		int _plusExp;
		int8 _isUpgrade;
	};

	int8 _battleIndex;
	uint32 _monsterGroupId;
	std::list<SCMD419Node> _rewards;
	std::list<SCMD419Node2> _exps;
};


class SCMD419Factory: public MessageFactory
{
public :

	virtual ~SCMD419Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD419();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BATTLE_GUA_REWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD419Handler 
{
public:
	static uint32 Execute(SCMD419* pPacket) ;
};

#endif