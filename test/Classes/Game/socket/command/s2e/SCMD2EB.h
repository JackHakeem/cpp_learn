/**
 * ����ɼ����	
	WMSG_SILVERMINE_DIG_RES = 0x2EB 
	�����->�ͻ���, ���ṹ
	int32		�ɼ���������ڵ����㣺�ɼ�����������С���㣺�ɼ�ʧ�ܴ����룩
	Uint32		�ɼ�CD
	Uint8		�Ƿ�ɼ�CD�У�0����1���ǣ�
 */
#ifndef _SCMD2EB_H_
#define _SCMD2EB_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD2EB : public Packet
{
public:
	SCMD2EB() {}
	virtual ~SCMD2EB() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_SILVERMINE_DIG_RES;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	int32 a_result;
	uint32 b_digCD;
	int8 c_inCD;
	int8 d_ENCHANT_ITEM_ID;
	int8 e_enchantNum;
};


class SCMD2EBFactory: public MessageFactory
{
public :

	virtual ~SCMD2EBFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2EB();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_SILVERMINE_DIG_RES;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2EBHandler 
{
public:
	static uint32 Execute(SCMD2EB* pPacket) ;
};

#endif