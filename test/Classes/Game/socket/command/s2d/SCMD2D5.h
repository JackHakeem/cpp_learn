/**
*����˷���ħ����Ϣ
WMSG_WORLD_REQ_ENCHANT_INFO = 0x2D5 ��725��
�����->�ͻ���, ���ṹ
Uint32��		���ӵ�ħʯ�����������������������Ǹ�����
Uint32 		��ǰӵ�еľ�����
 */

#ifndef _SCMD2D5_H_
#define _SCMD2D5_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD2D5 : public Packet
{
public:
	SCMD2D5() {}
	virtual ~SCMD2D5() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_REQ_ENCHANT_INFO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int a_add;
	int b_num;
};


class SCMD2D5Factory: public MessageFactory
{
public :
	
	virtual ~SCMD2D5Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2D5();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_REQ_ENCHANT_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2D5Handler 
{
public:
	static uint32 Execute(SCMD2D5* pPacket) ;
};

#endif