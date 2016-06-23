#ifndef  _SCMD2B1_H__
#define  _SCMD2B1_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
 *���������¼��б�
WMSG_WORLD_TRADE_EVENT_LIST = 0x2B1 (689)
�����->�ͻ���, ���ṹ
byte		һ���¼��Ƿ��ѷ���(0δ����, 1�ѷ���)
byte		һ���¼���ƷId1(û��Ϊ0)
byte		һ���¼���ƷId2(û��Ϊ0)
string		һ���¼�������������(û��Ϊ���ַ���)
byte		�����¼��Ƿ��ѷ���(0δ����, 1�ѷ���)
byte		�����¼���ƷId1(û��Ϊ0)
byte		�����¼���ƷId2(û��Ϊ0)
byte		�����¼���ƷId3(û��Ϊ0)
string		�����¼�������������(û��Ϊ���ַ���)
byte		�����¼��Ƿ��ѷ���(0δ����, 1�ѷ���)
byte		�����¼���ƷId1(û��Ϊ0)
byte		�����¼���ƷId2(û��Ϊ0)
byte		�����¼���ƷId3(û��Ϊ0)
byte		�����¼���ƷId4(û��Ϊ0)
string		�����¼�������������(û��Ϊ���ַ���)
 
 */
class SCMD2B1 : public Packet
{
public:
	SCMD2B1()
	{
		d_event1Name = "";
		i_event2Name = "";
		o_event3Name = "";
	}
	virtual ~SCMD2B1() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_TRADE_EVENT_LIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int8 a_event1isFound;
	int8 b_event1Item1;
	int8 c_event1Item2;
	string d_event1Name;
	int8 e_event2isFound;
	int8 f_event2Item1;
	int8 g_event2Item2;
	int8 h_event2Item3;
	string i_event2Name;
	int8 j_event3isFound;
	int8 k_event3Item1;
	int8 l_event3Item2;
	int8 m_event3Item3;
	int8 n_event3Item4;
	string o_event3Name;	
};


class SCMD2B1Factory: public MessageFactory
{
public :

	virtual ~SCMD2B1Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD2B1();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_TRADE_EVENT_LIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD2B1Handler 
{
public:
	static uint32 Execute(SCMD2B1* pPacket) ;
};
#endif