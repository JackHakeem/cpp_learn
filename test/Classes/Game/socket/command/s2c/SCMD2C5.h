#ifndef  _SCMD2C5_H__
#define  _SCMD2C5_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *������֪ͨ
WMSG_WORLD_TRADE_ATTACKED_NOTIFY= 0x2C5 (709)
�ͻ���->�����, ���ṹ
Uint32		�������ID
String		�����������
Uint8		���̽����0��ʧ�ܣ�1���ɹ���
short		��ʧ��Ʒ����
uint64		����ս��id	
 
 */ 

class SCMD2C5 : public Packet
{
public:
	SCMD2C5() {}
	virtual ~SCMD2C5() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_ATTACKED_NOTIFY;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	uint a_id;
	string b_name;
	int8 c_result;
	int16 d_lostNum;
	uint e_reportId_1;
	uint f_reportId_2;
};


class SCMD2C5Factory: public MessageFactory
{
public :

	virtual ~SCMD2C5Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2C5();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_ATTACKED_NOTIFY;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2C5Handler 
{
public:
	static uint32 Execute(SCMD2C5* pPacket) ;
};
#endif