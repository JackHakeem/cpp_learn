/**
 *����˷��ع�����
WMSG_WORLD_ REQ_IDENTIFY_INFO = 0x2A3 	(675)
�����->�ͻ���, ���ṹ
Uint8		������
Uint16		����ļٸ������������ͣ�
    Uint32 	ٸ��ΨһID
    Uint16   ٸ��ģ��ID
         Uint8�������ͣ������Ը�������Ϊ�����С��ÿ��ٸ�����и�����Ŀ���������ԣ�
         Uint8�����ȼ� 
 */
#ifndef _SCMD2A3_H_
#define _SCMD2A3_H_

#include "../../network/Packet.h"
#include "../../message/MessageFactory.h"
#include "../../message/SocketCMDConst.h"

class SCMD2A3 : public Packet
{
public:
	SCMD2A3() {}
	virtual ~SCMD2A3() {}


	virtual bool Read();
public :
	virtual int32 Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_REQ_IDENTIFY_INFO;}

	virtual	int32 GetMessageSize( ) const { return 0;}

public:
	struct SCMD2A3Node2 
	{
		uint8 a_statsType;
		uint8 b_statsLv;
	};

	struct SCMD2A3Node1 
	{
		int32 a_mercId;
		uint16 b_typeId;
		std::list<SCMD2A3Node2> c_statArr;
	};

	uint8 a_gridNum;
	std::list<SCMD2A3Node1> b_MercArr;
};


class SCMD2A3Factory: public MessageFactory
{
public :
	virtual ~SCMD2A3Factory ()  {}

	virtual Packet* CreateMessage () {return new SCMD2A3();}

	virtual PacketID_t GetPacketID ()const  {return WMSG_WORLD_REQ_IDENTIFY_INFO;}

	virtual uint32 GetMessageMaxSize ()const  {return 0;}

};

class SCMD2A3Handler 
{
public:
	static uint32 Execute(SCMD2A3* pPacket) ;
};
#endif