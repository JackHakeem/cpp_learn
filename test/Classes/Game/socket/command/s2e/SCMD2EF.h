/**
 * ����ս����ʹ�ý��	
WMSG_SILVERMINE_TOKEN_RES = 0x2EF 
�����->�ͻ���, ���ṹ
	Uint8		����ID
	Uint32		Ŀ������ID
	Uint8		����ִ�н����0���ɹ������㣺ʧ�ܣ�
	Uint32		���ز�����ֻ�Բ��������ã�����Ŀ��������������
 */
#ifndef _SCMD2EF_H_
#define _SCMD2EF_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD2EF : public Packet
{
public:
	SCMD2EF() {}
	virtual ~SCMD2EF() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_TOKEN_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	uint32 b_mineID;
	int8 c_ret;
	uint32 d_param;
};


class SCMD2EFFactory: public MessageFactory
{
public :

	virtual ~SCMD2EFFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2EF();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_TOKEN_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2EFHandler 
{
public:
	static uint32 Execute(SCMD2EF* pPacket) ;
};

#endif