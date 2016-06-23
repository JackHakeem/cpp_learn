/**
��ս����ս���б���Ϣ
CMSG_WORLD_GROUPINFO = 0x273 
�����->�ͻ���, ���ṹ
Uint16		����ID
Uint32		ս��ID
Int8		�Զ���ս������-1Ϊ�ֶ���ս��
uint32      �ӳ�ID
ս�������Ϣ���飺
Uint8		���λ�ã�0~7��
Uint32		���ID
String		�������
Uint8		��֮ˮ���ȼ�
string		������
*/

#ifndef _SCMD273_H_
#define _SCMD273_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD273 : public Packet
{
public:
	SCMD273() {}
	virtual ~SCMD273() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_GROUPINFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	struct SCMD273Node
	{
		uint8 a_sitNum;
		int32 b_playerId;
		uint16 c_mercId;  
		std::string d_playerName;
		uint8 e_cryLev;
		std::string f_guildName;
	};

	uint16 a_fbId;
	uint16 b_teamId;
	int8 c_auto;
	int32 d_captainId;
	std::list<SCMD273Node> e_members;
};


class SCMD273Factory: public MessageFactory
{
public :

	virtual ~SCMD273Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD273();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_GROUPINFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD273Handler 
{
public:
	static uint32 Execute(SCMD273* pPacket) ;
};

#endif