/**
	����ί�ɷ��ذ�(ί�ɽ��)
	WMSG_WORLD_DELEGATE_RESULT = 0x1E3 (483)
	�����->�ͻ���, ���ṹ
	Uint8:		���ί�ɴ���
	Uint16:		��������Ʒԭ��Id
	Uint8:		��������
	Uint8:		������Ϣ��ÿ��λ����һ�����ˣ�0�������ڣ�1�����ڣ�
	Uint8:		��ί�����˵ȼ�����ѡ�е�����(0 ~ 3)
 */
#ifndef _SCMD1E3_H_
#define _SCMD1E3_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD1E3 : public Packet
{
public:
	SCMD1E3() {}
	virtual ~SCMD1E3() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DELEGATE_RESULT;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	int8 a_freeNum;
	int16 a_goodsId;
	int8 b_traderType;
	int8 c_trader;
	int8 d_selected;
};


class SCMD1E3Factory: public MessageFactory
{
public :
	virtual ~SCMD1E3Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD1E3();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_DELEGATE_RESULT;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD1E3Handler 
{
public:
	static uint32 Execute(SCMD1E3* pPacket) ;
};
#endif