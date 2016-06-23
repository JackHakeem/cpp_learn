
/**  
318Node
Push formation list to the client
WMSG_WORLD_FORMATION_INFO = 0x318 (791)
The service side -> client package structure
The number of Uint16 formation
	Uint16 formation ID
	Uint8 formation level
	Uint8 whether to enable
	Uint16 formation in the number of members
		Uint8 formation in the position
		Uint32 mercenary unique ID
* /

/ ** 318Node2
* Uint16 formation, the number of members
	Uint8 formation in the position
	Uint32 mercenary unique ID

 */

#ifndef _SCMD318_H_
#define _SCMD318_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"

class SCMD318 : public Packet
{
public:
	SCMD318() {}
	virtual ~SCMD318() {}


	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_WORLD_FORMATION_INFO;}

	virtual	int32		GetMessageSize( ) const { return 0;}

public:

	uint16 SCMD318Node2Num;   //Formation in the number of members

	struct SCMD318Node2
	{
		uint8 a_sitGrid ;         //Formation in the position
		uint32 b_figureId ;        //The mercenary unique ID
	}; 

	uint16 SCMD318NodeNum;    //Formation number
	struct SCMD318Node
	{

		uint16 a_formationId ;    //Formation ID
		uint8 b_formationLel ;     //Formation Level
		uint8 c_active;                 //Is enabled
		std::list<SCMD318Node2> d_figures ;

	};

	


	std::list<SCMD318Node> a_fomations;
	 
	 
};


class SCMD318Factory: public MessageFactory
{
public :

	virtual ~SCMD318Factory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD318();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_WORLD_FORMATION_INFO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD318Handler 
{
public:
	static uint32 Execute(SCMD318* pPacket) ;
};

#endif 