		/**
		 *����-���ط����б�
		WMSG_WORLD_DUNGEON_RESP_ROOM_LIST = 0x37C(892),
		�ͻ���<-�����, ���ṹ
		Int��		��������		// 0 �C ����� / ������ʾn�㾫��		
		Byte:		��ҳ��
		Byte:		��ǰҳ��
		short:		������
			Int:      ����ID
			String:   �ӳ�����
			Byte:	�ӳ�ְҵID
			Byte:	�ӳ��ȼ�
			byte:	�������
			byte:	��ǰ����	
*/
#ifndef _SCMD37C_H_
#define _SCMD37C_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD37C : public Packet
{
public:
	SCMD37C()
	{
		a_consume = 0;
		b_totalPage = 0;
		c_curPage = 0;
	}

	struct SCMD37CNode
	{
		int a_roomId;
		std::string b_captainName;
		int8 c_careerId;
		int8 d_lev;
		int8 e_maxNum;
		int8 f_curNum;
	};
	int a_consume;
	int8 b_totalPage;
	int8 c_curPage;
	std::list<SCMD37CNode> d_rooms;

	virtual ~SCMD37C() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_DUNGEON_RESP_ROOM_LIST;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_mapId;
	int8 b_rank;
	int c_silver;
	int d_gold;
	int e_good1;
	int f_good2;
};


class SCMD37CFactory: public MessageFactory
{
public :
	
	virtual ~SCMD37CFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD37C();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_DUNGEON_RESP_ROOM_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD37CHandler 
{
public:
	static uint32 Execute(SCMD37C* pPacket) ;
};

#endif