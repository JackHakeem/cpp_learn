/** 
 * @author shenzhiqiang
 * @version 1.1.7.0
 * @description ����˷���-ϴ����Ӧ��
WMSG_EGG_PICK = 0x407
����� ->����, ���ṹ:
Uint8		��Ӧ��
����:0�ɹ�/1�����ռ䲻��/2ϵͳ�ڲ�����
Uint32		��ƷID
Uint32		��Ʒ����

 * @data 2012-3-26 ����11:58:29 
 * 
 */ 
#ifndef _SCMD409_H_
#define _SCMD409_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD409 : public Packet
{
public:
	SCMD409()
	{
	}

	virtual ~SCMD409() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_EGG_WASH;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_type;
	int32 b_goodsId;
	int32 c_num;
};


class SCMD409Factory: public MessageFactory
{
public :
	
	virtual ~SCMD409Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD409();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_EGG_WASH;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD409Handler 
{
public:
	static uint32 Execute(SCMD409* pPacket) ;
};

#endif