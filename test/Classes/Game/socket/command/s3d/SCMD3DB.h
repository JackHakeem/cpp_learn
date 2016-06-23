#ifndef _SCMD3DB_H_
#define _SCMD3DB_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

struct SCMD3DBNode
{
	int16 a_id;
	int8 b_star;

	SCMD3DBNode()
	{
		a_id = 0;
		b_star = 0;
	}
}; 


class SCMD3DB : public Packet
{
public:
	SCMD3DB() {}
	virtual ~SCMD3DB() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_MAPS_OF_CITY_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:
	int16 a_cityId;
	std::vector<SCMD3DBNode> b_mapsInfo;
	 
	 
};


class SCMD3DBFactory: public MessageFactory
{
public :

	virtual ~SCMD3DBFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD3DB();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_MAPS_OF_CITY_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD3DBHandler 
{
public:
	static uint32 Execute(SCMD3DB* pPacket) ;
};

#endif 