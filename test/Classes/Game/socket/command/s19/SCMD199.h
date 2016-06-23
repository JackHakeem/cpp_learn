#ifndef _SCMD199_H__
#define _SCMD199_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 * GMSG_COMMU_ERR_CHAT = 0x199(409),			//������������߷�����Ϣ
 * �����<-�ͻ���, ���ṹ
 * byte�� 		������
 */
class SCMD199 : public Packet
{
public:
	SCMD199() {}
	virtual ~SCMD199() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_ERR_CHAT;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	int8 a_err;

};


class SCMD199Factory: public MessageFactory
{
public :

	virtual ~SCMD199Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD199();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_ERR_CHAT;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD199Handler 
{
public:
	static uint32 Execute(SCMD199* pPacket) ;
};
#endif