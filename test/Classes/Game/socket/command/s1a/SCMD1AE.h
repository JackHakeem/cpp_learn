/**
	 *Gate��Client������ȡ������Ʒ���
	 GMSG_COMMU_MAIL_REQUEST_ATTAC_RESP		= 0x1AE (430)		
	 Gate<->Client, ���ṹ
	 Int	�ʼ�ID
	 Int8	��ȡ���(0ʧ�ܣ�1�ɹ�)
	 */

#ifndef _SCMD1AE_H_
#define _SCMD1AE_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1AE : public Packet
{
public:
	SCMD1AE() {}
	virtual ~SCMD1AE() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return GMSG_COMMU_MAIL_REQUEST_ATTAC_RESP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint32 a_mailId;
	uint8 b_result;
};


class SCMD1AEFactory: public MessageFactory
{
public :
	
	virtual ~SCMD1AEFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1AE();}

	virtual PacketID_t	GetPacketID ()const  {return GMSG_COMMU_MAIL_REQUEST_ATTAC_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1AEHandler 
{
public:
	static uint32 Execute(SCMD1AE* pPacket) ;
};

#endif 