#ifndef _SCMD41A_H_
#define _SCMD41A_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD41A : public Packet
{
public:
	SCMD41A() {}
	virtual ~SCMD41A() {}


	virtual bool	Read();
public :
	virtual int32 	Execute(); 

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_TWRGUA_REWARD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD41ANode
	{
		int _goodsId;
		int _goodsNum;
	};

	struct SCMD41ANode2
	{
		int _id;
		int _plusExp;
		int8 _isUpgrade;
	};

	int8 _battleIndex;
	uint32 _monsterGroupId;
	std::list<SCMD41ANode> _rewards;
	std::list<SCMD41ANode2> _exps;
};


class SCMD41AFactory: public MessageFactory
{
public :

	virtual ~SCMD41AFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD41A();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BATTLE_TWRGUA_REWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD41AHandler 
{
public:
	static uint32 Execute(SCMD41A* pPacket) ;
};

#endif