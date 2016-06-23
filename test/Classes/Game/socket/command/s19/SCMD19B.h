#ifndef _SCMD19B_H__
#define _SCMD19B_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	 ϵͳ����
	WMSG_COMMU_SYS_MSG = 0x19B(411),			//ϵͳ����
	�����<-�ͻ���, ���ṹ
	Byte��		���Ŵ���
	Byte:		������ʽ		// ����λ����ʾ����ͣ�����λ��1 = ��Ļ�Ϸ����	2 = �����	 4 = ����ʽ	
	String��	�������� 
 */

class SCMD19B : public Packet
{
public:
	SCMD19B():a_times(0),b_type(0),c_content("") {}
	virtual ~SCMD19B() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_COMMU_SYS_MSG;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	uint8 a_times;
	uint8 b_type;
	std::string c_content;

};


class SCMD19BFactory: public MessageFactory
{
public :

	virtual ~SCMD19BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD19B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_COMMU_SYS_MSG;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD19BHandler 
{
public:
	static uint32 Execute(SCMD19B* pPacket) ;
};
#endif