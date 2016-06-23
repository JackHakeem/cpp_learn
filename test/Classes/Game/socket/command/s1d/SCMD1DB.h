/** 
 * @author shenzhiqiang
 * @version 1.1.4.0
 * @description ����˷��ضһ����
	WMSG_WORLD_DELEGATE_BGET_BLESS_ITEM_RESP					= 0x1DB,
�����->�ͻ���, ���ṹ
Uint16:		�һ���Ʒԭ��Id
Uint8:		�һ����(0��ʧ�ܣ�1���ɹ�)
 * @data 2012-3-12 ����05:54:45 
 * 
 */ 

#ifndef _SCMD1DB_H_
#define _SCMD1DB_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD1DB : public Packet
{
public:
	SCMD1DB() {}
	virtual ~SCMD1DB() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DELEGATE_BGET_BLESS_ITEM_RESP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_id;
	int8 b_type;
};


class SCMD1DBFactory: public MessageFactory
{
public :
	
	virtual ~SCMD1DBFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD1DB();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DELEGATE_BGET_BLESS_ITEM_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD1DBHandler 
{
public:
	static uint32 Execute(SCMD1DB* pPacket) ;
};

#endif 