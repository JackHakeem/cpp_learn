#ifndef _SCMD3B3_H_
#define _SCMD3B3_H_

/**
	����˷��ش򿪻����������Ϣ
	WMSG_WORLD_ENTER_TOWER_GATE	= 0X3B3,			
	�����->�ͻ���, ���ṹ
	Uint8		��ѽ���ʣ�����
	Uint8		���ս������������Ѵ����⣩
	Uint8		�ϴδ���¥�㣨��ʼΪ0�㣩
	Uint8		��ʷ��ߴ���¥��
	Uint8		��������������0����100+��
	Uint16		��������������������ս����Ҹ�����������
		String	����
		Uint32 	ʱ��
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"

class SCMD3B3 : public Packet
{
public:
	SCMD3B3()
	{
		a_numFree = 0; 
		b_numPay = 0;
		c_lastFloor = 0;
		d_maxFloor = 0;
		e_myRank = 0;
	}
	~SCMD3B3()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_ENTER_TOWER_GATE;}

public:
	int8 a_numFree; 
	int8 b_numPay;
	int8 c_lastFloor;
	int8 d_maxFloor;
	int8 e_myRank;

	struct SCMD3B3Node
	{
		string a_name;
		int b_time;
		SCMD3B3Node()
		{
			a_name = "";
			b_time = 0;
		}
	};
	std::list<SCMD3B3Node> f_topRank;
};


class SCMD3B3Factory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3B3();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_ENTER_TOWER_GATE;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3B3Handler 
{
public:
	static uint32 Execute(SCMD3B3 *pPacket) ;
};

#endif
