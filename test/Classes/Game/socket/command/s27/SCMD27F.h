/**
ս�������Ϣ
WMSG_WORLD_GROUPFIGHT_END = 0x27F 	
�����->�ͻ���, ���ṹ
Uint16		����ID
Uint16		ս��ID
Uint8		ս�������0��ʤ����1��ʧ�ܣ�
������Ϣ��
Uint32		��������
Uint32		���ҽ���
Uint32		װ��ID
*/

#ifndef _SCMD27F_H_
#define _SCMD27F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD27F : public Packet
{
public:
	SCMD27F() {}
	virtual ~SCMD27F() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPFIGHT_END;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 a_fbId;
	uint16 b_teamId;
	uint8 c_result;
	int32 d_prac;
	int32 e_silver;
	int32 f_goodId;
};


class SCMD27FFactory: public MessageFactory
{
public :

	virtual ~SCMD27FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD27F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPFIGHT_END;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD27FHandler 
{
public:
	static uint32 Execute(SCMD27F* pPacket) ;
};

#endif