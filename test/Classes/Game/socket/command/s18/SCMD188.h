#ifndef  _SCMD188_H__
#define  _SCMD188_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/** 
WMSG_UPDATE_VIGOUR = 0x188 (392)
*/ 

class SCMD188 : public Packet
{
public:
	SCMD188() {}
	virtual ~SCMD188() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_UPDATE_VIGOUR;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
    int a_presentEnergy;
	int b_differance;
	int c_remainVigourBuffCount;
	int d_maxVigourBuffCount;
};


class SCMD188Factory: public MessageFactory
{
public :

	virtual ~SCMD188Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD188();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_UPDATE_VIGOUR;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD188Handler 
{
public:
	static uint32 Execute(SCMD188* pPacket) ;
};
#endif