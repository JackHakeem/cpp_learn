/**
 *����������� WMSG_SILVERMINE_RANK = 0x367 
	�����->�ͻ���, ���ṹ
����ս�����������
	Uint8	������0-9��
	Uint32	���ID
	String	�������
	Uint32	�ɼ�������
*/
#ifndef _SCMD367_H_
#define _SCMD367_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
#include "SCMD367Node.h"

class SCMD367 : public Packet
{
public:
	SCMD367()
	{

	}

	virtual ~SCMD367() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_RANK;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	std::list<SCMD367Node> a_ranks;
};


class SCMD367Factory: public MessageFactory
{
public :

	virtual ~SCMD367Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD367();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_RANK;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD367Handler 
{
public:
	static uint32 Execute(SCMD367* pPacket) ;
};

#endif