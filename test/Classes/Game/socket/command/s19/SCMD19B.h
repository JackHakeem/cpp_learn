#ifndef _SCMD19B_H__
#define _SCMD19B_H__

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"
/**
	 系统公告
	WMSG_COMMU_SYS_MSG = 0x19B(411),			//系统公告
	服务端<-客户端, 包结构
	Byte：		播放次数
	Byte:		播放形式		// 高四位：表示活动类型；低四位：1 = 屏幕上方横幅	2 = 聊天框	 4 = 弹出式	
	String：	公告内容 
 */

class SCMD19B : public Packet
{
public:
	SCMD19B():a_times(0),b_type(0),c_content("") {}
	virtual ~SCMD19B() {}

	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_COMMU_SYS_MSG;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:		 
	uint8 a_times;
	uint8 b_type;
	std::string c_content;

};


class SCMD19BFactory: public MessageFactory
{
public :

	virtual ~SCMD19BFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD19B();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_COMMU_SYS_MSG;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD19BHandler 
{
public:
	static uint32 Execute(SCMD19B* pPacket) ;
};
#endif