/**
ռ��ʦ����״̬����
 */

#ifndef _SCMD462_H_
#define _SCMD462_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD462 : public Packet
{
public:

	SCMD462()
	{
		a_ZXerState = 0;
	}

	virtual ~SCMD462() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ZX_ZXER_UPDATE;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int32 a_ZXerState;//��λ 
	/*���ӣ� a_ZXerState = 13
	����״̬   0  1  1  0  1  ==��01101 = a_ZXerState = 13
	ռ��ʦID   4  3  2  1  0  
	*/
};


class SCMD462Factory: public MessageFactory
{
public :
	
	virtual ~SCMD462Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD462();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ZX_ZXER_UPDATE;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD462Handler 
{
public:
	static uint32 Execute(SCMD462* pPacket) ;
};

#endif