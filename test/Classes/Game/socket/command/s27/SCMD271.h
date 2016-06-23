/**
��ս����ս���б���Ϣ
CMSG_WORLD_GROUPLIST = 0x271 
�����->�ͻ���, ���ṹ
Uint16		��ս����ID
ս����Ϣ���飺
Uint16		����ID
String		�ӳ�����
Uint8		��������(0:�����ƣ�1������)
Uint8		��ǰ����
uint        �ӳ�����ID 
String      �ӳ�������
Int8		�Զ���ս������-1Ϊ�ֶ���ս��
*/

#ifndef _SCMD271_H_
#define _SCMD271_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD271 : public Packet
{
public:
	SCMD271() {}
	virtual ~SCMD271() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPLIST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD271Node
	{
		uint16 a_teamId;
		std::string b_captain;
		uint8 c_type;
		uint8 d_currNum;
		uint32 e_guildId;
		std::string f_guildName;
		int8 g_auto;
	};

	uint16 a_fbId;
	std::list<SCMD271Node> b_teams;
};


class SCMD271Factory: public MessageFactory
{
public :

	virtual ~SCMD271Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD271();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPLIST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD271Handler 
{
public:
	static uint32 Execute(SCMD271* pPacket) ;
};

#endif