/**
	 * 
	 * ��¼������Ϣ���ذ�
	 WMSG_WORLD_ACTIVEDAY_AWARD_INFO_RESP = 0x1ED (493)
	 �����->�ͻ���, ���ṹ
	 Int16	��ҵ�½���
	 Int16	��ҵ�ǰ�ǵڼ����¼
	 Short	��Ʒ����
	 	Int16	��ƷID
		Int32	��Ʒ����
	 * 
	 */	

#ifndef _SCMD1ED_H_
#define _SCMD1ED_H_
#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD1ED : public Packet
{
public:
	SCMD1ED():a_presentValue(0),b_addValue(0)
	{}
	virtual ~SCMD1ED() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_ACTIVEDAY_AWARD_INFO_RESP;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	struct SCMD1EDNode
	{
		uint16 a_goodsId;
		int32 b_goodsNum;
		SCMD1EDNode()
		{
			a_goodsId = 0;
			b_goodsNum = 0;
		}
	};
	uint16 a_presentValue;
	uint16 b_addValue;
	std::vector<SCMD1EDNode> c_goodsArray;
};


class SCMD1EDFactory: public MessageFactory
{
public :
	virtual ~SCMD1EDFactory ()  {}

	virtual Packet* CreateMessage () {return new SCMD1ED();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_ACTIVEDAY_AWARD_INFO_RESP;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD1EDHandler 
{
public:
	static uint32 Execute(SCMD1ED* pPacket) ;
};
#endif