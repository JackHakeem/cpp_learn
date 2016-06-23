/**
更新每日免费占星数
 */

#ifndef _SCMD46F_H_
#define _SCMD46F_H_

#include "socket/message/SocketCMDConst.h"
#include "socket/message/MessageFactory.h"


class SCMD46F : public Packet
{
public:

	SCMD46F()
	{
	
		
	}

	virtual ~SCMD46F() {}
	virtual bool	Read();
public :
	virtual int32 	Execute();

	virtual PacketID_t getPacketID() const { return WMSG_ZX_GM_PRO;}
	
	virtual	int32		GetMessageSize( ) const { return 0;}
	
public:
	struct SCMD46FNode
	{
		std::string a_name;
		int32 phyAttack;
		int32 magAttack;
		int32 phydef;
		int32 magdef;
		int32 health;
		float critRating;
		float antiCrit;
		float critHarm;
		float counterRating;
		float antiCounterRating;
		float counterHarmRating;
		float hitRating;
		float dodgeRating;
		int32 startep;
	};
	std::vector<SCMD46FNode> nodes;
};


class SCMD46FFactory: public MessageFactory
{
public :
	
	virtual ~SCMD46FFactory ()  {}

	virtual Packet*		CreateMessage () {return new SCMD46F();}

	virtual PacketID_t	GetPacketID ()const  {return WMSG_ZX_GM_PRO;}

	virtual uint32		GetMessageMaxSize ()const  {return 0;}

};

class SCMD46FHandler 
{
public:
	static uint32 Execute(SCMD46F* pPacket) ;
};

#endif