/**
 * ����ս����ʹ�ý��	
WMSG_SILVERMINE_INSPIRE_RES = 0x369 
�����->�ͻ���, ���ṹ
Uint8		��������
Uint8		ִ�н��
Uint32		��ǰ��������ӳɰٷֱ�
Uint32		��ǰ���ع���ӳɰٷֱ�
 */
#ifndef _SCMD369_H_
#define _SCMD369_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD369 : public Packet
{
public:
	SCMD369()
	{

	}

	virtual ~SCMD369() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_INSPIRE_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int8 b_ret;
	uint32 c_attPlus;
	uint32 d_defPlus;
};


class SCMD369Factory: public MessageFactory
{
public :

	virtual ~SCMD369Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD369();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_INSPIRE_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD369Handler 
{
public:
	static uint32 Execute(SCMD369* pPacket) ;
};

#endif