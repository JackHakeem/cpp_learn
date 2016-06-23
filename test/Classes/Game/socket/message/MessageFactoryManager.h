#ifndef _MESSAGEFACTORYMANAGER_H_
#define _MESSAGEFACTORYMANAGER_H_

#include "BaseType.h"
#include "MessageFactory.h"


class MessageFactoryManager 
{
public :
	
	MessageFactoryManager( ) ;
	
	~MessageFactoryManager( ) ;

private :
	void AddFactory( MessageFactory* pFactory ) ;
	
public :
	//External call common interface

	//Initial interface
	bool Init() ;
	//According to the news from the memory type distribution news entity data (allow multithreading and call)
	Packet* CreateMessage( PacketID_t messageID ) ;
	//According to news type corresponding news has the largest size (allow multithreading and call)
	uint32 GetMessageMaxSize( PacketID_t messageID ) ;
	//Delete news entity (allow multithreading and call)
	void RemoveMessage( Packet* pMessage ) ;
	

private :
	
	MessageFactory **	m_Factories ;
	
	uint16				m_Size ;//SocketCMDConst 


public :
	//uint32*				m_pPacketAllocCount ;

};

extern MessageFactoryManager* g_pMessageFactoryManager ;







#endif
