#ifndef _SCMD3CB_H_
#define _SCMD3CB_H_

/**
	����˷��������������λ��Ϣ
	WMSG_WORLD_REQ_RANKLIST_BY_PAGE	= 0X3CB			
	�����->�ͻ���, ���ṹ
	Uint16		�ڼ�ҳ��1-10,���������Χ�򷵻ص�һҳ���ݣ�
	Uint8		�����ʷ��ߴ���¥��
	Uint8		��ҵ�ǰ����¥��
	Uint8		�������(0Ϊ100+��)
	Uint16		ÿҳ������ÿҳ10�ˣ�
		Uint8	����
		Uint8	¥��
		String	��ɫ��/���������
		String	��������������ռ����Ϊ�գ�
		Uint8	��֮ˮ���ȼ���������ռ������ϵȼ���
		Uint32	����ʱ��(������ռ����Ϊ��)
 */

#include "socket/network/Packet.h"
#include "socket/message/MessageFactory.h"
#include "socket/message/SocketCMDConst.h"
#include "BaseType.h"

class SCMD3CB : public Packet
{
public:
	SCMD3CB()
	{
		a_page = 0;
		b_maxFloor = 0;
		c_curFloor = 0;
		c_curFloor = 0;
	}
	~SCMD3CB()
	{
	}

	virtual int32 Execute();

	virtual bool Read();

	virtual PacketID_t getPacketID()const { return WMSG_WORLD_REQ_RANKLIST_BY_PAGE;}

public:
	int16 a_page;
	int8 b_maxFloor;
	int8 c_curFloor;
	int8 d_myRank;
	int8 d_nRestCount;
	int8 d_oLastRank;

	struct SCMD3CBNode
	{
		int8 a_rank;
		int8 b_floor;
		string c_name;
		string d_guild;
		int8 e_lev;
		int f_date;
		SCMD3CBNode()
		{
			a_rank = 0;
			b_floor = 0;
			c_name = "";
			d_guild = "";
			e_lev = 0;
			f_date = 0;
		}
	};
	std::list<SCMD3CBNode> e_rankList;
};


class SCMD3CBFactory : public MessageFactory
{
	virtual Packet* CreateMessage() {return new SCMD3CB();}

	virtual PacketID_t GetPacketID()const {return WMSG_WORLD_REQ_RANKLIST_BY_PAGE;}

	virtual uint32 GetMessageMaxSize()const {return 0;}

};


class SCMD3CBHandler 
{
public:
	static uint32 Execute(SCMD3CB *pPacket) ;
};

#endif
