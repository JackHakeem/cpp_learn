/**
 * �����������ս��ͼ���	
WMSG_SILVERMINE_ENTER_RES = 0x2E3 
�����->�ͻ���, ���ṹ
int8	������
    0������ɹ���������ӪID��0
    1������ɹ���������ӪID��1
    2������ɹ���������ӪID��2
    -1������ʧ�ܣ�ˮ���ȼ�δ�ﵽ
    -2������ʧ�ܣ���ǰ��������սʱ����
    -3������ʧ�ܣ�����ս������
    -4������ʧ�ܣ�ϵͳ����
 */

#ifndef _SCMD2E3_H_
#define _SCMD2E3_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2E3 : public Packet
{
public:
	SCMD2E3() {}
	virtual ~SCMD2E3() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_ENTER_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int8 a_ret;
};


class SCMD2E3Factory: public MessageFactory
{
public :

	virtual ~SCMD2E3Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2E3();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_ENTER_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2E3Handler 
{
public:
	static uint32 Execute(SCMD2E3* pPacket) ;
};

#endif