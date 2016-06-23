#ifndef _SCMD28B_H__
#define _SCMD28B_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	Ӣ�۰�㲥	
	WMSG_WORLD_HERO_BROADCAST = 0x28B 
	�����->�ͻ���, ���ṹ
	Ӣ�۰����飨0~2������0���ǵ�һ�����Դ����ƣ�
	    Uint32	���ID
	    String	��һ�����������
	   
	ע�����鳤���п���С��3��
 */

class SCMD28B : public Packet
{
public:
	SCMD28B() {}
	virtual ~SCMD28B() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_HERO_BROADCAST;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	struct SCMD28BNode
	{
		int32 a_id;
		std::string b_name;
	};
	std::list<SCMD28BNode> heros;
};

class SCMD28BFactory: public MessageFactory
{
public :

	virtual ~SCMD28BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD28B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_HERO_BROADCAST;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD28BHandler 
{
public:
	static uint32 Execute(SCMD28B* pPacket) ;
};
#endif