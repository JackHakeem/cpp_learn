#ifndef _SCMD142_H_
#define _SCMD142_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD142 : public Packet
{
public:
	SCMD142()
	{
		a_currentpoint = 0;
		b_rolehononameid = 0;
	}

	virtual ~SCMD142() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_GET_ACHIVEMENT_LIST_RESP;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}

	struct SCMD142Node1
	{
		int16 a_honorid;
		int8 b_completed;
		SCMD142Node1()
		{
			a_honorid = 0;
			b_completed = 0;
		}
	};
	struct SCMD142Node2
	{
		int16 a_wardpoint;
		SCMD142Node2()
		{
			a_wardpoint = 0;
		}
	};

public:
	int32 a_currentpoint;
	int16 b_rolehononameid;
	std::list<SCMD142Node1> c_idlist;
	std::list<SCMD142Node2> d_pointlist;
};


class SCMD142Factory: public MessageFactory
{
public :
	
	virtual ~SCMD142Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD142();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_GET_ACHIVEMENT_LIST_RESP;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD142Handler 
{
public:
	static uint32 Execute(SCMD142* pPacket) ;
};

#endif