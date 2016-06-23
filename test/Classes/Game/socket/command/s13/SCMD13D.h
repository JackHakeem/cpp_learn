#ifndef _SCMD13D_H_
#define _SCMD13D_H_
#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD13D : public Packet
{
public:
	SCMD13D() {}
	virtual ~SCMD13D() {}


	virtual bool	Read();
public :
	virtual int32 	Execute(); 

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_BATTLE_REWARD;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD13DNode
	{
		int _goodsId;
		int _goodsNum;
	};

	struct SCMD13DNode2
	{
		int _id;
		int _plusExp;
		int8 _isUpgrade;
	};

	uint32 _sceneId;
	std::list<SCMD13DNode> _rewards;
	std::list<SCMD13DNode2> _exps;
};


class SCMD13DFactory: public MessageFactory
{
public :

	virtual ~SCMD13DFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD13D();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_BATTLE_REWARD;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD13DHandler 
{
public:
	static uint32 Execute(SCMD13D* pPacket) ;
};

#endif